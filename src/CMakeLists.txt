
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)


# Configurations whihc get's added into config.h file for using in code
set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)
set (LOGGER_FILE_PATH "./logs/${CMAKE_PROJECT_NAME}.log")
set (LOGGER_FILE_EXT  ".log")

# should we use our own math functions?
option (FILE_LOGGER 
        "Log into file," ON) 



#change it to Release for production tunings
set(CONFIGURATION_NAME "Debug")
set(H2O_DEBUG ON)



# Set default locations
set(CL_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CL_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CL_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CL_OUTPUT_DIRECTORY})


set(CMAKE_BUILD_TYPE ${CONFIGURATION_NAME})

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_SOURCE_DIR}/src/config.h"
  )
  
  
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories(
					"${PROJECT_BINARY_DIR}"
				    "${PROJECT_BINARY_DIR}/src/spdlog"
				    )
				    
add_subdirectory (
				 spdlog
)
 
 
 
message("CMAKE_CURRENT_LIST_DIR :" ${CMAKE_CURRENT_LIST_DIR})
 
  # Define the CXX sources
#            set ( CXX_SRCS
#    	${CMAKE_CURRENT_LIST_DIR}/*.cpp
#	)

file(GLOB CXX_SRCS
          ${CMAKE_CURRENT_LIST_DIR}/*.cpp
          ${CMAKE_CURRENT_LIST_DIR}/*.h
     )     

message("SRC :" ${CXX_SRCS})
 
 # Compiler options
 
 if(H2O_DEBUG)
 
    message("in debug")
 	add_definitions(-g)
	add_definitions(-O0)
	add_definitions(-Wall)
	
	set_source_files_properties(
    ${CXX_SRCS} PROPERTIES COMPILE_FLAGS 
    " -g -O0 -Wall")

 else(H2O_DEBUG)
    message("in release") 	
    
    # Compiler options
	add_definitions(-O2)
	add_definitions(-Wall)
	add_definitions(
    	-DNDEBUG
	)
    set_source_files_properties(
    	${CXX_SRCS} PROPERTIES COMPILE_FLAGS " -O2 -Wall"
    	)
    
    
 endif(H2O_DEBUG)
 
message("Flags :" ${CXX_SRCS})
 


# pthread related lib linking 
find_package (Threads)
message("package search result :" ${Threads_FOUND} ${PACKAGE_FIND_NAME})

#Boost filesystem library
find_package(Boost REQUIRED COMPONENTS  filesystem  )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
message("Boost include :" ${Boost_INCLUDE_DIR})
message("Boost libs :" ${Boost_LIBRARIES})

add_executable(hubble ${CXX_SRCS})
link_directories(${Boost_LIBRARY_DIR})
target_link_libraries (hubble spdlog ${CMAKE_THREAD_LIBS_INIT}   ${Boost_LIBRARIES})
message("Thread init:" ${CMAKE_THREAD_LIBS_INIT})
target_compile_features(hubble PRIVATE cxx_range_for)
