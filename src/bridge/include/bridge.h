#ifndef BRIDGE_H
#define BRIDGE_H

#include <sys/types.h>
#include <mach/mach_types.h>

enum {
  BRIDGE_DATATYPE_NONE,
  BRIDGE_DATATYPE_KEYCODE,
  BRIDGE_DATATYPE_MODIFIERFLAG,
  BRIDGE_DATATYPE_MODIFIERFLAGS_END,
  BRIDGE_DATATYPE_CONSUMERKEYCODE,
  BRIDGE_DATATYPE_POINTINGBUTTON,
  BRIDGE_DATATYPE_SCROLLWHEEL,
  BRIDGE_DATATYPE_POINTINGRELATIVE,
  BRIDGE_DATATYPE_KEYBOARDTYPE,
  BRIDGE_DATATYPE_DEVICEVENDOR,
  BRIDGE_DATATYPE_DEVICEPRODUCT,
  BRIDGE_DATATYPE_DEVICELOCATION,
  BRIDGE_DATATYPE_OPTION,
  BRIDGE_DATATYPE_MILLISECOND,
  BRIDGE_DATATYPE_DELAYUNTILREPEAT,
  BRIDGE_DATATYPE_KEYREPEAT,
  BRIDGE_DATATYPE_THRESHOLDMILLISECOND,

  BRIDGE_REMAPTYPE_NONE,
  BRIDGE_REMAPTYPE_PASSTHROUGH,
  BRIDGE_REMAPTYPE_KEYTOKEY,
  BRIDGE_REMAPTYPE_DOUBLEPRESSMODIFIER,
  BRIDGE_REMAPTYPE_DROPKEYAFTERREMAP,
  BRIDGE_REMAPTYPE_DROPPOINTINGRELATIVECURSORMOVE,
  BRIDGE_REMAPTYPE_DROPSCROLLWHEEL,
  BRIDGE_REMAPTYPE_FLIPPOINTINGRELATIVE,
  BRIDGE_REMAPTYPE_FLIPSCROLLWHEEL,
  BRIDGE_REMAPTYPE_FORCENUMLOCKON,
  BRIDGE_REMAPTYPE_HOLDINGKEYTOKEY,
  BRIDGE_REMAPTYPE_IGNOREMULTIPLESAMEKEYPRESS,
  BRIDGE_REMAPTYPE_KEYOVERLAIDMODIFIER,
  BRIDGE_REMAPTYPE_POINTINGRELATIVETOKEY,
  BRIDGE_REMAPTYPE_POINTINGRELATIVETOSCROLL,
  BRIDGE_REMAPTYPE_SIMULTANEOUSKEYPRESSES,
  BRIDGE_REMAPTYPE_SETKEYBOARDTYPE,
  BRIDGE_REMAPTYPE_SCROLLWHEELTOSCROLLWHEEL,
  BRIDGE_REMAPTYPE_SCROLLWHEELTOKEY,
  BRIDGE_REMAPTYPE_BLOCKUNTILKEYUP,
  BRIDGE_REMAPTYPE_END,

