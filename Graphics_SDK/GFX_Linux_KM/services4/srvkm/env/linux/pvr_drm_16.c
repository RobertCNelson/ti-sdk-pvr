/**********************************************************************
 *
 * Copyright(c) 2008 Imagination Technologies Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful but, except
 * as otherwise stated in writing, without any warranty; without even the
 * implied warranty of merchantability or fitness for a particular purpose.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Contact Information:
 * Imagination Technologies Ltd. <gpl-support@imgtec.com>
 * Home Park Estate, Kings Langley, Herts, WD4 8LZ, UK
 *
 ******************************************************************************/

#if defined(SUPPORT_DRI_DRM)

#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,38)
#ifndef AUTOCONF_INCLUDED
 #include <linux/config.h>
#endif
#endif

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/ioctl.h>
#include <drm/drmP.h>
#include <drm/drm.h>

#include "img_defs.h"
#include "services.h"
#include "kerneldisplay.h"
#include "kernelbuffer.h"
#include "syscommon.h"
#include "pvrmmap.h"
#include "mm.h"
#include "mmap.h"
#include "mutex.h"
#include "pvr_debug.h"
#include "srvkm.h"
#include "perproc.h"
#include "handle.h"
#include "pvr_bridge_km.h"
#include "pvr_bridge.h"
#include "proc.h"
#include "pvrmodule.h"
#include "pvrversion.h"
#include "lock.h"
#include "linkage.h"
#include "pvr_drm.h"

#if defined(PVR_DRI_DRM_NOT_PCI)
#include "pvr_drm_mod.h"
#endif

#define PVR_DRM_NAME	PVRSRV_MODNAME
#define PVR_DRM_DESC	"Imagination Technologies PVR DRM"

DECLARE_WAIT_QUEUE_HEAD(sWaitForInit);

IMG_BOOL bInitComplete;
IMG_BOOL bInitFailed;

#if !defined(PVR_DRI_DRM_NOT_PCI)
struct pci_dev *gpsPVRLDMDev;
#endif

struct drm_device *gpsPVRDRMDev;

#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,24))
#error "Linux kernel version 2.6.25 or later required for PVR DRM support"
#endif

#define PVR_DRM_FILE struct drm_file *

#if !defined(SUPPORT_DRI_DRM_EXT)
static struct pci_device_id asPciIdList[] = {
#if defined(PVR_DRI_DRM_NOT_PCI)
	{1, 1, 1, 1, 0, 0, 0},
#else
	{SYS_SGX_DEV_VENDOR_ID, SYS_SGX_DEV_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
#if defined(SYS_SGX_DEV1_DEVICE_ID)
	{SYS_SGX_DEV_VENDOR_ID, SYS_SGX_DEV1_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
#endif
#endif
	{0}
};
#endif

DRI_DRM_STATIC int
PVRSRVDrmLoad(struct drm_device *dev, unsigned long flags)
{
	int iRes=0;

	PVR_TRACE(("PVRSRVDrmLoad"));

	gpsPVRDRMDev = dev;
#if !defined(PVR_DRI_DRM_NOT_PCI)
	gpsPVRLDMDev = dev->pdev;
#endif

#if defined(PDUMP)
	iRes = dbgdrv_init();
	if (iRes != 0)
	{
		goto exit;
	}
#endif

	iRes = PVRCore_Init();
	if (iRes != 0)
	{
		goto exit_dbgdrv_cleanup;
	}

#if defined(DISPLAY_CONTROLLER)
	iRes = PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Init)(dev);
	if (iRes != 0)
	{
		goto exit_pvrcore_cleanup;
	}
#endif
//	return 0;
        goto exit;
#if defined(DISPLAY_CONTROLLER)
exit_pvrcore_cleanup:
	PVRCore_Cleanup();
#endif
exit_dbgdrv_cleanup:
#if defined(PDUMP)
	dbgdrv_cleanup();
#endif
exit:
	if (iRes != 0)
	{
		bInitFailed = IMG_TRUE;
	}
	bInitComplete = IMG_TRUE;

	wake_up_interruptible(&sWaitForInit);


	return iRes;
}

DRI_DRM_STATIC int
PVRSRVDrmUnload(struct drm_device *dev)
{
	PVR_TRACE(("PVRSRVDrmUnload"));

#if defined(DISPLAY_CONTROLLER)
	PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Cleanup)(dev);
#endif

	PVRCore_Cleanup();

#if defined(PDUMP)
	dbgdrv_cleanup();
#endif

	return 0;
}

