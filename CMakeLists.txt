cmake_minimum_required(VERSION 3.17.2)

project(ImGUIDemo VERSION 0.1.0)

configure_file(ImGUIDemoConfig.h.in ImGUIDemoConfig.h)

# C++ standard = C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()

# add include
set(INCLUDE_LIST ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)
include_directories(${INCLUDE_LIST} ${PROJECT_BINARY_DIR})

# add subdirectory
add_subdirectory(${PROJECT_SOURCE_DIR}/include/glad)
add_subdirectory(${PROJECT_SOURCE_DIR}/include/imgui)
add_subdirectory(${PROJECT_SOURCE_DIR}/include/glm)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

# add library
set(LIB_GLFW ${PROJECT_SOURCE_DIR}/lib/libglfw3.a)
link_libraries(${LIB_GLFW} glad imgui glm game)

# add executable
file(GLOB SRC_FILES *.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# link OSX OpenGL framework
if(APPLE)
    target_link_libraries(${PROJECT_NAME} 
        "-framework OpenGL" 
        "-framework Cocoa" 
        "-framework IOKit" 
    )
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
