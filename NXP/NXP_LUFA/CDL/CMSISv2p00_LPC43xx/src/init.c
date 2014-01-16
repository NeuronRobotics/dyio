/*************************************************************************
 *
 *   Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2011
 *
 *    File name   : init.c
 *    Description : Low-Level Init Functions
 *
 *    History :
 *    1. Date        : November 2011
 *       Author      : Atanas Uzunov
 *       Description : initial revision
 *
 *    $Revision: 50291 $
 **************************************************************************/

#include "NXP\iolpc4350.h"
#include "stdint.h"

#pragma section=".intvec"

/*************************************************************************
 * Function Name: __low_level_init
 * Parameters: none
 *
 * Return: 1 - continue with data initialization
 *         0 - skip data initialization and go to main
 *
 * Description: Low-level initialization.
 *              Initializes vector table register and tunes EMC.
 *              Configures EMC address lines A14-A22
 *
 *************************************************************************/
int __low_level_init(void)
{
  VTOR = (uint32_t)__section_begin(".intvec");
#if ((!__RAM_MODE__) && (!__SPIFI_MODE__))
  /* Enable Buffer for External Flash */
  EMC_STATICCONFIG0_bit.B = 1;
  /* Configure delay from CS to Read Access */
  EMC_STATICWAITRD0_bit.WAITRD = 13;
  /* Configure Address Lines A14-A22 */
  /* Configure P6.8 as EMC_A14 */
  SCU_SFSP6_8 = 0xD1;
  /* Configure P6.7 as EMC_A15 */
  SCU_SFSP6_7 = 0xD1;
  /* Configure PD.16 as EMC_A16 */
  SCU_SFSPD_16 = 0xD2;
  /* Configure PD.15 as EMC_A17 */
  SCU_SFSPD_15 = 0xD2;
  /* Configure PE.0 as EMC_A18 */
  SCU_SFSPE_0 = 0xD3;
  /* Configure PE.1 as EMC_A19 */
  SCU_SFSPE_1 = 0xD3;
  /* Configure PE.2 as EMC_A20 */
  SCU_SFSPE_2 = 0xD3;
  /* Configure PE.3 as EMC_A21 */
  SCU_SFSPE_3 = 0xD3;
  /* Configure PE.4 as EMC_A22 */
  SCU_SFSPE_4 = 0xD3;
#endif
  return 1;
}
