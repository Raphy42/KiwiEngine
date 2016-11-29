//
// Created by Raphael DANTZER on 11/29/16.
//

#ifndef KIWIENGINE_MANAGER_H
#define KIWIENGINE_MANAGER_H

#include <memory>

namespace Kiwi {
    namespace Engine {
        namespace Event {
        class Manager {
        public:
            Manager() {};

            Manager     *getInstance() {
                if (_instance == nullptr)
                    _instance = std::unique_ptr<Manager>(new Manager);
                return _instance.get();
            }


        private:
            static std::unique_ptr<Manager>                 _instance;
            std::unordered_map<std::string, Dispatcher>     _dispatchers;
        };
        }
    }
}

#endif //KIWIENGINE_MANAGER_H
