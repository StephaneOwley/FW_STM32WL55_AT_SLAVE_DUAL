/*
 * mbmuxif_owley.h
 *
 *  Created on: Jul 24, 2025
 *      Author: sloiseau
 */

#ifndef APPLICATION_USER_MBMUX_MBMUXIF_OWLEY_H_
#define APPLICATION_USER_MBMUX_MBMUXIF_OWLEY_H_

int MBMUXIF_OwleyInit(void);
MBMUX_ComParam_t* MBMUXIF_GetOwleyCmdRespBuffer(void);
MBMUX_ComParam_t* MBMUXIF_GetOwleyFeatureCmdComPtr(void);


#endif /* APPLICATION_USER_MBMUX_MBMUXIF_OWLEY_H_ */
