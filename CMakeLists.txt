cmake_minimum_required(VERSION 3.22)
project(MyGuiUtils)
# set()
include(FetchContent)
option(MyGuiUtils_Example "build MyGuiUtils example" OFF)
function(fetch_content_check content_name)
    FetchContent_MakeAvailable(${content_name})
    message("---- ${content_name}_SOURCE_DIR is found in ${${content_name}_SOURCE_DIR}")
endfunction()

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG 10.0.0
)
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.82.0/boost-1.82.0.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)

FetchContent_Declare(
    toy
    GIT_REPOSITORY https://github.com/Michaelzhouisnotwhite/My-CXX-Small-Toys
    GIT_TAG main
)
FetchContent_Declare(
    clip
    GIT_REPOSITORY https://github.com/dacap/clip.git
    GIT_TAG main
    OVERRIDE_FIND_PACKAGE
)
# Disable clip examples and tests
set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")
set(BOOST_INCLUDE_LIBRARIES bind asio url beast)
fetch_content_check(Boost)
fetch_content_check(fmt)
fetch_content_check(toy)
# fetch_content_check(opencv)
fetch_content_check(clip)
# fetch_content_check(Eigen)

set(CMAKE_CXX_STANDARD 17)

set(include_dir ${MyGuiUtils_SOURCE_DIR}/include)
set(source_dir ${MyGuiUtils_SOURCE_DIR}/src)
message("---------------include dir: ${include_dir}")
add_subdirectory(src)
if(${MyGuiUtils_Example})
    message("----- enable examples")
    add_subdirectory(example)
endif()