  BRIDGE_FILTERTYPE_NONE,
  BRIDGE_FILTERTYPE_APPLICATION_NOT,
  BRIDGE_FILTERTYPE_APPLICATION_ONLY,
  BRIDGE_FILTERTYPE_WINDOWNAME_NOT,
  BRIDGE_FILTERTYPE_WINDOWNAME_ONLY,
  BRIDGE_FILTERTYPE_UIELEMENTROLE_NOT,
  BRIDGE_FILTERTYPE_UIELEMENTROLE_ONLY,
  BRIDGE_FILTERTYPE_CONFIG_NOT,
  BRIDGE_FILTERTYPE_CONFIG_ONLY,
  BRIDGE_FILTERTYPE_DEVICE_NOT,
  BRIDGE_FILTERTYPE_DEVICE_ONLY,
  BRIDGE_FILTERTYPE_ELAPSEDTIMESINCELASTPRESSED_GREATERTHAN,
  BRIDGE_FILTERTYPE_ELAPSEDTIMESINCELASTPRESSED_LESSTHAN,
  BRIDGE_FILTERTYPE_INPUTSOURCE_NOT,
  BRIDGE_FILTERTYPE_INPUTSOURCE_ONLY,
  BRIDGE_FILTERTYPE_INPUTSOURCEDETAIL_NOT,
  BRIDGE_FILTERTYPE_INPUTSOURCEDETAIL_ONLY,
  BRIDGE_FILTERTYPE_LASTPRESSEDPHYSICALKEY_NOT,
  BRIDGE_FILTERTYPE_LASTPRESSEDPHYSICALKEY_ONLY,
  BRIDGE_FILTERTYPE_MODIFIER_NOT,
  BRIDGE_FILTERTYPE_MODIFIER_ONLY,
  BRIDGE_FILTERTYPE_END,

  BRIDGE_STATUSMESSAGE,
  BRIDGE_MODIFIERNAME,
  BRIDGE_VK_MODIFIER,
  BRIDGE_VK_CONFIG,
  BRIDGE_VK_CHANGE_INPUTSOURCE,
  BRIDGE_VK_OPEN_URL,
};

// ------------------------------------------------------------
// UserClient definitions.
enum {
  BRIDGE_USERCLIENT_OPEN,
  BRIDGE_USERCLIENT_CLOSE,
  BRIDGE_USERCLIENT_SYNCHRONIZED_COMMUNICATION,
  BRIDGE_USERCLIENT_NOTIFICATION_FROM_KEXT,
  BRIDGE_USERCLIENT__END__,
};

enum {
  BRIDGE_USERCLIENT_OPEN_RETURN_SUCCESS = 0,
  BRIDGE_USERCLIENT_OPEN_RETURN_ERROR_GENERIC = 1,
  BRIDGE_USERCLIENT_OPEN_RETURN_ERROR_BRIDGE_VERSION_MISMATCH = 2,
};

enum {
  BRIDGE_USERCLIENT_SYNCHRONIZED_COMMUNICATION_RETURN_SUCCESS = 0,
  BRIDGE_USERCLIENT_SYNCHRONIZED_COMMUNICATION_RETURN_ERROR_GENERIC = 1,
};

enum {
  BRIDGE_USERCLIENT_TYPE_NONE,
  BRIDGE_USERCLIENT_TYPE_SET_REMAPCLASSES_INITIALIZE_VECTOR,
  BRIDGE_USERCLIENT_TYPE_SET_CONFIG_ALL,
  BRIDGE_USERCLIENT_TYPE_SET_CONFIG_ONE,
  BRIDGE_USERCLIENT_TYPE_SET_INITIALIZED,

  BRIDGE_USERCLIENT_TYPE_GET_CONFIG_ENABLED,
  BRIDGE_USERCLIENT_TYPE_GET_STATUS_MESSAGE,
  BRIDGE_USERCLIENT_TYPE_SET_WORKSPACEDATA,

  BRIDGE_USERCLIENT_TYPE_GET_DEVICE_INFORMATION_KEYBOARD,
  BRIDGE_USERCLIENT_TYPE_GET_DEVICE_INFORMATION_CONSUMER,
  BRIDGE_USERCLIENT_TYPE_GET_DEVICE_INFORMATION_POINTING,
};

enum {
  BRIDGE_USERCLIENT_NOTIFICATION_TYPE_NONE,
  BRIDGE_USERCLIENT_NOTIFICATION_TYPE_CONFIG_ENABLED_UPDATED,
  BRIDGE_USERCLIENT_NOTIFICATION_TYPE_STATUS_MESSAGE_UPDATED,
  BRIDGE_USERCLIENT_NOTIFICATION_TYPE_CHANGE_INPUT_SOURCE,
  BRIDGE_USERCLIENT_NOTIFICATION_TYPE_OPEN_URL,
  BRIDGE_USERCLIENT_NOTIFICATION_TYPE_IOHIDPOSTEVENT,
};

