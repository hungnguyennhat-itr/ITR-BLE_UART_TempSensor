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
    }
}

void ble_apphost_callback(void)
{
    Cy_BLE_ProcessEvents(void);
}
/* [] END OF FILE */
