cmake_minimum_required(VERSION 3.0.0)
project(BoggleSolver VERSION 0.1.0)

set(CODING_THEORY_HEADERS
    "CodingTheory/Include/Channel.h"
    "CodingTheory/Include/Decoder.h"
    "CodingTheory/Include/Encoder.h"
    "CodingTheory/Include/FiniteField.h"
    "CodingTheory/Include/Vector.h"
    "CodingTheory/Include/ColorPrinter.h"

    "CodingTheory/Include/Utils/stb_image_write.h"
    "CodingTheory/Include/Utils/stb_image.h"
)

set(CODING_THEORY_SOURCES
    "CodingTheory/Source/Utils/stb_image_write.cpp"
    "CodingTheory/Source/Utils/stb_image.cpp"
    
    "CodingTheory/Source/Platforms/Linux/ColorPrinter.cpp"

    "CodingTheory/Source/Main.cpp"
)

add_executable(CodingTheory ${CODING_THEORY_HEADERS} ${CODING_THEORY_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})