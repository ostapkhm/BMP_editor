cmake_minimum_required(VERSION 3.24)
project(BMP_editor)

set(CMAKE_CXX_STANDARD 17)

set(Headers src/Editor/Editor.h src/MyImage/MyImage.h)
set(Sources src/main.cpp src/MyImage/MyImage.cpp src/Editor/Editor.cpp)

add_executable(BMP_editor ${Headers} ${Sources})

set_target_properties(BMP_editor PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Images
        )