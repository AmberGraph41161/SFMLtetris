cmake_minimum_required(VERSION 3.30.3)

project(SFMLtetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# get SFML if needed
include(FetchContent)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 3.0.x
)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} src/main.cpp src/gamefunctions.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-system sfml-graphics sfml-audio)
