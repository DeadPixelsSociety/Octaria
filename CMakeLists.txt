#cmake_minimum_required(VERSION 3.2.1)
#
#set(PROJECT_NAME "Octaria")
#project(${PROJECT_NAME})
#
#include_directories("${SHSDK_INCLUDE_PATHES}/Include")
#include_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86")
#
##TODO: include pluginBox2D
#
#add_definitions(-DITERATOR_DEBUG_LEVEL=0)
#add_definitions(-DSH_DEBUG)


cmake_minimum_required(VERSION 3.2.1)

set(PROJECT_NAME "Octaria")
project(${PROJECT_NAME})

set(SH_ROOT_DIR ${SHSDK_INCLUDE_PATHES} CACHE PATH "Shine root directory")

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SH_ROOT_DIR}/cmake/Modules/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:/ShineResearch/ShineEngine/Shine/cmake/Modules")

include_directories("${SH_ROOT_DIR}/include")

find_library(SH_SDK_LIB			"ShSDK_Debug"			PATHS "${SH_ROOT_DIR}" PATH_SUFFIXES Lib lib NO_DEFAULT_PATH)
find_library(SH_ENTRYPOINT_LIB	"ShEntryPoint_Debug"	PATHS "${SH_ROOT_DIR}" PATH_SUFFIXES Lib lib NO_DEFAULT_PATH)
find_library(SH_STUB_LIB		"StubUserSystem_Debug"	PATHS "${SH_ROOT_DIR}" PATH_SUFFIXES Lib lib NO_DEFAULT_PATH)

if (WIN32)
	find_package(DirectX9 REQUIRED)
	include_directories("${DirectX9_INCLUDE_DIR}")

	find_package(XAudio REQUIRED)
	find_package(XInput REQUIRED)

endif (WIN32)

add_definitions(-DITERATOR_DEBUG_LEVEL=0)
add_definitions(-DSH_DEBUG)

# StdAfx files
set(SOURCES_StdAfx Sources/StdAfx.cpp Sources/StdAfx.h)
source_group("" FILES ${SOURCES_StdAfx})

# main files
set(SOURCES_main Sources/main.cpp)
source_group("" FILES ${SOURCES_main})

# resource files
set(SOURCES_resource Sources/resource.h)
source_group("" FILES ${SOURCES_resource})

# Inputs files
set(SOURCES_input Sources/Inputs.cpp Sources/Inputs.h)
source_group("Inputs" FILES ${SOURCES_input})

# gameState files
set(SOURCES_gameState Sources/CGameState.cpp Sources/CGameState.h)
source_group("GameState" FILES ${SOURCES_gameState})

# state manager files
set(SOURCES_stateManager Sources/CGameStateManager.cpp Sources/CGameStateManager.h)
source_group("GameState" FILES ${SOURCES_stateManager})

# multi resolution application files
set(SOURCES_multiResolutionApplication Sources/CMultiResolutionApplication.cpp Sources/CMultiResolutionApplication.h)
source_group("MultiResolutionApplication" FILES ${SOURCES_multiResolutionApplication})

# Level files
set(SOURCES_mainMenu Sources/CGameStateGameMainMenu.cpp Sources/CGameStateGameMainMenu.h)
source_group("Game\\Menu" FILES ${SOURCES_mainMenu})

# Put everything together before adding platform-specific files !
set(SOURCES ${SOURCES_StdAfx} ${SOURCES_main} ${SOURCES_resource} ${SOURCES_gameState} ${SOURCES_stateManager} ${SOURCES_multiResolutionApplication} ${SOURCES_mainMenu} ${SOURCES_input})

link_directories("../ShineEngine/Shine/Lib") # for manuel ShSDK link 

add_executable(Octaria WIN32 ${SOURCES_MAIN} ${SOURCES})
set_property(TARGET Octaria APPEND PROPERTY COMPILE_DEFINITIONS "SH_DEV=1")
#set_property(TARGET Octaria APPEND PROPERTY COMPILE_DEFINITIONS "SH_MASTER=1")
target_link_libraries(Octaria ${SH_SDK_LIB} ${SH_ENTRYPOINT_LIB} ${SH_STUB_LIB})
target_link_libraries(Octaria ${DirectX9_LIBRARIES} ${XInput_LIBRARIES} ${XAudio_LIBRARY})


#link_directories("../ShineEngine/Shine/Lib" "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86/")
#set(EXECUTABLE_NAME "${PROJECT_NAME}")
#add_executable(${EXECUTABLE_NAME} WIN32 ${SOURCES} ${RC_FILE_PATH})
#
#target_link_libraries(${PROJECT_NAME} 
#						ShSDK_Debug
#						ShEntryPoint_Debug 
#						StubUserSystem_Debug)
#
#target_link_libraries(${PROJECT_NAME} XInput dinput8 dxguid X3DAudio d3d9 d3dx9 DxErr)