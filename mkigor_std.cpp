/**
 * @brief		Mini Std Library for Arduino.
 * @author		Igor Mkprog, mkprogigor@gmail.com
 * @version	V1.1	@date	24.10.2025
 *
 * @remarks	Glossary, abbreviations used in the module. Name has small or capital letters ("camelCase"),
 *	and consist only 2 or 1 symbol '_', that divide it in => prefix + name + suffix.
 * 	prefix: 
 * 		gv_*	- Global Variable;
 * 		lv_*	- Local Variable (live inside statement);
 * 		cl_*	- CLass;
 * 		cd_*	- Class Definition;
 * 		cgv_*	- Class public (Global) member (Variable);
 * 		clv_*	- Class private (Local) member (Variable);
 * 		clf_*	- Class private (Local) metod (Function);
 * 		lp_*	- in function, local parameter.
 * 	suffix:
 * 		like ending *_t, as usual, point to the type, informative, but not mandatory to use.
 * 		possible is: _i8, _i16, _i32, _i64, _u8, _u16, _u32, _u64, _f, _df, _c, _b, _stru, etc.
 * 		example:	- prefix_nameOfFuncOrVar_suffix, gv_tphg_stru => global var (tphg) structure.
 */


#include "mkigor_std.h"

//===========================================================================================

/**
 * @brief	Convert normal decimal numbers to binary coded decimal.
 * 
 * @param	val is decimal value to convert
 * @return	converted value in BCD format	
 */
uint8_t mkistdf_decToBcd(uint8_t val) {
	return(((val / 10) << 4) | (val % 10));
}

/**
 * @brief	Convert binary coded decimal to normal decimal numbers
 * 
 * @param	val is BCD value to convert
 * @return	converted value in decimal format
 */
uint8_t mkistdf_bcdToDec(uint8_t val) {
	return((val / 16 * 10) + (val % 16));
}

/**	
 * @brief	Translate right 4 LSB to symbol 0..F  ex. 0xBA => 'A'
 * 
 * @param	lv_byte1 is byte to convert
 * @return	code ASCII char symbol
 */
char mkistdf_byte2char(uint8_t lv_byte1) {
	lv_byte1 = lv_byte1 & 0x0F;
	if (lv_byte1 > 9)	lv_byte1 = lv_byte1 + 55;
	else				lv_byte1 = lv_byte1 + 48;
	return lv_byte1;
}

/**	
 * @brief	Print byte like "FCh " by Fn Serial.print()
 * 
 * @param	lv_byte is byte to print
 * @return	void
 */
void mkistdf_prnByte(uint8_t lv_byte) {
	Serial.print(mkistdf_byte2char(lv_byte >> 4));
	Serial.print(mkistdf_byte2char(lv_byte));
	Serial.print("h ");
}

/**
 * @brief	convert pressure Pa to mmHg
 * 
 * @param	(float) pressure in Pa
 * @return	(float) pressure in mmHg
 */
float mkistdf_Pa2mmHg(float pressure) {
	return (float)(pressure * 0.00750061683f);
}

/**
 * @brief	Check connection WiFi,
 * 		if YES -> print IP address and return;
 * 		if NOT -> try ONE time duaring 16 sec to connect to WiFi with SSID, PASS 
 * 
 * @return	true if connected, otherwise false	
 */
bool mkistdf_wifiCon() {
	if (WiFi.status() == WL_CONNECTED) {
		Serial.print("WiFi conected => ");
		Serial.println(WiFi.localIP());
		return true;
	}
	else {
		Serial.print("Connect to WiFi SSID: ");
		Serial.print(ssid);
		Serial.print(" => ");
		WiFi.begin(ssid, pass);
		for (u8_t i = 0; i < 16; ++i) {
			if (WiFi.status() != WL_CONNECTED) {
				Serial.print("? ");
				delay(1000);
			}
			else {
				Serial.print(", it has done, IP: ");
				Serial.println(WiFi.localIP());
				return true;
			}
		}
		Serial.println(", it does NOT connect.");
		return false;
	}
}

/**
 * @brief Scan available WiFi AP and print info to Serial Monitor
 */
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

/**
 * @brief Print info about WiFi connection status
 */
