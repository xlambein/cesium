#ifndef __HPP__CORE_ENTITYMANAGER__
#define __HPP__CORE_ENTITYMANAGER__

#include <vector>
#include <bitset>
#include <stdexcept>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/shared_ptr.hpp>

#include "config.hpp"
#include "Component.hpp"
#include "ComponentTag.hpp"
#include "System.hpp"

class EntityManager
{
    public:
        EntityManager();
        ~EntityManager();
        
        // Fills m_components with registered component types. init() is called
        // by the contructor
        void init();
        
        // Clears m_components and m_entities. init() must be called after
        // clear() in order to keep using the EntityManager
        void clear();
        
        // Adds an entity in m_entities and an empty component per component
        // type in m_components
        unsigned addEntity();
        
        // Removes entity of ID id from m_entities and from each component
        // type of m_components. Does not preserver the IDs of entities
        void removeEntity(unsigned id) throw(std::out_of_range);

        // Gets the component T attached to an entity
        template<typename T>
        boost::shared_ptr<T> component(unsigned entity) throw(std::out_of_range, std::invalid_argument)
        {
            if (entity >= m_entities.size())
                throw std::out_of_range("Cannot get component: Entity ID is out of range");
            
            if (!ComponentTag<T>())
                throw std::invalid_argument("Cannot get component: Component type is not registered");

            unsigned id = ComponentTag<T>::id();
            return boost::static_pointer_cast<T>(m_components[id][entity]);
        }

        // Attached a component to an entity
        template<typename T>
        void attach(unsigned entity, T * component) throw(std::out_of_range, std::invalid_argument)
        {
            if (entity >= m_entities.size())
                throw std::out_of_range("Cannot attach component: Entity ID is out of range");

            if (!ComponentTag<T>())
                throw std::invalid_argument("Cannot attach component: Component type is not registered");
            
            unsigned id = ComponentTag<T>::id();
            m_components[id][entity] = boost::shared_ptr<Component>(static_cast<Component *>(component));
            m_entities[entity] |= ComponentTag<T>();
        }

        // Detaches a component from an entity
        template<typename T>
        void detach(unsigned entity) throw(std::out_of_range, std::invalid_argument)
        {
            if (entity >= m_entities.size())
                throw std::out_of_range("Cannot detach component: Entity ID is out of range");
        
            if (!ComponentTag<T>())
                throw std::invalid_argument("Cannot detach component: Component is not registered");

            unsigned id = ComponentTag<T>::id();
            delete m_components[id][entity];
            m_entities[entity] &= ~ComponentTag<T>();
        }

    private:
        // The components, organized by type and then by entity
        std::vector<std::vector< boost::shared_ptr<Component> > > m_components;
        
        // The entities' bitsets, which are used to tell whether a particular
        // entity has some component attached to it
        // Warning: since removing entities does not preserve the IDs, these
        // should be considered volatile and should not be kept
        // TODO: change system so that you can keep an entity's ID
        std::vector< ComponentBitset > m_entities;
};

#endif

