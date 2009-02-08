#include <tcl.h>

#include <id3/tag.h>
#include <id3/misc_support.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

#include <cstdio>
#include <iostream>
#include <map>
#include <string>

#include <tcl_id3lib_types.h>
#include <tcl_id3lib.h>
#include <tcl_id3lib_support.h>

using namespace std;

// get tagmask by char
// 0 = use config, 1 = id3v1, 2 = id3v2, 3 = both
flags_t getTagmask(const char* tmask)
{
	if (strcmp(tmask,"id3v1")==0)
	{
		cout << "ID3TT_ID3V1" << endl;
		return ID3TT_ID3V1;
	}
	if (strcmp(tmask,"id3v2")==0)
	{
		cout << "ID3TT_ID3V2" << endl;
		return ID3TT_ID3V2;
	}
	if (strcmp(tmask,"both")==0)
	{
		cout << "ID3TT_ID3" << endl;
		return ID3TT_ID3;
	}
	cout << "ID3TT_NONE" << endl;
	return ID3TT_NONE;
}

/** Close active mp3 Handle
*  @return bool  success */
static int cmd_close(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
	int success = 0;
	if (g_tag) 
	{
		delete g_tag;
		g_tag = NULL;
		success = 1;
	}
	Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
	return TCL_OK;
}
/** configure id3 module
*  @param  p_confid  { deletemask , updatemask }
*  @param  p_value   { id3v1, id3v2, both }
*  @return bool  success */
static int cmd_config(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
	int success = 0;
	if ( objc != 3 )
	{
		cout << "id3::config invalid arguments: "<< endl;
		Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
		return TCL_ERROR;
	}
	char *pConfID,*pValue;
	int ConfIDLength,ValueLength;
	pConfID = Tcl_GetStringFromObj(objv[1],&ConfIDLength);
	pValue = Tcl_GetStringFromObj(objv[2],&ValueLength);

	if (strcmp(pConfID,"deletemask")==0 )
	{
		g_config->deletemask = getTagmask(pValue);
		success=1;
	}
	else if (strcmp(pConfID,"updatemask")==0 )
	{
		g_config->updatemask = getTagmask(pValue);
		success=1;
	}
	else {
		cout << "id3::config invalid arguments: "<< endl;
		Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
		return TCL_ERROR;
	}
	Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
	return TCL_OK;
}
/** flush currently modified id3 tags
*  @return bool  success */
static int cmd_flush(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
	int success = 1;
	g_tagCue->clear();
	Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
	return TCL_OK;
}
/** get tag by id
*  @param  p_tagid
*  @return string  tag value */
static int cmd_get(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
	ID3_Frame *pFrame;
	char *ptagid;
	int tagidLength;
	std::string retvalue ="not found";
	if ( objc != 2 )
	{
		cout << "id3::get invalid arguments: "<< endl;
		Tcl_SetObjResult(interp, Tcl_NewStringObj("",-1));
		return TCL_ERROR;
	}
	ptagid = Tcl_GetStringFromObj(objv[1],&tagidLength);
	if (g_frames->find(ptagid)==g_frames->end()) {
		pFrame = g_tag->FindTXXXFrame(ptagid);
	}
	else {
		pFrame = g_tag->Find((*g_frames)[ptagid]);
	}
	if (pFrame) { 
		if (pFrame) { 
			retvalue = pFrame->Field(ID3FN_TEXT).GetRawText();
		}
	}
	Tcl_SetObjResult(interp, Tcl_NewStringObj(retvalue.c_str(),-1));

	return TCL_OK;
}
/** check if tag is set in id3frame
*  @param  p_tagid
*  @return bool  success */
static int cmd_isset(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
	int success = 0;
	ID3_Frame *pFrame;
	char *ptagid;
	int tagidLength;

	if ( objc != 2 )
	{
		cout << "id3::isset invalid arguments: "<< endl;
		Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
		return TCL_ERROR;
	}
	ptagid = Tcl_GetStringFromObj(objv[1],&tagidLength);
	if (g_frames->find(ptagid)==g_frames->end()) {
		pFrame = g_tag->FindTXXXFrame(ptagid);
	}
	else {
		pFrame = g_tag->Find((*g_frames)[ptagid]);
	}
	if (pFrame) { 
		success = 1;
	}
	Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
	return TCL_OK;
}
/** set a tag by id
*  @param  p_tagid
*  @param  p_value
*  @return bool  success */
static int cmd_set(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
	int success = 0;
	int keyLength,valueLength;
	char *pKey,*pValue;
	char *pKeyN,*pValueN;
	if ( objc != 3 )
	{
		cout << "id3::set invalid arguments: "<< endl;
		Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
		return TCL_ERROR;
	}
	// utf8 hack
	// ******************************************************

	pKey = (char*)Tcl_GetByteArrayFromObj(objv[1],&keyLength);
	pValue = (char*)Tcl_GetByteArrayFromObj(objv[2],&valueLength);
	pKeyN=new char[keyLength+1];
	pKeyN[keyLength]='\0';
	pValueN=new char[valueLength+1];
	pValueN[valueLength]='\0';
	memcpy(pKeyN,pKey,keyLength);
	memcpy(pValueN,pValue,valueLength);
	// encue in tagCue
	(*g_tagCue)[pKeyN]=pValueN;
	delete[](pKeyN);
	delete[](pValueN);
	success = 1;
	Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
	return TCL_OK;
}
/** delete all tags by configuration tagmask
*  @return bool  success */
static int cmd_strip(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
	int success = 0;
	if (g_tag) {
		g_tag->Clear();
		g_tag->Strip(g_config->deletemask);
		g_tag->Update();
		success = 1;
	}
	Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
	return TCL_OK;
}
/** open a mp3 for tagprocessing
*  @param  p_fn
*  @return bool  success */
static int cmd_open(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
	int success = 0;
	int argLength;
	char *parg;
	char *pfn;
	// check for argcount
	if ( objc != 2 )
	{
		cout << "id3::open invalid arguments: "<< endl;
		Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
		return TCL_ERROR;
	}
	// extract args 
	// quite dirty solution... but utf8 conform

	Tcl_Obj *arg2 = Tcl_DuplicateObj(objv[1]);
	parg = (char*)Tcl_GetByteArrayFromObj(arg2,&argLength);
	pfn=new char[argLength+1];
	pfn[argLength]='\0';
	memcpy(pfn,parg,argLength);

	// check if filename is fine...
	FILE * file = fopen(pfn, "r");
	if (!file)
	{
		cout << "id3::open file doesnt exist: " << pfn << endl;
		Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
		delete[](pfn);
		return TCL_ERROR;
	}
	fclose(file);
	// check if a file is linked allready
	if (g_tag) {
		delete g_tag;
		g_tag = NULL;
	}
	// link the mp3 to id3lib
	g_tag = new ID3_Tag();
	g_tag->Link(pfn);
	success=1;
	delete[](pfn);
	Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
	return TCL_OK;
}
/** write id3 modifications to mp3
*  @return bool  success */
static int cmd_write(ClientData clientData, Tcl_Interp *interp, int objc, Tcl_Obj *const objv[])
{
	int success = 0;
	if (g_tag) {
		// now iterate through tagCue
		for (TagCue::iterator tci = g_tagCue->begin(); tci!= g_tagCue->end(); tci++)
		{
			// frame to create
			ID3_Frame *myFrame = new ID3_Frame;
			// possible old frame
			ID3_Frame *pFrame;
			// if usertext frame find the matching one
			if (g_frames->find(tci->first)==g_frames->end()) {
				pFrame = g_tag->FindTXXXFrame(tci->first);
				myFrame->SetID(ID3FID_USERTEXT);
				myFrame->Field(ID3FN_DESCRIPTION) = tci->first.c_str();
				myFrame->Field(ID3FN_TEXT) = tci->second.c_str();
			}
			else {
				pFrame = g_tag->Find((*g_frames)[tci->first]);
				myFrame->SetID((*g_frames)[tci->first]);
				myFrame->Field(ID3FN_TEXT) = tci->second.c_str();
			}
			if (pFrame != NULL)
			{
				g_tag->RemoveFrame(pFrame);
			}
			g_tag->AttachFrame(myFrame);
		}
		g_tag->Update(g_config->updatemask);
		success = 1;
		// flush the tagCue
		g_tagCue->clear();
	}
	Tcl_SetObjResult(interp, Tcl_NewBooleanObj(success));
	return TCL_OK;
}

