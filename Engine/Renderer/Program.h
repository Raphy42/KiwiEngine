//
// Created by Raphael DANTZER on 11/23/16.
//

#ifndef KIWIENGINE_PROGRAM_H
#define KIWIENGINE_PROGRAM_H

template<typename Bind>
class Program {
public:
    Program(Bind bind) : _bind(bind) {}

private:
    Program &operator=(const Program &rhs) {
        static_assert(this != &rhs, "cant self assign");
        *this->_bind = rhs._bind;
        return *this;
    }

    Bind _bind;
};

typedef Program<GLuint> GLProgram_t;

#endif //KIWIENGINE_PROGRAM_H
