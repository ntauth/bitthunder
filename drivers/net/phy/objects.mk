PHY_OBJECTS-$(BT_CONFIG_DRIVERS_NET_PHY_MARVELL) += $(BUILD_DIR)/drivers/net/phy/marvell.o
PHY_OBJECTS += $(PHY_OBJECTS-y)

$(PHY_OBJECTS): MODULE_NAME="drivers-phy"

OBJECTS += $(PHY_OBJECTS)
