# This CMake script is mainly designed for CLion IDE and QTCreator projects on Windows
# It should find bundled binary dependencies automatically when using MinGW
cmake_minimum_required ( VERSION 3.1 )
project( ppgso CXX )

# Set up external dependencies for Wwindows users
if ( MINGW )
  set ( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/mingw/include/" )
  set ( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/mingw/lib/" )
endif ()

# Basic CMake settings
set ( CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/_install )
set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake )
set ( CMAKE_CXX_STANDARD 11 )
set ( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Warnings for Debug mode
option( USE_STRICT_COMPILE_WARNINGS "Use strict compilation warnings in debug mode." ON )
if( USE_STRICT_COMPILE_WARNINGS )
    # Assuming Clang and GCC (NOTE: Sign conversion is ok in CPP)
    set( STRICT_COMPILE_WARNINGS "-Wpedantic -Wall -Wfloat-equal -Wextra -Wsign-promo -Wsign-compare -Wconversion -Wno-sign-conversion" )
    set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${STRICT_COMPILE_WARNINGS}" )
endif()

# Find dependencies
find_package ( GLFW3 REQUIRED )
find_package ( GLEW REQUIRED )
find_package ( GLM REQUIRED )     # GLM is header only
find_package ( OpenGL REQUIRED )

# Include header directories
include_directories ( ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} )

# Prepare libraries for linking
set ( LIBRARIES ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} )

# ADD YOUR PROJECT HERE

add_executable( testt test.cpp )
target_link_libraries( testt ${LIBRARIES} )
install ( TARGETS testt DESTINATION . )

#add_executable( my_project my_project.cpp my_project_other.cpp )
#target_link_libraries( my_project ${LIBRARIES} )

#install ( TARGETS my_project DESTINATION . )
#install ( FILES my_project.file my_project.vert my_project.frag DESTINATION . )

# Install dlls to destination when on Windows
if ( MINGW )
  install ( FILES ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} DESTINATION . )
  # Install dlls into binary dir for development and debugging
  file ( COPY ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} DESTINATION ${CMAKE_BINARY_DIR} )
endif ()
