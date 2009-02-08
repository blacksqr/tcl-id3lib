#include <id3/tag.h>
#include <id3/misc_support.h>

#include <cstdio>
#include <iostream>
#include <map>
#include <string>

#include <Windows.h>

#include <tcl_id3lib_types.h>

extern FrameMap *g_frames;

using namespace std;

bool init_id3_mapping()
{
	(*g_frames)["AENC"]=ID3FID_AUDIOCRYPTO;
	(*g_frames)["APIC"]=ID3FID_PICTURE;
	(*g_frames)["COMM"]=ID3FID_COMMENT;
	(*g_frames)["ENCR"]=ID3FID_CRYPTOREG;
	(*g_frames)["EQUA"]=ID3FID_EQUALIZATION;
	(*g_frames)["ETCO"]=ID3FID_EVENTTIMING;
	(*g_frames)["GEOB"]=ID3FID_GENERALOBJECT;
	(*g_frames)["GRID"]=ID3FID_GROUPINGREG;
	(*g_frames)["IPLS"]=ID3FID_INVOLVEDPEOPLE;
	(*g_frames)["LINK"]=ID3FID_LINKEDINFO;
	(*g_frames)["MCDI"]=ID3FID_CDID;
	(*g_frames)["MLLT"]=ID3FID_MPEGLOOKUP;
	(*g_frames)["OWNE"]=ID3FID_OWNERSHIP;
	(*g_frames)["PRIV"]=ID3FID_PRIVATE;
	(*g_frames)["PCNT"]=ID3FID_PLAYCOUNTER;
	(*g_frames)["POPM"]=ID3FID_POPULARIMETER;
	(*g_frames)["POSS"]=ID3FID_POSITIONSYNC;
	(*g_frames)["RBUF"]=ID3FID_BUFFERSIZE;
	(*g_frames)["RVAD"]=ID3FID_VOLUMEADJ;
	(*g_frames)["RVRB"]=ID3FID_REVERB;
	(*g_frames)["SYLT"]=ID3FID_SYNCEDLYRICS;
	(*g_frames)["SYTC"]=ID3FID_SYNCEDTEMPO;
	(*g_frames)["TALB"]=ID3FID_ALBUM;
	(*g_frames)["TBPM"]=ID3FID_BPM;
	(*g_frames)["TCOM"]=ID3FID_COMPOSER;
	(*g_frames)["TCON"]=ID3FID_CONTENTTYPE;
	(*g_frames)["TCOP"]=ID3FID_COPYRIGHT;
	(*g_frames)["TDAT"]=ID3FID_DATE;
	(*g_frames)["TDLY"]=ID3FID_PLAYLISTDELAY;
	(*g_frames)["TENC"]=ID3FID_ENCODEDBY;
	(*g_frames)["TEXT"]=ID3FID_LYRICIST;
	(*g_frames)["TFLT"]=ID3FID_FILETYPE;
	(*g_frames)["TIME"]=ID3FID_TIME;
	(*g_frames)["TIT1"]=ID3FID_CONTENTGROUP;
	(*g_frames)["TIT2"]=ID3FID_TITLE;
	(*g_frames)["TIT3"]=ID3FID_SUBTITLE;
	(*g_frames)["TKEY"]=ID3FID_INITIALKEY;
	(*g_frames)["TLAN"]=ID3FID_LANGUAGE;
	(*g_frames)["TLEN"]=ID3FID_SONGLEN;
	(*g_frames)["TMED"]=ID3FID_MEDIATYPE;
	(*g_frames)["TOAL"]=ID3FID_ORIGALBUM;
	(*g_frames)["TOFN"]=ID3FID_ORIGFILENAME;
	(*g_frames)["TOLY"]=ID3FID_ORIGLYRICIST;
	(*g_frames)["TOPE"]=ID3FID_ORIGARTIST;
	(*g_frames)["TORY"]=ID3FID_ORIGYEAR;
	(*g_frames)["TOWN"]=ID3FID_FILEOWNER;
	(*g_frames)["TPE1"]=ID3FID_LEADARTIST;
	(*g_frames)["TPE2"]=ID3FID_BAND;
	(*g_frames)["TPE3"]=ID3FID_CONDUCTOR;
	(*g_frames)["TPE4"]=ID3FID_MIXARTIST;
	(*g_frames)["TPOS"]=ID3FID_PARTINSET;
	(*g_frames)["TPUB"]=ID3FID_PUBLISHER;
	(*g_frames)["TRCK"]=ID3FID_TRACKNUM;
	(*g_frames)["TRDA"]=ID3FID_RECORDINGDATES;
	(*g_frames)["TRSN"]=ID3FID_NETRADIOSTATION;
	(*g_frames)["TRSO"]=ID3FID_NETRADIOOWNER;
	(*g_frames)["TSIZ"]=ID3FID_SIZE;
	(*g_frames)["TSRC"]=ID3FID_ISRC;
	(*g_frames)["TSSE"]=ID3FID_ENCODERSETTINGS;
	(*g_frames)["TXXX"]=ID3FID_USERTEXT;
	(*g_frames)["TYER"]=ID3FID_YEAR;
	(*g_frames)["UFID"]=ID3FID_UNIQUEFILEID;
	(*g_frames)["USER"]=ID3FID_TERMSOFUSE;
	(*g_frames)["USLT"]=ID3FID_UNSYNCEDLYRICS;
	(*g_frames)["WCOM"]=ID3FID_WWWCOMMERCIALINFO;
	(*g_frames)["WCOP"]=ID3FID_WWWCOPYRIGHT;
	(*g_frames)["WOAF"]=ID3FID_WWWAUDIOFILE;
	(*g_frames)["WOAR"]=ID3FID_WWWARTIST;
	(*g_frames)["WOAS"]=ID3FID_WWWAUDIOSOURCE;
	(*g_frames)["WORS"]=ID3FID_WWWRADIOPAGE;
	(*g_frames)["WPAY"]=ID3FID_WWWPAYMENT;
	(*g_frames)["WPUB"]=ID3FID_WWWPUBLISHER;
	(*g_frames)["WXXX"]=ID3FID_WWWUSER;

	return true;
}