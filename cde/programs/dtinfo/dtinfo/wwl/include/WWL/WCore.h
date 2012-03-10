/*
 * $XConsortium: WCore.h /main/3 1996/06/11 16:58:16 cde-hal $
 *
 * Copyright (c) 1991 HaL Computer Systems, Inc.  All rights reserved.
 * UNPUBLISHED -- rights reserved under the Copyright Laws of the United
 * States.  Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 * 
 * This software contains confidential information and trade secrets of HaL
 * Computer Systems, Inc.  Use, disclosure, or reproduction is prohibited
 * without the prior express written permission of HaL Computer Systems, Inc.
 * 
 *                         RESTRICTED RIGHTS LEGEND
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions as set forth in subparagraph (c)(l)(ii) of the Rights in
 * Technical Data and Computer Software clause at DFARS 252.227-7013.
 *                        HaL Computer Systems, Inc.
 *                  1315 Dell Avenue, Campbell, CA  95008
 * 
 */

// This code is automatically generated in -*- C++ -*-
#ifndef WCore_h
#define WCore_h

#include "wwl.h"
#include <X11/Object.h>
#include "WObject.h"
#include <X11/RectObj.h>
#include "WRect.h"
#include <X11/Core.h>

class WCore : public WRect {
public :
   DEFINE_INIT (WCore, WRect, widgetClass)
   DEFINE_POPUP_INIT (WCore, WRect, widgetClass)
   inline void	Map () const	{ XtMapWidget (widget); }
   inline void	Unmap () const	{ XtUnmapWidget (widget); }
   inline void  Raise () const
    { XRaiseWindow (XtDisplay (widget), XtWindow (widget)); }
   inline Widget Parent () const { return XtParent (widget); }
   inline void	AddEventHandler(EventMask em, Boolean b, XtEventHandler ev,
				caddr_t p) const {
      XtAddEventHandler(widget, em, b, ev, p);
   }

// I had to change this so it would compile with X stuff. -GSH-
   DEFINE_GETTER_SETTER (_Screen,void*,"screen")

   DEFINE_GETTER_SETTER(Depth,		   int,		   "depth")
   DEFINE_GETTER_SETTER(Colormap,	   void*,	   "colormap")
   DEFINE_GETTER_SETTER(Background,	   Pixel,	   "background")
   DEFINE_GETTER_SETTER(BackgroundPixmap,  Pixmap,	   "backgroundPixmap")
   DEFINE_GETTER_SETTER(BorderColor,	   Pixel,	   "borderColor")
   DEFINE_GETTER_SETTER(BorderPixmap,	   Pixmap,	   "borderPixmap")
   DEFINE_GETTER_SETTER(MappedWhenManaged, Boolean,	   "mappedWhenManaged")
   DEFINE_GETTER_SETTER(Translations,	   XtTranslations, "translations")
   DEFINE_GETTER_SETTER(Accelerators,	   XtTranslations, "accelerators")
};

#define	NULLWCore		WCore((Widget)0)

#endif // WCore_h
