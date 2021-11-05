#pragma once
#include "glm/glm.hpp"
//#include "glm/ext.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"
#include <vector>
using namespace glm;

namespace ryan 
{
    class transform
    {
    private:
        std::vector<transform*> children;
        transform* parent;
        void addChild(transform* newChild);
        void removeChild(transform* child);
    public:
        vec3 localPos;
        quat localRot;
        vec3 localScl;

    public:
        transform();

        void setParent(transform* newParent);
        transform* getParent() const;

        transform* getChildAtIndex(size_t index) const;
        size_t getChildCount() const;

        mat4 localMat() const;
        mat4 worldMat() const;

        mat4 localToWorldMatrix() const;
        mat4 worldToLocalMatrix() const;

    };
}