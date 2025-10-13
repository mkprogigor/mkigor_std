/**
*	@brief		Mini Std Library for Arduino.
*	@author		Igor Mkprog, mkprogigor@gmail.com
*	@version	V1.0	@date	30.06.2025
*
*	@remarks	Glossary, abbreviations used in the module. Name has small or capital letters ("camelCase"),
*	and consist only 2 or 1 symbol '_', that divede it in => prefix + name + suffix.
*	prefix: 
*		gv_*	- Global Variable;
*		lv_*	- Local Variable (live inside statement);
*		cl_*	- CLass;
*		cd_*	- Class Definition;
*		cgv_*	- Class public (Global) member (Variable);
*		clv_*	- Class private (Local) member (Variable);
*		cgf_*	- Class public (Global) metod (Function), not need, no usefull, becouse we see parenthesis => ();
*		clf_*	- Class private (Local) metod (Function);
*		lp_*	- in function, local parameter.
*	suffix:
*		*_stru	- [like *_t] as usual, point to the type.
	example:	- prefix_nameOfFuncOrVar_suffix, gv_tphg_stru => global var (tphg) structure.
*/

#ifndef mkigor_std_h
#define mkigor_std_h

#include <Arduino.h>
#include <WiFi.h>

/// This is file "mydef.h" with personal defines
#include "/home/igor/Documents/mydef.h"
/// for WiFi connection, put your SSID and PASS
static const char ssid[] = WIFI_SSID;
static const char pass[] = WIFI_PASS;
/// ThingSpeak channel settings, put your chanel number & API keys from https://thingspeak.com
static const unsigned long my_channel_num = 2994389;
static const char write_api_key[] = MYTS_WR_APIKEY;
static const char read_api_key[]  = MYTS_RD_APIKEY;

uint8_t mkistdf_decToBcd(uint8_t val);		/// Convert normal decimal numbers to binary coded decimal
uint8_t mkistdf_bcdToDec(uint8_t val);		/// Convert binary coded decimal to normal decimal numbers
float   mkistdf_Pa2mmHg(float pressure);	/// convert Pa to mmHg
char    mkistdf_byte2char(uint8_t lv_byte1);	/// translate right 4 LSB to symbol 0..F  ex. 0xBA => 'A'
void    mkistdf_prnByte(uint8_t lv_byte);	/// print byte like "FCh "
bool    mkistdf_wifiCon();					/// check or connect to WiFi AP with SSID and PASS from file "mydef.h"
void    mkistdf_wifiScan();					/// Display info of available wifi AP 
void    mkistdf_wifiStatus();				/// display info about connection 
void    mkistdf_cpuInfo();					/// print info about ESP CPU & memory 

#endif