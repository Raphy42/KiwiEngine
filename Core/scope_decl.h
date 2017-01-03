//
// Created by Raphael DANTZER on 1/3/17.
//

#ifndef KIWIENGINE_SCOPE_DECL_H
#define KIWIENGINE_SCOPE_DECL_H

namespace Kiwi {
    namespace Core {
        template<class T, class U>
        struct Scope {
        public:
            explicit Scope(const T &t, const U &u) : _t(t), _u(u) { _t(); }
            ~Scope() { _u(); }

        private:
            T       _t;
            U       _u;
        };
    }
}

#endif //KIWIENGINE_SCOPE_DECL_H