DRI_DRM_STATIC int
PVRSRVDrmOpen(struct drm_device *dev, struct drm_file *file)
{
while (!bInitComplete)
	{
		DEFINE_WAIT(sWait);

		prepare_to_wait(&sWaitForInit, &sWait, TASK_INTERRUPTIBLE);

		if (!bInitComplete)
		{
			PVR_TRACE(("%s: Waiting for module initialisation to complete", __FUNCTION__));

			schedule();
		}

		finish_wait(&sWaitForInit, &sWait);

		if (signal_pending(current))
		{
			return -ERESTARTSYS;
		}
	}

	if (bInitFailed)
	{
		PVR_DPF((PVR_DBG_ERROR, "%s: Module initialisation failed", __FUNCTION__));
		return -EINVAL;
	}


	return PVRSRVOpen(dev, file);
}

#if defined(SUPPORT_DRI_DRM_EXT) && !defined(PVR_LINUX_USING_WORKQUEUES)
DRI_DRM_STATIC void
PVRSRVDrmPostClose(struct drm_device *dev, struct drm_file *file)
{
	PVRSRVRelease(file->driver_priv);

	file->driver_priv = NULL;
}
#else
DRI_DRM_STATIC int
PVRSRVDrmRelease(struct inode *inode, struct file *filp)
{
	struct drm_file *file_priv = filp->private_data;
	void *psDriverPriv = file_priv->driver_priv;
	int ret;

	ret = drm_release(inode, filp);

	if (ret != 0)
	{

		PVR_DPF((PVR_DBG_ERROR, "%s : drm_release failed: %d",
			__FUNCTION__, ret));
	}

	PVRSRVRelease(psDriverPriv);

	return 0;
}
#endif

DRI_DRM_STATIC int
PVRDRMIsMaster(struct drm_device *dev, void *arg, struct drm_file *pFile)
{
	return 0;
}

#if defined(SUPPORT_DRI_DRM_EXT)
int
PVRDRM_Dummy_ioctl(struct drm_device *dev, void *arg, struct drm_file *pFile)
{
	return 0;
}
#endif

DRI_DRM_STATIC int
PVRDRMUnprivCmd(struct drm_device *dev, void *arg, struct drm_file *pFile)
{
	int ret = 0;

	LinuxLockMutex(&gPVRSRVLock);

	if (arg == NULL)
	{
		ret = -EFAULT;
	}
	else
	{
		IMG_UINT32 *pui32Args = (IMG_UINT32 *)arg;
		IMG_UINT32 ui32Cmd = pui32Args[0];
		IMG_UINT32 *pui32OutArg = (IMG_UINT32 *)arg;

		switch (ui32Cmd)
		{
			case PVR_DRM_UNPRIV_INIT_SUCCESFUL:
				*pui32OutArg = PVRSRVGetInitServerState(PVRSRV_INIT_SERVER_SUCCESSFUL) ? 1 : 0;
				break;

			default:
				ret = -EFAULT;
		}

	}

	LinuxUnLockMutex(&gPVRSRVLock);

	return ret;
}

#if defined(DISPLAY_CONTROLLER) && defined(PVR_DISPLAY_CONTROLLER_DRM_IOCTL)
static int
PVRDRM_Display_ioctl(struct drm_device *dev, void *arg, struct drm_file *pFile)
{
	int res;

	LinuxLockMutex(&gPVRSRVLock);

	res = PVR_DRM_MAKENAME(DISPLAY_CONTROLLER, _Ioctl)(dev, arg, pFile);

	LinuxUnLockMutex(&gPVRSRVLock);

	return res;
}
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,33))
#define	PVR_DRM_FOPS_IOCTL	.unlocked_ioctl
#define	PVR_DRM_UNLOCKED	DRM_UNLOCKED
#define DRM_IOCTL_PVR_DRM_SRVKM_IOCTL PVR_DRM_SRVKM_IOCTL
#define DRM_PVR_DRM_SRVKM_IOCTL PVR_DRM_SRVKM_IOCTL
#define DRM_PVR_DRM_IS_MASTER_IOCTL PVR_DRM_IS_MASTER_IOCTL
#define DRM_IOCTL_PVR_DRM_IS_MASTER_IOCTL PVR_DRM_IS_MASTER_IOCTL
#define DRM_PVR_DRM_UNPRIV_IOCTL PVR_DRM_UNPRIV_IOCTL
#define DRM_IOCTL_PVR_DRM_UNPRIV_IOCTL PVR_DRM_UNPRIV_IOCTL
#else
#define	PVR_DRM_FOPS_IOCTL	.ioctl
#define	PVR_DRM_UNLOCKED	0
#endif

