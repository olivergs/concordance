/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
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
 *  (C) Copyright Phil Dibowitz 2007
 *  (C) Copyright Kevin Timmerman 2007
 */

#ifndef LIBHARMONY_H
#define LIBHARMONY_H

#ifdef WIN32
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned __int64 uint64_t;

/*
 * FIXME: We need to fix the code that is generating these warnings!!
 */
#if _MSC_VER >= 1400
#pragma warning( disable : 4996 )
#endif

#else
#include <stdint.h>
#endif

#define LH_ERROR 1
#define LH_ERROR_INVALID_DATA_FROM_REMOTE 2
#define LH_ERROR_READ 3
#define LH_ERROR_WRITE 4
#define LH_ERROR_INVALIDATE 5
#define LH_ERROR_ERASE 6
#define LH_ERROR_VERIFY 7
#define LH_ERROR_POST 8
#define LH_ERROR_GET_TIME 9
#define LH_ERROR_SET_TIME 10
#define LH_ERROR_CONNECT 11
#define LH_ERROR_OS 12
#define LH_ERROR_OS_NET 13
#define LH_ERROR_OS_FILE 14
#define LH_ERROR_UNSUPP 15
#define LH_ERROR_INVALID_CONFIG 16

/*
 * Actual C clients are not fully supported yet, but that's the goal...
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * CALLBACK INFORMATION
 *
 * There is currently only one kind of callback, and it's for status
 * information. It should be a void function and takes the following
 * arguments:
 *   uint32_t count - the amount of times this cb has been called in a
 *                    given call of a given functioin
 *   uint32_t curr  - current status (usually bytes read/written)
 *   uint32_t total - total goal status (usually bytes expected to read/write)
 *   void *arg      - opaque object you can pass to functions to have them
 *                    pass back to your callback.
 */
typedef void (*lh_callback)(uint32_t, uint32_t, uint32_t, void*);

/*
 * REMOTE INFORMATION ACCESSORS
 *
 * These take nothing, and return what they say. Simple stuff.
 */
const char *get_mfg();
const char *get_model();
const char *get_codename();
int get_skin();
int get_fw_ver_maj();
int get_fw_ver_min();
int get_fw_type();
int get_hw_ver_maj();
int get_hw_ver_min();
int get_flash_size();
int get_flash_mfg();
int get_flash_id();
const char *get_flash_part_num();
int get_arch();
int get_proto();
const char *get_hid_mfg_str();
const char *get_hid_prod_str();
int get_hid_irl();
int get_hid_orl();
int get_hid_frl();
int get_usb_vid();
int get_usb_pid();
int get_usb_bcd();
char *get_serial(int p);
int get_config_bytes_used();
int get_config_bytes_total();

/*
 * TIME ACCESSORS
 *
 * These can ONLY be called *after* get_time() or set_time(). Each call will
 * initialize the internal time structures to the time used, and these
 * accessors can be used to access that data.
 */
int get_time_second();
int get_time_minute();
int get_time_hour();
int get_time_day();
int get_time_dow();
int get_time_month();
int get_time_year();
int get_time_utc_offset();
const char *get_time_timezone();

/*
 * HELPER FUNCTIONS
 */

/*
 * Translate a return value into an actual error message. Pass in the int
 * you received, get back a string.
 */
const char *lh_strerror(int err);
/*
 * Get the value from the BINARYSIZE tag in the XML.
 */
int find_binary_size(uint8_t *ptr, uint32_t *size);
/*
 * Pass in a pointer to an array holding the read in config object (for
 * example, one you might get from read_config_from_remote()), and it'll
 * adjust that pointer to the beginning of the binary portion (aka skip
 * past the XML portion).
 * Size should be the size of the ptr, and it will be modified to account
 * for the the change in *ptr.
 */
int find_binary_start(uint8_t **ptr, uint32_t *size);
/*
 * Many functions require you to pass in a ptr which then gets pointed
 * to data that we allocate. You should then call this to clean that
 * data up when you are done with it.
 */
int delete_blob(uint8_t *ptr);


/*
 * GENERAL REMOTE INTERACTIONS
 */

/*
 * Initialize USB (and WinSock if necessary) and find the remote
 * if possible.
 */
int init_harmony();
/*
 * Release the USB device, and tear down anything else necessary.
 */
int deinit_harmony();
/*
 * This is another initialization function. Generally speaking you always
 * want to call this before you do anything. It will query the remote about
 * it's data and fill in internal data structures with that information. This
 * counts as a successful "connectivity test"
 */
int get_identity(lh_callback cb, void *cb_arg);
/*
 * Reboot the remote.
 */
int reset_remote();
/*
 * Get the time from the remote. Use the time accessors above to access
 * the data.
 */
int get_time();
/*
 * Set the time on the remote to the system time. To find out what time was
 * used, use the time accessors above.
 */
int set_time();
/*
 * POST to the harmonyremote.com website that the connection test was
 * successful. A Connectivity.EZHex file must be passed in so that we
 * can get the URL, cookie information, etc.
 */
int post_connect_test_success(char *file_name);
/*
 * Prior to updating the config, if you want to interact with the website
 * you have to send it some initial data. This does that. The data passed
 * in here is a pointer to the config data config block (with XML - this
 * should NOT be the pointer passed to find_binary_start().
 */
int post_preconfig(uint8_t *data);
/*
 * After writing the config to the remote, this should be called to tell
 * the harmonyremote.com website that it was successful.
 */
