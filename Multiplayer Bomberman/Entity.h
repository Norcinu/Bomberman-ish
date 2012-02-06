#ifndef SEG_ENTITY_H
#define SEG_ENTITY_H

#include <cassert>
#include <vector>
#include "Components.h"

class Entity
{
public:
	Entity(void)
	{
	}

	Entity(int size) 
    {
		components_.reserve(size);
	}

	~Entity(void)
	{
		clearAllComponents();
	}

	void addComponent(Component * comp)
	{
		assert(comp != nullptr);
		components_.push_back(comp);
	}

	void removeComponent(const int index)
	{
		assert(index > 0 && index < components_.size());
		components_.erase(components_.begin() + index);
	}
        
	void clearAllComponents()
	{
		for (auto itor = components_.begin(); itor != components_.end(); ++itor)
		{
			delete *itor;
		}

		components_.clear();
	}

    //template <typename wantedType>
    //Component* getComponent<wantedType>()
    //{
    //    auto temp = std::find_if()
    //}

private:
	std::vector<Component*> components_;
};

#endif
