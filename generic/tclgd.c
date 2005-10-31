/*
 * gdtcl
 *
 * Copyright (C) 2005 by Karl Lehenbauer, All Rights Reserved
 *
 * $Id: tclgd.c,v 1.6 2005-10-31 12:29:28 karl Exp $
 */

#include <tcl.h>
#include <gd.h>
#include "gdtcl.h"

static void
gd_complain(Tcl_Interp *interp, char *element) {
    Tcl_AppendResult (interp, " while converting ", element, " component", NULL);
}

static void
gd_complainX(Tcl_Interp *interp) {
    gd_complain (interp, "x");
}

static void
gd_complainY(Tcl_Interp *interp) {
    gd_complain (interp, "y");
}

static void
gd_complainX1(Tcl_Interp *interp) {
    gd_complain (interp, "x1");
}

static void
gd_complainY1(Tcl_Interp *interp) {
    gd_complain (interp, "y1");
}

static void
gd_complainX2(Tcl_Interp *interp) {
    gd_complain (interp, "x2");
}

static void
gd_complainY2(Tcl_Interp *interp) {
    gd_complain (interp, "y2");
}

static void
gd_complainWidth(Tcl_Interp *interp) {
    gd_complain (interp, "width");
}

static void
gd_complainHeight(Tcl_Interp *interp) {
    gd_complain (interp, "height");
}

static void
gd_complainStartDegrees(Tcl_Interp *interp) {
    gd_complain (interp, "startDegrees");
}

static void
gd_complainEndDegrees(Tcl_Interp *interp) {
    gd_complain (interp, "endDegrees");
}

static void
gd_complainCX(Tcl_Interp *interp) {
    gd_complain (interp, "cx");
}

static void
gd_complainCY(Tcl_Interp *interp) {
    gd_complain (interp, "cy");
}

static void
gd_complainRed(Tcl_Interp *interp) {
    gd_complain (interp, "red");
}

static void
gd_complainGreen(Tcl_Interp *interp) {
    gd_complain (interp, "green");
}

static void
gd_complainBlue(Tcl_Interp *interp) {
    gd_complain (interp, "blue");
}

static void
gd_complainAlpha(Tcl_Interp *interp) {
    gd_complain (interp, "alpha");
}

static void
gd_complainColor(Tcl_Interp *interp) {
    gd_complain (interp, "color");
}

static void
gd_complainAngle(Tcl_Interp *interp) {
    gd_complain (interp, "angle");
}

/*
 *----------------------------------------------------------------------
 *
 * gd_GDdeleteProc --
 *
 *    callback proc that deletes the corresponding gd image when one of our
 *    self-generated gd commands gets deleted
 *
 * Results:
 *    stuff
 *
 *----------------------------------------------------------------------
 */
void gd_GDdeleteProc (ClientData clientData) {
    gdImagePtr im = (gdImagePtr)clientData;

    gdImageDestroy(im);
}


/*
 *----------------------------------------------------------------------
 *
 * gd_GDdeleteProc --
 *
 *    callback proc that deletes the corresponding gd image when one of our
 *    self-generated gd commands gets deleted
 *
 * Results:
 *    stuff
 *
 *----------------------------------------------------------------------
 */
 int gdtcl_GetColor (Tcl_Interp *interp, Tcl_Obj *obj, int *color)
 {
     int optIndex;

     static CONST char *options[] = {
	"antialiased",
	"brushed",
	"styled",
	"styled_brushed",
	"tiled",
	"transparent",
	NULL
     };

    enum options {
	OPT_ANTIALIASED,
	OPT_BRUSHED,
	OPT_STYLED,
	OPT_STYLED_BRUSHED,
	OPT_TILED,
	OPT_TRANSPARENT
    };

    /* if color is an integer, we're done */
    if (Tcl_GetIntFromObj (interp, obj, color) == TCL_OK) {
	/* printf("gdtcl_GetColor returns normal color %d for %s\n", *color, Tcl_GetString (obj)); */
       return TCL_OK;
    }

    Tcl_ResetResult (interp);

    if (Tcl_GetIndexFromObj(interp, obj, options, "color", 
	TCL_EXACT, &optIndex) != TCL_OK) {
	Tcl_AppendResult (interp, ", or a color index", NULL);
	return TCL_ERROR;
    }

    switch ((enum options) optIndex) {
      case OPT_ANTIALIASED:
          *color = gdAntiAliased;
	  break;

      case OPT_BRUSHED:
          *color = gdBrushed;
	  break;

      case OPT_STYLED:
          *color = gdStyled;
	  break;

      case OPT_STYLED_BRUSHED:
          *color = gdStyledBrushed;

      case OPT_TILED:
          *color = gdTiled;
	  break;

      case OPT_TRANSPARENT:
          *color = gdTransparent;
	  break;
    }
    /* printf("gdtcl_GetColor returns custom color %d\n", *color); */
    return TCL_OK;
 }


/*
 *----------------------------------------------------------------------
 *
 * gdtcl_GDObjCmd --
 *
 *    dispatches the subcommands of a gd object command
 *
 * Results:
 *    stuff
 *
 *----------------------------------------------------------------------
 */
