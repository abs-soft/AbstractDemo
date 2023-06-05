// Copyright 2023 Abstract Software, Inc.

#pragma once

#include "AbstractSDKCommon.h"

namespace AbstractSDK
{
    class AbsLibrary;
}

namespace AbstractSDK
{
    struct AbsClassInternal;
    class ABSTRACT_SDK_API AbsClass
    {
    public:
        AbsClass();
        AbsClass(const AbsClass& rhs);
        AbsClass(AbsClass&& rref) noexcept;

        const AbsLibrary* GetSourceLib() const;

        std::size_t GetStateDataSizeRequirement() const;
        void* GetStateDataAddr() const;
        void SetStateDataAddr(void* state);

        template<typename DerivedAbsClass, typename ReturnType, typename ... InputTypes>
        ReturnType Invoke(AbsKey key, DerivedAbsClass& absClass, InputTypes ... inputs) const
        {
            if (Validate())
            {
                typedef ReturnType(*InternalFunctionPtr)(DerivedAbsClass&, InputTypes ...);
                AbsFunc queryResult = LibQuery(key);
                if (queryResult)
                {
#pragma warning(disable:4191)
                    return reinterpret_cast<InternalFunctionPtr>(queryResult)(absClass, inputs ...);
#pragma warning(default:4191)
                }
            }

            return ReturnType();
        }

        template<typename T>
        bool SetClassVar(AbsStringParam name, T value)
        {
            if (Validate())
            {
                typedef void* (*InternalFunctionPtr)(void* state);
                AbsFunc queryResult = LibQueryBlk(AbsValueTypeKey<T>(), name.ToKey());
                if (queryResult)
                {
#pragma warning(disable:4191)
                    * reinterpret_cast<T*>(reinterpret_cast<InternalFunctionPtr>(queryResult)(GetStateDataAddr())) = value;
#pragma warning(default:4191)
                    return true;
                }
            }

            return false;
        }

        template<typename T>
        T* GetClassVar(AbsStringParam name) const
        {
            if (Validate())
            {
                typedef void* (*InternalFunctionPtr)(void* state);
                AbsFunc queryResult = LibQueryBlk(AbsValueTypeKey<T>(), name.ToKey());
                if (queryResult)
                {
#pragma warning(disable:4191)
                    return reinterpret_cast<T*>(reinterpret_cast<InternalFunctionPtr>(queryResult)(GetStateDataAddr()));
#pragma warning(default:4191)
                }
            }

            return nullptr;
        }

    protected:
        void Load(const AbsLibrary& sourceLib, AbsKey classKey, AbsKey definitionKey);
        bool Validate() const;

    private:
        AbsFunc LibQuery(AbsKey key) const;
        AbsFunc LibQueryBlk(AbsKey type, AbsKey name) const;

        const AbsLibrary* m_sourceLib;

        AbsKey m_classKey;
        AbsKey m_definitionKey;
        AbsIndex m_index;

        void* m_state;
    };
}
