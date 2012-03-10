/* $XConsortium: trestore.c /main/3 1995/11/01 16:52:43 rswiston $ */
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
#include	"defs.h"
#include	"shnodes.h"
#include	"path.h"
#include	"io.h"

static struct dolnod	*r_comlist __PROTO__((void));
static struct argnod	*r_arg __PROTO__((void));
static struct ionod	*r_redirect __PROTO__((void));
static struct regnod	*r_switch __PROTO__((void));
static union anynode	*r_tree __PROTO__((void));
static char		*r_string __PROTO__((void));
static void		r_comarg __PROTO__((struct comnod*));

static Sfio_t *infile;

#define getnode(type)   ((union anynode*)stakalloc(sizeof(struct type)))

union anynode *sh_trestore __PARAM__((Sfio_t *in), (in)) __OTORP__(Sfio_t *in;){
	union anynode *t;
	infile = in;
	t = r_tree();
	return(t);
}
/*
 * read in a shell tree
 */
static union anynode *r_tree()
{
	long l = sfgetl(infile); 
	register int type;
	register union anynode *t=0;
	if(l<0)
		return(t);
	type = l;
	switch(type&COMMSK)
	{
		case TTIME:
		case TPAR:
			t = getnode(parnod);
			t->par.partre = r_tree();
			break;
		case TCOM:
			t = getnode(comnod);
			t->tre.tretyp = type;
			r_comarg((struct comnod*)t);
			break;
		case TSETIO:
		case TFORK:
			t = getnode(forknod);
			t->fork.forkline = sfgetu(infile);
			t->fork.forktre = r_tree();
			t->fork.forkio = r_redirect();
			break;
		case TIF:
			t = getnode(ifnod);
			t->if_.iftre = r_tree();
			t->if_.thtre = r_tree();
			t->if_.eltre = r_tree();
			break;
		case TWH:
			t = getnode(whnod);
			t->wh.whinc = (struct arithnod*)r_tree();
			t->wh.whtre = r_tree();
			t->wh.dotre = r_tree();
			break;
		case TLST:
		case TAND:
		case TORF:
		case TFIL:
			t = getnode(lstnod);
			t->lst.lstlef = r_tree();
			t->lst.lstrit = r_tree();
			break;
		case TARITH:
			t = getnode(arithnod);
			t->ar.arline = sfgetu(infile);
			t->ar.arexpr = r_arg();
			break;
		case TFOR:
			t = getnode(fornod);
			t->for_.fortre = r_tree();
			t->for_.fornam = r_string();
			t->for_.forlst = (struct comnod*)r_tree();
			break;
		case TSW:
			t = getnode(swnod);
			t->sw.swarg = r_arg();
			t->sw.swlst = r_switch();
			break;
		case TFUN:
		{
			Stak_t *savstak;
			struct slnod *slp;
			t = getnode(functnod);
			t->funct.functloc = -1;
			t->funct.functline = sfgetu(infile);
			t->funct.functnam = r_string();
			savstak = stakcreate(STAK_SMALL);
			savstak = stakinstall(savstak, 0);
			slp = (struct slnod*)stakalloc(sizeof(struct slnod));
			slp->slchild = 0;
			slp->slnext = sh.st.staklist;
			sh.st.staklist = 0;
			t->funct.functtre = r_tree(); 
			t->funct.functstak = slp;
			slp->slptr =  stakinstall(savstak,0);
			slp->slchild = sh.st.staklist;
			t->funct.functargs = (struct comnod*)r_tree();
			break;
		}
		case TTST:
			t = getnode(tstnod);
			t->tst.tstline = sfgetu(infile);
			if((type&TPAREN)==TPAREN)
				t->lst.lstlef = r_tree(); 
			else
			{
				t->lst.lstlef = (union anynode*)r_arg();
				if((type&TBINARY))
					t->lst.lstrit = (union anynode*)r_arg();
			}
	}
	t->tre.tretyp = type;
	return(t);
}

