#include "EntityManager.hpp"
#include "ComponentTagManager.hpp"

EntityManager::EntityManager()
{
    init();
}

EntityManager::~EntityManager()
{
}

void EntityManager::init()
{
    m_components.resize(
        ComponentTagManager::count(),
        std::vector< boost::shared_ptr<Component> >()
    );
}

void EntityManager::clear()
{
    m_components.clear();
    m_entities.clear();
}

unsigned EntityManager::addEntity()
{
    m_entities.push_back(0);
   
    std::vector<std::vector< boost::shared_ptr<Component> > >::iterator it;
    for (it = m_components.begin(); it != m_components.end(); ++it)
        it->push_back(boost::shared_ptr<Component>());

    return m_entities.size()-1;
}

void EntityManager::removeEntity(unsigned id) throw(std::out_of_range)
{
    if (id >= m_entities.size())
        throw std::out_of_range("Entity ID out of range");

    // Switch entity with back and pop back
    m_entities[id] = m_entities.back();
    m_entities.pop_back();

    std::vector<std::vector< boost::shared_ptr<Component> > >::iterator it;
    for (it = m_components.begin(); it != m_components.end(); ++it)
    {
        (*it)[id] = it->back();
        it->pop_back();
    }
}

