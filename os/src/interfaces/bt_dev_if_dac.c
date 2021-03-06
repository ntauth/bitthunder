/**
 *	DAC Configuration API.
 *
 *
 **/
#include <bitthunder.h>

struct _BT_OPAQUE_HANDLE {
	BT_HANDLE_HEADER h;
};


static BT_LIST_HEAD(g_dac_devices);
static BT_u32 g_total_dacs = 0;

static const BT_IF_HANDLE oHandleInterface;

static BT_HANDLE devfs_open(struct bt_devfs_node *node, BT_ERROR *pError) {
	BT_DAC_INFO *pInfo = (BT_DAC_INFO *) bt_container_of(node, BT_DAC_INFO, node);
	if(!pInfo->ulReferenceCount) {
		pInfo->ulReferenceCount += 1;
		//BT_AttachHandle(NULL, &oHandleInterface, (BT_HANDLE) &pInfo->hDac);
		return (BT_HANDLE) pInfo->hDac;
	}

	return NULL;
}

static const BT_DEVFS_OPS dac_devfs_ops = {
	.pfnOpen = devfs_open,
};

static BT_BOOL isDacHandle(BT_HANDLE hDac) {
	if(!hDac || !BT_IF_DEVICE(hDac) || (BT_IF_DEVICE_TYPE(hDac) != BT_DEV_IF_T_DAC)) {
		return BT_FALSE;
	}
	return BT_TRUE;
}

BT_ERROR BT_DacStart(BT_HANDLE hDac) {
	if(!isDacHandle(hDac)) {
		// ERR_INVALID_HANDLE_TYPE
		return (BT_ERROR) -1;
	}

	return BT_IF_DAC_OPS(hDac)->pfnStart(hDac);
}
BT_EXPORT_SYMBOL(BT_DacStart);

BT_ERROR BT_DacStop(BT_HANDLE hDac) {
	if(!isDacHandle(hDac)) {
		// ERR_INVALID_HANDLE_TYPE
		return (BT_ERROR) -1;
	}

	return BT_IF_DAC_OPS(hDac)->pfnStop(hDac);
}
BT_EXPORT_SYMBOL(BT_DacStop);

BT_HANDLE BT_DacRegisterCallback(BT_HANDLE hDac, BT_DAC_CALLBACK pfnCallback, void *pParam, BT_ERROR *pError) {
	if(!isDacHandle(hDac)) {
		// ERR_INVALID_HANDLE_TYPE
		return NULL;
	}

	return BT_IF_DAC_OPS(hDac)->pfnRegisterCallback(hDac, pfnCallback, pParam, pError);
}
BT_EXPORT_SYMBOL(BT_DacRegisterCallback);

BT_ERROR BT_DacUnregisterCallback(BT_HANDLE hDac, BT_HANDLE hCallback) {
	if(!isDacHandle(hDac)) {
		// ERR_INVALID_HANDLE_TYPE
		return (BT_ERROR) -1;
	}

	return BT_IF_DAC_OPS(hDac)->pfnUnregisterCallback(hDac, hCallback);
}
BT_EXPORT_SYMBOL(BT_DacUnregisterCallback);

BT_ERROR BT_DacWrite(BT_HANDLE hDac, BT_u32 ulChannel, BT_u32 ulSize, BT_u32 *pSrc) {
	if(!isDacHandle(hDac)) {
		// ERR_INVALID_HANDLE_TYPE
		return (BT_ERROR) -1;
	}

	return BT_IF_DAC_OPS(hDac)->pfnWrite(hDac, ulChannel, ulSize, pSrc);
}
BT_EXPORT_SYMBOL(BT_DacWrite);

/**
 *	@brief	Set a Complete TIMER configuration for the TIMER device specified by the BT_HANDLE.
 *
 **/
BT_ERROR BT_DacSetConfiguration(BT_HANDLE hDac, BT_DAC_CONFIG *pConfig) {
	if(!isDacHandle(hDac)) {
		// ERR_INVALID_HANDLE_TYPE
		return (BT_ERROR) -1;
	}
	return BT_IF_DAC_OPS(hDac)->pfnSetConfig(hDac, pConfig);
}
BT_EXPORT_SYMBOL(BT_DacSetConfiguration);

/**
 *	@brief	Get a Complete TIMER configuration for the TIMER device specified by the BT_HANDLE.
 *
 **/
BT_ERROR BT_DacGetConfiguration(BT_HANDLE hDac, BT_DAC_CONFIG *pConfig) {
	if(!isDacHandle(hDac)) {
		// ERR_INVALID_HANDLE_TYPE
		return (BT_ERROR) -1;
	}
	return BT_IF_DAC_OPS(hDac)->pfnGetConfig(hDac, pConfig);
}
BT_EXPORT_SYMBOL(BT_DacGetConfiguration);

BT_ERROR BT_DacRegisterDevice(BT_HANDLE hDevice, BT_DAC_INFO *dac) {	bt_list_add(&dac->item, &g_dac_devices);
	dac->node.pOps = &dac_devfs_ops;
	dac->hDac = hDevice;

	char name[10];

	const BT_RESOURCE *pResource = BT_GetDeviceResource(dac->pDevice, BT_RESOURCE_STRING, 0);
	if(!pResource) {
		bt_sprintf(name, "dac%d", g_total_dacs);
	}
	else {
		strncpy(name,  pResource->szpName, 10);
	}
	g_total_dacs++;

	BT_kPrint("Registering %s as /dev/%s", dac->pDevice->name, name);

	return BT_DeviceRegister(&dac->node, name);
}
BT_EXPORT_SYMBOL(BT_DACRegisterDevice);
