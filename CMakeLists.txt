cmake_minimum_required(VERSION 3.12)
project(hdfio)

set(CMAKE_CXX_STANDARD 14)

find_package(HDF5 REQUIRED COMPONENTS C CXX)
include_directories(${HDF5_INCLUDE_DIRS})

add_executable(hdfio main.cpp TaqLoader.h TaqDumper.h)


#add_executable( hdf write_hdf.cpp )

target_link_libraries( hdfio ${HDF5_CXX_LIBRARIES} ${HDF5_LIBRARIES})
