/**
*	@brief		Mini Std Library for Arduino.
*	@author		Igor Mkprog, mkprogigor@gmail.com
*	@version	V1.0	@date	30.06.2025
*
*	@remarks	Glossary, abbreviations used in the module.
*		Name of functions dont use symbol '_', only small or capital letters.
*		Symbol '_' divide name in: prefix_nameOfFunction_suffix (it can be only 2 '_' in name):
*		gv_*	- Global Variable;
*		lv_*	- Local Variable (live inside statement);
*		cl_*	- CLass;
*		cd_*	- Class Definition;
*		cgv_*	- Class public (Global) member (Variable);
*		clv_*	- Class private (Local) member (Variable);
*		cgf_*	- Class public (Global) metod (Function), not need, no usefull, becouse we see parenthesis => ();
*		clf_*	- Class private (Local) metod (Function);
*		lp_		- in function, local parameter
*		*_stru	- [or *_stru_t] suffix, as usual, point the type.
*		example: gv_tphg_stru - global var structure.
*/

#include "mkigor_std.h"

/**	@brief	Convert normal decimal numbers to binary coded decimal.
*	@param	val is decimal value to convert
*	@return	converted value in BCD format	*/
uint8_t mkistdf_decToBcd(uint8_t val) {
	return(((val / 10) << 4) | (val % 10));
}

/**	@brief	Convert binary coded decimal to normal decimal numbers
*	@param	val is BCD value to convert
*	@return	converted value in decimal format	*/
uint8_t mkistdf_bcdToDec(uint8_t val) {
	return((val / 16 * 10) + (val % 16));
}

/**	@brief	Translate right 4 LSB to symbol 0..F  ex. 0xBA => 'A'
*	@param	lv_byte1 is byte to convert
*	@return	code ASCII char symbol	*/
char mkistdf_byte2char(uint8_t lv_byte1) {
	lv_byte1 = lv_byte1 & 0x0F;
	if (lv_byte1 > 9)	lv_byte1 = lv_byte1 + 55;
	else				lv_byte1 = lv_byte1 + 48;
	return lv_byte1;
}

/**	@brief	Print byte like "FCh " by Fn Serial.print()
*	@param	lv_byte is byte to print
*	@return	void	*/
void mkistdf_prnByte(uint8_t lv_byte) {
	Serial.print(mkistdf_byte2char(lv_byte >> 4));
	Serial.print(mkistdf_byte2char(lv_byte));
	Serial.print("h ");
}

/**	@brief	convert pressure Pa to mmHg
*	@param	(float) pressure in Pa
*	@return	(float) pressure in mmHg	*/
float mkistdf_Pa2mmHg(float pressure) {
	return (float)(pressure * 0.00750061683f);
}

/**	@brief	Check connection WiFi, If not - Connect to WiFi with SSID, PASS
*	@return	true if connected, otherwise false	*/
bool mkistdf_wifiCon() {
	if (WiFi.status() == WL_CONNECTED) {
		Serial.print("WiFi conected => ");
		Serial.println(WiFi.localIP());
		return true;
	}
	else {
		WiFi.begin(ssid, pass);
		Serial.print("Connect to WiFi => ");
		for (u8_t i = 0; i < 16; ++i) {
			if (WiFi.status() != WL_CONNECTED) {
				Serial.print("? ");
				delay(1000);
			}
			else {
				Serial.print(", it has done, IP:");
				Serial.println(WiFi.localIP());
				return true;
			}
		}
		Serial.println(", it does NOT connect.");
		return false;
	}
}

/**	@brief	Scan available WiFi AP and print info to Serial Monitor	*/
void mkistdf_wifiScan() {
	Serial.println("==================== Scan WiFi networks ====================");
	u8_t n = WiFi.scanNetworks();
	if (n > 0) {
		for (u8_t i = 0; i < n; ++i) {	/// Print SSID and RSSI for each network found
			Serial.print(i + 1);
			Serial.print(": SSID=");
			Serial.print(WiFi.SSID(i));
			Serial.print(",\tRSSI=(");
			Serial.print(WiFi.RSSI(i));
			Serial.print("),\tEncr.= ");
			Serial.println(WiFi.encryptionType(i));
		}
	}
	else {
		Serial.println("No networks found.");
	}
	Serial.println("================== End Scan WiFi networks ==================");
}

/**	@brief	Print info about WiFi connection status	*/
void mkistdf_wifiStatus() {
	Serial.print("WiFi Status: ");
	byte tv_wifist = WiFi.status();
	Serial.print(tv_wifist); Serial.print("-");
	switch (tv_wifist) {
	case WL_CONNECTED:
		Serial.println("WL_CONNECTED");
		break;
	case WL_NO_SHIELD:
		Serial.println("WL_NO_SHIELD");
		break;
	case WL_IDLE_STATUS:
		Serial.println("WL_IDLE_STATUS");
		break;
	case WL_CONNECT_FAILED:
		Serial.println("WL_CONNECT_FAILED");
		break;
	case WL_NO_SSID_AVAIL:
		Serial.println("WL_NO_SSID_AVAIL");
		break;
	case WL_SCAN_COMPLETED:
		Serial.println("WL_SCAN_COMPLETED");
		break;
	case WL_CONNECTION_LOST:
		Serial.println("WL_CONNECTION_LOST");
		break;
	case WL_DISCONNECTED:
		Serial.println("WL_DISCONNECTED");
		break;
	default:
		Serial.println("undefine.");
		break;
	}
	if (tv_wifist == 3) {
		Serial.print("IP "); Serial.print(WiFi.localIP());
		Serial.print(", MASK "); Serial.print(WiFi.subnetMask());
		Serial.print(", GATE "); Serial.print(WiFi.gatewayIP());
		Serial.print(", DNS "); Serial.print(WiFi.dnsIP());
		Serial.print(", MAC ");
		uint8_t _lv_mac[6];
		WiFi.macAddress(_lv_mac);
		for (uint8_t i = 6; i > 0; i--) {
			Serial.print(_lv_mac[i - 1], HEX); Serial.print(":");
		}
		Serial.println();
	}
}

/**	@brief	Print some status and config info about ESP CPU & memory	*/
void mkistdf_cpuInfo() {
	Serial.println("=====================  Start MCU Info  =====================");
	esp_chip_info_t chip_info;
	esp_chip_info(&chip_info);
	Serial.print("Chip Model      = "); Serial.println(chip_info.model);
	Serial.print("Cores           = "); Serial.println(chip_info.cores);
	Serial.print("Revision number = "); Serial.println(chip_info.revision);
	Serial.print("Full rev.number = "); Serial.println(chip_info.full_revision);
	Serial.print("Features, BIN   = "); Serial.println(chip_info.features, BIN);
	Serial.print("CPU Freq, MHz   = ");   Serial.println(getCpuFrequencyMhz());
	Serial.print("XTAL Freq,  MHz = ");   Serial.println(getXtalFrequencyMhz());
	Serial.print("APB Freq, Hz    = ");   Serial.println(getApbFrequency());
	Serial.print("esp_get_idf_version()              = ");  Serial.println(esp_get_idf_version());
	Serial.print("esp_get_free_heap_size()           = ");  Serial.println(esp_get_free_heap_size());
	Serial.print("heap_caps_get_free_size()          = ");  Serial.println(heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
	Serial.print("heap_caps_get_largest_free_block() = ");  Serial.println(heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
	size_t spiram_size = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
	if (spiram_size) {
		Serial.print("PSRAM Size: "); Serial.println(spiram_size);
	}
	else Serial.println("No PSRAM detected.");
	Serial.println("=====================   End MCU Info   =====================");
}