/******************************************************************************

    TITLE     : SSE accelerated case-insensitive substring search
    AUTHOR    : anlarke
    COPYRIGHT : The Code Project Open License (CPOL)
                [http://www.codeproject.com/info/Licenses.aspx]
    DATE      : May 14, 2012

******************************************************************************/

#ifndef __WCSISTR_H__
#define __WCSISTR_H__

#include <wchar.h>

#ifdef __cplusplus
extern "C"
{
#endif

wchar_t* _wsetlocale_map(int category, const wchar_t *locale);
wchar_t towlower_map(wchar_t c);
wchar_t towupper_map(wchar_t c);
const wchar_t* wcsistr(const wchar_t *wcs1, const wchar_t *wcs2);

#ifdef __cplusplus
}
#endif

#endif // __WCSISTR_H__
