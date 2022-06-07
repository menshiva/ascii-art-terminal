cmake_minimum_required(VERSION 3.17.5)
project(ASCIIart)

set(CMAKE_CXX_STANDARD 17)

add_executable(ASCIIart src/main.cpp src/utils/Consts.hpp
        src/ui/UI.hpp src/ui/UI.cpp
        src/ui/view/Panel.hpp src/ui/view/Panel.cpp
        src/ui/view/Menu.hpp src/ui/view/Menu.cpp
        src/ui/view/Text.hpp src/ui/view/Text.cpp
        src/ui/view/View.hpp
        src/factory/ImageFactory.hpp src/factory/ImageFactory.cpp
        src/image/Pixel.hpp src/image/Image.hpp src/image/Image.cpp
        src/image/format/PPMImage.hpp src/image/format/PPMImage.cpp
        src/image/format/JPEGImage.hpp src/image/format/JPEGImage.cpp)