//
// Created by Raphael DANTZER on 12/7/16.
//

#ifndef KIWIENGINE_ACTUATOR_H
#define KIWIENGINE_ACTUATOR_H

#include <glm/vec3.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "../GUI/Easing.h"
#include <chrono>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>

/**
 * Constructs the transform matrix, which is then used by its bound entity
 */

namespace Kiwi { namespace Engine { namespace Scene {
            class Actuator {
            public:
                Actuator();

                virtual ~Actuator() {};

                Actuator        *position(glm::vec3 pos);
                Actuator        *setScale(glm::vec3 scale);
                Actuator        *rotate(glm::vec3 rotation, float angle);
                Actuator        *ease(GUI::Easing ease, float duration);

                glm::mat4            update(void);

            private:
                friend class boost::serialization::access;

                template <class Archive>
                void serialize(Archive &ar, const unsigned int flags) {
                    ar & BOOST_SERIALIZATION_NVP(_pos);
                    ar & BOOST_SERIALIZATION_NVP(_scale);
                    ar & BOOST_SERIALIZATION_NVP(_rotation);
                    ar & BOOST_SERIALIZATION_NVP(_transform);
                    ar & BOOST_SERIALIZATION_NVP(_angle);
                }

                glm::vec3                                           _pos;
                glm::vec3                                           _scale;
                glm::vec3                                           _rotation;
                glm::mat4                                           _transform;
                float                                               _angle;
                float                                               _duration;

                std::chrono::time_point<std::chrono::system_clock>  _start;
                std::chrono::time_point<std::chrono::system_clock>  _end;
                std::chrono::duration<float>                        _elapsedSeconds;
            };
        }
    }
}


#endif //KIWIENGINE_ACTUATOR_H
