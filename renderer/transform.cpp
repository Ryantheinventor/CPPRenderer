#include "transofrm.h"


namespace ryan 
{
	void transform::addChild(transform* newChild)
	{
		children.push_back(newChild);
	}

	void transform::removeChild(transform* child)
	{
		for (size_t i = 0; i < children.size(); ++i) 
		{
			if (children[i] == child) 
			{
				children.erase(children.begin() + i);
				break;
			}
		}
	}

	transform::transform()
	{
		localPos = vec3(0, 0, 0);
		localRot = quat(1, 0, 0, 0);
		localScl = vec3(1, 1, 1);

		parent = nullptr;
	}

	void transform::setParent(transform* newParent)
	{
		if (parent != nullptr) 
		{
			parent->removeChild(this);
			parent = nullptr;
		}
		parent = newParent;
		parent->addChild(this);
	}

	transform* transform::getParent() const
	{
		return parent;
	}

	transform* transform::getChildAtIndex(size_t index) const
	{
		return children[index];
	}

	size_t transform::getChildCount() const
	{
		return children.size();
	}

	mat4 transform::localMat() const
	{
		mat4 lM = identity<mat4>();
		lM *= translate(identity<mat4>(), localPos);
		lM *= toMat4(localRot);
		lM *= scale(identity<mat4>(), localScl);

		return lM;
	}

	mat4 transform::worldMat() const
	{
		if (parent == nullptr) 
		{
			return localMat();
		}
		else 
		{
			return parent->worldMat() * localMat();
		}
	}

	mat4 transform::localToWorldMatrix() const
	{
		if (parent == nullptr) 
		{
			return identity<mat4>();
		}
		else 
		{
			parent->worldMat();
		}
	}

	mat4 transform::worldToLocalMatrix() const
	{
		return inverse(localToWorldMatrix());
	}
}