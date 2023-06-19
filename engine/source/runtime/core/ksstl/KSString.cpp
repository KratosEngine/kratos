
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
#if KS_PLATFORM_WIN
        m_pBuffer[0] = _T('\0');
#else
        m_pBuffer[0] = '\0';
#endif
    }

    KSString::KSString(const KS_TCHAR *String)
    {
        KSMAC_ASSERT(String);
        m_pBuffer = nullptr;
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
#if KS_PLATFORM_WIN
            m_pBuffer[0] = _T('\0');
#else
            m_pBuffer[0] = '\0';
#endif
        }
    }
    KSString::KSString(const KSString &String)
    {
        m_pBuffer = nullptr;
        unsigned int uiLength = String.GetLength();
        m_pBuffer = KS_NEW KS_TCHAR[uiLength + 1];
        KSMAC_ASSERT(m_pBuffer);

        KSStrCopy(m_pBuffer, uiLength + 1, String.GetBuffer());
    }
    KSString::~KSString()
    {
        KSMAC_DELETEA(m_pBuffer);
    }

    void KSString::SetTCHARBufferNum(unsigned int uiLength)
    {
        KSMAC_ASSERT(m_pBuffer);
        m_pBuffer = KS_NEW KS_TCHAR[uiLength + 1];
#if KS_PLATFORM_WIN
        m_pBuffer[uiLength] = _T('\0');
#else
        m_pBuffer[uiLength] = '\0';
#endif
    }

    void KSString::Clear()
    {
        KSMAC_ASSERT(m_pBuffer);
        m_pBuffer = KS_NEW KS_TCHAR[1];
        KSMAC_DELETEA(m_pBuffer);
#if KS_PLATFORM_WIN
        m_pBuffer[0] = _T('\0');
#else
        m_pBuffer[0] = '\0';
#endif
    }

    KSString &KSString::operator=(const KSString &String)
    {
        KSMAC_DELETEA(m_pBuffer);
        unsigned int uiLength = String.GetLength();
        m_pBuffer = KS_NEW KS_TCHAR[uiLength + 1];
        KSMAC_ASSERT(m_pBuffer);
        KSStrCopy(m_pBuffer, uiLength + 1, String.GetBuffer());
        return *this;
    }

    KSString &KSString::operator=(const KS_TCHAR *String)
    {
        KSMAC_DELETEA(m_pBuffer);
        if (String)
        {
            unsigned int uiLength = (unsigned int)KSStrLen(String);
            m_pBuffer = KS_NEW KS_TCHAR[uiLength + 1];
            KSMAC_ASSERT(m_pBuffer);

            KSStrCopy(m_pBuffer, uiLength + 1, String);
        }
        else
        {
            KSString();
        }
        return *this;
    }

    KS_TCHAR &KSString::operator[](unsigned int i)
    {
        return m_pBuffer[i];
    }

    const KSString &KSString::operator+=(const KSString &String)
    {
        unsigned int uiLength1 = GetLength();
        unsigned int uiLength2 = String.GetLength();
        if (!uiLength1)
        {
            *this = String;
            return *this;
        }
        else if (!uiLength2)
            return *this;
        else
        {
            KS_TCHAR *pBuffer = nullptr;
            unsigned int uiLength = uiLength2 + uiLength1 + 1;
            pBuffer = KS_NEW KS_TCHAR[uiLength];
            KSMAC_ASSERT(pBuffer);

            KSStrCopy(pBuffer, uiLength, GetBuffer());
            KSStrcat(pBuffer, uiLength, String.GetBuffer());

            KSMAC_DELETEA(m_pBuffer);
            m_pBuffer = pBuffer;
            return *this;
        }
    }
    const KSString &KSString::operator+=(const KS_TCHAR *String)
    {
        unsigned int uiLength1 = GetLength();
        unsigned int uiLength2 = 0;
        if (String)
        {
            uiLength2 = (unsigned int)KSStrLen(String);
        }
        if (!uiLength1)
        {
            *this = String;
            return *this;
        }
        else if (!uiLength2)
            return *this;
        else
        {
            KS_TCHAR *pBuffer = nullptr;
            unsigned int uiLength = uiLength2 + uiLength1 + 1;
            pBuffer = KS_NEW KS_TCHAR[uiLength];
            KSMAC_ASSERT(pBuffer);

            KSStrCopy(pBuffer, uiLength, GetBuffer());
            KSStrcat(pBuffer, uiLength, String);

            KSMAC_DELETEA(m_pBuffer);
            m_pBuffer = pBuffer;
            return *this;
        }
    }

    bool KSString::GetString(const KSString &String, unsigned int uiFind, bool bIsFront, bool bIsHaveFind)
    {
        if (uiFind >= String.GetLength())
        {
            return false;
        }
        unsigned int uiLength = 0;
        unsigned int uiIndex = 0;
        if (bIsFront)
        {
            uiLength = uiFind;
            uiIndex = 0;
        }
        else
        {
            uiLength = String.GetLength() - uiFind - 1;
            uiIndex = uiFind + 1;
        }
        if (bIsHaveFind)
        {
            uiLength++;
            if (!bIsFront)
            {
                uiIndex--;
            }
        }
        if (uiIndex >= String.GetLength())
        {
            return false;
        }
        KSMAC_DELETEA(m_pBuffer);
        m_pBuffer = KS_NEW KS_TCHAR[uiLength + 1];
        KSMemcpy(m_pBuffer, &String.m_pBuffer[uiIndex], uiLength, uiLength + 1);
#if KS_PLATFORM_WIN
        m_pBuffer[uiLength] = _T('\0');
#else
        m_pBuffer[uiLength] = '\0';
#endif
        return true;
    }

    bool KSString::GetString(const KSString &String, KS_TCHAR cFind, int iFIndNum, bool bIsFront, bool bIsHaveFind)
    {
        if (iFIndNum == 0)
        {
            return false;
        }
        unsigned int uiFIndNumTemp = 0;
        int uiIndex = -1;
        for (unsigned int i = 0; i < String.GetLength(); i++)
        {
            if (cFind == String.m_pBuffer[i])
            {
                uiFIndNumTemp++;
                uiIndex = i;
            }
            if (uiFIndNumTemp == iFIndNum)
            {
                break;
            }
        }
        if (uiIndex == -1)
        {
            return false;
        }
        return GetString(String, uiIndex, bIsFront, bIsHaveFind);
    }

    int KSString::GetSubStringIndex(const KSString &String, int iFindNum) const
    {
        if (GetLength() < String.GetLength())
        {
            return -1;
        }
        unsigned int uiFindNumTemp = 0;
        int iFindIndex = -1;
        for (unsigned int Index = 0; Index < GetLength(); Index++)
        {
            unsigned int j = 0;
            for (unsigned int i = Index; i < String.GetLength() + Index; i++)
            {
                if (m_pBuffer[i] == String.m_pBuffer[j])
                {
                    j++;
                    continue;
                }
                else
                {
                    break;
                }
            }
            if (j == String.GetLength())
            {
                iFindIndex = Index;
                uiFindNumTemp++;
                if (uiFindNumTemp == iFindNum)
                {

                    return iFindIndex;
                }
            }
        }

        return iFindIndex;
    }
    bool KSString::RemoveSubString(const KSString &String, int iFindNum)
    {
        if (GetLength() < String.GetLength())
        {
            return false;
        }
        unsigned int uiFindNumTemp = 0;
        int iFindIndex = -1;
        for (unsigned int Index = 0; Index < GetLength(); Index++)
        {
            unsigned int j = 0;
            for (unsigned int i = Index; i < String.GetLength() + Index; i++)
            {
                if (m_pBuffer[i] == String.m_pBuffer[j])
                {
                    j++;
                    continue;
                }
                else
                {
                    break;
                }
            }
            if (j == String.GetLength())
            {
                iFindIndex = Index;
                uiFindNumTemp++;
                if (uiFindNumTemp == iFindNum)
                {
                    Remove(iFindIndex, String.GetLength() + iFindIndex - 1);
                    return true;
                }
            }
        }
        if (iFindIndex >= 0)
        {
            Remove(iFindIndex, String.GetLength() + iFindIndex - 1);
            return true;
        }
        return false;
    }
    void KSString::Remove(unsigned int i, unsigned int j)
    {
        if (j > GetLength() - 1)
        {
            j = GetLength() - 1;
        }
        if (i > j)
        {
            return;
        }
        unsigned int uiLength = j - i + 1;
        unsigned DeltaLength = GetLength() - uiLength;
        KS_TCHAR *pBuffer = KS_NEW KS_TCHAR[DeltaLength + 1];
#if KS_PLATFORM_WIN
        pBuffer[DeltaLength] = _T('\0');
#else
        pBuffer[DeltaLength] = '\0';
#endif
        if (i > 0)
        {
            KSMemcpy(pBuffer, m_pBuffer, i);
        }
        unsigned int LeftNum = DeltaLength - i;
        if (LeftNum > 0)
        {
            KSMemcpy(pBuffer + i, m_pBuffer + i + uiLength, LeftNum);
        }
        KSMAC_DELETEA(m_pBuffer);
        m_pBuffer = pBuffer;
    }

    bool KSString::StripChars(const KSString &String, const KS_TCHAR *pStripChars)
    {
        if (String.GetLength() > BUFFER_SIZE || !pStripChars)
        {
            return false;
        }

        unsigned int strip_chars_len = KSStrLen(pStripChars);
        KS_TCHAR *_string_in = String.GetBuffer(), *_string_out = TempBuffer;
#if KS_PLATFORM_WIN
        while (*_string_in != _T('\0'))
#else
        while (*_string_in != '\0')
#endif
        {
            int flag = 0;
            for (unsigned int i = 0; i < strip_chars_len; i++)
            {
                if (*_string_in == pStripChars[i])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                *_string_out = *_string_in;
                _string_out++;
            }
            _string_in++;
        }
#if KS_PLATFORM_WIN
        *_string_out = _T('\0');
#else
        *_string_out = '\0';
#endif
        *this = TempBuffer;
        return true;
    }

    bool KSString::ReplaceChars(const KSString &String, const KS_TCHAR *pReplaceChars, KS_TCHAR UseChar)
    {
        if (String.GetLength() > BUFFER_SIZE || !pReplaceChars)
        {
            return false;
        }
        unsigned int replace_chars_len = KSStrLen(pReplaceChars);
        KS_TCHAR *_string_in = String.GetBuffer(), *_string_out = TempBuffer;
#if KS_PLATFORM_WIN
        while (*_string_in != _T('\0'))
#else
        while (*_string_in != '\0')
#endif
        {
            int flag = 0;
            for (unsigned int i = 0; i < replace_chars_len; i++)
            {
                if (*_string_in == pReplaceChars[i])
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                *_string_out = *_string_in;
            }
            else
            {
                *_string_out = UseChar;
            }
            _string_out++;
            _string_in++;
        }
#if KS_PLATFORM_WIN
        *_string_out = _T('\0');
#else
        *_string_out = '\0';
#endif

        *this = TempBuffer;
        return true;
    }

    void KSString::StringLtrim(const KSString &String)
    {
        int index = 0;
        KS_TCHAR *pString = String.GetBuffer();
        while (KSIsSpace(pString[index]))
            index++;
        if (index == 0)
            return;
        else
        {
            unsigned int uiLength = String.GetLength();
            KSMemcpy((void *)TempBuffer, (void *)(pString + index), ((uiLength - index) + 1) * sizeof(KS_TCHAR));
            *this = TempBuffer;
        }
    }

    void KSString::StringRtrim(const KSString &String)
    {
        unsigned int uiLength = String.GetLength();
        if (!uiLength)
        {
            return;
        }
        unsigned int index = uiLength - 1;
        KS_TCHAR *pString = String.GetBuffer();
        while (KSIsSpace(pString[index]))
            index--;

        KSMemcpy((void *)TempBuffer, (void *)(pString), (index + 1) * sizeof(KS_TCHAR));
        index++;
#if KS_PLATFORM_WIN
        TempBuffer[index] = _T('\0');
#else
        TempBuffer[index] = '\0';
#endif
        *this = TempBuffer;
    }

    KSString operator+(const KSString &String1, const KSString &String2)
    {
        unsigned int uiLength1 = String1.GetLength();
        unsigned int uiLength2 = String2.GetLength();
        if (!uiLength2)
            return String1;
        else if (!uiLength1)
            return String2;
        else
        {
            KS_TCHAR *pBuffer = NULL;
            unsigned int uiLength = uiLength2 + uiLength1 + 1;
            pBuffer = KS_NEW KS_TCHAR[uiLength];
            KSMAC_ASSERT(pBuffer);

            KSStrCopy(pBuffer, uiLength, String1.GetBuffer());
            KSStrcat(pBuffer, uiLength, String2.GetBuffer());
            KSString ReturnValue(pBuffer);
            KSMAC_DELETEA(pBuffer);
            return ReturnValue;
        }
    }
    KSString operator+(const KSString &String1, const KS_TCHAR *String2)
    {
        KSMAC_ASSERT(String2);
        unsigned int uiLength1 = String1.GetLength();
        unsigned int uiLength2 = 0;
        if (String2)
        {
            uiLength2 = (unsigned int)KSStrLen(String2);
        }

        if (!uiLength2)
            return String1;
        else if (!uiLength1)
            return KSString(String2);
        else
        {
            KS_TCHAR *pBuffer = NULL;
            unsigned int uiLength = uiLength2 + uiLength1 + 1;
            pBuffer = KS_NEW KS_TCHAR[uiLength];
            KSMAC_ASSERT(pBuffer);

            KSStrCopy(pBuffer, uiLength, String1.GetBuffer());
            KSStrcat(pBuffer, uiLength, String2);
            KSString ReturnValue(pBuffer);
            KSMAC_DELETEA(pBuffer);
            return ReturnValue;
        }
    }
    KSString operator+(const KS_TCHAR *String1, const KSString &String2)
    {
        KSMAC_ASSERT(String1);
        unsigned int uiLength2 = String2.GetLength();
        unsigned int uiLength1 = 0;
        if (String1)
        {
            uiLength1 = (unsigned int)KSStrLen(String1);
        }

        if (!uiLength1)
            return String2;
        else if (!uiLength2)
            return KSString(String1);
        else
        {
            KS_TCHAR *pBuffer = NULL;
            unsigned int uiLength = uiLength2 + uiLength1 + 1;
            pBuffer = KS_NEW KS_TCHAR[uiLength];
            KSMAC_ASSERT(pBuffer);

            KSStrCopy(pBuffer, uiLength, String1);
            KSStrcat(pBuffer, uiLength, String2.GetBuffer());
            KSString ReturnValue(pBuffer);
            KSMAC_DELETEA(pBuffer);
            return ReturnValue;
        }
    }
    int CompareString(const KSString &String1, const KSString &String2)
    {
        return KSStrCmp(String1.GetBuffer(), String2.GetBuffer());
    }
    int CompareString(const KSString &String1, const KS_TCHAR *String2)
    {
        return KSStrCmp(String1.GetBuffer(), String2);
    }
    int CompareString(const KS_TCHAR *String1, const KSString &String2)
    {
        return KSStrCmp(String1, String2.GetBuffer());
    }

    bool operator==(const KSString &String1, const KSString &String2)
    {
        return (KSStrCmp(String1.GetBuffer(), String2.GetBuffer()) == 0);
    }
    bool operator==(const KSString &String1, const KS_TCHAR *String2)
    {
        return (KSStrCmp(String1.GetBuffer(), String2) == 0);
    }
    bool operator==(const KS_TCHAR *String1, KSString &String2)
    {
        return (KSStrCmp(String1, String2.GetBuffer()) == 0);
    }

    bool operator!=(const KSString &String1, const KSString &String2)
    {
        return (KSStrCmp(String1.GetBuffer(), String2.GetBuffer()) != 0);
    }
    bool operator!=(const KSString &String1, const KS_TCHAR *String2)
    {
        return (KSStrCmp(String1.GetBuffer(), String2) != 0);
    }
    bool operator!=(const KS_TCHAR *String1, const KSString &String2)
    {
        return (KSStrCmp(String1, String2.GetBuffer()) != 0);
    }
}