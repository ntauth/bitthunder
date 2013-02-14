#
#	Build the BitThunder as an operating system, or a software framework?
#
#	y = os... 		use BitThunder scheduling/process and memory management.
#	n = framework	Memory / process management is done by your underlying OS. Uses libc.
#
BT_CONFIG_OS=y

#
#	Kernel / Scheduler selection.
#
BT_CONFIG_KERNEL=FreeRTOS
#BT_CONFIG_KERNEL=BtKernel

#
#	Define the maximum number of IRQs allowed in the system.
#	This should cover all interrupts controllers.
#
BT_CONFIG_MAX_IRQ=95

ARCH=arm
SUBARCH=lpc11xx
#
#	Arch Specific configuration.
#

#
#	This enables the default BitThunder startup code,
#	You can replace this with your own code by disabling this option.
#
BT_CONFIG_MAX_INTERRUPT_CONTROLLERS=1
BT_CONFIG_MAX_GPIO_CONTROLLERS=1


#
#	Driver Configurations
#

include $(BASE).config.mk

