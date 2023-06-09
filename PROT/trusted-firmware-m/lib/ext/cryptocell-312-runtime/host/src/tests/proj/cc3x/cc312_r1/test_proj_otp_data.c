/*
 * Copyright (c) 2001-2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdint.h>

uint32_t OTP_CM_VALUES[] = { /* no PCI or TCI mode*/

/*  [0x00-0x07]: 256bit Device root key (HUK) */
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x08-0x0B]: 128bit ICV Provosioning secret (Kpicv) */
0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x0C-0x0F]: 128bit ICV Provosioning secret (Kceicv) */
0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x10]: manufacturer programmed flag */
0x00000000,
/*  [0x11-0x18]: a single 256b SHA256 (Hbk), or, two 128b truncated SHA256 HBK0 and HBK1 */
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x19-0x1C]: 128bit OEM provisioning secret (Kcp) */
0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x1D-0x20]: 128bit OEM code encryption secret (Kce) */
0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x21]: OEM programmed flag */
0x00000000,
/*  [0x22-0x23]: Hbk0 trusted FW min version */
0x00000000, 0x00000000,
/*  [0x24-0x26]: Hbk1 trusted FW min version */
0x00000000, 0x00000000, 0x00000000,
/*  [0x27]: general purpose configuration flag */
0x00000000,
/*  [0x28-0x2B] - 128b DCU lock mask */
0x00000000, 0x00000000, 0x00000000, 0x00000000,

};


uint32_t OTP_DM_HBK_VALUES[] = {

/*  [0x00-0x07]: 256bit Device root key (HUK) */
0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001,
/*  [0x08-0x0B]: 128bit ICV Provosioning secret (Kpicv) */
0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x0C-0x0F]: 128bit ICV Provosioning secret (Kceicv) */
0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x10]: manufacturer programmed flag */
0x808080f8,
/*  [0x11-0x18]: a single 256b SHA256 (Hbk), or, two 128b truncated SHA256 HBK0 and HBK1 */
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x19-0x1C]: 128bit OEM provisioning secret (Kcp) */
0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x1D-0x20]: 128bit OEM code encryption secret (Kce) */
0x00000000, 0x00000000, 0x00000000, 0x00000000,
/*  [0x21]: OEM programmed flag */
0x00000000,
/*  [0x22-0x23]: Hbk0 trusted FW min version */
0x00000000, 0x00000000,
/*  [0x24-0x26]: Hbk1 trusted FW min version */
0x00000000, 0x00000000, 0x00000000,
/*  [0x27]: general purpose configuration flag */
0x00000000,
/*  [0x28-0x2B] - 128b DCU lock mask */
0x00000000, 0x00000000, 0x00000000, 0x00000000,

};

