/**
* This file is autogenerated by nRFgo Studio 1.18.0.9
*/

#ifndef SETUP_MESSAGES_H__
#define SETUP_MESSAGES_H__

#include "hal_platform.h"
#include "aci.h"

// You have now chosen to upload the configuration to OTP on the device.
// This will result in a device that you can not modify afterwards. If this is your intention,
// remove this comment and the #error below
#error Generating configuration for OTP. Please verify usage by removing this error message from include file.

#define SETUP_ID 0
#define SETUP_FORMAT 3 /** nRF8001 D */
#define ACI_DYNAMIC_DATA_SIZE 158

/* Service: Gap - Characteristic: Device name - Pipe: SET */
#define PIPE_GAP_DEVICE_NAME_SET          1
#define PIPE_GAP_DEVICE_NAME_SET_MAX_SIZE 8

/* Service: RC Telemetry - Characteristic: Receiver RSSI - Pipe: TX */
#define PIPE_RC_TELEMETRY_RECEIVER_RSSI_TX          2
#define PIPE_RC_TELEMETRY_RECEIVER_RSSI_TX_MAX_SIZE 1

/* Service: RC Telemetry - Characteristic: Transmitter RSSI - Pipe: TX */
#define PIPE_RC_TELEMETRY_TRANSMITTER_RSSI_TX          3
#define PIPE_RC_TELEMETRY_TRANSMITTER_RSSI_TX_MAX_SIZE 1

/* Service: RC Telemetry - Characteristic: Battery Level - Pipe: TX */
#define PIPE_RC_TELEMETRY_BATTERY_LEVEL_TX          4
#define PIPE_RC_TELEMETRY_BATTERY_LEVEL_TX_MAX_SIZE 2

/* Service: Device Information - Characteristic: Hardware Revision String - Pipe: SET */
#define PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET          5
#define PIPE_DEVICE_INFORMATION_HARDWARE_REVISION_STRING_SET_MAX_SIZE 9


#define NUMBER_OF_PIPES 5

#define SERVICES_PIPE_TYPE_MAPPING_CONTENT {\
  {ACI_STORE_LOCAL, ACI_SET},   \
  {ACI_STORE_LOCAL, ACI_TX},   \
  {ACI_STORE_LOCAL, ACI_TX},   \
  {ACI_STORE_LOCAL, ACI_TX},   \
  {ACI_STORE_LOCAL, ACI_SET},   \
}

#define GAP_PPCP_MAX_CONN_INT 0x12 /**< Maximum connection interval as a multiple of 1.25 msec , 0xFFFF means no specific value requested */
#define GAP_PPCP_MIN_CONN_INT  0x6 /**< Minimum connection interval as a multiple of 1.25 msec , 0xFFFF means no specific value requested */
#define GAP_PPCP_SLAVE_LATENCY 0
#define GAP_PPCP_CONN_TIMEOUT 0xa /** Connection Supervision timeout multiplier as a multiple of 10msec, 0xFFFF means no specific value requested */

