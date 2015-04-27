/*********************************************************************
This is a library for our nRF8001 Bluetooth Low Energy Breakout

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1697

These displays use SPI to communicate, 4 or 5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Kevin Townsend/KTOWN  for Adafruit Industries.  
MIT license, check LICENSE for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/
#include <SPI.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <ble_system.h>
#include <lib_aci.h>
#include <aci_setup.h>
#include "rctelemetry/services.h"

#include "RCTelemetry_BLE.h"

/* Get the service pipe data created in nRFGo Studio */
#ifdef SERVICES_PIPE_TYPE_MAPPING_CONTENT
    static services_pipe_type_mapping_t
        services_pipe_type_mapping[NUMBER_OF_PIPES] = SERVICES_PIPE_TYPE_MAPPING_CONTENT;
#else
    #define NUMBER_OF_PIPES 0
    static services_pipe_type_mapping_t * services_pipe_type_mapping = NULL;
#endif

/* Length of the buffer used to store flash strings temporarily when printing. */
#define PRINT_BUFFER_SIZE 20

/* Store the setup for the nRF8001 in the flash of the AVR to save on RAM */
static const hal_aci_data_t setup_msgs[NB_SETUP_MESSAGES] PROGMEM = SETUP_MESSAGES_CONTENT;

static struct aci_state_t aci_state;            /* ACI state data */
static hal_aci_evt_t  aci_data;                 /* Command buffer */
static bool timing_change_done = false;



int8_t HAL_IO_RADIO_RESET, HAL_IO_RADIO_REQN, HAL_IO_RADIO_RDY, HAL_IO_RADIO_IRQ;

/**************************************************************************/
/*!
    Constructor for the UART service
*/
/**************************************************************************/


//// more callbacks

void RCTelemetry_BLE::defaultACICallback(aci_evt_opcode_t event)
{
  currentStatus = event;
}

aci_evt_opcode_t RCTelemetry_BLE::getState(void) {
  return currentStatus;
}



/**************************************************************************/
/*!
    Constructor for the UART service
*/
/**************************************************************************/
RCTelemetry_BLE::RCTelemetry_BLE(int8_t req, int8_t rdy, int8_t rst)
{
  debugMode = true;
  
  HAL_IO_RADIO_REQN = req;
  HAL_IO_RADIO_RDY = rdy;
  HAL_IO_RADIO_RESET = rst;

  aci_event = NULL;
  
  memset(device_name, 0x00, 8);


  currentStatus = ACI_EVT_DISCONNECTED;
}

void RCTelemetry_BLE::setACIcallback(aci_callback aciEvent) {
  aci_event = aciEvent;
}


void  RCTelemetry_BLE::sendRSSI(uint8_t rssi)
{
	if (lib_aci_is_pipe_available(&aci_state, PIPE_RC_TELEMETRY_RECEIVER_RSSI_TX)) {
		lib_aci_send_data(PIPE_RC_TELEMETRY_RECEIVER_RSSI_TX, &rssi, 1);
		aci_state.data_credit_available--;

		delay(35); // required delay between sends
		return;
	}

	pollACI();

	// TODO: how to handle when pipe is not available? retry? cache for later? warning on overriding cache?
}


/**************************************************************************/
/*!
    Update the device name (7 characters or less!)
*/
/**************************************************************************/
void RCTelemetry_BLE::setDeviceName(const char * deviceName)
{
  if (strlen(deviceName) > 7)
  {
    /* String too long! */
    return;
  }
  else
  {
    memcpy(device_name, deviceName, strlen(deviceName));
  }
}