// Tcl_SetObjResult(interp, Tcl_NewStringObj("Hello, World!", -1));
// Tcl_SetObjResult(interp, Tcl_NewIntObj(-1));

int Tcl_id_Init(Tcl_Interp *interp)
{
	// create namespace id3
	Tcl_Namespace *nsPtr;
	if (Tcl_InitStubs(interp, TCL_VERSION, 0) == NULL) {
		return TCL_ERROR;
	}
	nsPtr = Tcl_CreateNamespace(interp, "id3", NULL, NULL);
	if (nsPtr == NULL) {
		return TCL_ERROR;
	}

	// register commands
	Tcl_CreateObjCommand(interp, "id3::close", cmd_close, NULL, NULL);
	Tcl_CreateObjCommand(interp, "id3::config", cmd_config, NULL, NULL);
	Tcl_CreateObjCommand(interp, "id3::flush", cmd_flush, NULL, NULL);
	Tcl_CreateObjCommand(interp, "id3::get", cmd_get, NULL, NULL);
	Tcl_CreateObjCommand(interp, "id3::isset", cmd_isset, NULL, NULL);
	Tcl_CreateObjCommand(interp, "id3::set", cmd_set, NULL, NULL);
	Tcl_CreateObjCommand(interp, "id3::strip", cmd_strip, NULL, NULL);
	Tcl_CreateObjCommand(interp, "id3::open", cmd_open, NULL, NULL);
	Tcl_CreateObjCommand(interp, "id3::write", cmd_write, NULL, NULL);
	
	// setup package info
	Tcl_PkgProvide(interp, "id3", "1.0");
	
	// create some globals
	g_config = new LibConfig;
	g_frames = new FrameMap;
	g_tagCue = new TagCue;
	g_config->deletemask = ID3TT_NONE;
	g_config->updatemask = ID3TT_NONE;
	g_tag = NULL;
	
	// create supported mapping
	init_id3_mapping();
	
	return TCL_OK;
}