#define NB_SETUP_MESSAGES 22
#define SETUP_MESSAGES_CONTENT {\
    {0x00,\
        {\
            0x07,0x06,0x00,0x00,0x03,0x02,0x42,0x07,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x05,0x01,0x01,0x00,0x00,0x06,0x00,0x00,\
            0xd1,0x0a,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x1c,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x03,0x90,0x01,0xff,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x10,0x38,0xff,0xff,0x02,0x58,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,\
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x05,0x06,0x10,0x54,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x00,0x04,0x04,0x02,0x02,0x00,0x01,0x28,0x00,0x01,0x00,0x18,0x04,0x04,0x05,0x05,0x00,\
            0x02,0x28,0x03,0x01,0x0e,0x03,0x00,0x00,0x2a,0x04,0x14,0x08,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x1c,0x07,0x00,0x03,0x2a,0x00,0x01,0x52,0x43,0x54,0x65,0x6c,0x65,0x6d,0x65,0x04,0x04,\
            0x05,0x05,0x00,0x04,0x28,0x03,0x01,0x02,0x05,0x00,0x01,0x2a,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x38,0x06,0x04,0x03,0x02,0x00,0x05,0x2a,0x01,0x01,0x00,0x00,0x04,0x04,0x05,0x05,0x00,\
            0x06,0x28,0x03,0x01,0x02,0x07,0x00,0x04,0x2a,0x06,0x04,0x09,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x54,0x08,0x00,0x07,0x2a,0x04,0x01,0x06,0x00,0x12,0x00,0x00,0x00,0x0a,0x00,0x04,0x04,\
            0x02,0x02,0x00,0x08,0x28,0x00,0x01,0x01,0x18,0x04,0x04,0x10,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x70,0x10,0x00,0x09,0x28,0x00,0x01,0xfb,0x74,0xb8,0x21,0xca,0x60,0x1e,0x93,0x7d,0x4f,\
            0x1b,0x11,0x00,0x00,0xb2,0x02,0x04,0x04,0x13,0x13,0x00,0x0a,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0x8c,0x28,0x03,0x01,0x10,0x0b,0x00,0xfb,0x74,0xb8,0x21,0xca,0x60,0x1e,0x93,0x7d,0x4f,\
            0x1b,0x11,0x01,0x00,0xb2,0x02,0x16,0x00,0x02,0x01,0x00,0x0b,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xa8,0x00,0x01,0x02,0x00,0x46,0x14,0x03,0x02,0x00,0x0c,0x29,0x02,0x01,0x00,0x00,0x04,\
            0x04,0x13,0x13,0x00,0x0d,0x28,0x03,0x01,0x10,0x0e,0x00,0xfb,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xc4,0x74,0xb8,0x21,0xca,0x60,0x1e,0x93,0x7d,0x4f,0x1b,0x11,0x02,0x00,0xb2,0x02,0x16,\
            0x00,0x02,0x01,0x00,0x0e,0x00,0x02,0x02,0x00,0x46,0x14,0x03,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xe0,0x02,0x00,0x0f,0x29,0x02,0x01,0x00,0x00,0x04,0x04,0x13,0x13,0x00,0x10,0x28,0x03,\
            0x01,0x10,0x11,0x00,0xfb,0x74,0xb8,0x21,0xca,0x60,0x1e,0x93,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x20,0xfc,0x7d,0x4f,0x1b,0x11,0x03,0x00,0xb2,0x02,0x16,0x00,0x03,0x02,0x00,0x11,0x00,0x03,\
            0x02,0x00,0x00,0x46,0x14,0x03,0x02,0x00,0x12,0x29,0x02,0x01,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x21,0x18,0x00,0x00,0x04,0x04,0x02,0x02,0x00,0x13,0x28,0x00,0x01,0x0a,0x18,0x04,0x04,0x05,\
            0x05,0x00,0x14,0x28,0x03,0x01,0x02,0x15,0x00,0x27,0x2a,0x04,\
        },\
    },\
    {0x00,\
        {\
            0x15,0x06,0x21,0x34,0x04,0x09,0x01,0x00,0x15,0x2a,0x27,0x01,0x0a,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
            0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x1f,0x06,0x40,0x00,0x2a,0x00,0x01,0x00,0x80,0x04,0x00,0x03,0x00,0x00,0x00,0x01,0x02,0x00,0x02,0x04,\
            0x00,0x0b,0x00,0x0c,0x00,0x02,0x02,0x00,0x02,0x04,0x00,0x0e,\
        },\
    },\
    {0x00,\
        {\
            0x19,0x06,0x40,0x1c,0x00,0x0f,0x00,0x03,0x02,0x00,0x02,0x04,0x00,0x11,0x00,0x12,0x2a,0x27,0x01,0x00,\
            0x80,0x04,0x00,0x15,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x13,0x06,0x50,0x00,0xfb,0x74,0xb8,0x21,0xca,0x60,0x1e,0x93,0x7d,0x4f,0x1b,0x11,0x00,0x00,0xb2,0x02,\
        },\
    },\
    {0x00,\
        {\
            0x12,0x06,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
        },\
    },\
    {0x00,\
        {\
            0x06,0x06,0xf0,0x00,0x83,0xe9,0xfa,\
        },\
    },\
}

#endif
