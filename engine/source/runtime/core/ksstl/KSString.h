
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
        void SetTCHARBufferNum(unsigned int uiLength);
        void Clear();

        // 重载=操作符
        KSString &operator=(const KSString &String);
        KSString &operator=(const KS_TCHAR *String);

        // 重载[]操作符
        KS_TCHAR &operator[](unsigned int i);

        // 重载+=操作符
        const KSString &operator+=(const KSString &String);
        const KSString &operator+=(const KS_TCHAR *String);

        // 取得指定下标的前段字符串或者后段字符串
        bool GetString(const KSString &String, unsigned int uiFind, bool bIsFront = true, bool bIsHaveFind = false);
        // 查找第iFindNum次出现的指定字符，然后取前段字符串或者后段字符串。iFIndNum = -1表示最后一次出现的。
        bool GetString(const KSString &String, KS_TCHAR cFind, int iFIndNum, bool bIsFront = true, bool bIsHaveFind = false);
        // 查找当前字符串中第iFindNum次出现的String的下标，返回-1则表示查找失败
        int GetSubStringIndex(const KSString &String, int iFindNum) const;
        bool RemoveSubString(const KSString &String, int iFindNum);
        void Remove(unsigned int i, unsigned int j);
        // 去掉指定的字符
        bool StripChars(const KSString &String, const KS_TCHAR *pStripChars);
        // 替换指定的字符
        bool ReplaceChars(const KSString &String, const KS_TCHAR *pReplaceChars, KS_TCHAR UseChar);
        // 去掉字符串的左边所有空格
        void StringLtrim(const KSString &String);
        // 去掉字符串的右边所有空格
        void StringRtrim(const KSString &String);

    protected:
        KS_TCHAR *m_pBuffer;
    };
}