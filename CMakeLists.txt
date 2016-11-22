cmake_minimum_required(VERSION 3.5)
project(KiwiEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic")

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(BOOST_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries
set(Boost_ADDITIONAL_VERSION    "1.62.0")


find_package(Boost 1.62.0)
message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()


set(SOURCE_FILES main.cpp Engine/GraphicContextInterface.h Core/Initializable.h Engine/OpenglGraphicContext.cpp Engine/OpenglGraphicContext.h)
set(EXECUTABLE_OUTPUT_PATH ${SOURCE_FILES})

add_executable(KiwiEngine ${SOURCE_FILES})
target_link_libraries(KiwiEngine ${Boost_LIBRARIES})