void mkistdf_wifiStatus() {
	Serial.print("\nWiFi Status: ");
	uint8_t lv_wifist = WiFi.status();
	Serial.print(lv_wifist); Serial.print(" = ");
	switch (lv_wifist) {
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
	if (lv_wifist == 3) {
		Serial.print("SSID: ");	Serial.println(WiFi.SSID());
		Serial.print("IP:   ");	Serial.println(WiFi.localIP());
		Serial.print("GATE: ");	Serial.println(WiFi.gatewayIP());
		Serial.print("DNS:  ");	Serial.println(WiFi.dnsIP());
		Serial.print("MASK: ");	Serial.println(WiFi.subnetMask());
		Serial.print("MAC ");
		uint8_t _lv_mac[6];
		WiFi.macAddress(_lv_mac);
		for (uint8_t i = 6; i > 0; i--) {
			Serial.print(_lv_mac[i - 1], HEX); Serial.print(":");
		}
		Serial.println("\n");
	}
}

/**
 * @brief Print some status and config info about ESP CPU & memory
 */
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

/**
 * @brief Find the first occurrence of a null-terminated substring (Char2)
 * inside a null-terminated string (Char1).
 * Searches in `lp_charArr1` for the first occurrence of the pattern `lp_charFind`.
 * The function returns the zero-based index of the first matching position in
 * `lp_charArr1`. If the pattern is not found the function returns 0xFFFF.
 *
 * @param lp_charArr1 Pointer to the null-terminated target string to search in.
 * @param lp_charFind Pointer to the null-terminated pattern string to search for.
 * @return uint16_t Zero-based index of the first match, or 0xFFFF when not found.
 * @remark Both arguments must be classic C strings terminated with '\0'. The
 * function scans at max 2048 bytes or less if find end symbol '\0' early.
 */
uint16_t mkistdf_findC2inC1(char *lp_charArr1, char *lp_charFind) {
	uint16_t lv_sizeArr1 = 0, lv_sizeFind = 0, lv_findPos = 0xFFFF;
	for (uint16_t i = 0; i < 2048; i++)
		if (lp_charArr1[i] == '\0') {
			lv_sizeArr1 = i;
			break;
		}
	for (uint16_t i = 0; i < 2048; i++)
		if (lp_charFind[i] == '\0') {
			lv_sizeFind = i;
			break;
		}
	if (lv_sizeArr1<lv_sizeFind) return lv_findPos;
	
	for (uint16_t i = 0; i < lv_sizeArr1; i++) {
		if (lp_charArr1[i] == lp_charFind[0]) {
			for (uint16_t j = 1; j < lv_sizeFind; j++) {
				if (lp_charArr1[i+j] != lp_charFind[j]) {
					lv_findPos = 0xFFFF;
					break;
				}
				else lv_findPos = i;
			}
			if (lv_findPos == i) break;
		}
	}
/*	#ifdef DEBUG_EN
	printf("Size CharArr1 = %d, size CharFind = %d, Find Pos. = %d\n", lv_sizeArr1, lv_sizeFind, lv_findPos);
	#endif	*/
	return lv_findPos;
}

/**
 * @brief Make GET request to goodle.com find and save GMT date & time to struct var
 * 
 * @param lp_DTout_stru var structure DT_stru_t pass by reference
 * @return uint8_t 0 = error, 1 = Ok.
 */
uint8_t mkistdf_getDateTime(DT_stru_t &lp_DTout_stru) {
	lp_DTout_stru = {0,0,0,0,0,0,0,0};

	if (WiFi.status() != WL_CONNECTED) mkistdf_wifiCon();
	if (WiFi.status() != WL_CONNECTED) {
		Serial.println("No WiFi conection.");
		return 0;
	}

	WiFiClient	wifi_client;
	if (!wifi_client.connect("google.com", 80)) {
		Serial.println("http client NOT connected.");
		return 0;
	}

	unsigned long lv_msDT_u32;
	wifi_client.println("GET /search?q=mkprogigor HTTP/1.0\r\n\r\n");	/// Make a HTTP request:
	lv_msDT_u32 = millis();
	for (uint16_t i = 0; i < 3000; i++) {
		if (wifi_client.available()) {
			lv_msDT_u32 = lv_msDT_u32 + (millis() - lv_msDT_u32) / 2;
#ifdef DEBUG_EN
			printf("\nTime of delay request = %d\n", i);
#endif
			break;
		}
		delay(1);
	}

	uint16_t lv_nBuf = 512;
	char lv_buff[lv_nBuf];
	for (uint16_t i = 0; i < lv_nBuf; i++) {
		if (wifi_client.available()) lv_buff[i] = wifi_client.read();
		else break;
	}
	wifi_client.stop();
	lv_buff[511] = 0;

	char lv_fs1[] = "Date: ";
	uint16_t lv_strPos = mkistdf_findC2inC1(lv_buff, lv_fs1) + 6;
	if (lv_strPos == 0xFFFF) {
		Serial.println("Not found 'Date: ' in http GET request.");
		return 0;
	}
	char lv_fs3[] = "GMT";
	uint16_t lv_finPos = mkistdf_findC2inC1(lv_buff, lv_fs3) - 1;
	uint8_t lv_nDT = lv_finPos - lv_strPos;
	char lv_charDT[lv_nDT];
	for (uint8_t i = 0; i < lv_nDT; i++) lv_charDT[i] = lv_buff[lv_strPos + i];

#ifdef DEBUG_EN
	Serial.print("\n=> Buffer array:\n");
	for (uint16_t j = 0; j < lv_nBuf; j++) Serial.print(lv_buff[j]);
	Serial.print("\n=> end array.\n\n");
	for (uint16_t i = 0; i < lv_nDT; i++) Serial.print(lv_charDT[i]);
	Serial.println();
#endif

	uint8_t lv_Year_b, lv_Month_b, lv_Day_b, lv_DOW_b, lv_Hour_b, lv_Min_b, lv_Sec_b;
	uint16_t lv_pos1;
	char lv_tt[4] = { lv_charDT[0], lv_charDT[1], lv_charDT[2], 0 };
	char lv_fs2[] = "MonTueWedThuFriSatSun";
	lv_pos1 = mkistdf_findC2inC1(lv_fs2, lv_tt);
	lv_DOW_b = uint8_t(lv_pos1) / 3 + 1;
	uint8_t lv_stt;
	if (lv_charDT[6] == ' ') {
		lv_stt = 7;
		lv_Day_b = uint8_t(lv_charDT[5]) - 48;
	}
	else {
		lv_stt = 8;
		lv_Day_b = (uint8_t(lv_charDT[5]) - 48) * 10 + (uint8_t(lv_charDT[6]) - 48);
	}
	char lv_ttM[4] = { lv_charDT[lv_stt], lv_charDT[lv_stt + 1], lv_charDT[lv_stt + 2], 0 };
	char lv_fs4[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
	lv_pos1 = mkistdf_findC2inC1(lv_fs4, lv_ttM);
	lv_Month_b = uint8_t(lv_pos1) / 3 + 1;
	lv_Year_b = (uint8_t(lv_charDT[lv_stt + 6]) - 48) * 10 + uint8_t(lv_charDT[lv_stt + 7]) - 48;
	lv_Hour_b = (uint8_t(lv_charDT[lv_stt + 9]) - 48) * 10 + uint8_t(lv_charDT[lv_stt + 10]) - 48;
	lv_Min_b = (uint8_t(lv_charDT[lv_stt + 12]) - 48) * 10 + uint8_t(lv_charDT[lv_stt + 13]) - 48;
	lv_Sec_b = (uint8_t(lv_charDT[lv_stt + 15]) - 48) * 10 + uint8_t(lv_charDT[lv_stt + 16]) - 48;
#ifdef DEBUG_EN
	printf("\nDate & Time: %d-%d-%d, dow %d, %d:%d:%d, msecTime = %d\n",
		lv_Year_b, lv_Month_b + 1, lv_Day_b, lv_DOW_b + 1, lv_Hour_b, lv_Min_b, lv_Sec_b, lv_msDT_u32);
#endif
	lp_DTout_stru = {lv_Year_b, lv_Month_b, lv_Day_b, lv_DOW_b, lv_Hour_b, lv_Min_b, lv_Sec_b, lv_msDT_u32};
	return 1;
}

/**
 * @brief scan I2C devices from 0-127 address
 * 
 */
void mkistdf_scanI2C() {
	uint8_t lv_error;
	Serial.println("Scanning I2C address =>");
	for (uint8_t i = 1; i < 127; i++) {
		Wire.beginTransmission(i);
		lv_error = Wire.endTransmission(true);
		switch (lv_error) {
		case 0:
			printf("0 = I2C device found at address 0x%X\n", i);	break;
		case 1:
			printf("1 = data too long to fit in transmit buffer, at address 0x%X\n", i);	break;
		case 2:
			printf("2 = received NACK on transmit of address, at address 0x%X\n", i);	break;
		case 3:
			printf("3 = received NACK on transmit of data, at address 0x%X\n", i);	break;
		case 4:
			printf("4 = other error, at address 0x%X\n", i);	break;
		case 5:
			printf("5 = timeout error at address 0x%X\n", i);	break;
		default:
			printf("Unknow error %d at address 0x%X\n", lv_error, i);	break;
		}
		delay(10);
	}
}

/**
 * @brief print to terminal array lp_buf by lenth lp_len
 * 
 * @param lp_buf array to print by reference
 * @param lp_len lenth of array lp_buf
 */
void	mkistdf_prnBuf(uint8_t *lp_buf, uint8_t lp_len) {
	Serial.print("------ 0 - 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9 - A - B - C - D - E - F\n");
	for (uint8_t i = 0; i < lp_len; i++) {
		char c[] = "0x_0: ";
		c[2] = mkistdf_byte2char(i >> 4);
		Serial.print(c);
		for (uint8_t j = 0; j < 16; j++) {
			if (i + j >= lp_len) break;
			mkistdf_prnByte(lp_buf[i + j]);
		}
		i = i + 15;
		Serial.println();
	}
}
//===========================================================================================