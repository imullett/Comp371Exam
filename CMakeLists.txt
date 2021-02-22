cmake_minimum_required(VERSION 3.11)

project("OpenGL")

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH ${CMAKE_SOURCE_DIR}/dist FORCE)
set(CMAKE_BUILD_TYPE "Debug")

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

set(EXEC "OpenGL")

file(GLOB SRC 
    src/*.cpp 
    include/*.h)

add_executable(${EXEC} ${SRC})

target_include_directories(${EXEC} PRIVATE include)

target_link_libraries(${EXEC} OpenGL::GL GLEW glfw glm)

list(APPEND BIN ${EXEC})

# install files to install location
install(TARGETS ${BIN} DESTINATION ${CMAKE_INSTALL_PREFIX})