static struct argnod *r_arg __PARAM__((void), ()){
	register struct argnod *ap=0, *apold, *aptop=0;
	register long l;
	while((l=sfgetu(infile))>0)
	{
		ap = (struct argnod*)stakseek((unsigned)l+ARGVAL);
		if(!aptop)
			aptop = ap;
		else
			apold->argnxt.ap = ap;
		if(--l > 0)
			sfread(infile,ap->argval,(size_t)l);
		ap->argval[l] = 0;
		ap->argflag = sfgetc(infile);
		if(ap->argflag&ARG_MESSAGE)
		{
			/* replace international messages */
			ap = sh_endword(1);
			ap->argflag &= ~ARG_MESSAGE;
			if(!(ap->argflag&(ARG_MAC|ARG_EXP)))
				ap = sh_endword(0);
			else
			{
				ap = (struct argnod*)stakfreeze(0);
				if(ap->argflag==0)
					ap->argflag = ARG_RAW;
			}
		}
		else
			ap = (struct argnod*)stakfreeze(0);
		if(*ap->argval==0 && ap->argflag==0)
		{
			struct fornod *fp = (struct fornod*)getnode(fornod);
			fp->fortre = r_tree();
			fp->fornam = ap->argval+1;
			ap->argchn.ap = (struct argnod*)fp;
		}
		apold = ap;
	}
	if(ap)
		ap->argnxt.ap = 0;
	return(aptop);
}

static struct ionod *r_redirect __PARAM__((void), ()){
	register long l;
	register struct ionod *iop=0, *iopold, *ioptop=0;
	while((l=sfgetl(infile))>=0)
	{
		iop = (struct ionod*)getnode(ionod);
		if(!ioptop)
			ioptop = iop;
		else
			iopold->ionxt = iop;
		iop->iofile = l;
		iop->ioname = r_string();
		if(iop->iodelim = r_string())
		{
			iop->iosize = sfgetl(infile);
			if(sh.heredocs)
				iop->iooffset = sfseek(sh.heredocs,(off_t)0,SEEK_END);
			else
			{
				sh.heredocs = sftmp(512);
				iop->iooffset = 0;
			}
			sfmove(infile,sh.heredocs, iop->iosize, -1);
		}
		iopold = iop;
	}
	if(iop)
		iop->ionxt = 0;
	return(ioptop);
}

static void r_comarg __PARAM__((struct comnod *com), (com)) __OTORP__(struct comnod *com;){
	char *cmdname=0;
	com->comio = r_redirect();
	com->comset = r_arg();
	if(com->comtyp&COMSCAN)
	{
		com->comarg = r_arg();
		if(com->comarg->argflag==ARG_RAW)
			cmdname = com->comarg->argval;
	}
	else if(com->comarg = (struct argnod*)r_comlist())
		cmdname = ((struct dolnod*)(com->comarg))->dolval[ARG_SPARE];
	com->comline = sfgetu(infile);
	if(cmdname)
		com->comnamp = (__V_*)nv_search(cmdname,sh.fun_tree,0);
	else
		com->comnamp  = 0;
}

static struct dolnod *r_comlist __PARAM__((void), ()){
	register struct dolnod *dol=0;
	register long l;
	register char **argv;
	if((l=sfgetl(infile))>0)
	{
		dol = (struct dolnod*)stakalloc(sizeof(struct dolnod) + sizeof(char*)*(l+ARG_SPARE));
		dol->dolnum = l;
		dol->dolbot = ARG_SPARE;
		argv = dol->dolval+ARG_SPARE;
		while(*argv++ = r_string());
	}
	return(dol);
}

static struct regnod *r_switch __PARAM__((void), ()){
	register long l;
	struct regnod *reg=0,*regold,*regtop=0;
	while((l=sfgetl(infile))>=0)
	{
		reg = (struct regnod*)getnode(regnod);
		if(!regtop)
			regtop = reg;
		else
			regold->regnxt = reg;
		reg->regflag = l;
		reg->regptr = r_arg();
		reg->regcom = r_tree();
		regold = reg;
	}
	if(reg)
		reg->regnxt = 0;
	return(regtop);
}

static char *r_string __PARAM__((void), ()){
	register Sfio_t *in = infile;
	register unsigned long l = sfgetu(in);
	register char *ptr;
	if(l == 0)
		return(NIL(char*));
	ptr = stakalloc((unsigned)l);
	if(--l > 0)
	{
		if(sfread(in,ptr,(size_t)l)!=(size_t)l)
			return(NIL(char*));
	}
	ptr[l] = 0;
	return(ptr);
}