#if !defined(SUPPORT_DRI_DRM_EXT)
struct drm_ioctl_desc sPVRDrmIoctls[] = {
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
	DRM_IOCTL_DEF_DRV(PVR_DRM_SRVKM_IOCTL, PVRSRV_BridgeDispatchKM, PVR_DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(PVR_DRM_IS_MASTER_IOCTL, PVRDRMIsMaster, DRM_MASTER | PVR_DRM_UNLOCKED),
	DRM_IOCTL_DEF_DRV(PVR_DRM_UNPRIV_IOCTL, PVRDRMUnprivCmd, PVR_DRM_UNLOCKED),
#else
	DRM_IOCTL_DEF(PVR_DRM_SRVKM_IOCTL, PVRSRV_BridgeDispatchKM, PVR_DRM_UNLOCKED),
	DRM_IOCTL_DEF(PVR_DRM_IS_MASTER_IOCTL, PVRDRMIsMaster, DRM_MASTER | PVR_DRM_UNLOCKED),
	DRM_IOCTL_DEF(PVR_DRM_UNPRIV_IOCTL, PVRDRMUnprivCmd, PVR_DRM_UNLOCKED),
#endif
#if defined(PDUMP)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
	DRM_IOCTL_DEF_DRV(PVR_DRM_DBGDRV_IOCTL, dbgdrv_ioctl, PVR_DRM_UNLOCKED),
#else
	DRM_IOCTL_DEF(PVR_DRM_DBGDRV_IOCTL, dbgdrv_ioctl, PVR_DRM_UNLOCKED),
#endif
#endif
#if defined(DISPLAY_CONTROLLER) && defined(PVR_DISPLAY_CONTROLLER_DRM_IOCTL)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,36))
	DRM_IOCTL_DEF_DRV(PVR_DRM_DISP_IOCTL, PVRDRM_Display_ioctl, DRM_MASTER | PVR_DRM_UNLOCKED)
#else
	DRM_IOCTL_DEF(PVR_DRM_DISP_IOCTL, PVRDRM_Display_ioctl, DRM_MASTER | PVR_DRM_UNLOCKED)
#endif
#endif
};

static int pvr_max_ioctl = DRM_ARRAY_SIZE(sPVRDrmIoctls);

static struct drm_driver sPVRDrmDriver =
{
	.driver_features = 0,
	.dev_priv_size = 0,
	.load = PVRSRVDrmLoad,
	.unload = PVRSRVDrmUnload,
	.open = PVRSRVDrmOpen,
	.suspend = PVRSRVDriverSuspend,
	.resume = PVRSRVDriverResume,
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,32))
	.get_map_ofs = drm_core_get_map_ofs,
	.get_reg_ofs = drm_core_get_reg_ofs,
#endif
	.ioctls = sPVRDrmIoctls,
	.fops =
	{
		.owner = THIS_MODULE,
		.open = drm_open,
		.release = PVRSRVDrmRelease,
		PVR_DRM_FOPS_IOCTL = drm_ioctl,
		.mmap = PVRMMap,
		.poll = drm_poll,
		.fasync = drm_fasync,
	},
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,38))
	.pci_driver =
	{
		.name = PVR_DRM_NAME,
		.id_table = asPciIdList,
	},
#else
	.kdriver =
	{
	PVR_DRM_NAME,
	asPciIdList,
	},
//	{
//		.pci->name = PVR_DRM_NAME,
//		.pci->id_table = asPciIdList,
//	},
#endif

	.name = PVR_DRM_NAME,
	.desc = PVR_DRM_DESC,
	.date = PVR_BUILD_DATE,
	.major = PVRVERSION_MAJ,
	.minor = PVRVERSION_MIN,
	.patchlevel = PVRVERSION_BUILD,
};

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,39))
static struct pci_driver pci_pvr_driver = {
        .name = PVR_DRM_NAME,
        .id_table = asPciIdList,
};
#endif

static int __init PVRSRVDrmInit(void)
{
	int iRes;
	sPVRDrmDriver.num_ioctls = pvr_max_ioctl;


	PVRDPFInit();

#if defined(PVR_DRI_DRM_NOT_PCI)
	iRes = drm_pvr_dev_add();
	if (iRes != 0)
	{
		return iRes;
	}
#endif

#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,38))
	iRes = drm_init(&sPVRDrmDriver);
#else
	iRes = drm_pci_init(&sPVRDrmDriver,&pci_pvr_driver);
#endif
#if defined(PVR_DRI_DRM_NOT_PCI)
	if (iRes != 0)
	{
		drm_pvr_dev_remove();
	}
#endif
	return iRes;
}

static void __exit PVRSRVDrmExit(void)
{
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,38))
	drm_exit(&sPVRDrmDriver);
#else
	drm_pci_exit(&sPVRDrmDriver,&pci_pvr_driver);
#endif

#if defined(PVR_DRI_DRM_NOT_PCI)
	drm_pvr_dev_remove();
#endif
}

module_init(PVRSRVDrmInit);
module_exit(PVRSRVDrmExit);
#endif
#endif
