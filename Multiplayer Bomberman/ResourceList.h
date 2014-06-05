#ifndef RESOURCE_LIST_H
#define RESOURCE_LIST_H

#include <iostream>
#include <vector>

struct LevelResources
{
    std::string level_name;
    std::vector<std::string> resources;
    
    LevelResources()
    {
        level_name = "Default Level";
    }
    
    LevelResources(const int num)
    {
        level_name = "Default Name";
        resources.reserve(num);
    }
};


class ResourceList
{
public:
    ResourceList() {}
    ~ResourceList() {}
    
private:
    std::vector<LevelResources*> levels;
};


#endif
