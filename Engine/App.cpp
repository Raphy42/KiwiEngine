//
// Created by Raphael DANTZER on 11/24/16.
//

#include "App.h"
#include "OpenglGraphicContext.h"


Kiwi::Engine::App::App() :
        _graphics(new OpenglGraphicContext()),
        _vfs(new Core::Filesystem::VirtualFilesystem),
        _hid(new GLFWDispatcher) {

}

Kiwi::Engine::App::~App() {

}

void Kiwi::Engine::App::start() {
    _graphics->PreInit();
    _graphics->Init();
    _graphics->PostInit();

    _graphics->getNotifier()->bind(_hid.get());
}

void Kiwi::Engine::App::run() const {
    _graphics->Clear();
    _graphics->Update();
    _graphics->Render();
}

bool Kiwi::Engine::App::ok() const {
    return _keepOpen;
}


