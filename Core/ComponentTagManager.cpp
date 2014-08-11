#include "ComponentTagManager.hpp"
        
unsigned ComponentTagManager::m_nextId = 0;

ComponentTagManager::ComponentTagManager()
{
}

ComponentTagManager::~ComponentTagManager()
{
}
        
unsigned ComponentTagManager::count()
{
    return m_nextId;
}
