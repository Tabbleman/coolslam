cmake_minimum_required(VERSION 3.10)
project(rgbdSlam)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -fopenmp -pthread")
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#########dependencies#########
#eigen
include_directories("/usr/include/eigen3")

#opencv
find_package(OpenCV 3.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#pangolin
find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

#Sophus
find_package(Sophus REQUIRED)
include_directories(${Sophus_INCLUDE_DIRS})

#g2o
find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIRS})

#glog
find_package(Glog REQUIRED)
include_directories(${Glog_INCLUDE_DIRS})
#gflag
find_package(GFlags REQUIRED)
include_directories(${GFLAGS_INCLUDE_DIRS})

#glog
find_package(CSparse REQUIRED)
include_directories(${CSPARSE_INCLUDE_DIRS})

set(THIRD_PARTY_LIBS
    ${OpenCV_LIBS}
    ${Sophus_LIBRARIES}
    ${Pangolin_LIBRARIES} GL GLU GLEW glut
    g2o_core g2o_stuff g2o_types_sba g2o_solver_csparse g2o_csparse_extension
    ${GTEST_BOTH_LIBRARIES}
    ${GLOG_LIBRARIES}
    ${GFLAGS_LIBRARIES}
    pthread
    ${CSPARSE_LIBRARY}
    fmt
    )

# enable_testing()
################source and test##################
include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(src)
# add_subdirectory(test)
