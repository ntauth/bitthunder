#ifndef _BT_IF_FS_H_
#define _BT_IF_FS_H_

#include "bt_if_file.h"
#include "bt_if_dir.h"
#include "bt_if_inode.h"

typedef struct _BT_IF_FS {
	BT_u32		ulFlags;
	const BT_i8 *name;
    #define 	BT_FS_FLAG_NODEV	0x00000001	// No underlying block device is required
	union {
	    BT_HANDLE 	(*pfnMount)			(BT_HANDLE hFS, BT_HANDLE hVolume, const void *data, BT_ERROR *pError);
	    BT_HANDLE 	(*pfnMountPseudo) 	(BT_HANDLE hFS, const void *data, BT_ERROR *pError);
	};
	BT_ERROR	(*pfnUnmount)	(BT_HANDLE hMount);
	BT_HANDLE	(*pfnOpen)		(BT_HANDLE hMount, const BT_i8 *szpPath, BT_u32 ulModeFlags, BT_ERROR *pError);
	BT_ERROR	(*pfnMkDir)		(BT_HANDLE hMount, const BT_i8 *szpPath);
	BT_HANDLE	(*pfnOpenDir)	(BT_HANDLE hMount, const BT_i8 *szpPath, BT_ERROR *pError);
	BT_HANDLE	(*pfnGetInode)	(BT_HANDLE hMount, const BT_i8 *szpPath, BT_ERROR *pError);
	BT_ERROR	(*pfnRemove)	(BT_HANDLE hMount, const BT_i8 *szpPath);
	BT_ERROR	(*pfnRename)	(BT_HANDLE hMount, const BT_i8 *szpPathA, const BT_i8 *szpPathB);
} BT_IF_FS;






#endif
