/*
 *  vi: formatoptions+=tc textwidth=80 tabstop=8 shiftwidth=8 noexpandtab:
 *
 *  $Id$
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  (C) Copyright Phil Dibowitz 2008
 */

#ifndef PROTOCOL_Z_H
#define PROTOCOL_Z_H

// 1000 only
#define SERVICE_FAMILY_CLIENT 2
// 1000 only
#define SERVICE_FAMILY_TEST 12

// Literal for 890 only
#define TYPE_REQUEST 0			
// Literal for 890 only
#define TYPE_RESPONSE 1

/* .. and the 1000 is the opposite? */
#if 0
#define TYPE_REQUEST true
#deinfe TYPE_RESPONSE false
#endif

#define COMMAND_INVALID 0x00
#define COMMAND_EXECUTE_ACTION 0x01
#define COMMAND_EXECUTE_REPEATED_ACTION 0x02
#define COMMAND_CONTINUE_REPEATED_ACTION 0x03
#define COMMAND_FINISH_REPEATED_ACTION 0x04
#define COMMAND_INITIATE_DIAGNOSTIC_TCP_CHANNEL 0x10
#define COMMAND_UDP_ECHO 0x11
#define COMMAND_UDP_PING 0x12
#define COMMAND_TCP_ECHO 0x13
#define COMMAND_TCP_PING 0x14
#define COMMAND_READ_MEMORY_HEADER 0x15
#define COMMAND_READ_MEMORY_DATA 0x16
#define COMMAND_READ_MEMORY_DONE 0x17
#define COMMAND_WRITE_MEMORY_HEADER 0x18
#define COMMAND_WRITE_MEMORY_DATA 0x19
#define COMMAND_WRITE_MEMORY_DONE 0x1A
#define COMMAND_RESET 0x1B
#define COMMAND_CALCULATE_CHECKSUM 0x1C
#define COMMAND_INITIATE_UPDATE_TCP_CHANNEL 0x40
#define COMMAND_START_UDPATE 0x41
#define COMMAND_WRITE_UDPATE_HEADER 0x42
#define COMMAND_WRITE_UPDATE_DATA 0x43
#define COMMAND_WRITE_UPDATE_DONE 0x44
#define COMMAND_GET_UDPATE_CHECKSUM 0x45
#define COMMAND_FINISH_UPDATE 0x46
#define COMMAND_READ_REGION 0x47
#define COMMAND_READ_REGION_DATA 0x48
#define COMMAND_READ_REGION_DONE 0x49
/* BEGIN 890-ONLY */
#define COMMAND_START_RAW_IR_TCP_CHANNEL 0x50
#define COMMAND_CACHE_RAW_IR_HEADER 0x51
#define COMMAND_CACHE_RAW_IR_DATA 0x52
#define COMMAND_CACHE_RAW_IR_DONE 0x53
#define COMMAND_EXECUTE_RAW_IR 0x54
#define COMMAND_START_RAW_IR 0x55
#define COMMAND_CONTINUE_RAW_IR 0x56
#define COMMAND_FINISH_RAW_IR 0x57
/* END 890-ONLY */
#define COMMAND_INITIATE_SYSTEM_TCP_CHANNEL 0x60
#define COMMAND_GET_SYSTEM_INFO 0x61
#define COMMAND_GET_INTERFACE_LIST 0x62
#define COMMAND_IS_INTERFACE_SUPPORTED 0x65
#define COMMAND_GET_GUID 0x67
#define COMMAND_SET_GUID 0x68
#define COMMAND_GET_NAME 0x6A
#define COMMAND_SET_NAME 0x6B
#define COMMAND_GET_LOCATION 0x6C
#define COMMAND_SET_LOCATION 0x6D
/* BEGIN 1000-ONLY */
#define COMMAND_GET_REGION_IDS 0x6E
#define COMMAND_GET_REGION_VERSION 0x6F
/* END 1000-ONLY */
#define COMMAND_GET_CURRENT_TIME 0x70
#define COMMAND_UPDATE_TIME 0x71
#define COMMAND_INITIATE_ZWAVE_TCP_CHANNEL 0x80
#define COMMAND_SEND_LONG_ZWAVE_REQUEST_HEADER 0x81
#define COMMAND_SEND_LONG_ZWAVE_REQUEST_DATA 0x82
#define COMMAND_SEND_LONG_ZWAVE_REQUEST_DATA_DONE 0x83
#define COMMAND_SEND_SHORT_ZWAVE_REQUEST 0x84
#define COMMAND_SEND_SHORT_ZWAVE_RESPONSE 0x85
#define COMMAND_SET_NODE_ID 0x86
#define COMMAND_GET_NODE_ID 0x87
#define COMMAND_GET_HOME_ID 0x88
#define COMMAND_SET_HOME_ID 0x89
#define COMMAND_SEND_LONG_ZWAVE_RESPONSE_HEADER 0x8A
#define COMMAND_SEND_LONG_ZWAVE_RESPONSE_DATA 0x8B
#define COMMAND_SEND_LONG_ZWAVE_RESPONSE_DATA_DONE 0x8C
#define COMMAND_INITIATE_LEARNIR_TCP_CHANNEL 0xA0
#define COMMAND_LEARNIR 0xA1
#define COMMAND_LEARNIR_HEADER 0xA2
#define COMMAND_LEARNIR_DATA 0xA3
#define COMMAND_LEARNIR_DONE 0xA4
#define COMMAND_LEARNIR_STOP 0xA5
// 1000 only
#define COMMAND_RESET_TEST_FLAG 0xF2

#define STATUS_NULL 0x00
#define STATUS_OK 0x01
#define STATUS_BUSY 0x02
#define STATUS_BAD_VERSION 0x03
#define STATUS_UNKNOWN_HANDLE 0x04
#define STATUS_UNKNOWN_ACTION 0x05
#define STATUS_ALREADY_ABORTED 0x06
#define STATUS_NO_MORE_DATA 0x07
#define STATUS_INVALID_ADDRESS 0x08
#define STATUS_INVALID_TCP_COMMAND 0x09
#define STATUS_BAD_DATA_LENGTH 0x0A
#define STATUS_BAD_REGION 0x0B
// 890 only
#define STATUS_INVALID_ARGUMENT 0x0C
// 1000 only
#define STATUS_BAD_PACKET 0x0C
// 890 only
#define STATUS_DEVICE_NOT_READY 0x0D
// 1000 only
#define STATUS_PAUSE 0x0D
// 890 only
#define STATUS_INVALID_RESPONSE 0x0E
// 1000 only
#define STATUS_FAILED 0x0E
// 1000 only
#define STATUS_BAD_CHECKSUM 0x7F

#endif
