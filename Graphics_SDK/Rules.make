#Rules.make

################# FIELDS MODIFIABLE BY THE USER ###############################
############### All the fields below are MANDATORY ############################

#By default all below variables have been initialized with equivalent AMSDK variables
# Change them to appropriate paths as per your machine/build environment paths.
# Set home area (ex /home/user/)
HOME=$(SDK_INSTALL_DIR)/graphics

# Set Toolchain path (ex /home/user/toolchain/arago-2011.09/armv7a)
CSTOOL_DIR=$(LINUX_DEVKIT_PATH)

# Set Tool chain prefix (ex arm-arago-linux-gnueabi- )
CSTOOL_PREFIX=`basename $CROSS_COMPILE`

# Set kernel installation path ( ex /home/user/linux-04.00.01.13 )
KERNEL_INSTALL_DIR=$(LINUXKERNEL_INSTALL_DIR)

# Set Target filesystem path ( ex /home/user/targetfs )
TARGETFS_INSTALL_DIR=$(DESTDIR)

# Set installation folder
GRAPHICS_INSTALL_DIR=$(HOME)/Graphics_SDK_5_01_01_02
############### All the fields below are OPTIONAL ############################
############### BEST SUGGESTED TO LEAVE THE BELOW AS IS ############################

# Below is just an optional define given only to enable users who want to pass additional compiler/link flags.
# Only update the below options if you exactly know about the additional flag to be added & also are sure that its supported with your toolchain.
# Otherwise its best suggested to leave the below as is ie empty

# Add additional Compiler flags below only if required (Please read above comments)
EXTRA_CFLAGS?=
# Add additional Linker flags below only if required (Please read above comments)
EXTRA_LFLAGS?=

export EXTRA_CFLAGS
export EXTRA_LFLAGS

######################### PRE-DEFINED VARIABLES ###############################
######################## NOT MODIFIABLE BY USER ###############################


# Location of demo executables and install information
GFX_DEMOS_EXECPATH=$(GRAPHICS_INSTALL_DIR)/gfxsdkdemos

CSTOOL_PATH=$(CSTOOL_DIR)/bin
CSTOOL_LIBSTDC++_PATH=$(CSTOOL_DIR)/$(subst gnueabi-,gnueabi,$(CSTOOL_PREFIX))/lib
export CSTOOL_PATH
export CSTOOL_PREFIX

PLATFORM=LinuxARMV7

GFX_OGLES_SDKPATH=$(GRAPHICS_INSTALL_DIR)/GFX_Linux_SDK/OGLES/SDKPackage

GFX_OGLES2_SDKPATH=$(GRAPHICS_INSTALL_DIR)/GFX_Linux_SDK/OGLES2/SDKPackage

GFX_OVG_SDKPATH=$(GRAPHICS_INSTALL_DIR)/GFX_Linux_SDK/OVG/SDKPackage

GFX_OGLES_REL_LIB_DESTPATH=$(GFX_OGLES_SDKPATH)/Builds/OGLES/LinuxARMV7

GFX_OGLES2_REL_LIB_DESTPATH=$(GFX_OGLES2_SDKPATH)/Builds/OGLES2/LinuxARMV7

GFX_OVG_REL_LIB_DESTPATH=$(GFX_OVG_SDKPATH)/Builds/OVG/LinuxARMV7

GFX_KERNMOD_SRCPATH=$(GRAPHICS_INSTALL_DIR)/GFX_Linux_KM

GFX_PKG_TARGETFS_PATH = $(GRAPHICS_INSTALL_DIR)/targetfs

GFX_LIBRARY_TARGET_PATH = $(TARGETFS_INSTALL_DIR)/opt/gfxlibraries

GFX_DEVMEM2_SRCPATH = $(GRAPHICS_INSTALL_DIR)/tools/devmem2

# Where to copy the resulting executables and data to (when executing 'make
# install') in a proper file structure. This EXEC_DIR should either be visible
# from the target, or you will have to copy this (whole) directory onto the
# target filesystem.
EXEC_DIR=$(TARGETFS_INSTALL_DIR)/opt/gfxsdkdemos
################################################################################
