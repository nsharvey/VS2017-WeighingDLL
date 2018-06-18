#!/usr/bin/perl
############################################################################
local($path, $file);
die "Usage: " . $0 . " file [... files]\n" if ($#ARGV < 0);

undef($/);

sub checkViews31Link {
    local($file) = @_;
    local($needOldlibs) = "";

    if ($file =~ m|ilviews/chartpnl\.h|) {
	$needOldlibs .= "ilvedit31 ";
    }

    if ($file =~ m|ilviews/varmgr\.h| ||
	$file =~ m|ilviews/varcell\.h| ||
	$file =~ m|ilviews/vcontint\.h| ||
	$file =~ m|ilviews/vmgrint\.h| ||
	$file =~ m|ilviews/vrgadcon\.h| ||
	$file =~ m|ilviews/vrgadmgr\.h| ||
	$file =~ m|ilviews/vrgcnbpg\.h| ||
	$file =~ m|ilviews/vrgdcint\.h| ||
	$file =~ m|ilviews/vrmgrint\.h| ||
	$file =~ m|ilviews/variable\.h| ||
	$file =~ m|ilviews/ilvparse\.h| ||
	$file =~ m|ilviews/varcont\.h| ||
	$file =~ m|ilviews/ilvvar\.h| ||
        $file =~ m|ilviews/attribut\.h| ||
	$file =~ m|ilviews/attrcont\.h| ||
	$file =~ m|ilviews/ilvattr\.h| ||
	$file =~ m|ilviews/gaugattr\.h| ||
	$file =~ m|ilviews/animattr\.h| ||
	$file =~ m|ilviews/attrmgr\.h| ||
	$file =~ m|ilviews/gadattr\.h| ||
	$file =~ m|ilviews/attitem\.h| ||
	$file =~ m|ilviews/variable/actval\.h| ||
	$file =~ m|ilviews/variable/all\.h| ||
	$file =~ m|ilviews/variable/buffer\.h| ||
	$file =~ m|ilviews/variable/ccell\.h| ||
	$file =~ m|ilviews/variable/cell\.h| ||
	$file =~ m|ilviews/variable/celldump\.h| ||
	$file =~ m|ilviews/variable/cellfun\.h| ||
	$file =~ m|ilviews/variable/cellxref\.h| ||
	$file =~ m|ilviews/variable/cexpr\.h| ||
	$file =~ m|ilviews/variable/cluster\.h| ||
	$file =~ m|ilviews/variable/expr\.h| ||
	$file =~ m|ilviews/variable/hash\.h| ||
	$file =~ m|ilviews/variable/list\.h| ||
	$file =~ m|ilviews/variable/magic\.h| ||
	$file =~ m|ilviews/variable/manip\.h| ||
	$file =~ m|ilviews/variable/mlk\.h| ||
	$file =~ m|ilviews/variable/name\.h| ||
	$file =~ m|ilviews/variable/ostreams\.h| ||
	$file =~ m|ilviews/variable/sheet\.h| ||
	$file =~ m|ilviews/variable/stack\.h| ||
	$file =~ m|ilviews/variable/streams\.h| ||
	$file =~ m|ilviews/attrmac\.h|) {
	$needOldlibs .= "ilvvar31 ";
    }

    if ($file =~ m|ilviews/celledt\.h| ||
	$file =~ m|ilviews/cell\.h| ||
	$file =~ m|ilviews/cellmgr\.h| ||
	$file =~ m|ilviews/cellgr\.h| ||
	$file =~ m|ilviews/cellint\.h| ||
	$file =~ m|ilviews/cellio\.h| ||
	$file =~ m|ilviews/tablcell\.h| ||
	$file =~ m|ilviews/chartcsc\.h| ||
	$file =~ m|ilviews/comboint\.h| ||
	$file =~ m|ilviews/matinter\.h| ||
	$file =~ m|ilviews/matsel\.h| ||
	$file =~ m|ilviews/mbinter\.h| ||
	$file =~ m|ilviews/optmint\.h| ||
	$file =~ m|ilviews/popinter\.h| ||
	$file =~ m|ilviews/rectschc\.h| ||
	$file =~ m|ilviews/sbinter\.h| ||
	$file =~ m|ilviews/sclinter\.h| ||
	$file =~ m|ilviews/sclist\.h| ||
	$file =~ m|ilviews/scmatint\.h| ||
	$file =~ m|ilviews/scmatrix\.h| ||
	$file =~ m|ilviews/scmatsel\.h| ||
	$file =~ m|ilviews/scomboin\.h| ||
	$file =~ m|ilviews/sheetint\.h| ||
	$file =~ m|ilviews/slidint\.h| ||
	$file =~ m|ilviews/slinter\.h| ||
	$file =~ m|ilviews/textint\.h| ||
	$file =~ m|ilviews/tfdinter\.h| ||
	$file =~ m|ilviews/vcombint\.h| ||
	$file =~ m|ilviews/vmatint\.h| ||
	$file =~ m|ilviews/vmatsel\.h| ||
	$file =~ m|ilviews/vmbinter\.h| ||
	$file =~ m|ilviews/voptmint\.h| ||
	$file =~ m|ilviews/vpopint\.h| ||
	$file =~ m|ilviews/vsbinter\.h| ||
	$file =~ m|ilviews/vsclint\.h| ||
	$file =~ m|ilviews/vscmatin\.h| ||
	$file =~ m|ilviews/vscmatsl\.h| ||
	$file =~ m|ilviews/vscombin\.h| ||
	$file =~ m|ilviews/vsheetin\.h| ||
	$file =~ m|ilviews/vslidint\.h| ||
	$file =~ m|ilviews/vslinter\.h| ||
	$file =~ m|ilviews/vtextint\.h| ||
	$file =~ m|ilviews/vtfinter\.h|) {
	$needOldlibs .= "ilvgadgt31 ";
    }

    if ($file =~ m|ilviews/chartcnt\.h| ||
	$file =~ m|ilviews/chart\.h| ||
	$file =~ m|ilviews/piechart\.h| ||
	$file =~ m|ilviews/chartint\.h| ||
	$file =~ m|ilviews/contint\.h| ||
	$file =~ m|ilviews/dragint\.h| ||
	$file =~ m|ilviews/exclint\.h| ||
	$file =~ m|ilviews/gaugeint\.h| ||
	$file =~ m|ilviews/mgrinter\.h| ||
	$file =~ m|ilviews/objinter\.h| ||
	$file =~ m|ilviews/scmgrint\.h| ||
	$file =~ m|ilviews/vexclint\.h| ||
	$file =~ m|ilviews/vscmgrin\.h|) {
	$needOldlibs .= "views31 ";
    }

    if ($file =~ m|ilviews/protos/chartacc\.h|) {
	$needOldlibs .= "ilvprotos31 ";
    }

    if ($file =~ m|ilviews/protos/vrvalsrc\.h| ||
        $file =~ m|ilviews/protos/provrmgr\.h|) {
	$needOldlibs .= "ilvvrpro31";
    }

    if ($needOldlibs ne "") {
	print STDOUT
	    "\n\tThe library(ies) ${needOldlibs}must be linked when this file is used.\n\t";
    }
}

foreach $path (@ARGV) {
  if (open FILE, "<$path") {
    $file = <FILE>;
    close FILE;

    # Remove ^M's and trailing spaces
    $file =~ s|\r||gs;
    $file =~ s|[ \t]*\n|\n|gs;

    # Convert file
    $file =~ s|_Ilv_Error_H|_Ilv_Base_Error_H|gs;
    $file =~ s|ilviews/error\.h|ilviews/base/error\.h|gs;
    $file =~ s|_Ilv_Geometry_H|_Ilv_Base_Geometry_H|gs;
    $file =~ s|ilviews/geometry\.h|ilviews/base/geometry\.h|gs;
    $file =~ s|_Ilv_Script_H|_Ilv_Base_Script_H|gs;
    $file =~ s|ilviews/script\.h|ilviews/base/script\.h|gs;
    $file =~ s|_Ilv_Graphic_H|_Ilv_Base_Graphic_H|gs;
    $file =~ s|ilviews/graphic\.h|ilviews/base/graphic\.h|gs;
    $file =~ s|_Ilv_Gadget_H|_Ilv_Base_Gadget_H|gs;
    $file =~ s|ilviews/gadget\.h|ilviews/base/gadget\.h|gs;
    $file =~ s|_Ilv_Sstream_H|_Ilv_Base_Sstream_H|gs;
    $file =~ s|ilviews/sstream\.h|ilviews/base/sstream\.h|gs;
    $file =~ s|_Ilv_View_H|_Ilv_Base_View_H|gs;
    $file =~ s|ilviews/view\.h|ilviews/base/view\.h|gs;
    $file =~ s|_Ilv_Config_H|_Ilv_Base_Config_H|gs;
    $file =~ s|ilviews/config\.h|ilviews/base/config\.h|gs;
    $file =~ s|_Ilv_String_H|_Ilv_Base_String_H|gs;
    $file =~ s|ilviews/string\.h|ilviews/base/string\.h|gs;
    $file =~ s|_Ilv_Alloc_H|_Ilv_Base_Alloc_H|gs;
    $file =~ s|ilviews/alloc\.h|ilviews/base/alloc\.h|gs;
    $file =~ s|_Ilv_PathList_H|_Ilv_Base_Pathlist_H|gs;
    $file =~ s|ilviews/pathlist\.h|ilviews/base/pathlist\.h|gs;
    $file =~ s|_Ilv_Message_H|_Ilv_Base_Message_H|gs;
    $file =~ s|ilviews/message\.h|ilviews/base/message\.h|gs;
    $file =~ s|_Ilv_PathName_H|_Ilv_Base_PathName_H|gs;
    $file =~ s|ilviews/pathname\.h|ilviews/base/pathname\.h|gs;
    $file =~ s|_Ilv_Memory_H|_Ilv_Base_Memory_H|gs;
    $file =~ s|ilviews/memory\.h|ilviews/base/memory\.h|gs;
    $file =~ s|_Ilv_Modules_H|_Ilv_Base_Modules_H|gs;
    $file =~ s|ilviews/modules\.h|ilviews/base/modules\.h|gs;
    $file =~ s|_Ilv_Hash_H|_Ilv_Base_Hash_H|gs;
    $file =~ s|ilviews/hash\.h|ilviews/base/hash\.h|gs;
    $file =~ s|_Ilv_Region_H|_Ilv_Base_Region_H|gs;
    $file =~ s|ilviews/region\.h|ilviews/base/region\.h|gs;
    $file =~ s|_Ilv_Locale_H|_Ilv_Base_Locale_H|gs;
    $file =~ s|ilviews/locale\.h|ilviews/base/locale.h|gs;
    $file =~ s|_Ilv_Arg_H|_Ilv_Base_Value_H|gs;
    $file =~ s|ilviews/arg\.h|ilviews/base/value.h|gs;
    $file =~ s|_Ilv_Safeptr_H|_Ilv_Base_Safeptr_H|gs;
    $file =~ s|ilviews/safeptr\.h|ilviews/base/safeptr.h|gs;
    $file =~ s|_Ilv_Link_H|_Ilv_Base_Link_H|gs;
    $file =~ s|ilviews/link\.h|ilviews/base/link.h|gs;
    $file =~ s|_Ilv_Ptarray_H|_Ilv_Base_Ptarray_H|gs;
    $file =~ s|ilviews/ptarray\.h|ilviews/base/ptarray.h|gs;
    $file =~ s|_Ilv_Colormap_H|_Ilv_Base_Colormap_H|gs;
    $file =~ s|ilviews/colormap.h|ilviews/base/colormap.h|gs;
    $file =~ s|_Ilv_Gcontext_H|_Ilv_Base_Gcontext_H|gs;
    $file =~ s|ilviews/gcontext\.h|ilviews/base/gcontext\.h|gs;
    $file =~ s|_Ilv_Action_H|_Ilv_Base_Action_H|gs;
    $file =~ s|ilviews/action\.h|ilviews/base/action.h|gs;
    $file =~ s|_Ilv_Array_H|_Ilv_Base_Array_H|gs;
    $file =~ s|ilviews/array\.h|ilviews/base/array.h|gs;
    $file =~ s|_Ilv_Clssinfo_H|_Ilv_Base_Clssinfo_H|gs;
    $file =~ s|ilviews/clssinfo\.h|ilviews/base/clssinfo.h|gs;
    $file =~ s|_Ilv_Command_H|_Ilv_Base_Command_H|gs;
    $file =~ s|ilviews/command\.h|ilviews/base/command.h|gs;
    $file =~ s|_Ilv_Dellist_H|_Ilv_Base_Dellist_H|gs;
    $file =~ s|ilviews/dellist\.h|ilviews/base/dellist.h|gs;
    $file =~ s|_Ilv_Event_H|_Ilv_Base_Event_H|gs;
    $file =~ s|ilviews/event\.h|ilviews/base/event.h|gs;
    $file =~ s|_Ilv_Evloop_H|_Ilv_Base_Evloop_H|gs;
    $file =~ s|ilviews/evloop\.h|ilviews/base/evloop.h|gs;
    $file =~ s|_Ilv_Im_H|_Ilv_Base_Im_H|gs;
    $file =~ s|ilviews/im\.h|ilviews/base/im.h|gs;
    $file =~ s|_Ilv_Iostream_H|_Ilv_Base_Iostream_H|gs;
    $file =~ s|ilviews/iostream\.h|ilviews/base/iostream.h|gs;
    $file =~ s|_Ilv_Look_H|_Ilv_Base_Look_H|gs;
    $file =~ s|ilviews/look\.h|ilviews/base/look.h|gs;
    $file =~ s|_Ilv_Observer_H|_Ilv_Base_Observer_H|gs;
    $file =~ s|ilviews/observer\.h|ilviews/base/observer.h|gs;
    $file =~ s|_Ilv_Port_H|_Ilv_Base_Port_H|gs;
    $file =~ s|ilviews/port\.h|ilviews/base/port.h|gs;
    $file =~ s|_Ilv_Ilvres_H|_Ilv_Base_Resource_H|gs;
    $file =~ s|ilviews/ilvres\.h|ilviews/base/resource.h|gs;
    $file =~ s|_Ilv_Resource_H|_Ilv_Base_Resource_H|gs;
    $file =~ s|ilviews/resource\.h|ilviews/base/resource.h|gs;
    $file =~ s|_Ilv_Timer_H|_Ilv_Base_Timer_H|gs;
    $file =~ s|ilviews/timer\.h|ilviews/base/timer.h|gs;
    $file =~ s|_Ilv_Clip_H|_Ilv_Base_Clip_H|gs;
    $file =~ s|ilviews/clip\.h|ilviews/base/clip.h|gs;

    $file =~ s|_Ilv_Accel_H|_Ilv_Util_Accel_H|gs;
    $file =~ s|ilviews/accel\.h|ilviews/util/accel\.h|gs;
    $file =~ s|_Ilv_Datablck_H|_Ilv_Util_Datablck_H|gs;
    $file =~ s|ilviews/datablck\.h|ilviews/util/datablck\.h|gs;
    $file =~ s|_Ilv_Dialogs_H|_Ilv_Util_Dialogs_H|gs;
    $file =~ s|ilviews/dialogs\.h|ilviews/util/dialogs\.h|gs;
    $file =~ s|_Ilv_Imutil_H|_Ilv_Util_Im_H|gs;
    $file =~ s|ilviews/imutil\.h|ilviews/util/im\.h|gs;
    $file =~ s|_Ilv_Proplist_H|_Ilv_Util_Proplist_H|gs;
    $file =~ s|ilviews/proplist\.h|ilviews/util/proplist\.h|gs;
    $file =~ s|_Ilv_Ps_H|_Ilv_Util_Ps_H|gs;
    $file =~ s|ilviews/ps\.h|ilviews/util/ps\.h|gs;
    $file =~ s|_Ilv_Runtime_H|_Ilv_Util_Runtime_H|gs;
    $file =~ s|ilviews/runtime\.h|ilviews/util/runtime\.h|gs;
    $file =~ s|_Ilv_Util_H|_Ilv_Util_Util_H|gs;
    $file =~ s|ilviews/util\.h|ilviews/util/util\.h|gs;
    $file =~ s|_Ilv_Grhash_H|_Ilv_Util_Grhash_H|gs;
    $file =~ s|ilviews/grhash\.h|ilviews/util/grhash\.h|gs;
    $file =~ s|_Ilv_Iurlstr_H|_Ilv_Util_Iurlstr_H|gs;
    $file =~ s|ilviews/iurlstr\.h|ilviews/util/iurlstr\.h|gs;
    $file =~ s|_Ilv_Dump_H|_Ilv_Util_Dump_H|gs;
    $file =~ s|ilviews/dump\.h|ilviews/util/dump\.h|gs;
    $file =~ s|_Ilv_Util_H|_Ilv_Util_Util_H|gs;
    $file =~ s|ilviews/util\.h|ilviews/util/util\.h|gs;
    $file =~ s|_Ilv_Animator_H|_Ilv_Util_Animator_H|gs;
    $file =~ s|ilviews/animator\.h|ilviews/util/animator.h|gs;
    $file =~ s|_Ilv_Evplayer_H|_Ilv_Util_Evplayer_H|gs;
    $file =~ s|ilviews/evplayer\.h|ilviews/util/evplayer.h|gs;
    $file =~ s|_Ilv_Drview_H|_Ilv_Util_Drview_H|gs;
    $file =~ s|_Ilv_DrView_H|_Ilv_Util_Drview_H|gs;
    $file =~ s|ilviews/drview\.h|ilviews/util/drview.h|gs;
    $file =~ s|_Ilv_Table_H|_Ilv_Util_Table_H|gs;
    $file =~ s|ilviews/table\.h|ilviews/util/table.h|gs;

    $file =~ s|_Ilv_Contain_H|_Ilv_Contain_Contain_H|gs;
    $file =~ s|ilviews/contain\.h|ilviews/contain/contain\.h|gs;
    $file =~ s|_Ilv_Cgadhold_H|_Ilv_Contain_Holder_H|gs;
    $file =~ s|ilviews/cgadhold\.h|ilviews/contain/holder\.h|gs;
   
    $file =~ s|_Ilv_Rectcont_H|_Ilv_Contain_Rectangl_H|gs;
    $file =~ s|ilviews/rectcont\.h|ilviews/contain/rectangl\.h|gs;

    $file =~ s|_Ilv_Ilvpbm_H|_Ilv_Bitmaps_Pbm_H|gs;
    $file =~ s|ilviews/ilvpbm.h|ilviews/bitmaps/pbm.h|gs;
    $file =~ s|_Ilv_Ilvbmp_H|_Ilv_Bitmaps_Bmp_H|gs;
    $file =~ s|ilviews/ilvbmp.h|ilviews/bitmaps/bmp.h|gs;
    $file =~ s|_Ilv_Ilvgif_H|_Ilv_Bitmaps_Gif_H|gs;
    $file =~ s|ilviews/ilvgif.h|ilviews/bitmaps/gif.h|gs;
    $file =~ s|_Ilv_Bitmapio_H|_Ilv_Bitmaps_Io_H|gs;
    $file =~ s|ilviews/bitmapio.h|ilviews/bitmaps/io.h|gs;

    $file =~ s|_Ilv_Ivtstapi_H|_Ilv_Test_Display_H|gs;
    $file =~ s|ilviews/ivtstapi.h|ilviews/test/display.h|gs;
    $file =~ s|_Ilv_Testapi_H|_Ilv_Test_Api_H|gs;
    $file =~ s|ilviews/testapi.h|ilviews/test/api.h|gs;

    $file =~ s|_Ilv_Grio_H|_Ilv_Grapher_Io_H|gs;
    $file =~ s|ilviews/grio.h|ilviews/grapher/io.h|gs;
    $file =~ s|_Ilv_Grcom_H|_Ilv_Grapher_Commands_H|gs;
    $file =~ s|ilviews/grcom.h|ilviews/grapher/commands.h|gs;
    $file =~ s|_Ilv_Graphmgr_H|_Ilv_Grapher_Grapher_H|gs;
    $file =~ s|ilviews/graphmgr.h|ilviews/grapher/grapher.h|gs;
    $file =~ s|_Ilv_Glink_H|_Ilv_Grapher_Links_H|gs;
    $file =~ s|ilviews/glink.h|ilviews/grapher/links.h|gs;
    $file =~ s|_Ilv_Graphpin_H|_Ilv_Grapher_Pin_H|gs;
    $file =~ s|ilviews/graphpin.h|ilviews/grapher/pin.h|gs;
    $file =~ s|_Ilv_Ginterac_H|_Ilv_Grapher_Inters_H|gs;
    $file =~ s|ilviews/ginterac.h|ilviews/grapher/inters.h|gs;
    $file =~ s|_Ilv_Grselint_H|_Ilv_Grapher_Selinter_H|gs;
    $file =~ s|ilviews/grselint.h|ilviews/grapher/selinter.h|gs;
    $file =~ s|_Ilv_LinkHand_H|_Ilv_Grapher_Linkhand_H|gs;
    $file =~ s|_Ilv_Linkhand_H|_Ilv_Grapher_Linkhand_H|gs;
    $file =~ s|ilviews/linkhand\.h|ilviews/grapher/linkhand.h|gs;
    $file =~ s|_Ilv_Rectscgr_H|_Ilv_Gadgraph_Rectscgr_H|gs;
    $file =~ s|ilviews/rectscgr\.h|ilviews/gadgraph/rectscgr.h|gs;
    $file =~ s|_Ilv_Grapher_Rectscgr_H|_Ilv_Gadgraph_H|gs;
    $file =~ s|ilviews/gadmgr/rectscgr\.h|ilviews/gadgraph/rectscgr.h|gs;
    $file =~ s|_Ilv_Grapher_Scrlrect_h|_Ilv_Gadmgr|gs;
    $file =~ s|ilviews/grapher/scrlrect\.h|ilviews/gadmgr/rectscgr.h|gs;
    $file =~ s|_Ilv_Links_H|_Ilv_Grapher_Alllinks_H|gs;
    $file =~ s|ilviews/links\.h|ilviews/grapher/alllinks.h|gs;
    $file =~ s|_Ilv_Plylink_H|_Ilv_Grapher_Polylink_H|gs;
    $file =~ s|ilviews/plylink\.h|ilviews/grapher/polylink.h|gs;

    $file =~ s|_Ilv_Graphics_H|_Ilv_Graphics_All_H|gs;
    $file =~ s|ilviews/graphics\.h|ilviews/graphics/all.h|gs;
    $file =~ s|_Ilv_Allobj_H|_Ilv_Graphics_All_H|gs;
    $file =~ s|ilviews/allobj\.h|ilviews/graphics/all.h|gs;
    $file =~ s|_Ilv_Rectview_H|_Ilv_Graphics_Rectview_H|gs;
    $file =~ s|ilviews/rectview\.h|ilviews/graphics/rectview.h|gs;
    $file =~ s|_Ilv_Smartset_H|_Ilv_Graphics_Smartset_H|gs;
    $file =~ s|ilviews/smartset\.h|ilviews/graphics/smartset.h|gs;
    $file =~ s|_Ilv_Adapter_H|_Ilv_Graphics_Adapter_H|gs;
    $file =~ s|ilviews/adapter\.h|ilviews/graphics/adapter.h|gs;
    $file =~ s|_Ilv_Arcobj_H|_Ilv_Graphics_Arc_H|gs;
    $file =~ s|ilviews/arcobj\.h|ilviews/graphics/arc.h|gs;
    $file =~ s|_Ilv_Attach_H|_Ilv_Graphics_Attach_H|gs;
    $file =~ s|ilviews/attach\.h|ilviews/graphics/attach.h|gs;
    $file =~ s|_Ilv_Cirgauge_H|_Ilv_Graphics_Cirgauge_H|gs;
    $file =~ s|ilviews/cirgauge\.h|ilviews/graphics/cirgauge.h|gs;
    $file =~ s|_Ilv_Cirscale_H|_Ilv_Graphics_Cirscale_H|gs;
    $file =~ s|ilviews/cirscale\.h|ilviews/graphics/cirscale.h|gs;
    $file =~ s|_Ilv_Ellipse_H|_Ilv_Graphics_Ellipse_H|gs;
    $file =~ s|ilviews/ellipse\.h|ilviews/graphics/ellipse.h|gs;
    $file =~ s|_Ilv_Gauge_H|_Ilv_Graphics_Gauge_H|gs;
    $file =~ s|ilviews/gauge\.h|ilviews/graphics/gauge.h|gs;
    $file =~ s|_Ilv_Geomhan_H|_Ilv_Graphics_Geomhan_H|gs;
    $file =~ s|ilviews/geomhan\.h|ilviews/graphics/geomhan.h|gs;
    $file =~ s|_Ilv_Gridrect_H|_Ilv_Graphics_Gridrect_H|gs;
    $file =~ s|ilviews/gridrect\.h|ilviews/graphics/gridrect.h|gs;
    $file =~ s|_Ilv_Graphand_H|_Ilv_Graphics_Handle_H|gs;
    $file =~ s|ilviews/graphand\.h|ilviews/graphics/handle.h|gs;
    $file =~ s|_Ilv_Gadhold_H|_Ilv_Graphics_Holder_H|gs;
    $file =~ s|ilviews/gadhold\.h|ilviews/graphics/holder.h|gs;
    $file =~ s|_Ilv_Icon_H|_Ilv_Graphics_Icon_H|gs;
    $file =~ s|ilviews/icon\.h|ilviews/graphics/icon.h|gs;
    $file =~ s|_Ilv_Tcicon_H|_Ilv_Graphics_Tcicon_H|gs;
    $file =~ s|ilviews/tcicon\.h|ilviews/graphics/tcicon.h|gs;
    $file =~ s|_Ilv_Graphio_H|_Ilv_Graphics_Io_H|gs;
    $file =~ s|ilviews/graphio\.h|ilviews/graphics/io.h|gs;
    $file =~ s|_Ilv_Label_H|_Ilv_Graphics_Label_H|gs;
    $file =~ s|ilviews/label\.h|ilviews/graphics/label.h|gs;
    $file =~ s|_Ilv_Lablist_H|_Ilv_Graphics_Lablist_H|gs;
    $file =~ s|ilviews/lablist\.h|ilviews/graphics/lablist.h|gs;
    $file =~ s|_Ilv_Lcfilter_H|_Ilv_Graphics_Lcfilter_H|gs;
    $file =~ s|ilviews/lcfilter\.h|ilviews/graphics/lcfilter.h|gs;
    $file =~ s|_Ilv_Lineobj_H|_Ilv_Graphics_Line_H|gs;
    $file =~ s|ilviews/lineobj\.h|ilviews/graphics/line.h|gs;
    $file =~ s|_Ilv_Marker_H|_Ilv_Graphics_Marker_H|gs;
    $file =~ s|ilviews/marker\.h|ilviews/graphics/marker.h|gs;
    $file =~ s|_Ilv_Objprop_H|_Ilv_Graphics_Objprop_H|gs;
    $file =~ s|ilviews/objprop\.h|ilviews/graphics/objprop.h|gs;
    $file =~ s|_Ilv_Outpoly_H|_Ilv_Graphics_Outpoly_H|gs;
    $file =~ s|ilviews/outpoly\.h|ilviews/graphics/outpoly.h|gs;
    $file =~ s|_Ilv_Grpath_H|_Ilv_Graphics_Path_H|gs;
    $file =~ s|ilviews/grpath\.h|ilviews/graphics/path.h|gs;
    $file =~ s|_Ilv_Polyline_H|_Ilv_Graphics_Polyline_H|gs;
    $file =~ s|ilviews/polyline\.h|ilviews/graphics/polyline.h|gs;
    $file =~ s|_Ilv_Polypts_H|_Ilv_Graphics_Polypts_H|gs;
    $file =~ s|ilviews/polypts\.h|ilviews/graphics/polypts.h|gs;
    $file =~ s|_Ilv_Polysel_H|_Ilv_Graphics_Polysel_H|gs;
    $file =~ s|ilviews/polysel\.h|ilviews/graphics/polysel.h|gs;
    $file =~ s|_Ilv_Rectobj_H|_Ilv_Graphics_Rectangl_H|gs;
    $file =~ s|ilviews/rectobj\.h|ilviews/graphics/rectangl.h|gs;
    $file =~ s|_Ilv_Rectview_H|_Ilv_Graphics_Rectview_H|gs;
    $file =~ s|ilviews/rectview\.h|ilviews/graphics/rectview.h|gs;
    $file =~ s|_Ilv_Relflab_H|_Ilv_Graphics_Relflab_H|gs;
    $file =~ s|ilviews/relflab\.h|ilviews/graphics/relflab.h|gs;
    $file =~ s|_Ilv_Relfline_H|_Ilv_Graphics_Relfline_H|gs;
    $file =~ s|ilviews/relfline\.h|ilviews/graphics/relfline.h|gs;
    $file =~ s|_Ilv_Relfpoly_H|_Ilv_Graphics_Relfpoly_H|gs;
    $file =~ s|ilviews/relfpoly\.h|ilviews/graphics/relfpoly.h|gs;
    $file =~ s|_Ilv_Relfrect_H|_Ilv_Graphics_Relfrect_H|gs;
    $file =~ s|ilviews/relfrect\.h|ilviews/graphics/relfrect.h|gs;
    $file =~ s|_Ilv_Roundrec_H|_Ilv_Graphics_Roundrec_H|gs;
    $file =~ s|ilviews/roundrec\.h|ilviews/graphics/roundrec.h|gs;
    $file =~ s|_Ilv_Scale_H|_Ilv_Graphics_Scale_H|gs;
    $file =~ s|ilviews/scale\.h|ilviews/graphics/scale.h|gs;
    $file =~ s|_Ilv_Select_H|_Ilv_Graphics_Select_H|gs;
    $file =~ s|ilviews/select\.h|ilviews/graphics/select.h|gs;
    $file =~ s|_Ilv_Selector_H|_Ilv_Graphics_Selector_H|gs;
    $file =~ s|ilviews/selector\.h|ilviews/graphics/selector.h|gs;
    $file =~ s|_Ilv_Selline_H|_Ilv_Graphics_Selline_H|gs;
    $file =~ s|ilviews/selline\.h|ilviews/graphics/selline.h|gs;
    $file =~ s|_Ilv_Graphset_H|_Ilv_Graphics_Set_H|gs;
    $file =~ s|ilviews/graphset\.h|ilviews/graphics/set.h|gs;
    $file =~ s|_Ilv_Shadellp_H|_Ilv_Graphics_Shadellp_H|gs;
    $file =~ s|ilviews/shadellp\.h|ilviews/graphics/shadellp.h|gs;
    $file =~ s|_Ilv_Shadlab_H|_Ilv_Graphics_Shadlab_H|gs;
    $file =~ s|ilviews/shadlab\.h|ilviews/graphics/shadlab.h|gs;
    $file =~ s|_Ilv_Shadrect_H|_Ilv_Graphics_Shadrect_H|gs;
    $file =~ s|ilviews/shadrect\.h|ilviews/graphics/shadrect.h|gs;
    $file =~ s|_Ilv_Splines_H|_Ilv_Graphics_Spline_H|gs;
    $file =~ s|ilviews/splines\.h|ilviews/graphics/spline.h|gs;
    $file =~ s|_Ilv_Tooltip_H|_Ilv_Graphics_Tooltip_H|gs;
    $file =~ s|ilviews/tooltip\.h|ilviews/graphics/tooltip.h|gs;
    $file =~ s|_Ilv_Zicon_H|_Ilv_Graphics_Zicon_H|gs;
    $file =~ s|ilviews/zicon\.h|ilviews/graphics/zicon.h|gs;
    $file =~ s|_Ilv_Zoomlab_H|_Ilv_Graphics_Zoomlab_H|gs;
    $file =~ s|ilviews/zoomlab\.h|ilviews/graphics/zoomlab.h|gs;

    $file =~ s|_Ilv_Bidiitf_H|_Ilv_Bidi_Interf_H|gs;
    $file =~ s|ilviews/bidiitf\.h|ilviews/bidi/interf.h|gs;

    $file =~ s|_Ilv_Selectic_H|_Ilv_Icons_Select_H|gs;
    $file =~ s|ilviews/selectic\.h|ilviews/icons/select.h|gs;
    $file =~ s|_Ilv_Zoominic_H|_Ilv_Icons_Zoomin_H|gs;
    $file =~ s|ilviews/zoominic\.h|ilviews/icons/zoomin.h|gs;
    $file =~ s|_Ilv_Zoomout_H|_Ilv_Icons_Zoomout_H|gs;
    $file =~ s|ilviews/zoomout\.h|ilviews/icons/zoomout.h|gs;
    
    $file =~ s|_Ilv_Utilint_H|_Ilv_Manager_Utilint_H|gs;
    $file =~ s|ilviews/utilint\.h|ilviews/manager/utilint.h|gs;
    $file =~ s|_Ilv_Quadtree_H|_Ilv_Manager_Quadtree_H|gs;
    $file =~ s|ilviews/quadtree\.h|ilviews/manager/quadtree.h|gs;
    $file =~ s|_Ilv_Mkround_H|_Ilv_Manager_Mkround_H|gs;
    $file =~ s|ilviews/mkround\.h|ilviews/manager/mkround.h|gs;
    $file =~ s|_Ilv_Indexgr_H|_Ilv_Manager_Indexgr_H|gs;
    $file =~ s|ilviews/indexgr\.h|ilviews/manager/indexgr.h|gs;
    $file =~ s|_Ilv_Mgrdrhk_H|_Ilv_Manager_drawhook_H|gs;
    $file =~ s|ilviews/mgrdrhk\.h|ilviews/manager/drawhook.h|gs;
    $file =~ s|_Ilv_Allmgr_H|_Ilv_Manager_All_H|gs;
    $file =~ s|ilviews/allmgr\.h|ilviews/manager/all.h|gs;
    $file =~ s|_Ilv_Manager_H|_Ilv_Manager_Manager_H|gs;
    $file =~ s|ilviews/manager\.h|ilviews/manager/manager.h|gs;
    $file =~ s|_Ilv_Mgrselhk_H|_Ilv_Manager_Selhook_H|gs;
    $file =~ s|ilviews/mgrselhk\.h|ilviews/manager/selhook.h|gs;
    $file =~ s|_Ilv_Mgrgrid_H|_Ilv_Manager_grid_H|gs;
    $file =~ s|ilviews/mgrgrid\.h|ilviews/manager/grid.h|gs;
    $file =~ s|_Ilv_Mgadhold_H|_Ilv_Manager_Holder_H|gs;
    $file =~ s|ilviews/mgadhold\.h|ilviews/manager/holder.h|gs;
    $file =~ s|_Ilv_Rectmgr_H|_Ilv_Manager_Rectangl_H|gs;
    $file =~ s|ilviews/rectmgr\.h|ilviews/manager/rectangl.h|gs;
    $file =~ s|_Ilv_Magview_H|_Ilv_Manager_Magview_H|gs;
    $file =~ s|ilviews/magview\.h|ilviews/manager/magview.h|gs;
    $file =~ s|_Ilv_Mgrtxtin_H|_Ilv_Gadmgr_Txtinter_H|gs;
    $file =~ s|ilviews/mgrtxtin\.h|ilviews/gadmgr/txtinter.h|gs;
    $file =~ s|_Ilv_Manager_Txtinter_H|_Ilv_Gadmgr_Txtinter_H|gs;
    $file =~ s|ilviews/manager/txtinter.h|ilviews/gadmgr/txtinter.h|gs;
    $file =~ s|_Ilv_Movresh_H|_Ilv_Manager_Movresh_H|gs;
    $file =~ s|ilviews/movresh\.h|ilviews/manager/movresh.h|gs;
    $file =~ s|_Ilv_Movinter_H|_Ilv_Manager_Movinter_H|gs;
    $file =~ s|ilviews/movinter\.h|ilviews/manager/movinter.h|gs;
    $file =~ s|_Ilv_Reshint_H|_Ilv_Manager_Reshint_H|gs;
    $file =~ s|ilviews/reshint\.h|ilviews/manager/reshint.h|gs;
    $file =~ s|_Ilv_Manager_Mgrcom_H|_Ilv_Manager_Commands_H|gs;
    $file =~ s|ilviews/manager/mgrcom\.h|ilviews/manager/commands.h|gs;
    $file =~ s|_Ilv_Mgrcom_H|_Ilv_Manager_Commands_H|gs;
    $file =~ s|ilviews/mgrcom\.h|ilviews/manager/commands.h|gs;
    $file =~ s|_Ilv_Mgrio_H|_Ilv_Manager_Io_H|gs;
    $file =~ s|ilviews/mgrio\.h|ilviews/manager/io.h|gs;
    $file =~ s|_Ilv_Manager_Mgrio_H|_Ilv_Manager_Io_H|gs;
    $file =~ s|ilviews/manager/mgrio\.h|ilviews/manager/io.h|gs;
    $file =~ s|_Ilv_Mgrlayer_H|_Ilv_Manager_Layer_H|gs;
    $file =~ s|ilviews/mgrlayer\.h|ilviews/manager/layer.h|gs;
    $file =~ s|_Ilv_Manager_Mgrlayer_H|_Ilv_Manager_Layer_H|gs;
    $file =~ s|ilviews/manager/mgrlayer\.h|ilviews/manager/layer.h|gs;
    $file =~ s|_Ilv_Dragrin_H|_Ilv_Manager_Dragrin_H|gs;
    $file =~ s|ilviews/dragrin\.h|ilviews/manager/dragrin.h|gs;
    $file =~ s|_Ilv_Selinter_H|_Ilv_Manager_Selinter_H|gs;
    $file =~ s|ilviews/selinter\.h|ilviews/manager/selinter.h|gs;
    $file =~ s|_Ilv_Interact_H|_Ilv_Manager_Interact_H|gs;
    $file =~ s|ilviews/interact\.h|ilviews/manager/interact.h|gs;
    $file =~ s|_Ilv_Rotinter_H|_Ilv_Manager_Rotinter_H|gs;
    $file =~ s|ilviews/rotinter\.h|ilviews/manager/rotinter.h|gs;
    $file =~ s|_Ilv_Polyint_H|_Ilv_Manager_Polyint_H|gs;
    $file =~ s|ilviews/polyint\.h|ilviews/manager/polyint.h|gs;
    $file =~ s|_Ilv_Mklinein_H|_Ilv_Manager_Mklinein_H|gs;
    $file =~ s|ilviews/mklinein\.h|ilviews/manager/mklinein.h|gs;
    $file =~ s|_Ilv_Mkarcin_H|_Ilv_Manager_Mkarcin_H|gs;
    $file =~ s|ilviews/mkarcin\.h|ilviews/manager/mkarcin.h|gs;
    $file =~ s|_Ilv_Geointer_H|_Ilv_Manager_Geointer_H|gs;
    $file =~ s|ilviews/geointer\.h|ilviews/manager/geointer.h|gs;
    $file =~ s|_Ilv_Mkrectin_H|_Ilv_Manager_Mkrectin_H|gs;
    $file =~ s|ilviews/mkrectin\.h|ilviews/manager/mkrectin.h|gs;
    $file =~ s|_Ilv_Mkrelfin_H|_Ilv_Manager_Mkrelfin_H|gs;
    $file =~ s|ilviews/mkrelfin\.h|ilviews/manager/mkrelfin.h|gs;
    $file =~ s|_Ilv_Mkshadin_H|_Ilv_Manager_Mkshadin_H|gs;
    $file =~ s|ilviews/mkshadin\.h|ilviews/manager/mkshadin.h|gs;
    $file =~ s|_Ilv_Mkpolyin_H|_Ilv_Manager_Mkpolyin_H|gs;
    $file =~ s|ilviews/mkpolyin\.h|ilviews/manager/mkpolyin.h|gs;
    $file =~ s|_Ilv_Mgrddrop_H|_Ilv_Manager_Ddinter_H|gs;
    $file =~ s|ilviews/mgrddrop\.h|ilviews/manager/ddinter.h|gs;
    $file =~ s|_Ilv_Applylst_H|_Ilv_Manager_Applylst_H|gs;
    $file =~ s|ilviews/applylst\.h|ilviews/manager/applylst.h|gs;

    $file =~ s|_Ilv_Gadmgr_H|_Ilv_Gadmgr_Gadmgr_H|gs;
    $file =~ s|ilviews/gadmgr\.h|ilviews/gadmgr/gadmgr.h|gs;
    $file =~ s|_Ilv_Mathook_H|_Ilv_Gadmgr_Mathook_H|gs;
    $file =~ s|ilviews/mathook\.h|ilviews/gadmgr/mathook.h|gs;
    $file =~ s|_Ilv_Gadgets_Mathook_H|_Ilv_Gadmgr_Mathook_H|gs;
    $file =~ s|ilviews/gadgets/mathook\.h|ilviews/gadmgr/mathook.h|gs;
    $file =~ s|_Ilv_Mgrnbpg_H|_Ilv_Gadmgr_Mgrnbpg_H|gs;
    $file =~ s|ilviews/mgrnbpg\.h|ilviews/gadmgr/mgrnbpg.h|gs;
    $file =~ s|_Ilv_Mgrscrol_H|_Ilv_Gadmgr_Scrlhook_H|gs;
    $file =~ s|ilviews/mgrscrol\.h|ilviews/gadmgr/scrlhook.h|gs;
    $file =~ s|_Ilv_Mgrstrin_H|_Ilv_Gadmgr_Strinter_H|gs;
    $file =~ s|ilviews/mgrstrin\.h|ilviews/gadmgr/strinter.h|gs;
    $file =~ s|_Ilv_Mkrellab_H|_Ilv_Gadmgr_Mkrellab_H|gs;
    $file =~ s|ilviews/mkrellab\.h|ilviews/gadmgr/mkrellab.h|gs;
    $file =~ s|_Ilv_Rectscgr_H|_Ilv_Gadmgr_Rectscgr|gs;
    $file =~ s|ilviews/rectscgr\.h|ilviews/gadmgr/rectscgr.h|gs;
    $file =~ s|_Ilv_Rectscmg_H|_Ilv_Gadmgr_Rectscmg|gs;
    $file =~ s|ilviews/rectscmg\.h|ilviews/gadmgr/rectscmg.h|gs;
    $file =~ s|_Ilv_Txtinter_H|_Ilv_Gadmgr_Txtinter_H|gs;
    $file =~ s|ilviews/txtinter\.h|ilviews/gadmgr/txtinter.h|gs;
    $file =~ s|_Ilv_Txtinter_H|_Ilv_Gadmgr_Txtinter_H|gs;
    $file =~ s|ilviews/txtinter\.h|ilviews/gadmgr/txtinter.h|gs;

    $file =~ s|_Ilv_Windump_H|_Ilv_Windows_Dump_H|gs;
    $file =~ s|ilviews/windump\.h|ilviews/windows/dump.h|gs;

    $file =~ s|_Ilv_Amenu_H|_Ilv_Gadgets_Amenu_H|gs;
    $file =~ s|ilviews/amenu\.h|ilviews/gadgets/amenu.h|gs;
    $file =~ s|_Ilv_Appli_H|_Ilv_Gadgets_Appli_H|gs;
    $file =~ s|ilviews/appli\.h|ilviews/gadgets/appli.h|gs;
    $file =~ s|_Ilv_Arrowb_H|_Ilv_Gadgets_Arrowb_H|gs;
    $file =~ s|ilviews/arrowb\.h|ilviews/gadgets/arrowb.h|gs;
    $file =~ s|_Ilv_Button_H|_Ilv_Gadgets_Button_H|gs;
    $file =~ s|ilviews/button\.h|ilviews/gadgets/button.h|gs;
    $file =~ s|_Ilv_Colorch_H|_Ilv_Gadgets_Colorch_H|gs;
    $file =~ s|ilviews/colorch\.h|ilviews/gadgets/colorch.h|gs;
    $file =~ s|_Ilv_Combo_H|_Ilv_Gadgets_Combo_H|gs;
    $file =~ s|ilviews/combo\.h|ilviews/gadgets/combo.h|gs;
    $file =~ s|_Ilv_Ctoggle_H|_Ilv_Gadgets_Ctoggle_H|gs;
    $file =~ s|ilviews/ctoggle\.h|ilviews/gadgets/ctoggle.h|gs;
    $file =~ s|_Ilv_Datfield_H|_Ilv_Gadgets_Datfield_H|gs;
    $file =~ s|ilviews/datfield\.h|ilviews/gadgets/datfield.h|gs;
    $file =~ s|_Ilv_Dockpane_H|_Ilv_Gadgets_Dockpane_H|gs;
    $file =~ s|ilviews/dockpane\.h|ilviews/gadgets/dockpane.h|gs;
    $file =~ s|_Ilv_Fbrowser_H|_Ilv_Gadgets_Fbrowser_H|gs;
    $file =~ s|ilviews/fbrowser\.h|ilviews/gadgets/fbrowser.h|gs;
    $file =~ s|_Ilv_Filesel_H|_Ilv_Gadgets_Filesel_H|gs;
    $file =~ s|ilviews/filesel\.h|ilviews/gadgets/filesel.h|gs;
    $file =~ s|_Ilv_Fontsel_H|_Ilv_Gadgets_Fontsel_H|gs;
    $file =~ s|ilviews/fontsel\.h|ilviews/gadgets/fontsel.h|gs;
    $file =~ s|_Ilv_Frame_H|_Ilv_Gadgets_Frame_H|gs;
    $file =~ s|ilviews/frame\.h|ilviews/gadgets/frame.h|gs;
    $file =~ s|_Ilv_Gadcont_H|_Ilv_Gadgets_Gadcont_H|gs;
    $file =~ s|ilviews/gadcont\.h|ilviews/gadgets/gadcont.h|gs;
    $file =~ s|_Ilv_Gadgets_H|_Ilv_Gadgets_Gadgets_H|gs;
    $file =~ s|ilviews/gadgets\.h|ilviews/gadgets/gadgets.h|gs;
    $file =~ s|_Ilv_Idialog_H|_Ilv_Gadgets_Idialog_H|gs;
    $file =~ s|ilviews/idialog\.h|ilviews/gadgets/idialog.h|gs;
    $file =~ s|_Ilv_Matrix_H|_Ilv_Gadgets_Matrix_H|gs;
    $file =~ s|ilviews/matrix\.h|ilviews/gadgets/matrix.h|gs;
    $file =~ s|_Ilv_Menu_H|_Ilv_Gadgets_Menu_H|gs;
    $file =~ s|ilviews/menu\.h|ilviews/gadgets/menu.h|gs;
    $file =~ s|_Ilv_Menubar_H|_Ilv_Gadgets_Menubar_H|gs;
    $file =~ s|ilviews/menubar\.h|ilviews/gadgets/menubar.h|gs;
    $file =~ s|_Ilv_Msglabel_H|_Ilv_Gadgets_Msglabel_H|gs;
    $file =~ s|ilviews/msglabel\.h|ilviews/gadgets/msglabel.h|gs;
    $file =~ s|_Ilv_Notebook_H|_Ilv_Gadgets_Notebook_H|gs;
    $file =~ s|ilviews/notebook\.h|ilviews/gadgets/notebook.h|gs;
    $file =~ s|_Ilv_Numfield_H|_Ilv_Gadgets_Numfield_H|gs;
    $file =~ s|ilviews/numfield\.h|ilviews/gadgets/numfield.h|gs;
    $file =~ s|_Ilv_Panecont_H|_Ilv_Gadgets_Panecont_H|gs;
    $file =~ s|ilviews/panecont\.h|ilviews/gadgets/panecont.h|gs;
    $file =~ s|_Ilv_Passwded_H|_Ilv_Gadgets_Passwded_H|gs;
    $file =~ s|ilviews/passwded\.h|ilviews/gadgets/passwded.h|gs;
    $file =~ s|_Ilv_Optmenu_H|_Ilv_Gadgets_Optmenu_H|gs;
    $file =~ s|ilviews/optmenu\.h|ilviews/gadgets/optmenu.h|gs;
    $file =~ s|_Ilv_Rectgadc_H|_Ilv_Gadgets_Rectgadc_H|gs;
    $file =~ s|ilviews/rectgadc\.h|ilviews/gadgets/rectgadc.h|gs;
    $file =~ s|_Ilv_Rectscgc_H|_Ilv_Gadgets_Rectscgc_H|gs;
    $file =~ s|ilviews/rectscgc\.h|ilviews/gadgets/rectscgc.h|gs;
    $file =~ s|_Ilv_Scombo_H|_Ilv_Gadgets_Scombo_H|gs;
    $file =~ s|ilviews/scombo\.h|ilviews/gadgets/scombo.h|gs;
    $file =~ s|_Ilv_Scrollb_H|_Ilv_Gadgets_Scrollb_H|gs;
    $file =~ s|ilviews/scrollb\.h|ilviews/gadgets/scrollb.h|gs;
    $file =~ s|_Ilv_Scview_H|_Ilv_Gadgets_Scview_H|gs;
    $file =~ s|ilviews/scview\.h|ilviews/gadgets/scview.h|gs;
    $file =~ s|_Ilv_Sheet_H|_Ilv_Gadgets_Sheet_H|gs;
    $file =~ s|ilviews/sheet\.h|ilviews/gadgets/sheet.h|gs;
    $file =~ s|_Ilv_Slider_H|_Ilv_Gadgets_Slider_H|gs;
    $file =~ s|ilviews/slider\.h|ilviews/gadgets/slider.h|gs;
    $file =~ s|_Ilv_Slist_H|_Ilv_Gadgets_Slist_H|gs;
    $file =~ s|ilviews/slist\.h|ilviews/gadgets/slist.h|gs;
    $file =~ s|_Ilv_Spinbox_H|_Ilv_Gadgets_Spinbox_H|gs;
    $file =~ s|ilviews/spinbox\.h|ilviews/gadgets/spinbox.h|gs;
    $file =~ s|_Ilv_Splitgad_H|_Ilv_Gadgets_Splitgad_H|gs;
    $file =~ s|ilviews/splitgad\.h|ilviews/gadgets/splitgad.h|gs;
    $file =~ s|_Ilv_Stdialog_H|_Ilv_Gadgets_Stdialog_H|gs;
    $file =~ s|ilviews/stdialog\.h|ilviews/gadgets/stdialog.h|gs;
    $file =~ s|_Ilv_Text_H|_Ilv_Gadgets_Text_H|gs;
    $file =~ s|ilviews/text\.h|ilviews/gadgets/text.h|gs;
    $file =~ s|_Ilv_Textfd_H|_Ilv_Gadgets_Textfd_H|gs;
    $file =~ s|ilviews/textfd\.h|ilviews/gadgets/textfd.h|gs;
    $file =~ s|_Ilv_Toggle_H|_Ilv_Gadgets_Toggle_H|gs;
    $file =~ s|ilviews/toggle\.h|ilviews/gadgets/toggle.h|gs;
    $file =~ s|_Ilv_Toolbar_H|_Ilv_Gadgets_Toolbar_H|gs;
    $file =~ s|ilviews/toolbar\.h|ilviews/gadgets/toolbar.h|gs;
    $file =~ s|_Ilv_Tree_H|_Ilv_Gadgets_Tree_H|gs;
    $file =~ s|ilviews/tree\.h|ilviews/gadgets/tree.h|gs;
    $file =~ s|_Ilv__H|_Ilv_Gadgets__H|gs;
    $file =~ s|ilviews/\.h|ilviews/gadgets/.h|gs;
    $file =~ s|_Ilv__H|_Ilv_Gadgets__H|gs;
    $file =~ s|ilviews/\.h|ilviews/gadgets/.h|gs;

    $file =~ s|_Ilv_Inspanel_H|_Ilv_Edit_Inspanel_H|gs;
    $file =~ s|ilviews/inspanel\.h|ilviews/edit/inspanel.h|gs;
    $file =~ s|_Ilv_Respanel_H|_Ilv_Edit_Respanel_H|gs;
    $file =~ s|ilviews/respanel\.h|ilviews/edit/respanel.h|gs;

    if (open FILE, ">$path") {
      print FILE $file;
      close FILE;
      print "\'$path\' ";
      if ($file =~ m|getApplication|) {
	print STDOUT "\n\tWARNING: This script has found a call to getApplication.\n";
	print STDOUT "\tIf this is a call to IlvGadgetContainer::getApplication() const,\n\tyou should replace it with IlvApplication::GetApplication(const IlvContainer* cont).\n";
      }
      checkViews31Link($file);
      print "done.\n";
    } else {
      print "Couldn\'t open file $path for writing\n";
    }
  } else {
    print STDERR "Couldn\'t open file $path for reading\n";
  }
}
