#include "EntityManager.hpp"

EntityManager::EntityManager() :
    mNextId(0)
{
}

EntityManager::~EntityManager()
{
}
        
unsigned EntityManager::addEntity()
{
    mEntities.push_back(0);
   
    std::vector<std::vector< boost::shared_ptr<Component> > >::iterator it;
    for (it = mComponents.begin(); it != mComponents.end(); ++it)
        it->push_back(boost::shared_ptr<Component>());

    return mEntities.size()-1;
}

void EntityManager::removeEntity(unsigned id) throw(std::out_of_range)
{
    if (id >= mEntities.size())
        throw std::out_of_range("Entity ID out of range");

    mEntities[id] = mEntities.back();
    mEntities.pop_back();

    std::vector<std::vector< boost::shared_ptr<Component> > >::iterator it;
    for (it = mComponents.begin(); it != mComponents.end(); ++it)
    {
        (*it)[id] = it->back();
        it->pop_back();
    }
}

