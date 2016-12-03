//
// Created by Raphael DANTZER on 11/24/16.
//

#include <iostream>
#include "App.h"
#include "OpenglGraphicContext.h"
#include "Event/CoreNotifier.h"
#include "Renderer/ShaderBuilder.h"
#include "Renderer/ProgramBuilder.h"

std::unique_ptr<Kiwi::Engine::Event::CoreNotifier>
        Kiwi::Engine::Event::CoreNotifier::_instance;

Kiwi::Engine::App::App() :
        _graphics(new OpenglGraphicContext()),
        _hid(new GLFWDispatcher),
        _core(new CoreDispatcher),
        _config("config/config.ini"),
        _vfs(new VFS) {
    Event::CoreNotifier::getInstance()->bind(_core.get());
    _core->bind(&_coreListener);
    if (!_vfs->bind(_config.get<std::string>("Filesystem.root")))
        exit(EXIT_FAILURE);

    /**
     * Set directory aliases
     */
    _vfs->setDirectories(std::unordered_map<std::string, std::string>{
            {"shaders", _config.get<std::string>("Filesystem.shaders")},
            {"models", _config.get<std::string>("Filesystem.models")},
            {"textures", _config.get<std::string>("Filesystem.textures")},
            {"levels", _config.get<std::string>("Filesystem.levels")}
    });
    //TODO configure each module accordingly
}

Kiwi::Engine::App::~App() {

}

void Kiwi::Engine::App::start() {
    _graphics->PreInit();
    _graphics->Init();
    _graphics->PostInit();

    _graphics->getNotifier()->bind(_hid.get());

    Renderer::ProgramBuilder p_builder;
    Renderer::ShaderBuilder s_builder;

    std::unordered_map<std::string, std::string> sources = _vfs->from("shaders").loadAllFromCurrentDirectory();

    //TODO need refactor omg
    GLProgram program = p_builder.createProgramFromShaders(
            s_builder.createFromFile(GL_VERTEX_SHADER, sources["default_vert.glsl"]),
            s_builder.createFromFile(GL_FRAGMENT_SHADER, sources["default_frag.glsl"]));


    GLProgram program2 = p_builder.createProgramFromShaders(
            s_builder.createFromFile(GL_VERTEX_SHADER, sources["light_basic_vert.glsl"]),
            s_builder.createFromFile(GL_FRAGMENT_SHADER, sources["light_basic_frag.glsl"]));

    _renderer.bindShaders({program, program2});
}

void Kiwi::Engine::App::run() {
    /**
     * Triggers all event listeners listening to GLFWEvents
     */
    _graphics->Update();

    /**
     * Render the current frame
     */
    _renderer.render();

    /**
     * Render frame on screen
     */
    _graphics->swapBuffers();
}

bool Kiwi::Engine::App::ok() const {
    return _keepOpen;
}



