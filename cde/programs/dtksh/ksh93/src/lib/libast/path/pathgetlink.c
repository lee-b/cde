/* $XConsortium: pathgetlink.c /main/2 1996/05/08 19:53:24 drk $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*         THIS IS PROPRIETARY SOURCE CODE LICENSED BY          *
*                          AT&T CORP.                          *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*                     All Rights Reserved                      *
*                                                              *
*           This software is licensed by AT&T Corp.            *
*       under the terms and conditions of the license in       *
*       http://www.research.att.com/orgs/ssr/book/reuse        *
*                                                              *
*               This software was created by the               *
*           Software Engineering Research Department           *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                     gsf@research.att.com                     *
*                                                              *
***************************************************************/

/* : : generated by proto : : */

#if !defined(__PROTO__)
#if defined(__STDC__) || defined(__cplusplus) || defined(_proto) || defined(c_plusplus)
#if defined(__cplusplus)
#define __MANGLE__	"C"
#else
#define __MANGLE__
#endif
#define __STDARG__
#define __PROTO__(x)	x
#define __OTORP__(x)
#define __PARAM__(n,o)	n
#if !defined(__STDC__) && !defined(__cplusplus)
#if !defined(c_plusplus)
#define const
#endif
#define signed
#define void		int
#define volatile
#define __V_		char
#else
#define __V_		void
#endif
#else
#define __PROTO__(x)	()
#define __OTORP__(x)	x
#define __PARAM__(n,o)	o
#define __MANGLE__
#define __V_		char
#define const
#define signed
#define void		int
#define volatile
#endif
#if defined(__cplusplus) || defined(c_plusplus)
#define __VARARG__	...
#else
#define __VARARG__
#endif
#if defined(__STDARG__)
#define __VA_START__(p,a)	va_start(p,a)
#else
#define __VA_START__(p,a)	va_start(p)
#endif
#endif
#include "univlib.h"

#ifdef UNIV_MAX

#include <ctype.h>

#endif

/*
 * return external representation for symbolic link text of name in buf
 * the link text string length is returned
 */

int
pathgetlink __PARAM__((const char* name, char* buf, int siz), (name, buf, siz)) __OTORP__(const char* name; char* buf; int siz;){
	int	n;

	if ((n = readlink(name, buf, siz)) < 0) return(-1);
	if (n >= siz)
	{
		errno = EINVAL;
		return(-1);
	}
	buf[n] = 0;
#ifdef UNIV_MAX
	if (isspace(*buf))
	{
		register char*	s;
		register char*	t;
		register char*	u;
		register char*	v;
		int		match = 0;
		char		tmp[PATH_MAX];

		s = buf;
		t = tmp;
		while (isalnum(*++s) || *s == '_' || *s == '.');
		if (*s++)
		{
			for (;;)
			{
				if (!*s || isspace(*s))
				{
					if (match)
					{
						*t = 0;
						n = t - tmp;
						strcpy(buf, tmp);
					}
					break;
				}
				if (t >= &tmp[sizeof(tmp)]) break;
				*t++ = *s++;
				if (!match && t < &tmp[sizeof(tmp) - univ_size + 1]) for (n = 0; n < UNIV_MAX; n++)
				{
					if (*(v = s - 1) == *(u = univ_name[n]))
					{
						while (*u && *v++ == *u) u++;
						if (!*u)
						{
							match = 1;
							strcpy(t - 1, univ_cond);
							t += univ_size - 1;
							s = v;
							break;
						}
					}
				}
			}
		}
	}
#endif
	return(n);
}
