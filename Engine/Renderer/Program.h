//
// Created by Raphael DANTZER on 11/23/16.
//

#ifndef KIWIENGINE_PROGRAM_H
#define KIWIENGINE_PROGRAM_H

template<typename Bind>
class Program {
public:
    Program() {}
    Program(Bind bind) : _bind(bind) {}

    Bind get(void) const {
        return _bind;
    }

private:
    Bind _bind;
};

typedef Program<GLuint> GLProgram;

#endif //KIWIENGINE_PROGRAM_H
