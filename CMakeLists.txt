cmake_minimum_required(VERSION 4.4)
project("Boost Tutorials")

set(CMAKE_CXX_STANDARD 23)

# Pour que les extension d'autocomplétion fonctionne pour nvim / vscode
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tout les binaire sont mis dans le dossier bin/ et les objets dans obj/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/obj)

# Configuration des flags de compilation différentes sur Windows et Linux
if(MSVC)

	# MSCV version is important for compiling some libs locally
	message(STATUS "MSVC compiler detected")
	message(STATUS "MSVC version: ${MSVC_VERSION}")

	# Flag de warnings
	# target_compile_options(${EXECUTABLE_NAME} PRIVATE /W4 /WX)
	add_compile_definitions(_USE_MATH_DEFINES)
else()
	# Flag warnings
	add_compile_options(-Wall -Werror -Wextra)
endif()

# Boost lib
find_package(Boost CONFIG REQUIRED system)

# exercices
add_subdirectory(timer-1)
add_subdirectory(timer-2)
add_subdirectory(timer-3)
add_subdirectory(timer-4)

add_subdirectory(client)
add_subdirectory(server-1)
add_subdirectory(server-2)

