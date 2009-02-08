#ifndef _TCL_ID3LIB_TYPES_H_
#define _TCL_ID3LIB_TYPES_H_

typedef std::map<std::string, ID3_FrameID> FrameMap; // FrameName , FrameID
typedef std::map<std::string, std::string> TagCue; // FrameName(UserTextFieldId) , value
typedef struct TLibConfig {
		flags_t deletemask;
		flags_t updatemask;
	} LibConfig;

#endif /* _TCL_ID3LIB_TYPES_H_ */