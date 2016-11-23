//
// Created by Raphael DANTZER on 11/22/16.
//

#ifndef KIWIENGINE_INITIALIZABLE_H
#define KIWIENGINE_INITIALIZABLE_H

namespace Kiwi { namespace Core {
class Initializable {
public:
    virtual ~Initializable() = 0;

    typedef bool            *(Initializable::*IniterHandle)(void) const;
    virtual void            bind(std::vector<IniterHandle> initers) = 0;

protected:
    virtual void            PreInit() = 0;
    virtual void            Init() = 0;
    virtual void            PostInit() = 0;

private:
    IniterHandle            _pre_initer;
    IniterHandle            _initer;
    IniterHandle            _post_initer;

};
    }
}

#endif //KIWIENGINE_INITIALIZABLE_H
