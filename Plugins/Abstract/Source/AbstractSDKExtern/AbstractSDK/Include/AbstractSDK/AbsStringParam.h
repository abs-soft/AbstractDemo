// Copyright 2023 Abstract Software, Inc.

#pragma once

#include "AbstractSDKCommon.h"

namespace AbstractSDK
{
    class AbsString;
    class ABSTRACT_SDK_API AbsStringParam
    {
    public:
        AbsStringParam();
        AbsStringParam(const char* data);
        AbsStringParam(const char* data, std::size_t size);
        AbsStringParam(const std::string& str);
        AbsStringParam(const AbsStringParam& rhs);

        AbsKey ToKey() const;
        const AbsString& ToString() const;

    private:
        AbsKey m_key;
    };
}
