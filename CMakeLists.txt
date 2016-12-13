cmake_minimum_required(VERSION 3.5)
project(KiwiEngine)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall")

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(BOOST_ALL_DYN_LINK           ON)   # force dynamic linking for all libraries
set(Boost_ADDITIONAL_VERSION    "1.62.0")
set(BOOST_ROOT)


find_package(Boost 1.62.0 COMPONENTS filesystem system REQUIRED)
message(status "** Boost Include: ${Boost_INCLUDE_DIR}")
message(status "** Boost Libraries: ${Boost_LIBRARY_DIRS}")
message(status "** Boost Libraries: ${Boost_LIBRARIES}")
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if (NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif (NOT OPENGL_FOUND)

set(GLFW_BUILD_EXAMPLES     OFF)
set(GLFW_BUILD_TESTS        OFF)
add_subdirectory(vendor/glfw)
include_directories(vendor/glfw/include)

set(ASSIMP_BUILD_STATIC_LIB     ON)
add_subdirectory(vendor/assimp)
include_directories(vendor/assimp/include)


include_directories(vendor/stb)

set(SOURCE_FILES main.cpp Engine/GraphicContextInterface.h Core/Initializable.h Engine/OpenglGraphicContext.cpp Engine/OpenglGraphicContext.h Core/Graphics.h Engine/Renderer/Material.h Core/Filesystem/VirtualFilesystem.cpp Core/Filesystem/VirtualFilesystem.h Engine/Renderer/Texture.h Engine/Renderer/Shader.h Engine/Renderer/ShaderBuilder.h Engine/Renderer/ShaderBuilder.cpp Engine/Renderer/Program.h Engine/Renderer/ProgramBuilder.cpp Engine/Renderer/ProgramBuilder.h Engine/App.cpp Engine/App.h Engine/Event/Dispatcher.h Engine/Event/Notifier.h Engine/Event/GLFWNotifier.cpp Engine/Event/GLFWNotifier.h Engine/Event/Type.h Engine/Event/Listener.h Engine/Primitives/Mesh.h Engine/Primitives/Camera.h Engine/Primitives/FPSCamera.cpp Engine/Primitives/FPSCamera.h Engine/Renderer/Renderer.h Engine/Scene/Level.h Engine/Scene/Entity.h Engine/Scene/Creator.h Engine/Scene/Creator.cpp Engine/Assets/Loader.h Engine/Primitives/Mesh.cpp Engine/Assets/Loader.cpp Engine/Primitives/Model.h Core/Config.h Core/Utility.h Engine/Event/CoreNotifier.cpp Engine/Event/CoreNotifier.h Engine/Renderer/Renderer.cpp Engine/Assets/Storage.h Core/Opengl.h Engine/Event/Manager.h Engine/Assets/Tools.h Engine/Assets/ugly.h Engine/Assets/Manager.cpp Engine/Assets/Manager.h Engine/Renderer/Target.cpp Engine/Renderer/Target.h Engine/Renderer/PhongMaterial.cpp Engine/Renderer/PhongMaterial.h Engine/Renderer/PBRMaterial.cpp Engine/Renderer/PBRMaterial.h Engine/Renderer/Uniform.h Engine/Renderer/Shading.h Engine/Renderer/PhongTexturedMaterial.cpp Engine/Renderer/PhongTexturedMaterial.h Engine/Renderer/CubeMaterial.cpp Engine/Renderer/CubeMaterial.h Engine/Scene/Actuator.cpp Engine/Scene/Actuator.h Engine/Primitives/AABB.cpp Engine/Primitives/AABB.h Engine/GUI/Freetype.cpp Engine/GUI/Freetype.h Engine/Scene/Player.h Engine/GUI/Easing.h Engine/GUI/ImGui.cpp Engine/GUI/ImGui.h vendor/imgui/imgui.cpp vendor/imgui/imgui_draw.cpp Engine/Scene/Collection.cpp Engine/Scene/Collection.h Engine/Assets/Asset.h Engine/Assets/Asset.cpp Engine/Assets/Importer.cpp Engine/Assets/Importer.h Engine/GlobalInstance.h)

add_executable(KiwiEngine ${SOURCE_FILES})
target_link_libraries(KiwiEngine
        glfw        ${GLFW_LIBRAIRIES}
        assimp      ${ASSIMP_LIBRAIRIES}
        ${Boost_LIBRARIES}
        ${OPENGL_LIBRARIES}
        )