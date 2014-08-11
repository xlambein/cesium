#ifndef __HPP__CORE_ENTITYMANAGER__
#define __HPP__CORE_ENTITYMANAGER__

#include <map>
#include <vector>
#include <bitset>
#include <typeinfo>
#include <stdexcept>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_base_of.hpp>

//#include <iostream>

#include "config.hpp"
#include "Component.hpp"
#include "System.hpp"

class EntityManager
{
    public:
        EntityManager();
        ~EntityManager();
        
        unsigned addEntity();
        void removeEntity(unsigned id) throw(std::out_of_range);

        template<typename T>
        boost::shared_ptr<T> component(unsigned entity) throw(std::out_of_range, std::invalid_argument)
        {
            if (entity >= mEntities.size())
                throw std::out_of_range("Cannot get component: Entity ID is out of range");
            
            if (!Mask<T>())
                throw std::invalid_argument("Cannot get component: Component type is not registered");

            unsigned id = Mask<T>::id();
            return boost::static_pointer_cast<T>(mComponents[id][entity]);
        } 
        
        template<typename T>
        void registerComponent() throw(std::invalid_argument, std::length_error)
        {
            if (!Mask<T>())
            {
                if (!boost::is_base_of<Component, T>::value)
                    throw std::invalid_argument("Cannot register component: Type is not a subclass of Component");

                if (mNextId > MAX_COMPONENTS)
                    throw std::length_error("Cannot register component: Maximum amount of components reached");
                
                Mask<T>::init(mNextId);
                mNextId++;

                mComponents.push_back(std::vector< boost::shared_ptr<Component> >(mEntities.size()));                 
            }
        }

        template<typename T>
        void attach(unsigned entity, T * component) throw(std::out_of_range, std::invalid_argument)
        {
            if (entity >= mEntities.size())
                throw std::out_of_range("Cannot attach component: Entity ID is out of range");
            
            // if (!boost::is_base_of<Component, T>::value)
            //     throw std::invalid_argument("Type is not a subclass of Component");

            if (!Mask<T>())
                throw std::invalid_argument("Cannot attach component: Component type is not registered");
            
            // std::map<std::type_info, size_t>::iterator it = mComponentTypes.find(type); 
            // if (it == mComponentTypes.end())
            //     throw std::invalid_argument("Argument is not a registered Component");
            
            unsigned id = Mask<T>::id();
            mComponents[id][entity] = boost::shared_ptr<Component>(static_cast<Component *>(component));
            mEntities[entity] |= Mask<T>();
        }

        template<typename T>
        void detach(unsigned entity) throw(std::out_of_range, std::invalid_argument)
        {
            if (entity >= mEntities.size())
                throw std::out_of_range("Cannot detach component: Entity ID is out of range");
        
            if (!Mask<T>())
                throw std::invalid_argument("Cannot detach component: Component is not registered");
            // std::map<std::type_info, size_t>::iterator it = mComponentTypes.find(type); 
            // if (it == mComponentTypes.end())
            //     throw std::invalid_argument("Argument is not a registered Component");

            // if (mEntities[id] & Mask<T>())
            //     mComponents[type][id] = 0;

            unsigned id = Mask<T>::id();
            delete mComponents[id][entity];
            mEntities[entity] &= ~Mask<T>();
        }

    private:
        unsigned mNextId;
        std::vector<std::vector< boost::shared_ptr<Component> > > mComponents;
        //boost::ptr_vector<System> mSystems;
        std::vector< ComponentBitset > mEntities;
};

#endif

