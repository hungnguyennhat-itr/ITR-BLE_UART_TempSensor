/**
 * @file       sys_ble.c
 * @copyright  Copyright (C) 2023 ITR VN. All rights reserved.
 * @license    This project is released under the ITR VN License.
 * @version    1.0.0
 * @date       2024-9
 * @author     Hung Nguyen
 * @brief      System layer for BLE
 * @note       None
 */
/* Public includes ---------------------------------------------------------- */
#include "sys_ble.h"

/* Private includes --------------------------------------------------------- */
/* Private defines ---------------------------------------------------------- */


/* Private macros ----------------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------------- */
/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static uint8_t ble_rcv_val = 0;
static bool ble_rcv_flag = 0;
/* Private prototypes ------------------------------------------------------- */
static void sys_ble_event_handler(uint32_t event, void *event_param);
static void sys_ble_event_notify(void);
/* Public implementations --------------------------------------------------- */
bool sys_ble_init(void)
{
    if (Cy_BLE_Start(sys_ble_event_handler)  != CY_BLE_SUCCESS)
    {
        return 0;
    }
    while (Cy_BLE_GetState() != 2)
    {
        Cy_BLE_ProcessEvents();
    }
    Cy_BLE_RegisterAppHostCallback(sys_ble_event_notify);
    return 1;
}

bool sys_ble_receive(uint8_t* val)
{
    bool ret_flag = 0;
    if (ble_rcv_flag == 1)
    {
        *val = ble_rcv_val;
        ret_flag = ble_rcv_flag;
        ble_rcv_flag = 0;
    }
    return ret_flag;
}

bool sys_ble_transmit(uint8_t* val, uint8_t len)
{
    if (val == NULL)
    {
        return 0;
    }

    if ((len <= 0) && (len > 20))
    {
        return 0;
    }
    cy_stc_ble_gatt_handle_value_pair_t serviceHandle;
    cy_stc_ble_gatt_value_t serviceData;
    serviceData.val = val;
    serviceData.len = len;
    serviceHandle.attrHandle = CY_BLE_WIRELESS_UART_TRANSMIT_CHAR_HANDLE;
    serviceHandle.value = serviceData;
    Cy_BLE_GATTS_WriteAttributeValueLocal(&serviceHandle);
    return 1;
}
/* Private implementations -------------------------------------------------- */
/*******************************************************************************
 * Function Name: sys_ble_event_handler()
 ********************************************************************************
 *
 * Summary:
 *   This is an event callback function to receive events from the BLE Component.
 *
 *  event        - the event code
 *  *event_param - the event parameters
 *
 *******************************************************************************/
static void sys_ble_event_handler(uint32_t event, void *event_param)
{
    switch (event)
    {
    case CY_BLE_EVT_STACK_ON:
    case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
    {
        Cy_BLE_GAPP_StartAdvertisement(0, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
        break;
    }
    case CY_BLE_EVT_GATTS_WRITE_CMD_REQ:
    {
        cy_stc_ble_gatts_write_cmd_req_param_t* rcv_param = (cy_stc_ble_gatts_write_cmd_req_param_t *)event_param;
        if (rcv_param->handleValPair.attrHandle == CY_BLE_WIRELESS_UART_RECEIVE_CHAR_HANDLE)
        {
            ble_rcv_val = rcv_param->handleValPair.value.val[0];
            ble_rcv_flag = 1;
            Cy_BLE_GATTS_WriteRsp(rcv_param->connHandle);
        }
        break;
    }
    }
}

static void sys_ble_event_notify(void)
{
    Cy_BLE_ProcessEvents();
}
/* End of file -------------------------------------------------------------- */
