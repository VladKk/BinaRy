cmake_minimum_required(VERSION 3.5)
project(BinaRy LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# prefix path for default qt folder (you can change it on yours)
set(CMAKE_PREFIX_PATH #[["your_home_folder/Qt/your_qt_version/gcc_64/lib/cmake"]])

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(BinaRy
        res/resources.qrc
        src/main.cpp
        src/main_window/main_window.cpp
        src/main_window/main_window.h
        src/main_window/main_window.ui
        src/window_logic/window_logic.cpp
        src/window_logic/window_logic.h
        src/window_logic/window_logic.ui
        src/window_arithmetic/window_arithmetic.cpp
        src/window_arithmetic/window_arithmetic.h
        src/window_arithmetic/window_arithmetic.ui
        src/window_char_parse/window_char_parse.cpp
        src/window_char_parse/window_char_parse.h
        src/window_char_parse/window_char_parse.ui
        src/window_num_parse/window_num_parse.cpp
        src/window_num_parse/window_num_parse.h
        src/window_num_parse/window_num_parse.ui)

target_link_libraries(BinaRy PRIVATE Qt5::Widgets)