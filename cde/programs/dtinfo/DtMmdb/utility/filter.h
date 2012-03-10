/*
 * $XConsortium: filter.h /main/4 1996/08/21 15:54:29 drk $
 *
 * Copyright (c) 1993 HAL Computer Systems International, Ltd.
 * All rights reserved.  Unpublished -- rights reserved under
 * the Copyright Laws of the United States.  USE OF A COPYRIGHT
 * NOTICE IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 * 
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE
 * SECRETS OF HAL COMPUTER SYSTEMS INTERNATIONAL, LTD.  USE,
 * DISCLOSURE, OR REPRODUCTION IS PROHIBITED WITHOUT THE
 * PRIOR EXPRESS WRITTEN PERMISSION OF HAL COMPUTER SYSTEMS
 * INTERNATIONAL, LTD.
 * 
 *                         RESTRICTED RIGHTS LEGEND
 * Use, duplication, or disclosure by the Government is subject
 * to the restrictions as set forth in subparagraph (c)(l)(ii)
 * of the Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013.
 *
 *          HAL COMPUTER SYSTEMS INTERNATIONAL, LTD.
 *                  1315 Dell Avenue
 *                  Campbell, CA  95008
 * 
 */


#ifndef _filter_h
#define _filter_h 1

#ifdef C_API
#include "utility/c_strstream.h"
#else
#include <strstream.h>
#endif

#include "utility/funcs.h"
#include "utility/buffer.h"

typedef istream& (*filter_func_t)(istream&);


class filter 
{
public:
   filter();
   virtual ~filter() ;

   static Boolean assigned() { return v_assign; };
   static filter_func_t filter_func() { return f_filt_func; } ;

   static void reset_filter_func() { v_assign = false; }; 
   static void set_filter_func(filter_func_t f) 
   { 
      v_assign = true; 
      f_filt_func = f; 
   };

   

protected:
   static Boolean v_assign;
   static filter_func_t f_filt_func; 
};

typedef filter* filterPtr;

#endif

