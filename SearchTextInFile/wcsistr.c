/******************************************************************************

    TITLE     : SSE accelerated case-insensitive substring search
    AUTHOR    : anlarke
    COPYRIGHT : The Code Project Open License (CPOL)
                [http://www.codeproject.com/info/Licenses.aspx]
    DATE      : May 14, 2012

******************************************************************************/

#include "wcsistr.h"
#include <intrin.h>

//
// Emulating the global __isa_available variable that is normally only available 
// when building the CRT library
//

#define __ISA_AVAILABLE_X86     0
#define __ISA_AVAILABLE_SSE2    1
#define __ISA_AVAILABLE_SSE42   2

//
// These macros come from the Microsoft CRT library (look up wcsstr.c)
//

#define XMM_SIZE sizeof(__m128i)
#define XMM_ALIGNED(p) (0 == ((XMM_SIZE-1) & (intptr_t)(p)))
#define XMM_CHARS (XMM_SIZE / sizeof(wchar_t))

#define PAGE_SIZE ((intptr_t)0x1000)
#define PAGE_OFFSET(p) ((PAGE_SIZE-1) & (intptr_t)(p))
#define XMM_PAGE_SAFE(p) (PAGE_OFFSET(p) <= (PAGE_SIZE - XMM_SIZE))

//
// Cached case conversion and SSE detection
//

wchar_t g_mapToLower[256];
wchar_t g_mapToUpper[256];
int __isa_available = __ISA_AVAILABLE_X86;

wchar_t* _wsetlocale_map(int category, const wchar_t *locale)
{
    wchar_t *ret = _wsetlocale(category, locale);
    wchar_t c;
    int CPUInfo[4];
    
    for (c = 0; c < 256; ++c)
    {
        g_mapToLower[c] = towlower(c);
        g_mapToUpper[c] = towupper(c);
    }

    __cpuid(CPUInfo, 1);
    if (CPUInfo[2] & (1 << 20))
        __isa_available = __ISA_AVAILABLE_SSE42;
    else if (CPUInfo[3] & (1 << 26))
        __isa_available = __ISA_AVAILABLE_SSE2;
    
    return ret;
}

wchar_t towlower_map(wchar_t c)
    {return (c < 256 ? g_mapToLower[c] : towlower(c));}

wchar_t towupper_map(wchar_t c)
    {return (c < 256 ? g_mapToUpper[c] : towupper(c));}

//
// The case-insensitive substring search function
//

const wchar_t* wcsistr(const wchar_t *wcs1, const wchar_t *wcs2)
{
    const wchar_t *s1, *s2;
    const wchar_t l = towlower_map(*wcs2);
    const wchar_t u = towupper_map(*wcs2);

    if (!*wcs2)
        return wcs1; // an empty substring matches everything

    if (__isa_available >= __ISA_AVAILABLE_SSE2)
    {
        __m128i patl, patu, zero, tmp1, tmp2, tmp3, cachel, cacheu;
        int mask, i, cache_mask;
        unsigned long offset;

        // fill one XMM register completely with l, one with u and another with zeros

        patl = _mm_cvtsi32_si128(l);
        patl = _mm_shufflelo_epi16(patl, 0);
        patl = _mm_shuffle_epi32(patl, 0);
        patu = _mm_cvtsi32_si128(u);
        patu = _mm_shufflelo_epi16(patu, 0);
        patu = _mm_shuffle_epi32(patu, 0);
        zero = _mm_setzero_si128();

        // convert first 8 characters of substring to lower and upper case while putting
        // them in XMM registers

        cachel = _mm_setzero_si128();
        cacheu = _mm_setzero_si128();
        cache_mask = 0;
        s2 = wcs2;

        for (i = 0; i < XMM_CHARS; ++i)
        {
            cachel = _mm_srli_si128(cachel, sizeof(wchar_t)); // shift by one character
            cacheu = _mm_srli_si128(cacheu, sizeof(wchar_t));
            
            cachel = _mm_insert_epi16(cachel, towlower_map(*s2), XMM_CHARS-1); // insert character
            cacheu = _mm_insert_epi16(cacheu, towupper_map(*s2), XMM_CHARS-1);

            if (*s2)
            {
                cache_mask |= 3 << (i << 1); // decimal 3 is binary 11, set two bits for each character
                ++s2;
            }
        }

        // loop through string and try to match the first character

        for (;;)
        {
            // if page safe compare using the XMM registers

            if (XMM_PAGE_SAFE(wcs1))
            {
                // perform the comparison (also checks for end of string)

                tmp1 = _mm_loadu_si128((__m128i*)wcs1);  // load chunk of 8 characters at this position
                tmp2 = _mm_cmpeq_epi16(tmp1, patl);      // compare against lower case pattern, store mask
                tmp3 = _mm_cmpeq_epi16(tmp1, patu);      // compare against upper case pattern, store mask
                tmp2 = _mm_or_si128(tmp2, tmp3);         // combine both masks into tmp2
                tmp3 = _mm_cmpeq_epi16(tmp1, zero);      // compare against null character, store mask
                tmp2 = _mm_or_si128(tmp2, tmp3);         // combine both masks into tmp2
                mask = _mm_movemask_epi8(tmp2);          // convert to 32-bit mask

                // if no match found, continue with next chunk

                if (mask == 0)
                {
                    wcs1 += XMM_CHARS;
                    continue;
                }

                // advance string pointer to position of l, u or null

                _BitScanForward(&offset, mask);
                wcs1 += offset / sizeof(wchar_t);

                // if not at end of string and page safe, quickly check whether the first chunk
                // matches the substring

                if (*wcs1 && XMM_PAGE_SAFE(wcs1))
                {
                    tmp1 = _mm_loadu_si128((__m128i*)wcs1);
                    tmp2 = _mm_cmpeq_epi16(tmp1, cachel);
                    tmp3 = _mm_cmpeq_epi16(tmp1, cacheu);
                    tmp2 = _mm_or_si128(tmp2, tmp3);
                    mask = _mm_movemask_epi8(tmp2);

                    if (cache_mask == 0xFFFF) // only first part of substring in cache
                    {
                        if (mask == cache_mask)
                        {
                            s1 = wcs1 + XMM_CHARS;
                            s2 = wcs2 + XMM_CHARS;

                            while (*s1 && *s2 && towlower_map(*s1) == towlower_map(*s2))
                                ++s1, ++s2;

                            if (!*s2)
                                return wcs1;
                        }
                    }
                    else // full substring is in cache
                    {
                        if ((mask & cache_mask) == cache_mask)
                            return wcs1;
                    }

                    // no full match found, try next character in string

                    ++wcs1;
                    continue; 
                }
            }

            // if at the end of string, no match found

            if (!*wcs1)
                return NULL;

            // if first character matches, compare against the full substring
            
            if (*wcs1 == l || *wcs1 == u)
            {
                s1 = wcs1 + 1;
                s2 = wcs2 + 1;

                while (*s1 && *s2 && towlower_map(*s1) == towlower_map(*s2))
                    ++s1, ++s2;

                if (!*s2)
                    return wcs1;
            }

            ++wcs1;
        }
    }
    else
    {
        for (; *wcs1; ++wcs1)
        {
            if (*wcs1 == l || *wcs1 == u)
            {
                s1 = wcs1 + 1;
                s2 = wcs2 + 1;
                
                while (*s1 && *s2 && towlower_map(*s1) == towlower_map(*s2))
                    ++s1, ++s2;
            
                if (!*s2)
                    return wcs1;
            }
        }
    }

    return NULL;
}