int
gd_GDObjCmd(ClientData cData, Tcl_Interp *interp, int objc, Tcl_Obj *CONST objv[])
{
    gdImagePtr im = (gdImagePtr)cData;
    int         optIndex;
    Tcl_Obj    *resultObj = Tcl_GetObjResult(interp);

    static CONST char *options[] = {
	"pixel",
	"line",
	"polygon",
	"rectangle",
	"filled_rectangle",
	"arc",
	"filled_arc",
	"filled_ellipse",
	"fill_to_border",
	"fill",
	"text",
	"text_bounds",
	"allocate_color",
	"closest_color",
	"closest_color_hwb",
	"exact_color",
	"resolve_color",
	"total_colors",
	"deallocate_color",
	"true_color",
	"interlace",
	"transparent",
	"set_anti_aliased",
	"set_anti_aliased_dont_blend",
	"set_brush",
	"set_tile",
	"set_style",
	"set_thickness",
	"alpha_blending",
	"save_alpha",
	"clip",
	"get_alpha",
	"bounds_safe",
	"green_component",
	"red_component",
	"blue_component",
	"width",
	"height",
	"copy",
	"copy_resized",
	"copy_resampled",
	"copy_rotated",
	"copy_merge",
	"copy_merge_grey",
	"copy_palette",
	"sharpen",
	"compare",
	"square_to_circle",
	"write_jpeg",
	"jpeg_data",
	"write_gif",
	"gif_data",
	"write_png",
	"png_data",
	"write_wbmp",
	"wbmp_data",
	"write_gd",
	"gd_data",
	"write_gd2",
	"gd2_data",
	(char *)NULL
    };

    enum options {
	OPT_PIXEL,
	OPT_LINE,
	OPT_POLYGON,
	OPT_RECTANGLE,
	OPT_FILLED_RECTANGLE,
	OPT_ARC,
	OPT_FILLED_ARC,
	OPT_FILLED_ELLIPSE,
	OPT_FILL_TO_BORDER,
	OPT_FILL,
	OPT_TEXT,
	OPT_TEXT_BOUNDS,
	OPT_ALLOCATE_COLOR,
	OPT_CLOSEST_COLOR,
	OPT_CLOSEST_COLOR_HWB,
	OPT_EXACT_COLOR,
	OPT_RESOLVE_COLOR,
	OPT_TOTAL_COLORS,
	OPT_DEALLOCATE_COLOR,
	OPT_TRUE_COLOR,
	OPT_INTERLACE,
	OPT_TRANSPARENT,
	OPT_SET_ANTI_ALIASED,
	OPT_SET_ANTI_ALIASED_DONT_BLEND,
	OPT_SET_BRUSH,
	OPT_SET_TILE,
	OPT_STYLE,
	OPT_SET_THICKNESS,
	OPT_ALPHA_BLENDING,
	OPT_SAVE_ALPHA,
	OPT_CLIP,
	OPT_GET_ALPHA,
	OPT_BOUNDS_SAFE,
	OPT_GREEN_COMPONENT,
	OPT_RED_COMPONENT,
	OPT_BLUE_COMPONENT,
	OPT_WIDTH,
	OPT_HEIGHT,
	OPT_COPY,
	OPT_COPY_RESIZED,
	OPT_COPY_RESAMPLED,
	OPT_COPY_ROTATED,
	OPT_COPY_MERGE,
	OPT_COPY_MERGE_GREY,
	OPT_COPY_PALETTE,
	OPT_SHARPEN,
	OPT_COMPARE,
	OPT_SQUARE_TO_CIRCLE,
	OPT_WRITE_JPEG,
	OPT_JPEG_DATA,
	OPT_WRITE_GIF,
	OPT_GIF_DATA,
	OPT_WRITE_PNG,
	OPT_PNG_DATA,
	OPT_WRITE_WBMP,
	OPT_WBMP_DATA,
	OPT_WRITE_GD,
	OPT_GD_DATA,
	OPT_WRITE_GD2,
	OPT_GD2_DATA
    };

    if (objc == 1) {
	Tcl_WrongNumArgs (interp, 1, objv, "option ?args?");
	return TCL_ERROR;
    }

    if (Tcl_GetIndexFromObj(interp, objv[1], options, "option", 
	TCL_EXACT, &optIndex) != TCL_OK) {
	return TCL_ERROR;
    }

    switch ((enum options) optIndex) {
      case OPT_PIXEL: {
	int x, y, color;

	if ((objc < 4) || (objc > 5)) {
	    Tcl_WrongNumArgs (interp, 2, objv, "x y ?color?");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &x) == TCL_ERROR) {
	   gd_complainX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &y) == TCL_ERROR) {
	   gd_complainY (interp);
	   return TCL_ERROR;
       }

       if (objc == 4) {
	   Tcl_SetIntObj (resultObj, gdImageGetPixel (im, x, y));
	   return TCL_OK;
	}

	if (gdtcl_GetColor (interp, objv[4], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageSetPixel (im, x, y, color);
	break;
      }

      case OPT_LINE: {
	int x1, y1, x2, y2, color;

	if (objc != 7) {
	    Tcl_WrongNumArgs (interp, 2, objv, "x1 y1 x2 y2 color");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &x1) == TCL_ERROR) {
	   gd_complainX1 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &y1) == TCL_ERROR) {
	   gd_complainY1 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &x2) == TCL_ERROR) {
	   gd_complainX2 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &y2) == TCL_ERROR) {
	   gd_complainY2 (interp);
	   return TCL_ERROR;
       }

	if (gdtcl_GetColor (interp, objv[6], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	/* printf("gdImageLine %d %d %d %d %d\n", x1, y1, x2, y2, color); */
	gdImageLine (im, x1, y1, x2, y2, color);
	break;
      }

      case OPT_POLYGON: {
        int         suboptIndex;
	Tcl_Obj   **pointObjList;
	int         nElements;
	int         objOffset;
	gdPoint     *points;
	int          i;
	int          x;
	int          y;
	int          color;

	static CONST char *subOptions[] = {
	    "filled",
	    "open",
	    "basic"
	};

	enum suboptions {
	    SUBOPT_FILLED,
	    SUBOPT_OPEN,
	    SUBOPT_BASIC
	};

        if ((objc < 4) || (objc > 5)) {
	    Tcl_WrongNumArgs (interp, 2, objv,"?filled|open? pointList color");
	    return TCL_ERROR;
	}

	if (objc == 4) {
	    suboptIndex = SUBOPT_BASIC;
	    objOffset = 3;
	} else {
	    objOffset = 4;
	    if (Tcl_GetIndexFromObj(interp, objv[2], subOptions, "suboption", 
		TCL_EXACT, &suboptIndex) != TCL_OK) {
		return TCL_ERROR;
	    }
	}

	if (Tcl_ListObjGetElements (interp, objv[objOffset], &nElements, &pointObjList) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	if ((nElements % 2 != 0) || (nElements < 6)) {
	    Tcl_WrongNumArgs (interp, 2, objv,"point list must at least three pairs of points");
	}

	points = (gdPoint *)ckalloc (sizeof (gdPoint) * (nElements / 2));

	for (i = 0; i < nElements; i += 2) {
	    if (Tcl_GetIntFromObj (interp, pointObjList[i], &x) == TCL_ERROR) {
	        return TCL_ERROR;
	    }

	    if (Tcl_GetIntFromObj (interp, pointObjList[i+1], &y) == TCL_ERROR) {
	        return TCL_ERROR;
	    }

	    points[i/2].x = x;
	    points[i/2].y = y;
	}

	if (gdtcl_GetColor (interp, objv[6], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}


	switch ((enum suboptions) suboptIndex) {
	  case SUBOPT_FILLED: {
	      gdImageFilledPolygon (im, points, nElements/2, color);
	  }

	  case SUBOPT_OPEN: {
	      gdImageOpenPolygon (im, points, nElements/2, color);
	  }

	  case SUBOPT_BASIC: {
	      gdImagePolygon (im, points, nElements/2, color);
	  }
	}

	return TCL_OK;
      }

      case OPT_RECTANGLE: {
	int x1, y1, x2, y2, color;

	if (objc != 7) {
	    Tcl_WrongNumArgs (interp, 2, objv, "x1 y1 x2 y2 color");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &x1) == TCL_ERROR) {
	   gd_complainX1 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &y1) == TCL_ERROR) {
	   gd_complainY1 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &x2) == TCL_ERROR) {
	   gd_complainX2 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &y2) == TCL_ERROR) {
	   gd_complainY2 (interp);
	   return TCL_ERROR;
       }

	if (gdtcl_GetColor (interp, objv[6], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageFilledRectangle (im, x1, y1, x2, y2, color);
	break;
      }

      case OPT_FILLED_RECTANGLE: {
	int x1, y1, x2, y2, color;

	if (objc != 7) {
	    Tcl_WrongNumArgs (interp, 2, objv, "x1 y1 x2 y2 color");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &x1) == TCL_ERROR) {
	   gd_complainX1 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &y1) == TCL_ERROR) {
	   gd_complainY1 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &x2) == TCL_ERROR) {
	   gd_complainX2 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &y2) == TCL_ERROR) {
	   gd_complainY2 (interp);
	   return TCL_ERROR;
       }

	if (gdtcl_GetColor (interp, objv[6], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageFilledRectangle (im, x1, y1, x2, y2, color);
	break;
      }

      case OPT_ARC: {
	int cx, cy, w, h, s, e, color;

	if (objc != 9) {
	    Tcl_WrongNumArgs (interp, 2, objv, "cx cy width height startDegrees endDegrees color");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &cx) == TCL_ERROR) {
	   gd_complainCX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &cy) == TCL_ERROR) {
	   gd_complainCY (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &w) == TCL_ERROR) {
	   gd_complainWidth (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &h) == TCL_ERROR) {
	   gd_complainHeight (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[6], &s) == TCL_ERROR) {
	   gd_complainStartDegrees (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[7], &e) == TCL_ERROR) {
	   gd_complainEndDegrees (interp);
	   return TCL_ERROR;
       }

	if (gdtcl_GetColor (interp, objv[8], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageArc (im, cx, cy, w, h, s, e, color);
	break;
      }

      case OPT_FILLED_ARC: {
	int     i;
	int     cx;
	int     cy;
	int     w;
	int     h;
	int     s;
	int     e;
	int     color;
	int     style = 0;
	int     styleIndex;

	static CONST char *styles[] = {
	    "arc",
	    "chord",
	    "pie",
	    "nofill",
	    "edged"
	};

	enum styles {
	    STYLE_ARC,
	    STYLE_CHORD,
	    STYLE_PIE,
	    STYLE_NOFILL,
	    STYLE_EDGED
	};

	if (objc < 10) {
	    Tcl_WrongNumArgs (interp, 2, objv, "cx cy width height startDegrees endDegrees color ?arc? ?chord? ?pie? ?nofill? ?edged?");
	    return TCL_ERROR;
	}
       if (Tcl_GetIntFromObj (interp, objv[2], &cx) == TCL_ERROR) {
	   gd_complainCX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &cy) == TCL_ERROR) {
	   gd_complainCY (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &w) == TCL_ERROR) {
	   gd_complainWidth (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &h) == TCL_ERROR) {
	   gd_complainHeight (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[6], &s) == TCL_ERROR) {
	   gd_complainStartDegrees (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[7], &e) == TCL_ERROR) {
	   gd_complainEndDegrees (interp);
	   return TCL_ERROR;
       }

	if (gdtcl_GetColor (interp, objv[8], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	if (Tcl_GetIndexFromObj(interp, objv[9], styles, "style", 
	    TCL_EXACT, &styleIndex) != TCL_OK) {
	    return TCL_ERROR;
	}

	for (i = 9; i < objc; i++) {

	    switch ((enum styles) styleIndex) {
	      case STYLE_ARC:
		style |= gdArc;
		break;

	      case STYLE_CHORD:
		style |= gdChord;
		break;

	      case STYLE_PIE:
		style |= gdPie;
		break;

	      case STYLE_NOFILL:
		style |= gdNoFill;
		break;

	      case STYLE_EDGED:
		style |= gdEdged;
		break;
	    }
	}

	gdImageFilledArc (im, cx, cy, w, h, s, e, color, style);
	break;
      }

      case OPT_FILLED_ELLIPSE: {
	int cx, cy, w, h, color;

	if (objc != 7) {
	    Tcl_WrongNumArgs (interp, 2, objv, "cx cy width height color");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &cx) == TCL_ERROR) {
	   gd_complainCX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &cy) == TCL_ERROR) {
	   gd_complainCY (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &w) == TCL_ERROR) {
	   gd_complainWidth (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &h) == TCL_ERROR) {
	   gd_complainHeight (interp);
	   return TCL_ERROR;
       }

	if (gdtcl_GetColor (interp, objv[6], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageFilledEllipse (im, cx, cy, w, h, color);
	break;
      }

      case OPT_FILL_TO_BORDER: {
	int x, y, border, color;

	if (objc != 6) {
	    Tcl_WrongNumArgs (interp, 2, objv, "x y borderColor color");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &x) == TCL_ERROR) {
	   gd_complainX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &y) == TCL_ERROR) {
	   gd_complainY (interp);
	   return TCL_ERROR;
       }

	if (gdtcl_GetColor (interp, objv[4], &border) == TCL_ERROR) {
	   gd_complain (interp, "borderColor");
	    return TCL_ERROR;
	}

	if (gdtcl_GetColor (interp, objv[5], &color) == TCL_ERROR) {
	    gd_complainColor (interp);
	    return TCL_ERROR;
	}

	gdImageFillToBorder (im, x, y, border, color);
	break;
      }

      case OPT_FILL: {
	int x, y, color;

	if (objc != 5) {
	    Tcl_WrongNumArgs (interp, 2, objv, "x y color");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &x) == TCL_ERROR) {
	    gd_complainX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &y) == TCL_ERROR) {
	    gd_complainY (interp);
	   return TCL_ERROR;
       }

	if (gdtcl_GetColor (interp, objv[4], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageFill (im, x, y, color);
	break;
      }

      case OPT_TEXT_BOUNDS:
      case OPT_TEXT: {
	gdImagePtr textIm = NULL;
	int        color;
	char      *fontName;
	double     pointSize;
	double     angle;
	int        x;
	int        y;
	char      *text;
	char      *resultString;

	int        brect[8];
	Tcl_Obj    *brectObjv[8];

	if (optIndex == OPT_TEXT) {
	    textIm = im;
	}

	if (objc != 9) {
	    Tcl_WrongNumArgs (interp, 2, objv, "color font pointSize angle x y text");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &color) == TCL_ERROR) {
	    gd_complainColor (interp);
	    return TCL_ERROR;
	}

	fontName = Tcl_GetString (objv[3]);

       if (Tcl_GetDoubleFromObj (interp, objv[4], &pointSize) == TCL_ERROR) {
	    gd_complain (interp, "pointSize");
	   return TCL_ERROR;
       }

       if (Tcl_GetDoubleFromObj (interp, objv[5], &angle) == TCL_ERROR) {
	    gd_complain (interp, "angle");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[6], &x) == TCL_ERROR) {
	    gd_complainX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[7], &y) == TCL_ERROR) {
	    gd_complainY (interp);
	   return TCL_ERROR;
       }

       text = Tcl_GetString (objv[8]);

	resultString = gdImageStringFT (im, &brect[0], color, fontName, pointSize, angle, x, y, text);
	if (resultString != NULL) {
	    Tcl_SetStringObj (resultObj, resultString, -1);
	    Tcl_AppendResult (interp, " '", fontName, "'", NULL);
	    return TCL_ERROR;
	}

	if (optIndex == OPT_TEXT_BOUNDS) {
	    int i;

	    for (i = 0; i < 8; i++) {
		brectObjv[i] = Tcl_NewIntObj(brect[i]);
	    }
	    Tcl_SetListObj (resultObj, 8, brectObjv);
	}
	break;
      }

      case OPT_ALLOCATE_COLOR: {
	int r, g, b, alpha;

	if ((objc < 5) || (objc > 6)) {
	    Tcl_WrongNumArgs (interp, 2, objv, "r g b ?alpha?");
	    return TCL_ERROR;
	}

        if (Tcl_GetIntFromObj (interp, objv[2], &r) == TCL_ERROR) {
	    gd_complainRed (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[3], &g) == TCL_ERROR) {
	    gd_complainGreen (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[4], &b) == TCL_ERROR) {
	    gd_complainBlue (interp);
	   return TCL_ERROR;
        }

	if (objc == 5) {
	    Tcl_SetIntObj (resultObj, gdImageColorAllocate (im, r, g, b));
	    return TCL_OK;
	}

	if (Tcl_GetIntFromObj (interp, objv[5], &alpha) == TCL_ERROR) {
	   gd_complainAlpha (interp);
	    return TCL_ERROR;
	}

	Tcl_SetIntObj (resultObj, gdImageColorAllocateAlpha (im, r, g, b, alpha));
	return TCL_OK;
      }

      case OPT_CLOSEST_COLOR: {
	int r, g, b, alpha;

	if ((objc < 5) || (objc > 6)) {
	    Tcl_WrongNumArgs (interp, 2, objv, "r g b ?alpha?");
	    return TCL_ERROR;
	}

        if (Tcl_GetIntFromObj (interp, objv[2], &r) == TCL_ERROR) {
	   gd_complainRed (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[3], &g) == TCL_ERROR) {
	   gd_complainGreen (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[4], &b) == TCL_ERROR) {
	   gd_complainBlue (interp);
	   return TCL_ERROR;
        }

	if (objc == 5) {
	    Tcl_SetIntObj (resultObj, gdImageColorClosest (im, r, g, b));
	    return TCL_OK;
	}

	if (Tcl_GetIntFromObj (interp, objv[5], &alpha) == TCL_ERROR) {
	   gd_complainAlpha (interp);
	    return TCL_ERROR;
	}

	Tcl_SetIntObj (resultObj, gdImageColorClosestAlpha (im, r, g, b, alpha));
	return TCL_OK;
      }

      case OPT_CLOSEST_COLOR_HWB: {
	int r, g, b;

	if (objc != 5) {
	    Tcl_WrongNumArgs (interp, 2, objv, "r g b");
	    return TCL_ERROR;
	}

        if (Tcl_GetIntFromObj (interp, objv[2], &r) == TCL_ERROR) {
	   gd_complainRed (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[3], &g) == TCL_ERROR) {
	   gd_complainGreen (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[4], &b) == TCL_ERROR) {
	   gd_complainBlue (interp);
	   return TCL_ERROR;
        }

	Tcl_SetIntObj (resultObj, gdImageColorClosestHWB (im, r, g, b));
	return TCL_OK;
      }

      case OPT_EXACT_COLOR: {
	int r, g, b, alpha;

	if ((objc < 5) || (objc > 6)) {
	    Tcl_WrongNumArgs (interp, 2, objv, "r g b ?alpha?");
	    return TCL_ERROR;
	}

        if (Tcl_GetIntFromObj (interp, objv[2], &r) == TCL_ERROR) {
	   gd_complainRed (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[3], &g) == TCL_ERROR) {
	   gd_complainGreen (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[4], &b) == TCL_ERROR) {
	   gd_complainBlue (interp);
	   return TCL_ERROR;
        }

	if (objc == 5) {
	    Tcl_SetIntObj (resultObj, gdImageColorExact (im, r, g, b));
	    return TCL_OK;
	}

        if (Tcl_GetIntFromObj (interp, objv[5], &alpha) == TCL_ERROR) {
	   gd_complainAlpha (interp);
	   return TCL_ERROR;
        }

	Tcl_SetIntObj (resultObj, gdImageColorExactAlpha (im, r, g, b, alpha));
	return TCL_OK;
      }

      case OPT_RESOLVE_COLOR: {
	int r, g, b, alpha;

	if ((objc < 5) || (objc > 6)) {
	    Tcl_WrongNumArgs (interp, 2, objv, "r g b ?alpha?");
	    return TCL_ERROR;
	}

        if (Tcl_GetIntFromObj (interp, objv[2], &r) == TCL_ERROR) {
	   gd_complainRed (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[3], &g) == TCL_ERROR) {
	   gd_complainGreen (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[4], &b) == TCL_ERROR) {
	   gd_complainBlue (interp);
	   return TCL_ERROR;
        }

	if (objc == 5) {
	    Tcl_SetIntObj (resultObj, gdImageColorResolve (im, r, g, b));
	    return TCL_OK;
	}

	if (Tcl_GetIntFromObj (interp, objv[5], &alpha) == TCL_ERROR) {
	   gd_complainAlpha (interp);
	    return TCL_ERROR;
	}

	Tcl_SetIntObj (resultObj, gdImageColorResolveAlpha (im, r, g, b, alpha));
	break;
      }

      case OPT_TOTAL_COLORS:
	if (objc != 2) {
	    Tcl_WrongNumArgs (interp, 2, objv, "");
	    return TCL_ERROR;
	}
	Tcl_SetIntObj (resultObj, gdImageColorsTotal (im));
	break;

      case OPT_DEALLOCATE_COLOR: {
	int color;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "color");
	    return TCL_ERROR;
	}

	if (gdtcl_GetColor (interp, objv[2], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageColorDeallocate (im, color);
	break;
      }

      case OPT_TRUE_COLOR: {
	int r, g, b, alpha;

	if ((objc < 5) || (objc > 6)) {
	    Tcl_WrongNumArgs (interp, 2, objv, "r g b ?alpha?");
	    return TCL_ERROR;
	}

        if (Tcl_GetIntFromObj (interp, objv[2], &r) == TCL_ERROR) {
	   gd_complainRed (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[3], &g) == TCL_ERROR) {
	   gd_complainGreen (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[4], &b) == TCL_ERROR) {
	   gd_complainBlue (interp);
	   return TCL_ERROR;
        }

	if (objc == 5) {
	    Tcl_SetIntObj (resultObj, gdTrueColor (r, g, b));
	    return TCL_OK;
	}

	if (Tcl_GetIntFromObj (interp, objv[5], &alpha) == TCL_ERROR) {
	   gd_complainAlpha (interp);
	    return TCL_ERROR;
	}

	Tcl_SetIntObj (resultObj, gdTrueColorAlpha (r, g, b, alpha));
	return TCL_OK;
      }

      case OPT_INTERLACE: {
	int interlaced;

	if (objc == 2) {
	  Tcl_SetIntObj (resultObj, gdImageGetInterlaced (im));
	  return TCL_OK;
	}

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "?boolean?");
	}

	if (Tcl_GetBooleanFromObj (interp, objv[2], &interlaced) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageInterlace (im, interlaced);
	return TCL_OK;
      }

      case OPT_TRANSPARENT: {
	int color;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "color");
	    return TCL_ERROR;
	}

	if (gdtcl_GetColor (interp, objv[2], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageColorTransparent (im, color);
	break;
      }

      case OPT_SET_ANTI_ALIASED: {
	int color;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "color");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	/* printf("gdImageSetAntiAliased %d\n", color); */
	gdImageSetAntiAliased (im, color);
	return TCL_OK;
      }

      case OPT_SET_ANTI_ALIASED_DONT_BLEND: {
	int color, dontBlend;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "color");
	    return TCL_ERROR;
	}

	if (gdtcl_GetColor (interp, objv[2], &color) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[3], &dontBlend) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageSetAntiAliasedDontBlend (im, color, dontBlend);
	return TCL_OK;
      }

      case OPT_SET_BRUSH:
	break;

      case OPT_SET_TILE:
	break;

      case OPT_STYLE:
	break;

      case OPT_SET_THICKNESS: {
	int thickness;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "thickness");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &thickness) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	/* printf("gdImageSetThickness %d\n", thickness); */
	gdImageSetThickness (im, thickness);
	return TCL_OK;
      }

      case OPT_ALPHA_BLENDING: {
	int blending;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "blending");
	    return TCL_ERROR;
	}

	if (Tcl_GetBooleanFromObj (interp, objv[2], &blending) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageAlphaBlending (im, blending);
	return TCL_OK;
      }

      case OPT_SAVE_ALPHA: {
	int saveAlpha;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "boolean");
	    return TCL_ERROR;
	}

	if (Tcl_GetBooleanFromObj (interp, objv[2], &saveAlpha) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageSaveAlpha (im, saveAlpha);
	return TCL_OK;
      }

      case OPT_CLIP: {
	int x1, y1, x2, y2;

	if (objc != 2 && objc != 6) {
	    Tcl_WrongNumArgs (interp, 2, objv, "?x1 y1 x2 y2?");
	    return TCL_ERROR;
	}

	if (objc == 2) {
	    Tcl_Obj *clipObjv[4];

	    gdImageGetClip (im, &x1, &y1, &x2, &y2);
	    clipObjv[0] = Tcl_NewIntObj(x1);
	    clipObjv[1] = Tcl_NewIntObj(y1);
	    clipObjv[2] = Tcl_NewIntObj(x2);
	    clipObjv[3] = Tcl_NewIntObj(y2);
	    Tcl_SetListObj (resultObj, 4, clipObjv);
	    return TCL_OK;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &x1) == TCL_ERROR) {
	   gd_complainX1 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &y1) == TCL_ERROR) {
	   gd_complainY1 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &x2) == TCL_ERROR) {
	   gd_complainX2 (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &y2) == TCL_ERROR) {
	   gd_complainY2 (interp);
	   return TCL_ERROR;
       }

	gdImageSetClip (im, x1, y1, x2, y2);
	break;
      }

      case OPT_GET_ALPHA:
	break;

      case OPT_BOUNDS_SAFE: {
	int x, y;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "x y");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[2], &x) == TCL_ERROR) {
	   gd_complainX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[3], &y) == TCL_ERROR) {
	   gd_complainY (interp);
	   return TCL_ERROR;
       }

	Tcl_SetBooleanObj (resultObj, gdImageBoundsSafe (im, x, y));
	break;
      }

      case OPT_GREEN_COMPONENT: {
	int color;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "color");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &color) == TCL_ERROR) {
	   gd_complainColor (interp);
	    return TCL_ERROR;
	}

	Tcl_SetIntObj (resultObj, gdImageGreen (im, color));
	return TCL_OK;
      }

      case OPT_RED_COMPONENT: {
	int color;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "color");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &color) == TCL_ERROR) {
	    gd_complainColor (interp);
	    return TCL_ERROR;
	}

	Tcl_SetIntObj (resultObj, gdImageRed (im, color));
	return TCL_OK;
      }

      case OPT_BLUE_COMPONENT: {
	int color;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "color");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &color) == TCL_ERROR) {
	    gd_complainColor (interp);
	    return TCL_ERROR;
	}

	Tcl_SetIntObj (resultObj, gdImageBlue (im, color));
	return TCL_OK;
      }

      case OPT_WIDTH:
	Tcl_SetIntObj (resultObj, gdImageSX(im));
	break;

      case OPT_HEIGHT:
	Tcl_SetIntObj (resultObj, gdImageSY(im));
	break;

      case OPT_COPY: {
        int          dstX;
	int          dstY;
	int          srcX;
	int          srcY;
	int          w;
	int          h;
	gdImagePtr   srcIm;
	Tcl_CmdInfo  cmdInfo;

	if (objc != 9) {
	    Tcl_WrongNumArgs (interp, 2, objv, "srcImageCommand dstX dstY srcX srcY w h");
	    return TCL_ERROR;
	}

	if (!Tcl_GetCommandInfo ( interp, Tcl_GetString(objv[2]), &cmdInfo)) {
	    return TCL_ERROR;
	}
	srcIm = (gdImagePtr)cmdInfo.objClientData;


       if (Tcl_GetIntFromObj (interp, objv[3], &dstX) == TCL_ERROR) {
	   gd_complain (interp, "dstX");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &dstY) == TCL_ERROR) {
	   gd_complain (interp, "dstY");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &srcX) == TCL_ERROR) {
	   gd_complain (interp, "srcX");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[6], &srcY) == TCL_ERROR) {
	   gd_complain (interp, "srcY");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[7], &w) == TCL_ERROR) {
	   gd_complainWidth (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[8], &h) == TCL_ERROR) {
	   gd_complainHeight (interp);
	   return TCL_ERROR;
       }

	gdImageCopy (im, srcIm, dstX, dstY, srcX, srcY, w, h);
	break;
      }

      case OPT_COPY_RESAMPLED:
      case OPT_COPY_RESIZED: {
        int          dstX;
	int          dstY;
	int          srcX;
	int          srcY;
	int          destW;
	int          destH;
	int          srcW;
	int          srcH;
	gdImagePtr   srcIm;
	Tcl_CmdInfo  cmdInfo;

	if (objc != 11) {
	    Tcl_WrongNumArgs (interp, 2, objv, "srcImageCommand dstX dstY srcX srcY destW destH srcW srcH");
	    return TCL_ERROR;
	}

	if (!Tcl_GetCommandInfo ( interp, Tcl_GetString(objv[2]), &cmdInfo)) {
	    return TCL_ERROR;
	}
	srcIm = (gdImagePtr)cmdInfo.objClientData;


       if (Tcl_GetIntFromObj (interp, objv[3], &dstX) == TCL_ERROR) {
	   gd_complain (interp, "dstX");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &dstY) == TCL_ERROR) {
	   gd_complain (interp, "dstY");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &srcX) == TCL_ERROR) {
	   gd_complain (interp, "srcX");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[6], &srcY) == TCL_ERROR) {
	   gd_complain (interp, "srcY");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[7], &destW) == TCL_ERROR) {
	   gd_complain (interp, "destWidth");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[8], &destH) == TCL_ERROR) {
	   gd_complain (interp, "destHeight");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[9], &srcW) == TCL_ERROR) {
	   gd_complain (interp, "srcWidth");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[10], &srcH) == TCL_ERROR) {
	   gd_complain (interp, "srcHeight");
	   return TCL_ERROR;
       }

	if (optIndex == OPT_COPY_RESIZED) {
	    gdImageCopyResized (im, srcIm, dstX, dstY, srcX, srcY, destW, destH, srcW, srcH);
	} else {
	    gdImageCopyResampled (im, srcIm, dstX, dstY, srcX, srcY, destW, destH, srcW, srcH);
	}
	break;
      }


      case OPT_COPY_ROTATED: {
        double       dstX;
	double       dstY;
	int          srcX;
	int          srcY;
	int          srcW;
	int          srcH;
	int          angle;
	gdImagePtr   srcIm;
	Tcl_CmdInfo  cmdInfo;

	if (objc != 10) {
	    Tcl_WrongNumArgs (interp, 2, objv, "srcImageCommand dstX dstY srcX srcY destW destH srcW srcH angle");
	    return TCL_ERROR;
	}

	if (!Tcl_GetCommandInfo ( interp, Tcl_GetString(objv[2]), &cmdInfo)) {
	    return TCL_ERROR;
	}
	srcIm = (gdImagePtr)cmdInfo.objClientData;


       if (Tcl_GetDoubleFromObj (interp, objv[3], &dstX) == TCL_ERROR) {
	   gd_complain (interp, "dstX");
	   return TCL_ERROR;
       }

       if (Tcl_GetDoubleFromObj (interp, objv[4], &dstY) == TCL_ERROR) {
	   gd_complain (interp, "dstY");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &srcX) == TCL_ERROR) {
	   gd_complain (interp, "srcX");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[6], &srcY) == TCL_ERROR) {
	   gd_complain (interp, "srcY");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[7], &srcW) == TCL_ERROR) {
	   gd_complain (interp, "srcWidth");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[8], &srcH) == TCL_ERROR) {
	   gd_complain (interp, "srcHeight");
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[9], &angle) == TCL_ERROR) {
	   gd_complainAngle (interp);
	   return TCL_ERROR;
       }

	gdImageCopyRotated (im, srcIm, dstX, dstY, srcX, srcY, srcW, srcH, angle);
	break;
     }

      case OPT_COPY_MERGE_GREY:
      case OPT_COPY_MERGE: {
        int          dstX;
	int          dstY;
	int          srcX;
	int          srcY;
	int          w;
	int          h;
	int          pct;
	gdImagePtr   srcIm;
	Tcl_CmdInfo  cmdInfo;

	if (objc != 10) {
	    Tcl_WrongNumArgs (interp, 2, objv, "srcImageCommand dstX dstY srcX srcY w h pct");
	    return TCL_ERROR;
	}

	if (!Tcl_GetCommandInfo ( interp, Tcl_GetString(objv[2]), &cmdInfo)) {
	    return TCL_ERROR;
	}
	srcIm = (gdImagePtr)cmdInfo.objClientData;


        if (Tcl_GetIntFromObj (interp, objv[3], &dstX) == TCL_ERROR) {
	   gd_complain (interp, "destX");
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[4], &dstY) == TCL_ERROR) {
	   gd_complain (interp, "destY");
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[5], &srcX) == TCL_ERROR) {
	   gd_complain (interp, "srcX");
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[6], &srcY) == TCL_ERROR) {
	   gd_complain (interp, "srcY");
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[7], &w) == TCL_ERROR) {
	   gd_complainWidth (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[8], &h) == TCL_ERROR) {
	   gd_complainHeight (interp);
	   return TCL_ERROR;
        }

        if (Tcl_GetIntFromObj (interp, objv[9], &pct) == TCL_ERROR) {
	   gd_complain (interp, "pct");
	   return TCL_ERROR;
        }

        if (optIndex == OPT_COPY_MERGE) {
	    gdImageCopyMerge (im, srcIm, dstX, dstY, srcX, srcY, w, h, pct);
        } else {
	    gdImageCopyMergeGray (im, srcIm, dstX, dstY, srcX, srcY, w, h, pct);
        }
        break;
      }

      case OPT_COPY_PALETTE: {
	Tcl_CmdInfo  cmdInfo;
	gdImagePtr   srcIm;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "srcImageCommand");
	    return TCL_ERROR;
	}

	if (!Tcl_GetCommandInfo ( interp, Tcl_GetString(objv[2]), &cmdInfo)) {
	    return TCL_ERROR;
	}
	srcIm = (gdImagePtr)cmdInfo.objClientData;

	gdImagePaletteCopy (im, srcIm);
	break;
      }

      case OPT_SHARPEN: {
	int pct;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "pct");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &pct) == TCL_ERROR) {
	   gd_complain (interp, "pct");
	    return TCL_ERROR;
	}

