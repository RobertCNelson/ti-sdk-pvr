#
# Copyright (C) Imagination Technologies Ltd. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms and conditions of the GNU General Public License,
# version 2, as published by the Free Software Foundation.
#
# This program is distributed in the hope it will be useful but, except
# as otherwise stated in writing, without any warranty; without even the
# implied warranty of merchantability or fitness for a particular purpose.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
#
# The full GNU General Public License is included in this distribution in
# the file called "COPYING".
#
# Contact Information:
# Imagination Technologies Ltd. <gpl-support@imgtec.com>
# Home Park Estate, Kings Langley, Herts, WD4 8LZ, UK
#
#

$(call must-be-defined,$(SUPPORT_DRI_DRM))

DRM_SOURCE_DIR := drivers/gpu/drm

ccflags-y += \
	 -I$(KERNELDIR)/include/drm \
	 -I$(DRM_SOURCE_DIR)

drm-y += \
	services4/3rdparty/linux_drm/pvr_drm_stubs.o \
	external/$(DRM_SOURCE_DIR)/drm_auth.o \
	external/$(DRM_SOURCE_DIR)/drm_bufs.o \
	external/$(DRM_SOURCE_DIR)/drm_cache.o \
	external/$(DRM_SOURCE_DIR)/drm_context.o \
	external/$(DRM_SOURCE_DIR)/drm_dma.o \
	external/$(DRM_SOURCE_DIR)/drm_drawable.o \
	external/$(DRM_SOURCE_DIR)/drm_drv.o \
	external/$(DRM_SOURCE_DIR)/drm_fops.o \
	external/$(DRM_SOURCE_DIR)/drm_gem.o \
	external/$(DRM_SOURCE_DIR)/drm_ioctl.o \
	external/$(DRM_SOURCE_DIR)/drm_irq.o \
	external/$(DRM_SOURCE_DIR)/drm_lock.o \
	external/$(DRM_SOURCE_DIR)/drm_memory.o \
	external/$(DRM_SOURCE_DIR)/drm_proc.o \
	external/$(DRM_SOURCE_DIR)/drm_stub.o \
	external/$(DRM_SOURCE_DIR)/drm_vm.o \
	external/$(DRM_SOURCE_DIR)/drm_agpsupport.o \
	external/$(DRM_SOURCE_DIR)/drm_scatter.o \
	external/$(DRM_SOURCE_DIR)/ati_pcigart.o \
	external/$(DRM_SOURCE_DIR)/drm_pci.o \
	external/$(DRM_SOURCE_DIR)/drm_sysfs.o \
	external/$(DRM_SOURCE_DIR)/drm_hashtab.o \
	external/$(DRM_SOURCE_DIR)/drm_sman.o \
	external/$(DRM_SOURCE_DIR)/drm_mm.o \
	external/$(DRM_SOURCE_DIR)/drm_crtc.o \
	external/$(DRM_SOURCE_DIR)/drm_modes.o \
	external/$(DRM_SOURCE_DIR)/drm_edid.o \
	external/$(DRM_SOURCE_DIR)/drm_info.o \
	external/$(DRM_SOURCE_DIR)/drm_debugfs.o \
	external/$(DRM_SOURCE_DIR)/drm_encoder_slave.o

# extra flags for some files
CFLAGS_pvr_drm_stubs.o := -DCONFIG_PCI
CFLAGS_drm_drv.o := -DCONFIG_PCI
CFLAGS_drm_stub.o := -DCONFIG_PCI
CFLAGS_ati_pcigart.o := -DCONFIG_PCI
