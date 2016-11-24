//
// Created by Raphael DANTZER on 11/24/16.
//

#include "App.h"
#include "OpenglGraphicContext.h"


Kiwi::Engine::App::App() :
        _graphics(new OpenglGraphicContext()),
        _vfs(new Core::Filesystem::VirtualFilesystem) {

}

Kiwi::Engine::App::~App() {

}

void Kiwi::Engine::App::start() const {
    _graphics->PreInit();
    _graphics->Init();
    _graphics->PostInit();
}

