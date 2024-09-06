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

int main(void)
{
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    if (Cy_BLE_Start(NULL) == CY_BLE_SUCCESS)
    {
        Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);
    }
    else
    {
        /* Halt the CPU */
        CY_ASSERT(0u);
    }
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for (;;)
    {
        /* Place your application code here. */
        Cy_BLE_ProcessEvents();
        // Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    }
}

/* [] END OF FILE */
