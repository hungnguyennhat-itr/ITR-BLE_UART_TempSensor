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
#include "sys/sys_ble.h"

uint8_t data[20]       = { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24,
                           0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24 };
bool    init_result    = 0;
bool    receive_result = 0;
uint8_t rcv_data;
int     main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    init_result = sys_ble_init();
    for (;;)
    {
        /* Place your application code here. */
        if (init_result)
        {
            receive_result = sys_ble_receive(&rcv_data);
            if (receive_result)
            {
                Cy_GPIO_Write(LED_GREEN_0_PORT, LED_GREEN_0_NUM, 0);
                CyDelay(1000);
            }
            else
            {
                Cy_GPIO_Write(LED_GREEN_0_PORT, LED_GREEN_0_NUM, 1);
            }
        }
    }
}

/* [] END OF FILE */
