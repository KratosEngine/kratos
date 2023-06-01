
#pragma once

#include "runtime/core/ksstl/KSContainer.h"

namespace Kratos
{
    class KSString : public KSContainer<char>
    {
    public:
        enum
        {
            BUFFER_SIZE = 2048
        };
        KSString();
        KSString(const KS_TCHAR *String);
        KSString(const KSString &String);
        ~KSString();
        static KSString ms_StringNULL;
        static KS_TCHAR TempBuffer[BUFFER_SIZE];
        inline KS_TCHAR *GetBuffer() const
        {
            return m_pBuffer;
        }
        inline unsigned int GetLength() const
        {
            return (unsigned int)KSStrLen(m_pBuffer);
        }

    protected:
        KS_TCHAR *m_pBuffer;
    };
}