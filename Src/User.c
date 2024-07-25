/*
  ******************************************************************************
  * @file    user.c 
  * @author  AMS - RF Application Team
  * @date    27 - 04 - 2021
  * @brief   Application functions
  ******************************************************************************
  * @attention
  *
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2021 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/** \cond DOXYGEN_SHOULD_SKIP_THIS
 */ 
 
/* Includes-----------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bluenrg_lps_it.h"
#include "ble_const.h"
#include "bluenrg_lp_stack.h"
#include "rf_driver_hal_power_manager.h"
#include "rf_driver_hal_vtimer.h"
#include "bluenrg_lp_evb_com.h"
#include "gatt_profile.h"
#include "gap_profile.h"
#include "user.h"
 

#ifndef DEBUG
#define DEBUG 1
#endif


#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#define DEVICE_ADDRESS       0xa2, 0x00, 0x00, 0xE1, 0x80, 0x02

static volatile uint8_t set_discoverable=TRUE; 
static Advertising_Set_Parameters_t Advertising_Set_Parameters[1];


/**
 * @brief  Init a BlueNRG device
 * @param  None.
 * @retval None.
*/
void device_initialization(void)
{
  uint8_t bdaddr[] = {DEVICE_ADDRESS};
  uint8_t device_name[]={'T', 'e', 's', 't'};
  uint8_t ret;
  uint16_t service_handle, dev_name_char_handle, appearance_char_handle;
  
  static uint8_t adv_data[] = {0x02,AD_TYPE_FLAGS, FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE|FLAG_BIT_BR_EDR_NOT_SUPPORTED,
                               5, AD_TYPE_COMPLETE_LOCAL_NAME,'N', 'o', 'd', 'e'};

  /* Configure Public address */
  ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET, CONFIG_DATA_PUBADDR_LEN, bdaddr);
  if(ret != BLE_STATUS_SUCCESS) {
    PRINTF("aci_hal_write_config_data() failed: 0x%02x\r\n", ret);
  }
  
  /* Set the TX power to 0 dBm */
  aci_hal_set_tx_power_level(0, 25);
  
  /* GATT Init */
  ret = aci_gatt_srv_init();    
  if(ret){
    PRINTF("aci_gatt_srv_init() failed: 0x%02x\r\n", ret);
  }
      
  /* GAP Init */
  ret = aci_gap_init(GAP_PERIPHERAL_ROLE, 0, 0x07,  0x00, &service_handle, &dev_name_char_handle, &appearance_char_handle);
  if(ret){
    PRINTF("aci_gap_Init() failed: 0x%02x\r\n", ret);
  }
      
    /* Update device name */
  Gap_profile_set_dev_name(0, sizeof(device_name), device_name);
  
  ret = aci_gap_set_advertising_configuration(0, GAP_MODE_GENERAL_DISCOVERABLE,
                                              ADV_PROP_CONNECTABLE|ADV_PROP_SCANNABLE|ADV_PROP_LEGACY,
                                              100, 
                                              100,
                                              ADV_CH_ALL,
                                              PUBLIC_ADDR,NULL,
                                              ADV_NO_WHITE_LIST_USE,
                                              0, /* 0 dBm */
                                              LE_1M_PHY, /* Primary advertising PHY */
                                              0, /* 0 skips */
                                              LE_1M_PHY, /* Secondary advertising PHY. Not used with legacy advertising. */
                                              0, /* SID */
                                              0 /* No scan request notifications */);
  PRINTF("Advertising configuration %02X\n", ret);
  
  ret = aci_gap_set_advertising_data(0, ADV_COMPLETE_DATA, sizeof(adv_data), adv_data);
  
  PRINTF("Set advertising data %02X\n", ret);  
 
}

/**
 * @brief  Put a device in discoverable mode
 * @param  None.
 * @retval None.
*/
void set_device_discoverable(void)
{  
  uint8_t ret;    

  Advertising_Set_Parameters[0].Advertising_Handle = 0;
  Advertising_Set_Parameters[0].Duration = 0;
  Advertising_Set_Parameters[0].Max_Extended_Advertising_Events = 0;
  
  ret = aci_gap_set_advertising_enable(ENABLE, 1, Advertising_Set_Parameters); 

  if (ret != BLE_STATUS_SUCCESS)
    PRINTF ("Error in aci_gap_set_advertising_enable(): 0x%02x\r\n", ret);
  else
    PRINTF ("aci_gap_set_advertising_enable() --> SUCCESS\r\n");

  PRINTF("Start Advertising \r\n");
}

/**
 * @brief  Device Demo state machine.
 * @param  None.
 * @retval None.
*/
void APP_Tick(void)
{

  //USER ACTION IS NEEDED
  
  /* Make the device discoverable */
  if(set_discoverable) {
    set_device_discoverable();
    set_discoverable = FALSE;
  } 
}



/* ***************** BlueNRG-LP Stack Callbacks ********************************/

void hci_le_connection_complete_event(uint8_t Status,
                                      uint16_t Connection_Handle,
                                      uint8_t Role,
                                      uint8_t Peer_Address_Type,
                                      uint8_t Peer_Address[6],
                                      uint16_t Conn_Interval,
                                      uint16_t Conn_Latency,
                                      uint16_t Supervision_Timeout,
                                      uint8_t Master_Clock_Accuracy)

{ 
  //USER ACTION IS NEEDED
  PRINTF ("CONNECTION, Status:  0x%0x\r\n", Status);
    
}/* end hci_le_connection_complete_event() */

void hci_le_enhanced_connection_complete_event(uint8_t Status,
                                               uint16_t Connection_Handle,
                                               uint8_t Role,
                                               uint8_t Peer_Address_Type,
                                               uint8_t Peer_Address[6],
                                               uint8_t Local_Resolvable_Private_Address[6],
                                               uint8_t Peer_Resolvable_Private_Address[6],
                                               uint16_t Conn_Interval,
                                               uint16_t Conn_Latency,
                                               uint16_t Supervision_Timeout,
                                               uint8_t Master_Clock_Accuracy)
{
  //USER ACTION IS NEEDED
  hci_le_connection_complete_event(Status,
                                   Connection_Handle,
                                   Role,
                                   Peer_Address_Type,
                                   Peer_Address,
                                   Conn_Interval,
                                   Conn_Latency,
                                   Supervision_Timeout,
                                   Master_Clock_Accuracy);
}

void hci_disconnection_complete_event(uint8_t Status,
                                      uint16_t Connection_Handle,
                                      uint8_t Reason)
{
  //USER ACTION IS NEEDED
  set_discoverable = TRUE;
  PRINTF ("DISCONNECTION, Status:  0x%0x\r\n", Status);
  
}/* end hci_disconnection_complete_event() */

/** \endcond 
*/

