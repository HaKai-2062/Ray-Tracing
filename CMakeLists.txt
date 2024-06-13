# CMakeList.txt : CMake project for RayTracing, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>")
else()
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
endif()

#set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization

project ("Ray-Tracing")


include(FetchContent)

function(CloneRepository repositoryURL branchName projectName sourceDir customCMakePath)
	message("Starting to clone ${projectName} into ${sourceDir}")
		
	FetchContent_Declare(
		"${projectName}"
		GIT_REPOSITORY "${repositoryURL}"
		SOURCE_DIR "${sourceDir}"
		GIT_TAG "origin/${branchName}"
		SOURCE_SUBDIR  "${customCMakePath}"
		CONFIGURE_COMMAND ""
		BUILD_COMMAND ""
		INSTALL_COMMAND ""
	)

	FetchContent_MakeAvailable(${projectName})

endfunction(CloneRepository)

CloneRepository("https://github.com/glfw/glfw.git" "master" "GLFW" "${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW" "")
CloneRepository("https://github.com/g-truc/glm.git" "master" "glm" "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm" "")
CloneRepository("https://github.com/ocornut/imgui.git" "docking" "imgui-docking" "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking" "../CMake/imgui-docking") 

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/CMake/Glad)

# Dont specify dirs with custom CMakefiles.txt that arent in Git repo?
#add_subdirectory(vendor/CMake/imgui-docking)

# Add source to this project's executable.
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS 
"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking/backends/imgui_impl_glfw.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking/backends/imgui_impl_opengl3.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/Glad/*.c")

add_executable("${CMAKE_PROJECT_NAME}")

set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY CXX_STANDARD 20)

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC 
GLFW_INCLUDE_NONE=1
IMGUI_IMPL_OPENGL_LOADER_GLAD=1)

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

if(MSVC) # If using the VS compiler...

	set_target_properties(${BUILD_TARGET} PROPERTIES LINK_FLAGS "/PROFILE") # for profiling

	#target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)		# secure function warnings

	#set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
	
	#set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebug<$<CONFIG:Debug>:Debug>")
	#set_property(TARGET "${CMAKE_PROJECT_NAME}" PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

endif()

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR}/src"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/Glad/include"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/GLFW/include"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm/"
"${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui-docking")

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE 
glfw
glad
glm
imgui)
