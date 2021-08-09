cmake_minimum_required(VERSION 3.12)

project(OpenGLBoilerplate)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} Application.cpp)

#           DOWNLOAD ALL THE SUBMODULES
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#           CHECK ALL THE SUBMODULES
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

add_definitions(-DGLEW_STATIC)

#glfw
add_subdirectory(external/glfw EXCLUDE_FROM_ALL)

# glew
add_subdirectory(external/glew EXCLUDE_FROM_ALL)

# glm
add_subdirectory(external/glm EXCLUDE_FROM_ALL)

# ImGui
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLEW=1)

set(IMGUI_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external/imgui)

file(GLOB IMGUI_SOURCES ${IMGUI_PATH}/*.cpp ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp ${IMGUI_PATH}/backends/imgui_impl_opengl3.cpp) 
add_library("ImGui" STATIC ${IMGUI_SOURCES})
target_include_directories("ImGui" 
    PUBLIC ${IMGUI_PATH}
    PUBLIC ${IMGUI_PATH}/backends
    PUBLIC external/glfw/include
    PUBLIC external/glew/include
)

# Spdlog
add_subdirectory(external/spdlog EXCLUDE_FROM_ALL)

target_include_directories(${PROJECT_NAME} 
    PUBLIC external/glfw/include
    PUBLIC external/glew/include
    PUBLIC external/glm
    PUBLIC external/spdlog/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE glfw
    PRIVATE libglew_static
    PRIVATE glm
    PRIVATE spdlog
    PUBLIC ImGui
)

