//
// Created by Raphael DANTZER on 12/17/16.
//

#ifndef KIWIENGINE_SERIALIZATION_H
#define KIWIENGINE_SERIALIZATION_H

#include <glm/common.hpp>
#include <glm/detail/type_mat4x4.hpp>

namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive &ar, glm::mat4 &transform, const unsigned int flags) {
            ar & transform[0];
            ar & transform[1];
            ar & transform[2];
            ar & transform[3];
        }

        template<class Archive>
        void serialize(Archive &ar, glm::vec3 &vec, const unsigned int flags) {
            ar & vec.x;
            ar & vec.y;
            ar & vec.z;
        }

        template<class Archive>
        void serialize(Archive &ar, glm::vec4 &vec, const unsigned int flags) {
            ar & vec.x;
            ar & vec.y;
            ar & vec.z;
            ar & vec.w;
        }

        template<class Archive>
        void serialize(Archive &ar, glm::vec2 &vec, const unsigned int flags) {
            ar & vec.x;
            ar & vec.y;
        }
    }
}

#endif //KIWIENGINE_SERIALIZATION_H