int post_postconfig(uint8_t *data);
/*
 * This sends the remote a command to tell it we're about to start
 * writing to it's flash area and that it shouldn't read from it.
 * This must be used before writing a config, firmware, or anything
 * else that touches flash.
 *
 * If something goes wrong, or you change your mind after invalidating
 * flash, you should reboot the device.
 */
int invalidate_flash();

/*
 * CONFIGURATION INTERACTIONS
 */
 
/*
 * Read the config from the remote and store it into the unit8_t array
 * *out. The callback is for status information. See above for CB info.
 *
 * NOTE: The pointer *out should not point to anything useful. We will
 * allocate a char array and point your pointer at it. Use delete[] to
 * reclaim this memory.
 */
int read_config_from_remote(uint8_t **out, uint32_t *size,
	lh_callback cb, void *cb_arg);
/*
 * Given a config block in the byte array *in that is size big, write
 * it to the remote. This should be *just* the binary blog (see
 * find_binary_start()). CB info above.
 */
int write_config_to_remote(uint8_t *in, uint32_t size,
	lh_callback cb, void *cb_arg);
/*
 * Read the config from a file. If it's a standard XML file from the
 * harmonyremote.com website, the XML will be included. If it's just
 * the binary blob, that's fine too. size will be returned.
 *
 * NOTE: The pointer *out should not point to anything useful. We will
 * allocate a char array and point your pointer at it. Use delete[] to
 * reclaim this memory.
 */
int read_config_from_file(char *file_name, uint8_t **out, uint32_t *size);
/*
 * Given a binary-only config blob *in, write the config to a file. Unless
 * binary is true, the XML will be constructed and written to the file
 * as well.
 */
int write_config_to_file(uint8_t *in, char *file_name, uint32_t size,
	int binary);
/*
 * Given a blob of XML+binary config *in, calculate the checksums and compare
 * it to what's in the XML. Also compare the size reported from the actual
 * size.
 */
int verify_xml_config(uint8_t *in, uint32_t size);
/*
 * After doing a write_config_to_remote(), this should be called to verify
 * that config. The data will be compared to what's in *in.
 */
int verify_remote_config(uint8_t *in, uint32_t size, lh_callback cb,
	void *cb_arg);
/*
 * Flash can be changed to 0, but not back to 1, so you must erase the
 * flash (to 1) in order to write the flash.
 */
int erase_config(uint32_t size, lh_callback cb, void *cb_arg);

/*
 * SAFEMODE FIRMWARE INTERACTIONS
 */
/*
 * Make the safemode area of the flash all 1's so you can write
 * to it.
 */
int erase_safemode(lh_callback cb, void *cb_arg);
/*
 * Same as read_config_from_remote(), but reading the safemode firmware
 * instead.
 *
 * NOTE: The pointer *out should not point to anything useful. We will
 * allocate a char array and point your pointer at it. Use delete[] to
 * reclaim this memory.
 */
int read_safemode_from_remote(uint8_t **out, lh_callback cb,
	void *cb_arg);
/*
 * NOTE: You CAN NOT WRITE SAFEMODE FIRMWARE OVER USB!
 */

/*
 * Write aforementioned safemode data to a file. Note that this is always
 * written as pure binary.
 */
int write_safemode_to_file(uint8_t *in, char *file_name);
/*
 * Read safemode firmware from file_name into out.
 */
int read_safemode_from_file(char *file_name, uint8_t **out);

/*
 * FIRMWARE INTERACTIONS
 */
/*
 * We don't yet support live firmware upgrades on all remotes,
 * this will return 0 for yes and LH_ERROR_UNSUPP otherwise.
 */
int is_fw_update_supported();
/*
 * Preps the remote for a firmware upgrade
 */
int prep_firmware();
/*
 * Tells the remote the firmware upgrade was successful and that it should
 * copy the firmware from the "staging" area to the live area on next reboot.
 * Don't forget to reboot.
 */
int finish_firmware();
/*
 * Make the firmware area of the flash all 1's so you can write
 * to it.
 */
int erase_firmware(int direct, lh_callback cb, void *cb_arg);
/*
 * Same as read_config_from_remote(), but reading the firmware instead.
 *
 * NOTE: The pointer *out should not point to anything useful. We will
 * allocate a char array and point your pointer at it. Use delete[] to
 * reclaim this memory.
 */
int read_firmware_from_remote(uint8_t **out, lh_callback cb,
	void *cb_arg);
int write_firmware_to_remote(uint8_t *in, int direct, lh_callback cb,
	void *cb_arg);
/*
 * Same as write_config_to_remote(), but with the firmware instead. Note
 * that unless binary is specified, the firmware is broken into chunks
 * and written in ASCII-encoded HEX in XML <DATA> blocks, the way
 * the harmonyremote.com website delivers it.
 */
int write_firmware_to_file(uint8_t *in, char *file_name, int binary);
/*
 * Read firmware from file_name into out. NOTE: ONLY supported
 * in BINARY MODE!! Will return an error otherwise.
 */
int read_firmware_from_file(char *file_name, uint8_t **out, int binary);

/*
 * IR-stuff. This stuff hasn't yet been cleaned up, you'll have to
 * dig in yourself.
 */
int learn_ir_commands(char *file_name, int post);

#ifdef __cplusplus
}
#endif

#endif // LIBHARMONY_H
