project(pixelcat)
cmake_minimum_required(VERSION 2.8)

# collect files
file(GLOB_RECURSE SRC_LIST "./include/*" "./src/*")
include_directories("./include" "./src" "../external/mlk/include")

add_executable(${PROJECT_NAME} ${SRC_LIST})

# set compiler flags
set(CMAKE_CXX_FLAGS "-std=c++1y -O0")
set(CMAKE_CXX_COMPILER "clang++")


# link
#target_link_libraries(${PROJECT_NAME} "-lGLEW")

# zlib
find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
endif()

# sfml
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
#find_package(SFML 2 REQUIRED system window graphics network audio)
#if(SFML_FOUND)
#    include_directories(${SFML_INCLUDE_DIR})
#    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
#endif()

