<dl>
    <h1 align="center">
        <img src="img/logo.png" alt="ASCII Art Terminal" width="192">
        <br><br>ASCII Art Terminal<br>
    </h1>
    <p align="center">
        <a href="#key-features-">Key Features 🍪</a> |
        <a href="#dependencies-">Dependencies 🧬</a> |
        <a href="#build-">Build 🚀</a> |
        <a href="#how-to-use-">How to Use 📃</a> |
        <a href="#credits-">Credits ✍</a>
    </p>
    <h1 align="center">
        <img src="img/preview.gif" alt="Preview">
    </h1>
</dl>

## Key Features 🍪

* User interface in terminal!
* Supports JPEG, PPM image formats
* Your own ASCII art symbol style!
* Preserve an image's aspect ratio
* ASCII art animation
* Export art to .txt file in full image resolution
* Supporting art effects:
    - _Contrast_
    - _Negative_
    - _Sharpen_

## Requirements 🧬

* C++ 14
* libncurses
* libjpeg

## Build 🚀

#### Install dependencies

Run this command to install all necessary dependencies:

```bash
$ sudo apt install libncurses-dev libjpeg-dev
```

#### Build application

Use this command to build ASCII Art Terminal:

```bash
$ make compile
```

#### Run application

Use this command to run ASCII Art Terminal:

```bash
$ make run
```

#### Generate documentation (optional)

Use this command to generate a documentation:

```bash
$ make doc
```

You can find documentation located at: _doc/index.html_

#### Clean build (optional)

Use this command to clean compiled binaries and docs:

```bash
$ make clean
```

## How to Use 📃

#### Basics

1) [Build and run](#build-) the application
2) Choose _Add image(s)_ section to add image
3) Enter absolute path to image you want to add or simply drag your image into terminal - this action will paste path to image
4) Press Enter and wait for image to convert
5) You can add more images if you want or enter the "q" symbol to cancel
6) To display your image as ASCII Art, choose _Show ASCII art_ section
7) Choose image you want to show by entering it's index in loaded path's list
8) **Enjoy** your ASCII art!

#### Image properties

* To apply effects to your image:
    1) Choose image in _Show ASCII art_ section
    2) Choose _Image effects_ section
    3) Enter index of effect you want to add or to remove if its already applied or enter the "q" symbol to cancel
    4) Press Enter to save changes
* To remove image from list:
    1) Choose _Remove image_ section
    2) Choose image you want to remove by entering it's index in loaded path's list
* To export image to _.txt_ file:
    1) Choose image in _Show ASCII art_ section
    2) Choose _Export art_ section
    3) Enter absolute path to .txt file you want to create
    4) Press Enter to save changes

#### Animation

* To enable this function you need to add **at least 2 images**
* Animation controls:
    1) Choose _Play animation_ section to start animation
    2) Choose _Pause animation_ section to stop animation

Note: Images will display in order they were loaded

#### Optional utils

* **Style ASCII art** with your own symbols in _Set grayscale level_ section:
    - You need to enter the sequence of symbols from darkest to lightest
    - Your ASCII art will be shown by these symbols

## Credits ✍

#### Third-party libraries

* [ncurses](https://invisible-island.net/ncurses/announce.html)
* [libjpeg](http://libjpeg.sourceforge.net/)

#### Used algorithms

* If you are interested in program's idea, read [zadani.txt](https://github.com/menshiva/ascii-art-terminal/blob/master/zadani.txt) (**NOTE: Czech language only**)
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
