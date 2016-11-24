//
// Created by Raphael DANTZER on 11/24/16.
//

#include "Pool.h"

void Kiwi::Engine::Event::Pool::enqueue(Notification notification) {
    _notifs.push_back(notification);
}

void Kiwi::Engine::Event::Pool::erase() {
    _notifs.clear();
}

unsigned long Kiwi::Engine::Event::Pool::size() const {
    return _notifs.size();
}

const Kiwi::Engine::Event::Pool::NotificationPool &Kiwi::Engine::Event::Pool::get_notifs() const {
    return _notifs;
}
