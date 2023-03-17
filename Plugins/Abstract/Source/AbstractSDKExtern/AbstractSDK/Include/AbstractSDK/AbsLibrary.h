// Copyright 2023 Abstract Software, Inc.

#pragma once

#include "AbstractSDKCommon.h"

namespace AbstractSDK
{
    class AbsLibraryInternal;
    class ABSTRACT_SDK_API AbsLibrary
    {
    public:
        AbsLibrary();
        AbsLibrary(const AbsLibrary& rhs) = delete;
        AbsLibrary(AbsLibrary&& rref) = delete;
        ~AbsLibrary();

        bool Load(AbsStringParam exportedFilepath);
        bool Reload(AbsStringParam exportedFilepath);
        void Unload();
        bool Loaded() const;

        AbsLibraryInternal* Get() const;

    private:
        bool LoadInternal(AbsStringParam exportedFilepath, AbsLibraryInternal& target);

        AbsLibraryInternal* m_internal;
    };
}
