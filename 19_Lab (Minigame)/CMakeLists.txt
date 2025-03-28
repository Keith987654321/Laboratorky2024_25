cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME Minigame)
project("${PROJECT_NAME}")

add_definitions(-DSFML_STATIC)		 # дефайны

include_directories("ext/SFML/include/")

link_directories("ext/SFML/lib/")

add_executable("${PROJECT_NAME}" main.cpp list_array.cpp)

target_link_libraries("${PROJECT_NAME}" sfml-graphics-s-d
						  sfml-window-s-d
						  sfml-system-s-d
						  opengl32
						  freetype
						  winmm
						  gdi32
						  sfml-audio-s-d
						  openal32
						  flac
						  vorbisenc
						  vorbisfile
						  vorbis
						  ogg)