#if 0
	gdImageSharpen (im, pct);
#endif
	return TCL_OK;
      }

      case OPT_COMPARE:
	break;

      case OPT_SQUARE_TO_CIRCLE: {
        int radius;
	gdImagePtr newIm = NULL;

	if (gdImageSX(im) != gdImageSY(im)) {
	    Tcl_AppendResult (interp, "image must be square for square_to_circle to work", NULL);
	    return TCL_ERROR;
	}

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name radius");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[3], &radius) == TCL_ERROR) {
	   gd_complain (interp, "radius");
	    return TCL_ERROR;
	}

#if 0
	newIm = gdImageSquareToCircle (im, radius);
#endif
	Tcl_CreateObjCommand (interp, Tcl_GetString(objv[2]), gd_GDObjCmd, newIm, gd_GDdeleteProc);
	break;
      }

      case OPT_WRITE_JPEG: {
	int   quality;
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "fileHandle quality");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[2]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[3], &quality) == TCL_ERROR) {
	   gd_complain (interp, "quality");
	    return TCL_ERROR;
	}

	gdImageJpeg (im, file, quality);
	fflush (file);
	return TCL_OK;
      }

      case OPT_JPEG_DATA: {
	int      quality;
	int      size;
	void    *memPtr;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "quality");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &quality) == TCL_ERROR) {
	   gd_complain (interp, "quality");
	    return TCL_ERROR;
	}

	memPtr = gdImageJpegPtr (im, &size, quality);
	Tcl_SetByteArrayObj (resultObj, memPtr, size);
	return TCL_OK;
      }

      case OPT_WRITE_GIF: {
	FILE *file;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "fileHandle");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[2]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageGif (im, file);
	fflush (file);
	return TCL_OK;
      }

      case OPT_GIF_DATA: {
	int      size;
	void    *memPtr;

	if (objc != 2) {
	    Tcl_WrongNumArgs (interp, 2, objv, "");
	    return TCL_ERROR;
	}

	memPtr = gdImageGifPtr (im, &size);
	Tcl_SetByteArrayObj (resultObj, memPtr, size);
	return TCL_OK;
      }

      case OPT_WRITE_PNG: {
	int   compression;
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "fileHandle compressionLevel");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[2]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[3], &compression) == TCL_ERROR) {
	   gd_complain (interp, "compression");
	    return TCL_ERROR;
	}

	if ((compression < -1) || (compression > 9)) {
	    Tcl_AppendResult (interp, "compression must be between -1 (default), 0 (no compression), 1 (quick compress) - 9 (best possible)", NULL);
	    return TCL_ERROR;
	}

	gdImagePngEx (im, file, compression);
	fflush (file);
	return TCL_OK;
      }

      case OPT_PNG_DATA: {
	int      compression;
	int      size;
	void    *memPtr;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "compressionLevel");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &compression) == TCL_ERROR) {
	   gd_complain (interp, "compression");
	    return TCL_ERROR;
	}

	if ((compression < -1) || (compression > 9)) {
	    Tcl_AppendResult (interp, "compression must be between -1 (default), 0 (no compression), 1 (quick compress) - 9 (best possible)", NULL);
	    return TCL_ERROR;
	}

	memPtr = gdImagePngPtrEx (im, &size, compression);
	Tcl_SetByteArrayObj (resultObj, memPtr, size);
	return TCL_OK;
      }

      case OPT_WRITE_WBMP: {
	int   fgcolor;
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "fileHandle fgcolor");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[2]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[3], &fgcolor) == TCL_ERROR) {
	   gd_complain (interp, "fgcolor");
	    return TCL_ERROR;
	}

	gdImageWBMP (im, fgcolor, file);
	fflush (file);
	return TCL_OK;
      }

      case OPT_WBMP_DATA: {
	int   fgcolor;
	int      size;
	void    *memPtr;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "fgcolor");
	    return TCL_ERROR;
	}

	if (Tcl_GetIntFromObj (interp, objv[2], &fgcolor) == TCL_ERROR) {
	   gd_complain (interp, "fgcolor");
	    return TCL_ERROR;
	}

	memPtr = gdImageWBMPPtr (im, &size, fgcolor);
	Tcl_SetByteArrayObj (resultObj, memPtr, size);
	return TCL_OK;
      }

      case OPT_WRITE_GD: {
	FILE *file;

	if (objc != 3) {
	    Tcl_WrongNumArgs (interp, 2, objv, "fileHandle");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[2]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	gdImageGd (im, file);
	fflush (file);
	return TCL_OK;
      }

      case OPT_GD_DATA: {
	int      size;
	void    *memPtr;

	if (objc != 2) {
	    Tcl_WrongNumArgs (interp, 2, objv, "");
	    return TCL_ERROR;
	}

	memPtr = gdImageGdPtr (im, &size);
	Tcl_SetByteArrayObj (resultObj, memPtr, size);
	return TCL_OK;
      }

      case OPT_WRITE_GD2: {
      }

      case OPT_GD2_DATA: {
      }

    }

    return TCL_OK;
}


