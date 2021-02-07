#ifndef ASCII_IMAGE_HPP
#define ASCII_IMAGE_HPP

#include <vector>
#include "../utils/Utils.hpp"
#include "../utils/Consts.hpp"

/**
 * @brief Abstract base class for all supported image formats.
 *
 * Holds all image data without compression.\n
 * Operates with image in common way, such as: convert to ASCII, add effect etc.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class Image {
protected:
    const std::string path; /**< Absolute path to image file. */
    /**
     * Pixels created from color components values, which were read from image file.
     * @note Has #height * #width size.
     */
    std::vector<std::vector<Pixel>> rawData;
    /**
     * ASCII data converted from #rawData.
     * @note Has #height * #width size.
     */
    std::vector<std::string> rawAsciiData;
    /**
     * Scaled #rawAsciiData used for ASCII art representation.
     * @note Has ASCII art size based on terminal window size (more at #computeArtSize() and #getAsciiArt()).
     */
    mutable std::vector<std::string> resizedAsciiData;
    size_t height; /**< Height of image (_in pixels_). */
    size_t width; /**< Width of image (_in pixels_). */
    bool isContrasted; /**< If _contrast_ effect is applied. */
    bool isNegatived; /**< If _negative_ effect is applied. */
    bool isSharpened; /**< If _sharpen_ effect is applied. */

    /**
     * Calculates _grayscale_ value from Pixel.
     * @note Algorithm for grayscale conversion is referenced from:
     * https://en.wikipedia.org/wiki/Grayscale#Colorimetric_(perceptual_luminance-preserving)_conversion_to_grayscale
     *
     * @param pixel Pixel to convert.
     * @return Grayscale value.
     */
    static unsigned char rgbToGray(const Pixel &pixel);

    /**
     * Applies _contrast_ effect on given Pixel.
     * @note Contrast algorithm is referenced from:
     * https://en.wikipedia.org/wiki/Contrast_(vision) and
     * https://math.stackexchange.com/questions/906240/algorithms-to-increase-or-decrease-the-contrast-of-an-image
     *
     * @param[in] pixel Pixel.
     * @param[out] pixel Pixel with _contrast_ effect.
     * @param level Contrast level from `0` to `255`. Default value is AsciiConsts::DEFAULT_CONTRAST_LEVEL.
     */
    static void applyContrast(Pixel &pixel, double level = AsciiConsts::DEFAULT_CONTRAST_LEVEL);

    /**
     * Applies _negative_ effect on given Pixel.
     *
     * @param[in] pixel Pixel.
     * @param[out] pixel Pixel with _negative_ effect.
     */
    static void applyNegative(Pixel &pixel);

    /**
     * Applies _sharpen_ effect on raw data.
     * @note Sharpen effect algorithm is referenced from:
     * https://setosa.io/ev/image-kernels/
     *
     * @param src Image data.
     * @return Image data with _sharpen_ effect.
     */
    static std::vector<std::vector<Pixel>> applySharpen(const std::vector<std::vector<Pixel>> &src);
public:
    /**
     * Constructor.\n
     * Initializes image by setting its #path.
     * @note Sets #height and #width to `0` and all effect flags (#isContrasted, #isNegatived, #isConvoluted) to `false`.
     *
     * @param imgPath _Absolute_ path to image file.
     */
    explicit Image(std::string imgPath);

    ///@attention Copy constructor is forbidden.
    Image(const Image &) = delete;

    ///@attention Copy assignment operator is forbidden.
    Image &operator=(const Image &) = delete;

    ///@attention Move constructor is forbidden.
    Image(Image &&) = delete;

    ///@attention Move assignment operator is forbidden.
    Image &operator=(Image &&) = delete;

    ///Destructor.
    virtual ~Image() = default;

    ///@return #path.
    const std::string &getPath() const;

    ///@return #rawAsciiData.
    const std::vector<std::string> &getRawAsciiData() const;

    ///@return #isContrasted.
    bool hasContrast() const;

    ///@return #isNegatived.
    bool hasNegative() const;

    ///@return #isSharpened.
    bool hasSharpen() const;

    ///Toggles #isContrasted.
    void toggleContrast();

    ///Toggles #isNegatived.
    void toggleNegative();

    ///Toggles #isSharpened.
    void toggleSharpen();

    /**
     * Converts all _RGB_ pixels from #rawData to _Gray_ pixels with #rgbToGray() function.\n
     * Finds needful ASCII characters in `grayscaleLevel` for all _Gray_ pixels by their brightness.
     * @note If #isContrasted is set, then calls #applyContrast() function.
     * @note If #isNegatived is set, then calls #applyNegative() function.
     * @note If #isSharpened is set, then calls #applySharpen() function.
     *
     * @param grayscaleLevel Range of symbols from _darkest_ to _lightest_ (more at #ImageFactory::grayscaleLevel).
     */
    void convertToAscii(const std::string &grayscaleLevel);

    /**
     * Based on #height and #width of the given Image, computes new `height` and `width` for ASCII art to display.
     * @note Computations _preserves_ aspect ratio of Image.
     *
     * @param[in] viewH Height of View to display ASCII art in.
     * @param[in] viewW Width of View to display ASCII art in.
     * @param[out] viewH ASCII art height.
     * @param[out] viewW ASCII art width.
     */
    void computeArtSize(size_t &viewH, size_t &viewW) const;

    /**
     * Scales #rawAsciiData to given sizes and stores this data in #resizedAsciiData.
     * @note Scaling algorithm is referenced from:
     * https://en.wikipedia.org/wiki/Image_scaling#Nearest-neighbor_interpolation
     * @warning Cache optimization: if given sizes are equal to #resizedAsciiData sizes,
     * this function does _not_ provide new computations.
     *
     * @param asciiH ASCII art height.
     * @param asciiW ASCII art width.
     * @return #resizedAsciiData.
     */
    const std::vector<std::string> &getAsciiArt(size_t asciiH, size_t asciiW) const;

    /**
     * Opens image file from #path.\n
     * Reads it's metadata (#height, #width etc.) and #rawData.
     *
     * @return `true` if file is successfully opened and converted/decompressed to #rawData, `false` otherwise.
     */
    virtual bool loadFromFile() = 0;
};

#endif