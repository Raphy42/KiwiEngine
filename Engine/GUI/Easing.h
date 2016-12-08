//
// Created by Raphael DANTZER on 12/8/16.
//

#ifndef KIWIENGINE_EASING_H
#define KIWIENGINE_EASING_H


/**
 * https://github.com/jesusgollonet/ofpennereasing/PennerEasing
 */
#include <cmath>

namespace Kiwi { namespace Engine { namespace GUI {
            class Easing {
                /**
                 * @param t time
                 * @param b beginning
                 * @param c change
                 * @param d duration
                 * @return
                 */
            public:
                virtual float easeIn(float t, float b, float c, float d) = 0;
                virtual float easeOut(float t, float b, float c, float d) = 0;
                virtual float easeInOut(float t, float b, float c, float d) = 0;
            };

            class Bounce : public Easing {

                virtual float easeOut(float t, float b, float c, float d) override {
                    float postFix;

                    if ((t /= d) < (1 / 2.75f)) {
                        return c * (7.5625f * t * t) + b;
                    } else if (t < (2 / 2.75f)) {
                        postFix = t -= (1.5f / 2.75f);
                        return c * (7.5625f * (postFix) * t + .75f) + b;
                    } else if (t < (2.5 / 2.75)) {
                        postFix = t -= (2.25f / 2.75f);
                        return c * (7.5625f * (postFix) * t + .9375f) + b;
                    } else {
                        postFix = t -= (2.625f / 2.75f);
                        return c * (7.5625f * (postFix) * t + .984375f) + b;
                    }
                }

                virtual float easeInOut(float t, float b, float c, float d) override {
                    if (t < d / 2)
                        return easeIn(t * 2, 0, c, d) * .5f + b;
                    else
                        return easeOut(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
                }

            public:
                virtual float easeIn(float t, float b, float c, float d) override {
                    return c - easeOut(d - t, 0, c, d) + b;
                }
            };

            class Elastic : public Easing {
                virtual float easeIn(float t, float b, float c, float d) override {
                    if (!t)
                        return b;
                    if ((t /= d) == 1)
                        return b + c;
                    float p = d * .3f;
                    float a = c;
                    float s = p / 4;
                    float postFix = a * powf(2, 10 * (t -= 1));

                    return -(postFix * sinf((t * d - s) * (2 * (float)M_PI) / p)) + b;
                }

                virtual float easeOut(float t, float b, float c, float d) override {
                    if (!t)
                        return b;
                    if ((t /= d) ==1)
                        return b + c;
                    float p = d * .3f;
                    float a = c ;
                    float s = p / 4;

                    return (a * powf(2, -10 * t) * sinf((t * d - s) * (2 * (float)M_PI) / p) + c + b);
                }

                virtual float easeInOut(float t, float b, float c, float d) override {
                    if (!t)
                        return b;
                    if ((t /= d / 2) == 2)
                        return b + c;
                    float p = d * (.3f * 1.5f);
                    float a = c;
                    float s = p / 4;

                    if (t < 1) {
                        float postFix =a * powf(2, 10 * (t -= 1));

                        return -.5f * (postFix * sinf((t * d - s) * (2 * (float)M_PI) / p)) + b;
                    }
                    float postFix = a * powf(2, -10 * (t -= 1));

                    return postFix * sinf((t * d - s) * (2 * (float)M_PI) / p ) * .5f + c + b;
                }
            };

            class Linear : public Easing {
                virtual float easeIn(float t, float b, float c, float d) override {
                    return c * t / d + b;
                }

                virtual float easeOut(float t, float b, float c, float d) override {
                    return c * t / d + b;
                }

                virtual float easeInOut(float t, float b, float c, float d) override {
                    return c * t / d + b;
                }
            };
        }
    }
}


#endif //KIWIENGINE_EASING_H
