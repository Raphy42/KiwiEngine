//
// Created by Raphaël Dantzer on 27/11/16.
//

#ifndef KIWIENGINE_CORENOTIFIER_H
#define KIWIENGINE_CORENOTIFIER_H

#include "Notifier.h"

namespace Kiwi {
    namespace Engine {
        namespace Event {
            class CoreNotifier : public Notifier<Type::CoreEvent> {
            public:
                CoreNotifier() : Notifier<Type::CoreEvent>() {}

                virtual void notify(Type::CoreEvent &notification) override;

                virtual void bind(Dispatcher<Type::CoreEvent> *dispatcher) override;

                virtual void unbind(void) override;

                static CoreNotifier *getInstance(void);

            private:
                static std::unique_ptr<CoreNotifier> _instance;
                Dispatcher<Type::CoreEvent> *_dispatcher;
            };
        }
    }
}


#endif //KIWIENGINE_CORENOTIFIER_H
