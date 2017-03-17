# _______________________________________________
# 		Project Information 
# _______________________________________________
project(Test)
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)

# _______________________________________________
# 		Requirement 
# _______________________________________________
cmake_minimum_required( VERSION 2.8)

# _______________________________________________
# 		Setting 
# _______________________________________________
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )
include_directories( /usr/local/include )
link_directories(/usr/local/lib)

include_directories( /home/zhehua/mylibs/include)
# _______________________________________________
# 		SourceTree
# _______________________________________________
aux_source_directory( ./src MAIN_SRC)
add_executable(main ${MAIN_SRC})

target_link_libraries(main yaml-cpp)


