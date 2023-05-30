
#include "runtime/core/base/platform.h"
#include "runtime/core/base/macro.h"

namespace Kratos
{
    inline void KSMemset(void *pDest, int iC, size_t uiCount)
    {
        memset(pDest, iC, uiCount);
    }

    inline void KSStrCopy(KS_TCHAR *pDest, unsigned int uiCount, const KS_TCHAR *pSource)
    {
#if KS_PLATFORM == KS_PLATFORM_WIN
        _tcscpy_s(pDest, uiCount, pSource);
#else
        strncpy(pDest, pSource, uiCount);
        return;
#endif
    }

}