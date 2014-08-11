#ifndef __HPP__CORE_COMPONENT__
#define __HPP__CORE_COMPONENT__

#include <bitset>
#include <stdexcept>

#include "config.hpp"

typedef std::bitset<MAX_COMPONENTS> ComponentBitset;

template<class T>
class Mask
{
    friend class EntityManager;

    public:
        Mask() {}
        ~Mask() {}

        static ComponentBitset mask()
        {
            return mMask;
        }

        static unsigned id()
        {
            return mId;
        }

        operator ComponentBitset()
        {
            return mMask;
        }

        operator unsigned()
        {
            return mId;
        }

        operator bool()
        {
            return mMask.any();
        }

    private:
        static void init(unsigned id)
        {
            if (!mId)
            {
                mId = id;
                mMask.set(id);
            }
        }

        static unsigned mId;
        static ComponentBitset mMask;

};

class Component
{
    public:
        Component();
        virtual ~Component();

};

template<class T>
ComponentBitset Mask<T>::mMask = 0;
template<class T>
unsigned Mask<T>::mId = 0;

#endif

