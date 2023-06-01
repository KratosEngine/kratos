
#include "runtime/core/ksstl/KSString.h"

namespace Kratos
{
    KSString KSString::ms_StringNULL;
    KS_TCHAR KSString::TempBuffer[BUFFER_SIZE] = {0};

    KSString::KSString()
    {
        m_pBuffer = nullptr;
        m_pBuffer = KS_NEW KS_TCHAR[1];
        KSMAC_ASSERT(m_pBuffer);
        m_pBuffer[0] = _T('\0');
    }

    KSString::KSString(const KS_TCHAR *String)
    {
        KSMAC_ASSERT(String);
        m_pBuffer = NULL;
        if (String)
        {
            unsigned int uiLength = (unsigned int)KSStrLen(String);
            m_pBuffer = KS_NEW KS_TCHAR[uiLength + 1];
            KSMAC_ASSERT(m_pBuffer);

            KSStrCopy(m_pBuffer, uiLength + 1, String);
        }
        else
        {
            m_pBuffer = KS_NEW KS_TCHAR[1];
            KSMAC_ASSERT(m_pBuffer);
            m_pBuffer[0] = _T('\0');
        }
    }
    KSString::KSString(const KSString &String)
    {
        m_pBuffer = NULL;
        unsigned int uiLength = String.GetLength();
        m_pBuffer = KS_NEW KS_TCHAR[uiLength + 1];
        KSMAC_ASSERT(m_pBuffer);

        KSStrCopy(m_pBuffer, uiLength + 1, String.GetBuffer());
    }
    KSString::~KSString()
    {

        KSMAC_DELETEA(m_pBuffer);
    }

}