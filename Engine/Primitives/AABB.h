//
// Created by Raphael DANTZER on 12/7/16.
//

#ifndef KIWIENGINE_AABB_H
#define KIWIENGINE_AABB_H

#include <glm/vec3.hpp>

namespace Kiwi {
    namespace Engine {
        namespace Primitive {
            class AABB {
            public:
                AABB();
                AABB(const glm::vec3 &center, float radius);
                AABB(const glm::vec3 &min, const glm::vec3 &max);
                AABB(const AABB &src);

                ~AABB();

                enum class Intersection : int {
                    INSIDE,
                    INTERSECT,
                    OUTSIDE
                };

                Intersection    intersect(const AABB &box) const;

            protected:
                glm::vec3   _min;
                glm::vec3   _max;

            private:
                void extend(float value);
                void extend(const glm::vec3 &v);
                void extend(const glm::vec3 &v, float radius);

                bool isDirty() const;

            };
        }
    }
}

#endif //KIWIENGINE_AABB_H
