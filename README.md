<dl>
    <h1 align="center">
        <img src="img/logo.png" alt="ASCII Art Terminal" width="192">
        <br><br>ASCII Art Terminal<br>
    </h1>
    <p align="center">
        <a href="#key-features-">Key Features 🍪</a> |
        <a href="#requirements-">Requirements 🧬</a> |
        <a href="#build-">Build 🚀</a> |
        <a href="#how-to-use-">How to Use 📃</a> |
        <a href="#credits-">Credits ✍</a>
    </p>
    <h1 align="center">
        <img src="img/preview.gif" alt="Preview">
    </h1>
</dl>

## Key Features 🍪

* User interface
* Supports JPEG, PPM image formats
* Your own ASCII art symbol style
* Preserve an image's aspect ratio
* ASCII art animation
* Export art to .txt file in full image resolution
* Available effects:
    - _Contrast_
    - _Negative_
    - _Sharpen_

## Requirements 🧬

* C++ 14
* libncurses
* libjpeg
* doxygen (optional)

## Build 🚀

#### Install dependencies

Install all necessary dependencies:

```bash
$ sudo apt install libncurses-dev libjpeg-dev
```

#### Build application

Build ASCII Art Terminal:

```bash
$ make compile
```

#### Run application

Run ASCII Art Terminal:

```bash
$ make run
```

#### Generate documentation (optional)

Firstly, you need to install _doxygen_:

```bash
$ sudo apt install doxygen
```

Generate documentation:

```bash
$ make doc
```

You can find generated documentation located at: _doc/index.html_

#### Clean build (optional)

To clean compiled binaries and docs:

```bash
$ make clean
```

## How to Use 📃

#### Basics

1) [Build and run](#build-) the application
2) Press on the _Add image(s)_ button to add an image
3) Enter absolute path to image you want to add or simply drag your image into the terminal - this action will automatically paste image's path
4) Press Enter and wait for image to convert
5) You can add more images if you want or enter the "q" symbol to return back to the menu
6) To display your image as ASCII Art, press the _Show ASCII art_ button
7) Choose the image you want to show by entering it's index from list of loaded paths
8) **Enjoy** your ASCII art!

#### Image properties

* To apply effects to your image:
    1) Choose the image in the _Show ASCII art_ section
    2) Press the _Image effects_ button
    3) Enter index of the effect you want to add or to remove it if its already applied. Enter the "q" symbol to return back to the menu
    4) Press Enter to save the changes
* To remove image from the list:
    1) Press the _Remove image_ button
    2) Choose the image you want to remove by entering it's index from list of loaded paths
* To export image to _.txt_ file:
    1) Choose the image in the _Show ASCII art_ section
    2) Press the _Export art_ button
    3) Enter absolute path to .txt file you want to create
    4) Press Enter to save the changes

#### Animation

* To enable this function you need to add **at least 2 images**
* Press the:
    1) _Play animation_ button to start animation
    2) _Pause animation_ button to stop animation

Note: Images will be displayed in order they were loaded

#### Optional utils

* **Style ASCII art** with your own symbols in a _Set grayscale level_ section:
    - Enter the sequence of symbols from darkest to lightest
    - Now your ASCII art will be displayed by these symbols

## Credits ✍

#### Third-party libraries

* [ncurses](https://invisible-island.net/ncurses/announce.html)
* [libjpeg](http://libjpeg.sourceforge.net/)
* [doxygen](https://www.doxygen.nl/index.html)

#### Used algorithms

* If you are interested in program's idea, see also [zadani.txt](https://github.com/menshiva/ascii-art-terminal/blob/master/zadani.txt) (**NOTE: Czech language only**)
* [Image scaling algorithm](https://en.wikipedia.org/wiki/Image_scaling#Nearest-neighbor_interpolation)
* [RGB to Grayscale algorithm](https://en.wikipedia.org/wiki/Grayscale#Colorimetric_(perceptual_luminance-preserving)_conversion_to_grayscale)
* [Contrast algorithm](https://en.wikipedia.org/wiki/Contrast_(vision))
* [Convolution algorithm](https://setosa.io/ev/image-kernels/)
* [JPEG decompression example](https://github.com/LuaDist/libjpeg/blob/master/example.c#L210)

#### Author

* Ivan Menshikov (menshiva@fit.cvut.cz)

#### License

```
Copyright 2021 Ivan Menshikov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
