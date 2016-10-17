cmake_minimum_required(VERSION 3.2.1)

set(PROJECT_NAME "Octaria")
project(${PROJECT_NAME})

set(SH_ROOT_DIR ${SHSDK_INCLUDE_PATHES} CACHE PATH "Shine root directory")

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SH_ROOT_DIR}/cmake/Modules/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:/ShineResearch/ShineEngine/Shine/cmake/Modules")

include_directories("${SH_ROOT_DIR}/include")

find_library(SH_SDK_LIB			"ShSDK"				PATHS "${SH_ROOT_DIR}" PATH_SUFFIXES Lib lib NO_DEFAULT_PATH)
find_library(SH_ENTRYPOINT_LIB	"ShEntryPoint"		PATHS "${SH_ROOT_DIR}" PATH_SUFFIXES Lib lib NO_DEFAULT_PATH)
find_library(SH_STUB_LIB		"StubUserSystem"	PATHS "${SH_ROOT_DIR}" PATH_SUFFIXES Lib lib NO_DEFAULT_PATH)
find_library(SH_CORE_LIB		"ShCore"			PATHS "${SH_ROOT_DIR}" PATH_SUFFIXES Lib lib NO_DEFAULT_PATH)

if (WIN32)
	find_package(DirectX9 REQUIRED)
	include_directories("${DirectX9_INCLUDE_DIR}")

	find_package(XAudio REQUIRED)
	find_package(XInput REQUIRED)
	
endif (WIN32)


if (MSVC)
	add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
	STRING(REPLACE "/MDd" "/MD" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
	STRING(REPLACE "D_DEBUG" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
	message("${CMAKE_CXX_FLAGS_DEBUG}")
endif (MSVC)

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

# Game level files
set(SOURCES_game Sources/CGameStateGame.cpp Sources/CGameStateGame.h)
source_group("Game\\" FILES ${SOURCES_game})

# Main Menu files
set(SOURCES_mainMenu Sources/CGameStateMainMenu.cpp Sources/CGameStateMainMenu.h)
source_group("Game\\Menu" FILES ${SOURCES_mainMenu})

# Poulpe caracter files
set(SOURCES_poulpe Sources/CGamePoulpe.cpp Sources/CGamePoulpe.h)
source_group("Game\\Character" FILES ${SOURCES_poulpe})

# Generation procedurale
set(SOURCES_levelgenerator Sources/Block.cpp Sources/Block.h Sources/ProceduralGeneration.cpp Sources/ProceduralGeneration.h Sources/FieldManager.cpp Sources/FieldManager.h)
source_group("LevelGenerator" FILES ${SOURCES_levelgenerator})

set(SOURCES ${SOURCES_StdAfx} ${SOURCES_main} ${SOURCES_resource} ${SOURCES_gameState} ${SOURCES_stateManager} ${SOURCES_multiResolutionApplication} ${SOURCES_mainMenu} ${SOURCES_input} ${SOURCES_game} ${SOURCES_poulpe} ${SOURCES_levelgenerator})

#link_directories("../ShineEngine/Shine/Lib")

add_executable(Octaria WIN32 ${SOURCES_MAIN} ${SOURCES})
set_property(TARGET Octaria APPEND PROPERTY COMPILE_DEFINITIONS "SH_MASTER=1")
target_link_libraries(Octaria ${SH_SDK_LIB} ${SH_ENTRYPOINT_LIB} ${SH_STUB_LIB} ${SH_CORE_LIB})
target_link_libraries(Octaria ${DirectX9_LIBRARIES} ${XInput_LIBRARIES} ${XAudio_LIBRARY})