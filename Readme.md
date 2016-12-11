#Kiwi::Engine

This project is currently a WIP.

My aim is to have a better understanding of a modern game engine by coding one.
The engine uses modern OpenGL but has only been tested on MacOS.
By the end I want it to be cross platform, so I try to be as platform agnostic as I can.


##Implemented
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

###Other:
1. Rigid body physics (with middleware abstraction in order to select different physic engine)
2. Animation
3. Voxels !!!! (need some work on those octree tho)


##Usage:
`git clone --recursive https://github.com/Raphy42/KiwiEngine.git`  
`cmake . && make`

##Librairies:
`boost` for the filesystem abstraction (added in c++17) and some other neat things (not included in vendor, need to install it with your favorite package manager)  
`assimp` for model loading (will be removed as soon as the engine has its own 3D file format)  
`glad`, currently unused as MacOS does its own things with OpenGL 3+ context creation  
`glfw` for OpenGL/Vulkan context creation and window management  
`stb/stb_image.h` for image loading  
