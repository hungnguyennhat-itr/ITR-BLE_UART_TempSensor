/**
 * @file       sys_ble.h
 * @copyright  Copyright (C) 2023 ITR VN. All rights reserved.
 * @license    This project is released under the ITR VN License.
 * @version    1.0.0
 * @date       2024-9
 * @author     Hung Nguyen
 * @brief      Sytem layer for BLE
 * @note       None
 */
/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __SYS_BLE_H
#define __SYS_BLE_H

/* Includes ----------------------------------------------------------------- */
#include <stdbool.h>
#include "project.h"



/* Public defines ----------------------------------------------------------- */
/* Public macros ------------------------------------------------------------ */
/* Public enumerate/structure ----------------------------------------------- */
/* Public variables --------------------------------------------------------- */

/* Public APIs -------------------------------------------------------------- */
bool sys_ble_init(void);
bool sys_ble_receive(uint8_t* val);
bool sys_ble_transmit(uint8_t* val, uint8_t len);
/* -------------------------------------------------------------------------- */

#endif /* __SYS_BLE_H */

/* End of file -------------------------------------------------------------- */
