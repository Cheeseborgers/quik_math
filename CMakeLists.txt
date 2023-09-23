cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(quik_math
	VERSION 0.0.2
	DESCRIPTION "A math lib"
	HOMEPAGE_URL "https://github.com/Cheeseborgers"
	LANGUAGES C CXX)

# Build messages
message(STATUS "${PROJECT_NAME}: Build type: " ${CMAKE_BUILD_TYPE})
message(STATUS "${PROJECT_NAME}: Version " ${PROJECT_VERSION})

# Set compiler-specific flags (if needed)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Add GCC-specific flags here
    message(STATUS "GNU: " ${CMAKE_CXX_COMPILER_ID})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Add Clang-specific flags here
    message(STATUS "Clang: " ${CMAKE_CXX_COMPILER_ID})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Add MSVC-specific flags here
    message(STATUS "MSVC: " ${CMAKE_CXX_COMPILER_ID})
endif()

# Define the library target
add_library(${PROJECT_NAME}
    src/vec2.cpp
    src/vec3.cpp
    src/vec4.cpp
)

# Create an alias for the library
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Specify the include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
