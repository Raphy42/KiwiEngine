#Kiwi::Engine
<img width="1279" alt="Sponza scene" src="https://cloud.githubusercontent.com/assets/9398077/21079205/de8d433c-bf8a-11e6-97f1-b38b9d276915.png">
_Sponza scene from Crytek_

This project is currently a WIP.

My aim is to have a better understanding of a modern game engine by coding one.
The engine uses modern OpenGL but has only been tested on MacOS.
By the end I want it to be cross platform, so I try to be as platform agnostic as I can.


##Usage:
macOS only (for the moment)  
`brew install boost` (for `boost::property_tree`, `boost::filesystem`)  
`git clone --recursive https://github.com/Raphy42/KiwiEngine.git`  
`cmake . && make`


##Implemented
###Demo:
1. PhongTexturedMaterial test on small scene with one dynamic light. (no shadows)

###Scene:
1. Mesh, complex meshes and simple primitive (cube, plane)
2. Actuator (position, rotation, scale)
3. Camera (FPS)

###Material:
1. Phong (basic, simple light)
2. Phong textured (diffuse, specular, normal and alpha)
3. Cubemap

###Event:
1. Listener, Notifier and Dispatcher

###Context:
1. OpenGL 3+

##Todo
###Scene:
1. Refactor entity storage
2. Matrix hierarchy
3. Scene manager (loading scene from json or xml?)
    
###Renderer:
1. PBR material (metallic workflow)
2. uniform buffer object (std140)
3. GLSL abstraction?
4. Point shadow

###Other:
1. Rigid body physics (with middleware abstraction in order to select different physic engine)
2. Animation
3. Voxels !!!! (need some work on those octree tho)

##Librairies:
`boost` for the filesystem abstraction (added in c++17) and some other neat things (not included in vendor, need to install it with your favorite package manager)  
`assimp` for model loading (will be removed as soon as the engine has its own 3D file format)  
`glad`, currently unused as MacOS does its own things with OpenGL 3+ context creation  
`glfw` for OpenGL/Vulkan context creation and window management  
`stb/stb_image.h` for image loading  
