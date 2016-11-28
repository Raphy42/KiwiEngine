//
// Created by Raphaël Dantzer on 27/11/16.
//

#include "CoreNotifier.h"

using Kiwi::Engine::Event::CoreNotifier;

void Kiwi::Engine::Event::CoreNotifier::notify(Kiwi::Engine::Event::Type::CoreEvent &notification) {
    _dispatcher->update(notification);
}

void Kiwi::Engine::Event::CoreNotifier::bind(
        Kiwi::Engine::Event::Dispatcher<Kiwi::Engine::Event::Type::CoreEvent> *dispatcher) {
    _dispatcher = dispatcher;
}

void Kiwi::Engine::Event::CoreNotifier::unbind(void) {
    _dispatcher = nullptr;
}

Kiwi::Engine::Event::CoreNotifier *Kiwi::Engine::Event::CoreNotifier::getInstance(void) {
    if (!_instance)
        _instance = new CoreNotifier();
    return _instance;
}

