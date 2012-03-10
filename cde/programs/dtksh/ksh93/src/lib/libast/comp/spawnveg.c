/* $XConsortium: spawnveg.c /main/2 1996/05/08 19:40:35 drk $ */
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
#include <ast.h>

#if _lib_spawnveg

NoN(spawnveg)

#else

#include <error.h>

#ifndef ENOSYS
#define ENOSYS	EINVAL
#endif

#if _lib_vfork
#if _hdr_vfork
#include	<vfork.h>
#endif
#if _sys_vfork
#include	<sys/vfork.h>
#endif
#endif

#if !_lib_spawnve
#ifdef _map_spawnve
#undef	spawnve
#define spawnve	_map_spawnve
extern __MANGLE__ pid_t	spawnve __PROTO__((const char*, char* const[], char* const[]));
#undef	_lib_spawnve
#define _lib_spawnve	1
#endif
#endif

/*
 * fork+exec+(setsid|setpgid) with script check to avoid shell double fork
 */

pid_t
spawnveg __PARAM__((const char* cmd, char* const argv[], char* const envv[], pid_t pgid), (cmd, argv, envv, pgid)) __OTORP__(const char* cmd; char* const argv[]; char* const envv[]; pid_t pgid;){
#if _lib_fork || _lib_vfork
	int	n;
	pid_t	pid;
#if !_real_vfork
	int	err[2];
#endif
#endif

#if _lib_spawnve
#if _lib_fork || _lib_vfork
	if (!pgid)
#endif
		return(spawnve(cmd, argv, envv));
#endif
#if _lib_fork || _lib_vfork
	n = errno;
#if _real_vfork
	errno = 0;
#else
	if (pipe(err) < 0) err[0] = -1;
	else
	{
		fcntl(err[0], F_SETFD, FD_CLOEXEC);
		fcntl(err[1], F_SETFD, FD_CLOEXEC);
	}
#endif
	sigcritical(1);
#if _lib_vfork
	pid = vfork();
#else
	pid = fork();
#endif
	sigcritical(0);
	if (!pid)
	{
		if (pgid < 0)
			setsid();
		else if (pgid > 0)
		{
			if (pgid == 1)
				pgid = 0;
			if (setpgid(0, pgid) < 0 && pgid && errno == EPERM)
				setpgid(0, 0);
		}
		execve(cmd, argv, envv);
		if (errno == ENOEXEC)
		{
			register char**	o;
			register char**	p;
			register char**	v;

			for (p = o = (char**)argv; *p; p++);
			if (v = newof(0, char*, p - o + 2, 0))
			{
				p = v;
				if (*p = *o) o++;
				else *p = (char*)cmd;
				*++p = (char*)cmd;
				while (*++p = *o++);
				execve(pathshell(), v, envv);
				free(v);
			}
#ifdef ENOMEM
			else errno = ENOMEM;
#endif
		}
#if !_real_vfork
		if (err[0] != -1)
		{
			n = errno;
			write(err[1], &n, sizeof(n));
		}
#endif
		_exit(errno == ENOENT ? EXIT_NOTFOUND : EXIT_NOEXEC);
	}
	else if (pid != -1)
	{
#if _real_vfork
		if (errno) pid = -1;
		else
#endif
		{
			if (pgid > 0)
			{
				/*
				 * parent and child are in a race here
				 */

				if (pgid == 1)
					pgid = pid;
				if (setpgid(pid, pgid) < 0 && pid != pgid && errno == EPERM)
					setpgid(pid, pid);
			}
			errno = n;
		}
	}
#if !_real_vfork
	if (err[0] != -1)
	{
		close(err[1]);
		if (read(err[0], &n, sizeof(n)) == sizeof(n))
		{
			while (waitpid(pid, NiL, 0) == -1 && errno == EINTR);
			pid = -1;
			errno = n;
		}
		close(err[0]);
	}
#endif
	return(pid);
#else
	errno = ENOSYS;
	return(-1);
#endif
}

#endif
