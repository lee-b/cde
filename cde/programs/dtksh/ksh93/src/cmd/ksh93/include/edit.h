/* $XConsortium: edit.h /main/3 1995/11/01 16:39:33 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*        THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF        *
*                    AT&T BELL LABORATORIES                    *
*         AND IS NOT TO BE DISCLOSED OR USED EXCEPT IN         *
*            ACCORDANCE WITH APPLICABLE AGREEMENTS             *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*              Unpublished & Not for Publication               *
*                     All Rights Reserved                      *
*                                                              *
*       The copyright notice above does not evidence any       *
*      actual or intended publication of such source code      *
*                                                              *
*               This software was created by the               *
*           Advanced Software Technology Department            *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                    {research,attmail}!dgk                    *
*                                                              *
***************************************************************/

/* : : generated by proto : : */
                  
#ifndef SEARCHSIZE
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

/*
 *  edit.h -  common data structure for vi and emacs edit options
 *
 *   David Korn
 *   AT&T Bell Laboratories
 *   Room 2B-102
 *   Murray Hill, N. J. 07974
 *   Tel. x7975
 *
 */

#define SEARCHSIZE	80

#include	"FEATURE/options"
#if !defined(SHOPT_VSH) && !defined (SHOPT_ESH)
#   define ed_winsize()	(SEARCHSIZE)
#else

#ifndef KSHELL
#   include	<setjmp.h>
#   include	<sig.h>
#   include	<ctype.h>
#endif /* KSHELL */

#include	"FEATURE/setjmp"

#ifdef SHOPT_SEVENBIT
#   define STRIP	0177
#else
#   define STRIP	0377
#endif /* SHOPT_SEVENBIT */
#define LOOKAHEAD	80

#ifdef SHOPT_MULTIBYTE
#   ifndef ESS_MAXCHAR
#   include	"national.h"
#   endif /* ESS_MAXCHAR */
#   if ESS_MAXCHAR<=2
	typedef unsigned short genchar;
#   else
	typedef long genchar;
#   endif
#   define CHARSIZE	2
#else
    typedef char genchar;
#   define CHARSIZE	1
#endif /* SHOPT_MULTIBYTE */

#define TABSIZE	8
#define PRSIZE	80
#define MAXLINE	502		/* longest edit line permitted */

struct edit
{
	int	e_kill;
	int	e_erase;
	int	e_werase;
	int	e_eof;
	int	e_lnext;
	int	e_fchar;
	char	e_plen;		/* length of prompt string */
	char	e_crlf;		/* zero if cannot return to beginning of line */
	sigjmp_buf e_env;
	int	e_llimit;	/* line length limit */
	int	e_hline;	/* current history line number */
	int	e_hloff;	/* line number offset for command */
	int	e_hismin;	/* minimum history line number */
	int	e_hismax;	/* maximum history line number */
	int	e_raw;		/* set when in raw mode or alt mode */
	int	e_cur;		/* current line position */
	int	e_eol;		/* end-of-line position */
	int	e_pcur;		/* current physical line position */
	int	e_peol;		/* end of physical line position */
	int	e_mode;		/* edit mode */
	int	e_index;	/* index in look-ahead buffer */
	int	e_repeat;
	int	e_saved;
	int	e_fcol;		/* first column */
	int	e_ucol;		/* column for undo */
	int	e_wsize;	/* width of display window */
	char	*e_outbase;	/* pointer to start of output buffer */
	char	*e_outptr;	/* pointer to position in output buffer */
	char	*e_outlast;	/* pointer to end of output buffer */
	genchar	*e_inbuf;	/* pointer to input buffer */
	char	*e_prompt;	/* pointer to buffer containing the prompt */
	genchar	*e_ubuf;	/* pointer to the undo buffer */
	genchar	*e_killbuf;	/* pointer to delete buffer */
	char	e_search[SEARCHSIZE];	/* search string */
	genchar	*e_Ubuf;	/* temporary workspace buffer */
	genchar	*e_physbuf;	/* temporary workspace buffer */
	int	e_lbuf[LOOKAHEAD];/* pointer to look-ahead buffer */
	int	e_fd;		/* file descriptor */
	int	e_ttyspeed;	/* line speed, also indicates tty parms are valid */
	int	*e_globals;	/* global variables */
	genchar	*e_window;	/* display window  image */
	char	e_inmacro;	/* processing macro expansion */
#ifndef KSHELL
	char	e_prbuff[PRSIZE]; /* prompt buffer */
#endif /* KSHELL */
};

#undef MAXWINDOW
#define MAXWINDOW	160	/* maximum width window */
#define FAST	2
#define SLOW	1
#define ESC	033
#define	UEOF	-2			/* user eof char synonym */
#define	UINTR	-3			/* user intr char synonym */
#define	UERASE	-4			/* user erase char synonym */
#define	UKILL	-5			/* user kill char synonym */
#define	UWERASE	-6			/* user word erase char synonym */
#define	ULNEXT	-7			/* user next literal char synonym */

#define	cntl(x)		(x&037)

#ifndef KSHELL
#   define STRIP	0377
#   define GMACS	1
#   define EMACS	2
#   define VIRAW	4
#   define EDITVI	8
#   define NOHIST	16
#   define EDITMASK	15
#   define is_option(m)	(opt_flag&(m))
    extern __MANGLE__ char opt_flag;
#   ifdef SYSCALL
#	define read(fd,buff,n)	syscall(3,fd,buff,n)
#   else
#	define read(fd,buff,n)	rEAd(fd,buff,n)
#   endif /* SYSCALL */
#endif	/* KSHELL */

extern __MANGLE__ struct edit editb;

extern __MANGLE__ void	ed_crlf __PROTO__((void));
extern __MANGLE__ void	ed_putchar __PROTO__((int));
extern __MANGLE__ void	ed_ringbell __PROTO__((void));
extern __MANGLE__ void	ed_setup __PROTO__((int));
extern __MANGLE__ void	ed_flush __PROTO__((void));
extern __MANGLE__ int	ed_getchar __PROTO__((int));
extern __MANGLE__ int	ed_virt_to_phys __PROTO__((genchar*,genchar*,int,int,int));
extern __MANGLE__ int	ed_window __PROTO__((void));
extern __MANGLE__ void	ed_ungetchar __PROTO__((int));
extern __MANGLE__ int	ed_viread __PROTO__((int, char*, int));
extern __MANGLE__ int	ed_read __PROTO__((int, char*, int));
extern __MANGLE__ int	ed_emacsread __PROTO__((int, char*, int));
#ifdef KSHELL
	extern __MANGLE__ int	ed_macro __PROTO__((int));
	extern __MANGLE__ int	ed_expand __PROTO__((char[],int*,int*,int));
	extern __MANGLE__ int	ed_fulledit __PROTO__((void));
#endif /* KSHELL */
#   ifdef SHOPT_MULTIBYTE
	extern __MANGLE__ int ed_internal __PROTO__((const char*, genchar*));
	extern __MANGLE__ int ed_external __PROTO__((const genchar*, char*));
	extern __MANGLE__ void ed_gencpy __PROTO__((genchar*,const genchar*));
	extern __MANGLE__ void ed_genncpy __PROTO__((genchar*,const genchar*,int));
	extern __MANGLE__ int ed_genlen __PROTO__((const genchar*));
	extern __MANGLE__ int ed_setwidth __PROTO__((const char*));
#  endif /* SHOPT_MULTIBYTE */

extern __MANGLE__ const char	e_runvi[];
#ifndef KSHELL
   extern __MANGLE__ const char	e_version[];
#endif /* KSHELL */

#endif
#endif
