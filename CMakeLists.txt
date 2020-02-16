cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(BINARY_NAME run)

set (SDL2_DLL_PATH ${CMAKE_SOURCE_DIR}/libs/SDL2/bin/SDL2.dll)
set (GLEW_DLL_PATH ${CMAKE_SOURCE_DIR}/libs/GL/bin/glew32.dll)
set (ASSIMP_DLL_PATH ${CMAKE_SOURCE_DIR}/libs/assimp/bin/libassimp.dll)

project(Bliep)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/rendering)
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${BINARY_NAME} ${SOURCES})

#SDL2
find_package(SDL2 REQUIRED)
target_link_libraries(${BINARY_NAME} ${SDL2_LIBRARY})
include_directories(${BINARY_NAME} PUBLIC ${SDL2_INCLUDE_DIR})

#OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${BINARY_NAME} ${OPENGL_gl_LIBRARY})
include_directories(${BINARY_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})

#GLEW
find_package(GL REQUIRED)
target_link_libraries(${BINARY_NAME} ${GLEW_LIBRARY})
target_include_directories(${BINARY_NAME} PUBLIC ${GLEW_INCLUDE_DIR})

#ASSIMP
find_package(ASSIMP REQUIRED)
target_link_libraries(${BINARY_NAME} ${ASSIMP_LIBRARIES})
target_include_directories(${BINARY_NAME} PUBLIC ${ASSIMP_INCLUDE_DIRS})

#GLM / PLOG / stb_image
target_include_directories(${BINARY_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/libs")

#Copy DLL
file(COPY ${SDL2_DLL_PATH} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${GLEW_DLL_PATH} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${ASSIMP_DLL_PATH} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})