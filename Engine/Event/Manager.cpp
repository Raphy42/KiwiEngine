//
// Created by Raphael DANTZER on 11/24/16.
//

#include "Manager.h"

void Kiwi::Engine::Event::Manager::update(void) const {
    for ()
}

void Kiwi::Engine::Event::Manager::registerNotifier(Kiwi::Engine::Event::Notifier notifier, int channel) {
    _notifiers[channel] = notifier;
}

void Kiwi::Engine::Event::Manager::registerListener(Kiwi::Engine::Event::Listener listener, int channel) {
    _listeners[channel] = listener;
}
