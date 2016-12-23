//
// Created by Raphael DANTZER on 11/24/16.
//

#include <iostream>
#include "App.h"


std::unique_ptr<Kiwi::Engine::Event::CoreNotifier>
        Kiwi::Engine::Event::CoreNotifier::_instance;

Kiwi::Engine::App::App() :
        _graphics(new OpenglGraphicContext()),
        _hid(new GLFWDispatcher),
        _core(new CoreDispatcher),
        _config("config/config.ini") {
    Event::CoreNotifier::getInstance()->bind(_core.get());
    _core->bind(&_coreListener);
    g_globalInstance.VFS.bind(_config.get<std::string>("Filesystem.root"));
    g_globalInstance.VFS.setDirectories({
                                                {"shaders",  _config.get<std::string>("Filesystem.shaders")},
                                                {"models",   _config.get<std::string>("Filesystem.models")},
                                                {"textures", _config.get<std::string>("Filesystem.textures")},
                                                {"levels",   _config.get<std::string>("Filesystem.levels")}
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

    std::unordered_map<std::string, std::string> sources = g_globalInstance.VFS.from(
            "shaders").loadAllFromCurrentDirectory();

    _renderer.bindShader(Renderer::Shading::Type::PHONG, p_builder.createProgramFromShaders(
            s_builder.createFromFile(GL_VERTEX_SHADER, sources["phong_vert.glsl"]),
            s_builder.createFromFile(GL_FRAGMENT_SHADER, sources["phong_frag.glsl"])
    ));

    _renderer.bindShader(Renderer::Shading::Type::POST_PROCESS, p_builder.createProgramFromShaders(
            s_builder.createFromFile(GL_VERTEX_SHADER, sources["screen_vert.glsl"]),
            s_builder.createFromFile(GL_FRAGMENT_SHADER, sources["screen_frag.glsl"])
    ));

    _renderer.bindShader(Renderer::Shading::Type::PHONG_TEXTURED, p_builder.createProgramFromShaders(
            s_builder.createFromFile(GL_VERTEX_SHADER, sources["phong_map_vert.glsl"]),
            s_builder.createFromFile(GL_FRAGMENT_SHADER, sources["phong_map_frag.glsl"])
    ));

    _renderer.bindShader(Renderer::Shading::Type::SKYBOX, p_builder.createProgramFromShaders(
            s_builder.createFromFile(GL_VERTEX_SHADER, sources["skybox_vert.glsl"]),
            s_builder.createFromFile(GL_FRAGMENT_SHADER, sources["skybox_frag.glsl"])
    ));


}

void Kiwi::Engine::App::run() {
    /**
     * Render the current frame
     */
//    _renderer.render();

    ImGui::Render();


    /**
     * Render frame on screen
     */
    _graphics->swapBuffers();
}

bool Kiwi::Engine::App::ok() const {
    return _keepOpen;
}



