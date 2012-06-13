#Rules.make

################# FIELDS MODIFIABLE BY THE USER ###############################
############### All the fields below are mandatory ############################

# Set home area (ex /home/user/)
HOME=

# Set Toolchain path (ex /home/user/toolchain/arago-2011.09/armv7a)
CSTOOL_DIR=

# Set Tool chain prefix (ex arm-arago-linux-gnueabi- )
CSTOOL_PREFIX=

# Set kernel installation path ( ex /home/user/linux-04.00.01.13 )
KERNEL_INSTALL_DIR=

# Set Target filesystem path ( ex /home/user/targetfs )
TARGETFS_INSTALL_DIR=

######################### PRE-DEFINED VARIABLES ###############################
######################## NOT MODIFIABLE BY USER ###############################

# Set installation folder
GRAPHICS_INSTALL_DIR=$(HOME)/Graphics_SDK_4_06_00_02

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

GFX_REL_ES3_LIB_SRCPATH=$(GRAPHICS_INSTALL_DIR)/gfx_rel_es3.x

GFX_DBG_ES3_LIB_SRCPATH=$(GRAPHICS_INSTALL_DIR)/gfx_dbg_es3.x

GFX_REL_ES5_LIB_SRCPATH=$(GRAPHICS_INSTALL_DIR)/gfx_rel_es5.x

GFX_DBG_ES5_LIB_SRCPATH=$(GRAPHICS_INSTALL_DIR)/gfx_dbg_es5.x

GFX_REL_ES6_LIB_SRCPATH=$(GRAPHICS_INSTALL_DIR)/gfx_rel_es6.x

GFX_DBG_ES6_LIB_SRCPATH=$(GRAPHICS_INSTALL_DIR)/gfx_dbg_es6.x

GFX_REL_ES8_LIB_SRCPATH=$(GRAPHICS_INSTALL_DIR)/gfx_rel_es8.x

GFX_DBG_ES8_LIB_SRCPATH=$(GRAPHICS_INSTALL_DIR)/gfx_dbg_es8.x

GFX_OGLES_REL_LIB_DESTPATH=$(GFX_OGLES_SDKPATH)/Builds/OGLES/LinuxOMAP3

GFX_OGLES2_REL_LIB_DESTPATH=$(GFX_OGLES2_SDKPATH)/Builds/OGLES2/LinuxOMAP3

GFX_OVG_REL_LIB_DESTPATH=$(GFX_OVG_SDKPATH)/Builds/OVG/LinuxOMAP3

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
