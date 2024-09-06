/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
 */
#include "project.h"

void genericstack_callback(uint32_t event, void *event_param);
void ble_apphost_callback(void);

uint8_t operation_mode = 0;
uint8_t data[20]       = { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
                           0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24 };

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    if (Cy_BLE_Start(genericstack_callback) == CY_BLE_SUCCESS)
    {
        Cy_BLE_RegisterAppHostCallback(ble_apphost_callback);
    }
    else
    {
        CY_ASSERT(0u);
    }

    for (;;)
    {
        /* Place your application code here. */
        cy_stc_ble_gatt_handle_value_pair_t service_handle;
        cy_stc_ble_gatt_value_t service_data;
        service_data.val = data;
        service_data.len = 20;

        service_handle.attrHandle = CY_BLE_TEMPERATURE_READINGS_CHAR_HANDLE;
        service_handle.value = service_data;
        Cy_BLE_GATTS_WriteAttributeValueLocal(&service_handle);
        CyDelay(10000);
        // Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

void ble_apphost_callback(void)
{
    Cy_BLE_ProcessEvents();
}

void genericstack_callback(uint32_t event, void *event_param)
{
    cy_stc_ble_gatt_write_param_t *write_param;
    switch (event)
    {
    case CY_BLE_EVT_STACK_ON:
        Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
        break;
    case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
        operation_mode = 0;
        Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
        break;
    case CY_BLE_EVT_GATTS_WRITE_REQ:
        write_param = (cy_stc_ble_gatt_write_param_t *) event_param;
        if (write_param->handleValPair.attrHandle == CY_BLE_TEMPERATURE_OPERATION_CHAR_HANDLE)
        {
            operation_mode = write_param->handleValPair.value.val[0];
            Cy_BLE_GATTS_WriteRsp(write_param->connHandle);
        }
    }
}
/* [] END OF FILE */