/**************************************************************************/
/*!
    Handles low level ACI events, and passes them up to an application
    level callback when appropriate
*/
/**************************************************************************/
void RCTelemetry_BLE::pollACI()
{
  // We enter the if statement only when there is a ACI event available to be processed
  if (lib_aci_event_get(&aci_state, &aci_data))
  {
    aci_evt_t * aci_evt;
    
    aci_evt = &aci_data.evt;    
    switch(aci_evt->evt_opcode)
    {
        /* As soon as you reset the nRF8001 you will get an ACI Device Started Event */
        case ACI_EVT_DEVICE_STARTED:
        {          
          aci_state.data_credit_total = aci_evt->params.device_started.credit_available;
          switch(aci_evt->params.device_started.device_mode)
          {
            case ACI_DEVICE_SETUP:
            /* Device is in setup mode! */
            if (ACI_STATUS_TRANSACTION_COMPLETE != do_aci_setup(&aci_state))
            {
              if (debugMode) {
                Serial.println(F("Error in ACI Setup"));
              }
            }
            break;
            
            case ACI_DEVICE_STANDBY:
              /* Start advertising ... first value is advertising time in seconds, the */
              /* second value is the advertising interval in 0.625ms units */
              if (device_name[0] != 0x00)
              {
                /* Update the device name */
                lib_aci_set_local_data(&aci_state, PIPE_GAP_DEVICE_NAME_SET , (uint8_t *)&device_name, strlen(device_name));
              }
              lib_aci_connect(adv_timeout, adv_interval);
              defaultACICallback(ACI_EVT_DEVICE_STARTED);
	      if (aci_event) 
				aci_event(ACI_EVT_DEVICE_STARTED);
          }
        }
        break;
        
      case ACI_EVT_CMD_RSP:
        /* If an ACI command response event comes with an error -> stop */
        if (ACI_STATUS_SUCCESS != aci_evt->params.cmd_rsp.cmd_status)
        {
          // ACI ReadDynamicData and ACI WriteDynamicData will have status codes of
          // TRANSACTION_CONTINUE and TRANSACTION_COMPLETE
          // all other ACI commands will have status code of ACI_STATUS_SUCCESS for a successful command
          if (debugMode) {
            Serial.print(F("ACI Command "));
            Serial.println(aci_evt->params.cmd_rsp.cmd_opcode, HEX);
			Serial.println(aci_evt->params.cmd_rsp.cmd_status, HEX);

			Serial.println(F("Evt Cmd respone: Error. Arduino is in an while(1); loop"));

          }
          while (1);
        }
        if (ACI_CMD_GET_DEVICE_VERSION == aci_evt->params.cmd_rsp.cmd_opcode)
        {
          // Store the version and configuration information of the nRF8001 in the Hardware Revision String Characteristic
          lib_aci_set_local_data(&aci_state, PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET, 
            (uint8_t *)&(aci_evt->params.cmd_rsp.params.get_device_version), sizeof(aci_evt_cmd_rsp_params_get_device_version_t));
        }        
        break;
        
      case ACI_EVT_CONNECTED:
        aci_state.data_credit_available = aci_state.data_credit_total;
        /* Get the device version of the nRF8001 and store it in the Hardware Revision String */
        lib_aci_device_version();
        
	defaultACICallback(ACI_EVT_CONNECTED);
	if (aci_event) 
	  aci_event(ACI_EVT_CONNECTED);
        
	// TODO: how to adapt this to multiple pipes?
      case ACI_EVT_PIPE_STATUS:
     /*   if (lib_aci_is_pipe_available(&aci_state, PIPE_UART_OVER_BTLE_UART_TX_TX) && (false == timing_change_done))
        {
          lib_aci_change_timing_GAP_PPCP(); // change the timing on the link as specified in the nRFgo studio -> nRF8001 conf. -> GAP. 
                                            // Used to increase or decrease bandwidth
          timing_change_done = true;
        }
		*/
        break;
        
      case ACI_EVT_TIMING:
        /* Link connection interval changed */
        break;
        
      case ACI_EVT_DISCONNECTED:
        /* Restart advertising ... first value is advertising time in seconds, the */
        /* second value is the advertising interval in 0.625ms units */

	defaultACICallback(ACI_EVT_DISCONNECTED);
	if (aci_event)
	  aci_event(ACI_EVT_DISCONNECTED);

	lib_aci_connect(adv_timeout, adv_interval);

	defaultACICallback(ACI_EVT_DEVICE_STARTED);
	if (aci_event)
	  aci_event(ACI_EVT_DEVICE_STARTED);
	break;
        
	/*
      case ACI_EVT_DATA_RECEIVED:
	defaultRX(aci_evt->params.data_received.rx_data.aci_data, aci_evt->len - 2);
        if (rx_event)
	  rx_event(aci_evt->params.data_received.rx_data.aci_data, aci_evt->len - 2);
        break;
   */

      case ACI_EVT_DATA_CREDIT:
        aci_state.data_credit_available = aci_state.data_credit_available + aci_evt->params.data_credit.credit;
        break;
      
      case ACI_EVT_PIPE_ERROR:
        /* See the appendix in the nRF8001 Product Specication for details on the error codes */
        if (debugMode) {
          Serial.print(F("ACI Evt Pipe Error: Pipe #:"));
          Serial.print(aci_evt->params.pipe_error.pipe_number, DEC);
          Serial.print(F("  Pipe Error Code: 0x"));
          Serial.println(aci_evt->params.pipe_error.error_code, HEX);
        }

        /* Increment the credit available as the data packet was not sent */
        aci_state.data_credit_available++;
        break;
    }
  }
  else
  {
    // Serial.println(F("No ACI Events available"));
    // No event in the ACI Event queue and if there is no event in the ACI command queue the arduino can go to sleep
    // Arduino can go to sleep now
    // Wakeup from sleep from the RDYN line
  }
}

/**************************************************************************/
/*!
    Configures the nRF8001 and starts advertising the UART Service
    
    @param[in]  advTimeout  
                The advertising timeout in seconds (0 = infinite advertising)
    @param[in]  advInterval
                The delay between advertising packets in 0.625ms units
*/
/**************************************************************************/
bool RCTelemetry_BLE::begin(uint16_t advTimeout, uint16_t advInterval) 
{
  /* Store the advertising timeout and interval */
  adv_timeout = advTimeout;   /* ToDo: Check range! */
  adv_interval = advInterval; /* ToDo: Check range! */
  
  /* Setup the service data from nRFGo Studio (services.h) */
  if (NULL != services_pipe_type_mapping)
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = &services_pipe_type_mapping[0];
  }
  else
  {
    aci_state.aci_setup_info.services_pipe_type_mapping = NULL;
  }
  aci_state.aci_setup_info.number_of_pipes    = NUMBER_OF_PIPES;
  aci_state.aci_setup_info.setup_msgs         = (hal_aci_data_t*)setup_msgs;
  aci_state.aci_setup_info.num_setup_msgs     = NB_SETUP_MESSAGES;

  /* Pass the service data into the appropriate struct in the ACI */
  lib_aci_init(&aci_state);

  /* ToDo: Check for chip ID to make sure we're connected! */
  
  return true;
}
