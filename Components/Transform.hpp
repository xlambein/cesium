#ifndef __HPP__COMPONENTS_TRANSFORM__
#define __HPP__COMPONENTS_TRANSFORM__

#include "../Core/Component.hpp"

class Transform : public Component
{
    public:
        Transform();
        Transform(float x_, float y_, float angle_);
        virtual ~Transform();
        
        float x;
        float y;
        float angle;
        
};

#endif

