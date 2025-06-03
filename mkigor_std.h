/************************************************************************************
Mini Std Library
by Igor Mkprog, mkprogigor@gmail.com

V1.0 from 01.06.2025
************************************************************************************/
#ifndef mkigor_std_h
#define mkigor_std_h

#include <Arduino.h>
#include <WiFi.h>
#include "/home/igor/Documents/mydef.h"
static const char ssid[] = WIFI_SSID;
static const char pass[] = WIFI_PASS;
static const unsigned long my_channel_num = 1059748;
static const char write_api_key[] = MYTS_WR_APIKEY;
static const char read_api_key[]  = MYTS_RD_APIKEY;

uint8_t gf_decToBcd(uint8_t val);     // Convert normal decimal numbers to binary coded decimal
uint8_t gf_bcdToDec(uint8_t val);     // Convert binary coded decimal to normal decimal numbers
char gf_byte2char(uint8_t lv_byte1);  // translate right 4 LSB to symbol 0..F  ex. 0xBA => 'A'
void gf_prn_byte(uint8_t lv_byte);    // print byte like "FCh "
void gf_wifi_scan();                  // Display info of available wifi AP 
void gf_wifi_status();                // display info about connection 
void gf_prm_cpu_info();               // print info about ESP CPU & memory 
float gf_Pa2mmHg(float pressure);     // convert Pa to mmHg
bool gf_wifi_con();

#endif
