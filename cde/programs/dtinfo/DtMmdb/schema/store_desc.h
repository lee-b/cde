/*
 * $XConsortium: store_desc.h /main/6 1996/07/18 14:51:13 drk $
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


#ifndef _store_desc_h
#define _store_desc_h 1

#include "object/handler.h"
#include "schema/desc.h"

#include "storage/lru.h"
#include "storage/page_storage.h"
#include "storage/unixf_storage.h"

#define NUM_FILES 20
#define ACTIVE_UNIXF_SZ NUM_FILES
#define INACTIVE_UNIXF_SZ 1000


class store_desc : public desc 
{

public:
   store_desc(const char* name);
   store_desc(int class_code, const char* comment = "");
   ~store_desc();

   virtual abs_storage* get_store() { 
     return v_store_ptr; 
   };

   void set_mode(const char*);
   void set_order(const char*);

   int get_mode();
   mmdb_byte_order_t get_order();

   virtual ostream& asciiOut(ostream& out, Boolean last = true);

protected:
/*
   char mode_str[NAMESIZ];
   char order_str[NAMESIZ];
*/

#ifdef C_API
   static lru* v_unixf_pool_ptr;
#define v_unixf_pool (*v_unixf_pool_ptr)
#else
   static lru v_unixf_pool;
#endif

   abs_storage* v_store_ptr; 

private:
   char* mode_str;
   char* order_str;

#ifdef C_API
   friend void initialize_MMDB();
   friend void quit_MMDB();
#endif
};

class page_store_desc : public store_desc 
{

public:
   page_store_desc();
   ~page_store_desc() {};

   abs_storage* init_store(char* store_path);

   void sync_store();
   void quit_store();

   void set_page_sz(int);
   void set_cached_pages(int);

   virtual ostream& asciiOut(ostream& out, Boolean last = true);

protected:
   int page_sz;
   int cached_pages;
};

#endif