/*
 *----------------------------------------------------------------------
 *
 * gdtcl_gdtclObjCmd --
 *
 *	This procedure is invoked to process the "gdtcl" command.
 *	See the user documentation for details on what it does.
 *
 * Results:
 *	A standard Tcl result.
 *
 * Side effects:
 *	See the user documentation.
 *
 *----------------------------------------------------------------------
 */

    /* ARGSUSED */
int
gdtcl_gdtclObjCmd(clientData, interp, objc, objv)
    ClientData clientData;		/* registered proc hashtable ptr. */
    Tcl_Interp *interp;			/* Current interpreter. */
    int objc;				/* Number of arguments. */
    Tcl_Obj   *CONST objv[];
{
    int          optIndex;
    gdImagePtr   im = NULL;


    static CONST char *options[] = {
        "create",
	"create_truecolor",
	"create_from_jpeg",
	"create_from_jpeg_data",
	"create_from_png",
	"create_from_png_data",
	"create_from_gif",
	"create_from_gif_data",
	"create_from_gd",
	"create_from_gd_data",
	"create_from_gd2",
	"create_from_gd2_data",
	"create_from_gd2_part",
	"create_from_gd2_part_data",
	"create_from_wbmp",
	"create_from_wbmp_data",
	"create_from_xbm",
	"create_from_xpm",
        (char *)NULL
    };

    enum options
    {
        OPT_CREATE, 
	OPT_CREATE_TRUECOLOR,
	OPT_CREATE_FROM_JPEG,
	OPT_CREATE_FROM_JPEG_DATA,
	OPT_CREATE_FROM_PNG,
	OPT_CREATE_FROM_PNG_DATA,
	OPT_CREATE_FROM_GIF,
	OPT_CREATE_FROM_GIF_DATA,
	OPT_CREATE_FROM_GD,
	OPT_CREATE_FROM_GD_DATA,
	OPT_CREATE_FROM_GD2,
	OPT_CREATE_FROM_GD2_DATA,
	OPT_CREATE_FROM_GD2_PART,
	OPT_CREATE_FROM_GD2_PART_DATA,
	OPT_CREATE_FROM_WBMP,
	OPT_CREATE_FROM_WBMP_DATA,
	OPT_CREATE_FROM_XBM,
	OPT_CREATE_FROM_XPM
    };

    if (objc < 3) {
	Tcl_WrongNumArgs (interp, 1, objv, "subcommand name ?args?");
	return TCL_ERROR;
    }

    if (Tcl_GetIndexFromObj(interp, objv[1], options, "option", TCL_EXACT,
        &optIndex) != TCL_OK)
    {
	    return TCL_ERROR;
    }

    switch ((enum options) optIndex) {
      case OPT_CREATE: {
	int x, y;

	if (objc != 5) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name x y");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[3], &x) == TCL_ERROR) {
	   gd_complainX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &y) == TCL_ERROR) {
	   gd_complainY (interp);
	   return TCL_ERROR;
       }

       im = gdImageCreate (x, y);
       break;
      }

      case OPT_CREATE_TRUECOLOR: {
	int x, y;

	if (objc != 5) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name x y");
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[3], &x) == TCL_ERROR) {
	   gd_complainX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[4], &y) == TCL_ERROR) {
	   gd_complainY (interp);
	   return TCL_ERROR;
       }

       im = gdImageCreateTrueColor (x, y);
       break;
      }

      case OPT_CREATE_FROM_JPEG: {
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name fileHandle");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[3]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	im = gdImageCreateFromJpeg (file);
	fflush (file);
	break;
      }

      case OPT_CREATE_FROM_JPEG_DATA: {
        int            size;
	unsigned char *memPtr;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name data");
	    return TCL_ERROR;
	}

	memPtr = Tcl_GetByteArrayFromObj (objv[2], &size);
	im = gdImageCreateFromJpegPtr (size, memPtr);
	break;
      }

      case OPT_CREATE_FROM_PNG: {
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name fileHandle");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[3]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	im = gdImageCreateFromPng (file);
	fflush (file);
	break;
      }

      case OPT_CREATE_FROM_PNG_DATA: {
        int            size;
	unsigned char *memPtr;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name data");
	    return TCL_ERROR;
	}

	memPtr = Tcl_GetByteArrayFromObj (objv[3], &size);
	im = gdImageCreateFromPngPtr (size, memPtr);
	break;
      }

      case OPT_CREATE_FROM_GIF: {
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name fileHandle");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[3]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	im = gdImageCreateFromGif (file);
	fflush (file);
	break;
      }

      case OPT_CREATE_FROM_GIF_DATA: {
        int            size;
	unsigned char *memPtr;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name data");
	    return TCL_ERROR;
	}

	memPtr = Tcl_GetByteArrayFromObj (objv[3], &size);
	im = gdImageCreateFromGifPtr (size, memPtr);
	break;
      }

      case OPT_CREATE_FROM_GD: {
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name fileHandle");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[3]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	im = gdImageCreateFromGd (file);
	fflush (file);
	break;
      }

      case OPT_CREATE_FROM_GD_DATA: {
        int            size;
	unsigned char *memPtr;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name data");
	    return TCL_ERROR;
	}

	memPtr = Tcl_GetByteArrayFromObj (objv[3], &size);
	im = gdImageCreateFromGdPtr (size, memPtr);
	break;
      }

      case OPT_CREATE_FROM_GD2: {
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name fileHandle");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[3]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	im = gdImageCreateFromGd2 (file);
	fflush (file);
	break;
      }

      case OPT_CREATE_FROM_GD2_DATA: {
        int            size;
	unsigned char *memPtr;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name data");
	    return TCL_ERROR;
	}

	memPtr = Tcl_GetByteArrayFromObj (objv[3], &size);
	im = gdImageCreateFromGd2Ptr (size, memPtr);
	break;
      }

      case OPT_CREATE_FROM_GD2_PART: {
	FILE *file;
	int   x;
	int   y;
	int   w;
	int   h;

	if (objc != 8) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name fileHandle x y w h");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[3]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

       if (Tcl_GetIntFromObj (interp, objv[4], &x) == TCL_ERROR) {
	   gd_complainX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &y) == TCL_ERROR) {
	   gd_complainY (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[6], &w) == TCL_ERROR) {
	   gd_complainWidth (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[7], &h) == TCL_ERROR) {
	   gd_complainHeight (interp);
	   return TCL_ERROR;
       }

	im = gdImageCreateFromGd2Part (file, x, y, w, h);
	fflush (file);
	break;
      }

      case OPT_CREATE_FROM_GD2_PART_DATA: {
        int            size;
	unsigned char *memPtr;

	int            x;
	int            y;
	int            w;
	int            h;

	if (objc != 8) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name data x y w h");
	    return TCL_ERROR;
	}

	memPtr = Tcl_GetByteArrayFromObj (objv[3], &size);

       if (Tcl_GetIntFromObj (interp, objv[4], &x) == TCL_ERROR) {
	   gd_complainX (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[5], &y) == TCL_ERROR) {
	   gd_complainY (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[6], &w) == TCL_ERROR) {
	   gd_complainWidth (interp);
	   return TCL_ERROR;
       }

       if (Tcl_GetIntFromObj (interp, objv[7], &h) == TCL_ERROR) {
	   gd_complainHeight (interp);
	   return TCL_ERROR;
       }

	im = gdImageCreateFromGd2PartPtr (size, memPtr, x, y, w, h);
	break;
      }

      case OPT_CREATE_FROM_WBMP: {
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name fileHandle");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[3]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	im = gdImageCreateFromWBMP (file);
	fflush (file);
	break;
      }

      case OPT_CREATE_FROM_WBMP_DATA: {
        int            size;
	unsigned char *memPtr;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name data");
	    return TCL_ERROR;
	}

	memPtr = Tcl_GetByteArrayFromObj (objv[3], &size);
	im = gdImageCreateFromWBMPPtr (size, memPtr);
	break;
      }

      case OPT_CREATE_FROM_XBM: {
	FILE *file;

	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name fileHandle");
	    return TCL_ERROR;
	}

	if (Tcl_GetOpenFile (interp, Tcl_GetString(objv[3]), 1, 1, (ClientData *)&file) == TCL_ERROR) {
	    return TCL_ERROR;
	}

	im = gdImageCreateFromXbm (file);
	fflush (file);
	break;
      }

      case OPT_CREATE_FROM_XPM: {
	if (objc != 4) {
	    Tcl_WrongNumArgs (interp, 2, objv, "name fileName");
	    return TCL_ERROR;
	}

	im = gdImageCreateFromXpm (Tcl_GetString(objv[2]));
	break;
      }
    }

    if (im == NULL) {
	Tcl_AppendResult (interp, "image is corrupt or incorrect image type", NULL);
	return TCL_ERROR;
    }

    Tcl_CreateObjCommand (interp, Tcl_GetString(objv[2]), gd_GDObjCmd, im, gd_GDdeleteProc);
    return TCL_OK;
}
