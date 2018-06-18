// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: include/ivstudio/st2dlibini.h
// --------------------------------------------------------------------------
//
// Licensed Materials - Property of Rogue Wave Software, Inc.
// (c) Copyright Rogue Wave Software, Inc. 2012, 2018
// (c) Copyright IBM Corp. 2009, 2011
// (c) Copyright ILOG 1992, 2009
// All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// The Software and Documentation were developed at private expense and
// are "Commercial Items" as that term is defined at 48 CFR 2.101,
// consisting of "Commercial Computer Software" and
// "Commercial Computer Software Documentation", as such terms are
// used in 48 CFR 12.212 or 48 CFR 227.7202-1 through 227.7202-4,
// as applicable.
//
// --------------------------------------------------------------------------
// ivstudio library header files
// --------------------------------------------------------------------------

#if !defined(ILVNODEFAULTLOOK)
#if      !defined(__Ilv_Motif_H)
#include <ilviews/motif.h>
#endif
#if      !defined(__Ilv_Windows_H)
#include <ilviews/windows.h>
#endif
#if      !defined(__Ilv_Win95_H)
#include <ilviews/win95.h>
#endif
#if      !defined(__Ilv_Vx_H)
#include <ilviews/vx.h>
#endif
#endif
#if      !defined(__IlvSt_Stbuffer_H)
#include <ivstudio/stbuffer.h>
#endif
#if      !defined(__IlvSt_Bufview_H)
#include <ivstudio/bufview.h>
#endif
#if      !defined(__IlvSt_Cbinsp_H)
#include <ivstudio/cbinsp.h>
#endif
#if      !defined(__IlvSt_Cmdpan_H)
#include <ivstudio/cmdpan.h>
#endif
#if      !defined(__IlvSt_Cmnpanel_H)
#include <ivstudio/cmnpanel.h>
#endif
#if      !defined(__IlvSt_Codesc_H)
#include <ivstudio/codesc.h>
#endif
#if      !defined(__IlvSt_Command_H)
#include <ivstudio/command.h>
#endif
#if      !defined(__IlvSt_Document_H)
#include <ivstudio/document.h>
#endif
#if      !defined(__IlvSt_Edappli_H)
#include <ivstudio/edappli.h>
#endif
#if      !defined(__IlvSt_Edit_H)
#include <ivstudio/edit.h>
#endif
#if      !defined(__IlvSt_Editarc_H)
#include <ivstudio/editarc.h>
#endif
#if      !defined(__IlvSt_Editline_H)
#include <ivstudio/editline.h>
#endif
#if      !defined(__IlvSt_Editpoly_H)
#include <ivstudio/editpoly.h>
#endif
#if      !defined(__IlvSt_Editrndr_H)
#include <ivstudio/editrndr.h>
#endif
#if      !defined(__IlvSt_Editshdo_H)
#include <ivstudio/editshdo.h>
#endif
#if      !defined(__IlvSt_Error_H)
#include <ivstudio/error.h>
#endif
#if      !defined(__IlvSt_Eventseq_H)
#include <ivstudio/eventseq.h>
#endif
#if      !defined(__IlvSt_Gencom_H)
#include <ivstudio/gencom.h>
#endif
#if      !defined(__IlvSt_Geninsp_H)
#include <ivstudio/geninsp.h>
#endif
#if      !defined(__IlvSt_Inout_H)
#include <ivstudio/inout.h>
#endif
#if      !defined(__IlvSt_Inspect_H)
#include <ivstudio/inspect.h>
#endif
#if      !defined(__IlvSt_Mainpan_H)
#include <ivstudio/mainpan.h>
#endif
#if      !defined(__IlvSt_Message_H)
#include <ivstudio/message.h>
#endif
#if      !defined(__IlvSt_Mlangmsg_H)
#include <ivstudio/mlangmsg.h>
#endif
#if      !defined(__IlvSt_Mode_H)
#include <ivstudio/mode.h>
#endif
#if      !defined(__IlvSt_Name_H)
#include <ivstudio/name.h>
#endif
#if      !defined(__IlvSt_Object_H)
#include <ivstudio/object.h>
#endif
#if      !defined(__IlvSt_Option_H)
#include <ivstudio/option.h>
#endif
#if      !defined(__IlvSt_Panel_H)
#include <ivstudio/panel.h>
#endif
#if      !defined(__IlvSt_Stddrop_H)
#include <ivstudio/stddrop.h>
#endif
#if      !defined(__IlvSt_Stdesc_H)
#include <ivstudio/stdesc.h>
#endif
#if      !defined(__IlvSt_Sthelp_H)
#include <ivstudio/sthelp.h>
#endif
#if      !defined(__IlvSt_Stlayer_H)
#include <ivstudio/stlayer.h>
#endif
#if      !defined(__IlvSt_Stprop_H)
#include <ivstudio/stprop.h>
#endif
#if      !defined(__IlvSt_Stselect_H)
#include <ivstudio/stselect.h>
#endif
#if      !defined(__IlvSt_Sttext_H)
#include <ivstudio/sttext.h>
#endif
#if      !defined(__IlvSt_Studapp_H)
#include <ivstudio/studapp.h>
#endif
#if      !defined(__IlvSt_Studio_H)
#include <ivstudio/studio.h>
#endif
#if      !defined(__IlvSt_Toolbar_H)
#include <ivstudio/toolbar.h>
#endif
#if      !defined(__IlvSt_Util_H)
#include <ivstudio/util.h>
#endif
#if      !defined(__IlvSt_Vobj_H)
#include <ivstudio/vobj.h>
#endif
#if !defined(__IlvSt_Ddpalet_H)
#include <ivstudio/ddpalet.h>
#endif

// New inpsector inclusions
#if !defined(__IlvSt_Inspall_H)
#include <ivstudio/inspectors/inspall.h>
#endif

#if !defined(__IlvSt_Optpnl_H)
#include <ivstudio/optpnl.h>
#endif

#if !defined(__IlvSt_PropAcc_H)
#include <ivstudio/propacc.h>
#endif

// Other header files for the lib
#if      !defined(__Ilv_Base_Iostream_H)
#include <ilviews/base/iostream.h>
#endif
#if !defined(__Ilv_Graphics_Selector_H)
#include <ilviews/graphics/selector.h>
#endif

#ifndef __Ilv_Gadmgr_Rectscmg_H
#include <ilviews/gadmgr/rectscmg.h>
#endif

//== New object interactors
#ifndef __Ilv_Graphics_Inter_H
#include <ilviews/graphics/inter.h>
#endif

//== Bitmap Streamers
#ifndef __Ilv_Bitmaps_Ppm_H
#include <ilviews/bitmaps/ppm.h>
#endif

#ifndef __Ilv_Bitmaps_Png_H
#include <ilviews/bitmaps/png.h>
#endif

#ifndef __Ilv_Bitmaps_Bmp_H
#include <ilviews/bitmaps/bmp.h>
#endif

