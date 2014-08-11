#ifndef __HPP__CORE_COMPONENTTAG__
#define __HPP__CORE_COMPONENTTAG__

#include <bitset>

#include "config.hpp"

typedef std::bitset<MAX_COMPONENTS> ComponentBitset;

// Component tags are used to assign a unique bitmask and ID to every
// registered component type, so that they can be organized easily
template<class T>
class ComponentTag
{
    friend class ComponentTagManager;

    public:
        ComponentTag() {}
        ~ComponentTag() {}

        static ComponentBitset mask()
        {
            return m_mask;
        }

        static unsigned id()
        {
            return m_id;
        }

        operator ComponentBitset()
        {
            return m_mask;
        }

        operator unsigned()
        {
            return m_id;
        }

        operator bool()
        {
            return m_mask.any();
        }

    private:
        static unsigned m_id;
        static ComponentBitset m_mask;

};

template<class T>
ComponentBitset ComponentTag<T>::m_mask = 0;

template<class T>
unsigned ComponentTag<T>::m_id = 0;

#endif

