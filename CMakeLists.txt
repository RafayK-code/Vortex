cmake_minimum_required(VERSION 3.12)
project("HelloVulkan")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (DEFINED ENV{VULKAN_SDK})
    set(VULKAN_SDK $ENV{VULKAN_SDK})
    message(STATUS "Vulkan SDK found at: ${VULKAN_SDK}")
else()
    message(FATAL_ERROR "VULKAN_SDK environment variable not set. Please set it to the Vulkan SDK installation path.")
endif()

add_subdirectory(GLFW3)

include_directories(${VULKAN_SDK}/Include)

set(CMAKE_CXX_STANDARD 17)
find_package(Vulkan REQUIRED)

# configure_file(${CMAKE_SOURCE_DIR}/cmake/compile.in ${CMAKE_SOURCE_DIR}/shaders/${SHELL_SCRIPT_NAME} @ONLY)

# add_subdirectory(shaders)

set(SOURCES 
    src/main.cpp
    src/Window.cpp
    src/Application.cpp
    src/Window.hpp
    src/Application.hpp
    src/Pipeline.cpp 
    src/Pipeline.hpp
    src/Device.cpp 
    src/Device.hpp 
)

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE glfw/include)

target_link_libraries(main PRIVATE glfw)
target_link_libraries(main PRIVATE ${VULKAN_SDK}/Lib/vulkan-1.lib)

# Creating script file to compile shaders

if (UNIX)
    set(SHELL_SCRIPT_NAME "compile_shaders.sh")
    find_program(GLSLC NAMES glslc)
    if (NOT glslc)
        message(WARNING "Ensure you have glslc in your /usr/local/bin to compile shaders.")
    endif()
elseif (APPLE)
    set(SHELL_SCRIPT_NAME "compile_shaders.sh")
    find_program(GLSLC NAMES glslc)
    if (NOT GLSLC)
        set(FILE_PATH ${VULKAN_SDK}/Bin/glslc)
        if (EXISTS FILE_PATH)
            set (GLSLC ${FILE_PATH})
        else()
            message(WARNING "Could not locate glslc program to compile shaders.")
        endif()
    endif()
elseif (WIN32)
    set(SHELL_SCRIPT_NAME "compile_shaders.bat")
    set(FILE_PATH ${VULKAN_SDK}\\Bin\\glslc.exe)
    if (EXISTS ${FILE_PATH})
        set (GLSLC ${FILE_PATH})
    else()
        message(WARNING "Could not locate glslc program to compile shaders.")
    endif()
else()
    message(FATAL_ERROR "OS could not be detected.")
endif()

set(SHADERS_IN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
set(SHADERS_OUT_DIR "${CMAKE_BINARY_DIR}/shaders")

file(GLOB SHADERS "${SHADERS_IN_DIR}/*.vert" "${SHADERS_IN_DIR}/*.frag")

file(MAKE_DIRECTORY ${SHADERS_OUT_DIR})

foreach(SHADER ${SHADERS})
	get_filename_component(SHADER_NAME ${SHADER} NAME)
	set(SHADER_OUT_NAME "${SHADERS_OUT_DIR}/${SHADER_NAME}.spv")
	list(APPEND SHADER_OUT_NAMES ${SHADER_OUT_NAME})
	add_custom_command(
        MAIN_DEPENDENCY ${SHADER}
		OUTPUT ${SHADER_OUT_NAME}
		COMMAND ${GLSLC}  ${SHADER} "-o" ${SHADER_OUT_NAME}
        VERBATIM
        )
endforeach()

add_custom_target(Shaders DEPENDS ${SHADER_OUT_NAMES})

add_dependencies(main Shaders)