enum {
  BRIDGE_USERCLIENT_STATUS_MESSAGE_NONE,
  BRIDGE_USERCLIENT_STATUS_MESSAGE_EXTRA,
  BRIDGE_USERCLIENT_STATUS_MESSAGE_MODIFIER_LOCK,
  BRIDGE_USERCLIENT_STATUS_MESSAGE_MODIFIER_STICKY,
  BRIDGE_USERCLIENT_STATUS_MESSAGE_POINTING_BUTTON_LOCK,
  BRIDGE_USERCLIENT_STATUS_MESSAGE__END__,
};
enum {
  BRIDGE_USERCLIENT_STATUS_MESSAGE_MAXLEN = 128,
};

// 64bit alignment.
struct BridgeUserClientStruct {
  uint32_t type;
  uint32_t option;
  user_addr_t data;
  user_size_t size;
};
// STATIC_ASSERT for sizeof(struct BridgeUserClientStruct).
// We need to make this value same in kext and userspace.
enum { STATIC_ASSERT__sizeof_BridgeUserClientStruct = 1 / (sizeof(struct BridgeUserClientStruct) == 24) };

struct BridgeSetConfigOne {
  uint32_t isEssentialConfig;
  uint32_t index;
  int32_t value;
};
enum { STATIC_ASSERT__sizeof_BridgeSetConfigOne = 1 / (sizeof(struct BridgeSetConfigOne) == 12) };

struct BridgeWorkSpaceData {
  uint32_t applicationtype;
  uint32_t windowname;
  uint32_t uielementrole;
  uint32_t inputsource;
  uint32_t inputsourcedetail;
};
enum { STATIC_ASSERT__sizeof_BridgeWorkSpaceData = 1 / (sizeof(struct BridgeWorkSpaceData) == 20) };

struct BridgeDeviceInformation {
  uint32_t isFound;
  char manufacturer[128];
  char product[128];
  uint32_t vendorID;
  uint32_t productID;
  uint32_t locationID;
};
enum { STATIC_ASSERT__sizeof_BridgeDeviceInformation = 1 / (sizeof(struct BridgeDeviceInformation) == 4 + 128 * 2 + 12) };

// remapclasses_initialize_vector format:
//
// base:
// { the_count_of_initialize_vector, [<initialize_vector>] }
//
// <initialize_vector>
//   { size, configindex, {[<remap>], {<filter>}} }
//
// <filter>
//   { size, BRIDGE_FILTERTYPE_XXX, values }
//
// <remap>
//   { size, BRIDGE_REMAPTYPE_XXX, values }
//
// --------------------
//
// Example of <base>:
//   { 3, initialize_vector1, initialize_vector2, initialize_vector3 }
//
// Example of <initialize_vector>:
//   {
//     19,
//     1044,
//     5,BRIDGE_REMAPTYPE_KEYTOKEY,BRIDGE_DATATYPE_KEYCODE,0,BRIDGE_DATATYPE_KEYCODE,11,
//     2,BRIDGE_FILTERTYPE_CONFIG_NOT,881,
//     2,BRIDGE_FILTERTYPE_CONFIG_NOT,882,
//     5,BRIDGE_REMAPTYPE_KEYTOKEY,BRIDGE_DATATYPE_KEYCODE,1,BRIDGE_DATATYPE_KEYCODE,56,
//   };
//
//   No remap version
//   {
//     1,
//     2321,
//   }
//
// Example of <filter>:
//   { 2,BRIDGE_FILTERTYPE_CONFIG_NOT,881 }
//
// Example of <remap>:
//   { 5,BRIDGE_REMAPTYPE_KEYTOKEY,BRIDGE_DATATYPE_KEYCODE,0,BRIDGE_DATATYPE_KEYCODE,11 };
//

#endif
