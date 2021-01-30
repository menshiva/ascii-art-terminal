#ifndef SEMESTR_IMAGE_HPP
#define SEMESTR_IMAGE_HPP

#include "../utils/Utils.hpp"
#include "../utils/Consts.hpp"
#include <vector>

/**
 * @brief Abstract base class for all supported image formats.
 *
 * This class holds all data, needed for raw format without any compression.\n
 * Operates with image in common way, such as: convert to ASCII, add effect etc.
 *
 * @author Ivan Menshikov (<menshiva@fit.cvut.cz>).
 */
class Image {
protected:
    const std::string path; /**< Absolute path to image file. */
    /**
     * Pixels created from color components values read from image file.
     * @note Has #height * #width size.
     */
    std::vector<std::vector<Pixel>> rawData;
    /**
     * ASCII data converted from #rawData.
     * @note Has #height * #width size.
     */
    std::vector<std::string> rawAsciiData;
    /**
     * Scaled #rawAsciiData used for drawing an ASCII art.
     * @note Has ASCII art size based on terminal window size (more in #computeArtSize() and #getAsciiArt()).
     */
    mutable std::vector<std::string> resizedAsciiData;
    size_t height; /**< Height of image (_in pixels_). */
    size_t width; /**< Width of image (_in pixels_). */
    bool isContrasted; /**< Flag, which indicates if _contrast_ effect is applied. */
    bool isNegatived; /**< Flag, which indicates if _negative_ effect is applied. */
    bool isConvoluted; /**< Flag, which indicates if _convolution_ effect is applied. */
public:
    /**
     * Constructor initializes image by setting its #path.
     * @note Sets #height and #width to `0` and all effect flags (#isContrasted, #isNegatived, #isConvoluted) to `false`.
     *
     * @param imgPath _Absolute_ path to image file.
     */
    explicit Image(std::string imgPath);

    /**
     * @attention Copy constructor is forbidden.
     */
    Image(const Image &) = delete;

    /**
     * @attention Assignment operator is forbidden.
     */
    Image &operator=(const Image &) = delete;

    /**
     * Opens image file from #path and reads it's metadata (#height, #width etc.) and #rawData.
     *
     * @return `true` if file is successfully opened and converted/decompressed to #rawData, `false` otherwise.
     */
    virtual bool loadFromFile() = 0;

    /**
     * Converts each _RGB_ Pixel from #rawData to _Gray_ Pixel with #rgbToGray() function.
     * Then finds needful ASCII character in `grayscaleLevel` by brightness level of this _Gray_ Pixel.
     * @note If #isContrasted flag is set, then #applyContrast() function is on.
     * @note If #isNegatived flag is set, then #applyNegative() function is on.
     * @note If #isConvoluted flag is set, then #applyConvolution() function is on.
     *
     * @param grayscaleLevel Range of symbols from _darkest_ to _lightest_ (more at #ImageFactory::grayscaleLevel).
     */
    void convertToAscii(const std::string &grayscaleLevel);

    /**
     * Computes new `height` and `width` for ASCII art to display, based on #height and #width of Image.
     * @note Computations _preserves_ aspect ratio of Image.
     *
     * @param[in] viewH Height of View to display ASCII art in.
     * @param[in] viewW Width of View to display ASCII art in.
     * @param[out] viewH Height of ASCII art.
     * @param[out] viewW Width of ASCII art.
     */
    void computeArtSize(size_t &viewH, size_t &viewW) const;

    /**
     * Scales #rawAsciiData to specific `height` and `width` and stores this data in #resizedAsciiData.
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
     * @return #path.
     */
    const std::string &getPath() const;

    /**
     * Toggle #isContrasted flag.
     */
    void toggleContrast();

    /**
     * Toggle #isNegatived flag.
     */
    void toggleNegative();

    /**
     * Toggle #isConvoluted flag.
     */
    void toggleConvolution();

    /**
     * @return #isContrasted flag.
     */
    bool hasContrast() const;

    /**
     * @return #isNegatived flag.
     */
    bool hasNegative() const;

    /**
     * @return #isConvoluted flag.
     */
    bool hasConvolution() const;

    /**
     * @return #rawAsciiData.
     */
    const std::vector<std::string> &getRawAsciiData() const;

    /**
     * Default destructor.
     */
    virtual ~Image() = default;

private:
    /**
     * Calculates _grayscale_ value from Pixel.
     * @note Conversion to grayscale algorithm is referenced from:
     * https://en.wikipedia.org/wiki/Grayscale#Colorimetric_(perceptual_luminance-preserving)_conversion_to_grayscale
     *
     * @param pixel Pixel to convert.
     * @return Grayscale value.
     * @relatesalso Image
     */
    static unsigned char rgbToGray(const Pixel &pixel);

    /**
     * Applies _convolution_ effect to raw data.
     * @note Convolution effect algorithm is referenced from:
     * https://setosa.io/ev/image-kernels/
     *
     * @param src Image data.
     * @return Image data with _convolution_ effect.
     * @relatesalso Image
     */
    static std::vector<std::vector<Pixel>> applyConvolution(const std::vector<std::vector<Pixel>> &src);

    /**
     * Applies _negative_ effect to Pixel.
     *
     * @param[in] pixel Pixel.
     * @param[out] pixel Pixel with _negative_ effect.
     * @relatesalso Image
     */
    static void applyNegative(Pixel &pixel);

    /**
     * Applies _contrast_ effect to Pixel.
     * @note Contrast algorithm is referenced from:
     * https://en.wikipedia.org/wiki/Contrast_(vision) and
     * https://math.stackexchange.com/questions/906240/algorithms-to-increase-or-decrease-the-contrast-of-an-image
     *
     * @param[in] pixel Pixel.
     * @param[out] pixel Pixel with _contrast_ effect.
     * @param level Contrast level from `0` to `255`. Default value is AsciiConsts::DEFAULT_CONTRAST_LEVEL.
     * @relatesalso Image
     */
    static void applyContrast(Pixel &pixel, double level = AsciiConsts::DEFAULT_CONTRAST_LEVEL);
};

#endif