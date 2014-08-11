#ifndef __HPP__CORE_COMPONENTTAGMANAGER__
#define __HPP__CORE_COMPONENTTAGMANAGER__

#include <stdexcept>
#include <boost/type_traits/is_base_of.hpp>

#include "config.hpp"
#include "ComponentTag.hpp"

class Component;

// The component tag manager is used to assign tags to component types by
// registering them. Every component used by the engine must first be
// initialized by the component tag manager
class ComponentTagManager
{
    public:
        template<typename T>
        static bool registerComponent() throw(std::invalid_argument, std::length_error)
        {
            if (!ComponentTag<T>())
            {
                if (!boost::is_base_of<Component, T>::value)
                    throw std::invalid_argument("Cannot register component: Type is not a subclass of Component");

                if (m_nextId > MAX_COMPONENTS)
                    throw std::length_error("Cannot register component: Maximum amount of components reached");
                
                
                ComponentTag<T>::m_id = m_nextId;
                ComponentTag<T>::m_mask.set(m_nextId);
                m_nextId++;
                
                return true;
            }
            
            return false;
        }
        
        static unsigned count();

    private:
        ComponentTagManager();
        ~ComponentTagManager();
        
        static unsigned m_nextId;
};

#endif

