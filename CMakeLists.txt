# This CMake script is mainly designed for CLion IDE and QTCreator projects on Windows
# It should find bundled binary dependencies automatically when using MinGW

cmake_minimum_required ( VERSION 3.5 )
project( pokemon-custom-_evolution CXX )

#
# Configuration
#

# Basic CMake settings
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/_install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Warnings for Debug mode
option(USE_STRICT_COMPILE_WARNINGS "Use strict compilation warnings in debug mode." ON)
if (USE_STRICT_COMPILE_WARNINGS)
    # Assuming Clang and GCC
    set(STRICT_COMPILE_WARNINGS "-Wpedantic -Wall -Wfloat-equal -Wextra -Wsign-promo -Wsign-compare -Wconversion -Wno-sign-conversion -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${STRICT_COMPILE_WARNINGS}")
endif ()

# Make sure GLM uses radians
add_definitions ( -DGLM_FORCE_RADIANS )

# Add custom target for installation in CLion
add_custom_target(run_install COMMAND ${CMAKE_MAKE_PROGRAM} install)

# Use generate_shader function to convert .glsl sources to C++ headers
include(shaders)

#
# DEPENDENCIES
#

# Set up external dependencies for Wwindows users
if ( MINGW )
    set ( CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/mingw/include/" )
    set ( CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/mingw/lib/" )
endif ()

# Find dependencies
find_package ( GLFW3 REQUIRED )
find_package ( GLEW REQUIRED )
find_package ( GLM REQUIRED )
find_package ( OpenGL REQUIRED )
find_package ( PNG REQUIRED )
find_package ( GLUT REQUIRED )
find_package ( Freetype REQUIRED )

# Set default installation destination
if (NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX "../_install")
endif ()

file(GLOB evolution_main "src/*.cpp")
file(GLOB evolution_shaders "src/shaders/*.cpp")
file(GLOB evolution_loaders "src/loaders/*.cpp")
file(GLOB evolution_windows "src/windows/*.cpp")
file(GLOB evolution_images "src/images/*.cpp")
file(GLOB evolution_engine "src/engine/*.cpp")
file(GLOB evolution_engine_text "src/engine/text/*.cpp")
file(GLOB evolution_engine_rendering "src/engine/rendering/*.cpp")
file(GLOB evolution_engine_loaders "src/engine/loaders/*.cpp")
file(GLOB evolution_engine_animation "src/engine/animation/*/*.cpp")
file(GLOB evolution_objects "src/objects/*.cpp")
file(GLOB evolution_scenes "src/scenes/*.cpp")
file(GLOB evolution_constants "src/constants/*.hpp")
file(GLOB evolution_shader_programs "src/shaders/*.glsl")

# Include header directories
include_directories (
        src
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${PNG_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS})

# Prepare libraries for linking
set ( LIBRARIES
        ${OPENGL_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${GLEW_LIBRARIES}
        evolutionlib )

# Evolution library
add_library(evolutionlib STATIC
        ${evolution_shaders}
        ${evolution_loaders}
        ${evolution_windows}
        ${evolution_images}
        ${evolution_engine}
        ${evolution_engine_text}
        ${evolution_engine_rendering}
        ${evolution_objects}
        ${evolution_engine_loaders}
        ${evolution_engine_animation}
        ${evolution_scenes}
        ${evolution_constants})

target_link_libraries(evolutionlib ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${PNG_LIBRARY} ${GLUT_LIBRARIES} ${FREETYPE_LIBRARIES})

#
# TARGETS
#

# _evolution
set ( EVOLUTION_SRC
        ${evolution_main}
        ${evolution_shaders}
        ${evolution_loaders}
        ${evolution_windows}
        ${evolution_images}
        ${evolution_engine}
        ${evolution_engine_text}
        ${evolution_engine_rendering}
        ${evolution_objects}
        ${evolution_engine_loaders}
        ${evolution_engine_animation}
        ${evolution_scenes}
        ${evolution_constants})

generate_shaders( EVOLUTION_SHADERS
        src/shaders/frag_text.glsl
        src/shaders/frag_texture.glsl
        src/shaders/vert_text.glsl
        src/shaders/vert_texture.glsl)

add_executable ( PokemonCustomEvolution ${EVOLUTION_SRC} ${EVOLUTION_SHADERS})

target_link_libraries( PokemonCustomEvolution ${LIBRARIES} )

install ( TARGETS PokemonCustomEvolution DESTINATION . )

#
# INSTALLATION
#

install(DIRECTORY _data DESTINATION .)
install(DIRECTORY data DESTINATION .)
install(FILES ${evolution_shader_programs} DESTINATION src/shaders)

# Install dlls to destination when on Windows
if ( MINGW )
    install ( FILES ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} DESTINATION . )
    # Install dlls into binary dir for development and debugging
    file ( COPY ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} DESTINATION ${CMAKE_BINARY_DIR} )
endif ()
