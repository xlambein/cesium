#include <exception>
#include <iostream>

#include "Core/EntityManager.hpp"
#include "Core/ComponentTagManager.hpp"
#include "Components/Transform.hpp"

int main()
{
    // We register the component Transform so that it can be recognized by
    // the engine
    ComponentTagManager::registerComponent<Transform>();
    
    EntityManager eMgr;

    // Entities are just IDs with components attached to them, so an int
    // is enough to stock an entity
    // TODO: create an Entity class to interface with the EntityManager
    int entity = eMgr.addEntity();
    eMgr.attach(entity, new Transform(50.f, 25.f, -45.f));
    
    // We can recover the component of an entity via C++ templates
    Transform & tr = *eMgr.component<Transform>(entity);
    std::cout << tr.x << ';' << tr.y << ';' << tr.angle << std::endl;

    return 0;
}

