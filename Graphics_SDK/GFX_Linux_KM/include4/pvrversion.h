/**********************************************************************
 *
 * Copyright (C) Imagination Technologies Ltd. All rights reserved.
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











#ifndef _PVRVERSION_H_
#define _PVRVERSION_H_

#define PVR_STR(X) #X
#define PVR_STR2(X) PVR_STR(X)

#define PVRVERSION_MAJ               1
#define PVRVERSION_MIN               7
#define PVRVERSION_BRANCH            17

#define PVRVERSION_FAMILY           "sgxddk"
#define PVRVERSION_BRANCHNAME       "1.7"
#define PVRVERSION_BUILD             867897
#define PVRVERSION_BSCONTROL        "CustomerTI_OMAP4430_Linux_GPL"

#define PVRVERSION_STRING           "CustomerTI_OMAP4430_Linux_GPL sgxddk 17 1.7@" PVR_STR2(PVRVERSION_BUILD)
#define PVRVERSION_STRING_SHORT     "1.7@" PVR_STR2(PVRVERSION_BUILD)

#define COPYRIGHT_TXT               "Copyright (c) Imagination Technologies Ltd. All Rights Reserved."

#define PVRVERSION_BUILD_HI          86
#define PVRVERSION_BUILD_LO          7897
#define PVRVERSION_STRING_NUMERIC    PVR_STR2(PVRVERSION_MAJ) "." PVR_STR2(PVRVERSION_MIN) "." PVR_STR2(PVRVERSION_BUILD_HI) "." PVR_STR2(PVRVERSION_BUILD_LO)

#endif