/* $XConsortium: slowio.c /main/3 1995/11/01 18:04:43 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*        THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF        *
*                    AT&T BELL LABORATORIES                    *
*         AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN         *
*            ACCORDANCE WITH APPLICABLE AGREEMENTS             *
*                                                              *
*          Copyright (c) 1994 AT&T Bell Laboratories           *
*              Unpublished & Not for Publication               *
*                     All Rights Reserved                      *
*                                                              *
*       The copyright notice above does not evidence any       *
*      actual or intended publication of such source code      *
*                                                              *
*               This software was created by the               *
*           Software Engineering Research Department           *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                   advsoft@research.att.com                   *
*                 Randy Hackbarth 908-582-5245                 *
*                  Dave Belanger 908-582-7427                  *
*                                                              *
***************************************************************/

/* : : generated by proto : : */

#line 1

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

#line 9
#include <ast.h>
#include <errno.h>

#ifndef errno
extern __MANGLE__ int	errno;
#endif

/*
 * slowio exception handler
 * EOF in interrupt
 * free on close
 */

static int
slowexcept __PARAM__((Sfio_t* sp, int op, Sfdisc_t* dp), (sp, op, dp)) __OTORP__(Sfio_t* sp; int op; Sfdisc_t* dp;)
#line 24
{
	NoP(sp);
	switch (op)
	{
	case SF_CLOSE:
		free(dp);
		break;
	case SF_READ:
	case SF_WRITE:
		if (errno == EINTR)
			return(-1);
		break;
	}
	return(0);
}

/*
 * create and push slowio discipline
 */

int
slowio __PARAM__((Sfio_t* sp), (sp)) __OTORP__(Sfio_t* sp;)
#line 46
{
	Sfdisc_t*	dp;

	if (!(dp = newof(0, Sfdisc_t, 1, 0)))
		return(-1);
	dp->exceptf = slowexcept;
	return(sfdisc(sp, dp) ? 0 : -1);
}
