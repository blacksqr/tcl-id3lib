#ifndef _TCL_ID3LIB_H_
#define _TCL_ID3LIB_H_

#ifdef WIN32
#define TCL_ID3LIB_API __declspec(dllexport)
#else
#define TCL_ID3LIB_API
#endif

extern "C" TCL_ID3LIB_API int Tcl_id_Init(Tcl_Interp *interp);

static int cmd_close(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
static int cmd_config(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
static int cmd_flush(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
static int cmd_get(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
static int cmd_isset(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
static int cmd_set(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
static int cmd_strip(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
static int cmd_open(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);
static int cmd_write(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[]);

FrameMap* g_frames;
TagCue* g_tagCue;
LibConfig* g_config;
ID3_Tag *g_tag;

#endif /* _TCL_ID3LIB_H_ */