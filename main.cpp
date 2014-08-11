#include <exception>
#include <iostream>

#include "Components/Transform.hpp"

int main()
{
    EntityManager eMgr;
    // We register the component Transform so that it can be recognized by
    // the entity manager
    eMgr.registerComponent<Transform>();

    // Entities are just IDs with components attached to it.
    // When we "create" an entity, we simply ask the manager for a free ID
    // to which we can add components. If we don't add any component to
    // the entity, the ID stays free
    int entity = eMgr.addEntity();
    eMgr.attach(entity, new Transform(50.f, 25.f, -45.f));
    
    // We can recover the component of an entity via C++ templates
    Transform & tr = *eMgr.component<Transform>(entity);
    std::cout << tr.x << ';' << tr.y << ';' << tr.angle << std::endl;

    return 0;
}

