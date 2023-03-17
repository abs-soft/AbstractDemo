// Copyright 2023 Abstract Software, Inc.

#pragma once

#include "AbstractSDKCommon.h"

namespace AbstractSDK
{
    class ABSTRACT_SDK_API AbsString
    {
    public:
        AbsString();
        AbsString(const char* data);
        AbsString(const char* data, std::size_t size);
        AbsString(const AbsString& rhs);
        AbsString(AbsString&& rref);
        ~AbsString();

        char* data() const;
        std::size_t size() const;

        AbsStringParam ToStringParam() const;

        AbsString operator+(const AbsString& rhs) const;
        AbsString& operator=(const AbsString& rhs);
        AbsString& operator=(AbsString&& rref);
        AbsString& operator+=(const AbsString& rhs);

    private:
        std::size_t m_size;
        char* m_data;
    };
}
