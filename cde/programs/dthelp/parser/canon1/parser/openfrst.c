/* $XConsortium: openfrst.c /main/3 1995/11/08 09:39:20 rswiston $ */
/* Copyright 1988, 1989 Hewlett-Packard Co. */

/* Default open SYSTEM entity procedure */

#include "userinc.h"
#include "globdec.h"

void *m_openfirst(M_NOPAR)
  {
    return((void *) stdin) ;
    }


