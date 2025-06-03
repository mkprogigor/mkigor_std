/************************************************************************************
Mini Std Library
by Igor Mkprog, mkprogigor@gmail.com

V1.0 from 01.06.2025
************************************************************************************/
#include "mkigor_std.h"

uint8_t gf_decToBcd(uint8_t val)  {   // Convert normal decimal numbers to binary coded decimal
  return(((val/10) << 4) | (val%10)); 
}

uint8_t gf_bcdToDec(uint8_t val)  {   // Convert binary coded decimal to normal decimal numbers
  return((val/16*10) + (val%16));
}

char gf_byte2char(uint8_t lv_byte1) { // translate right 4 LSB to symbol 0..F  ex. 0xBA => 'A'
  lv_byte1 = lv_byte1 & 0x0F;
  if (lv_byte1 > 9) lv_byte1 = lv_byte1 + 55;
  else              lv_byte1 = lv_byte1 + 48;
  return lv_byte1;
}

void gf_prn_byte(uint8_t lv_byte) {   // print byte like "FCh "
  Serial.print(gf_byte2char(lv_byte>>4));
  Serial.print(gf_byte2char(lv_byte));
  Serial.print("h ");
}


void gf_wifi_scan() {     // Display info of available wifi AP 
  Serial.println("Scan WiFi networks =>");
  u8_t n = WiFi.scanNetworks();
  if (n > 0) {
    for (u8_t i = 0; i < n; ++i) {  // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": SSID=");
      Serial.print(WiFi.SSID(i));
      Serial.print(",\tRSSI=(");
      Serial.print(WiFi.RSSI(i));
      Serial.print("),\tEncr.= " );
      Serial.println(WiFi.encryptionType(i));
    }
  }
  else {
    Serial.println("No networks found.");
  }
}

void gf_wifi_status() {   // display info about connection 
  Serial.println("===================== WiFi Status Info =====================");
  byte tv_wifist = WiFi.status();
  Serial.print(tv_wifist); Serial.print(" - ");
  switch (tv_wifist)  {
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
  if (tv_wifist == 3)  {
    Serial.print("IP "); Serial.print(WiFi.localIP());
    Serial.print(", MASK "); Serial.print(WiFi.subnetMask());
    Serial.print(", GATE "); Serial.print(WiFi.gatewayIP());
    Serial.print(", DNS  "); Serial.print(WiFi.dnsIP());
    Serial.print(", MAC: ");
    uint8_t mac[6];
    WiFi.macAddress(mac);
    for (uint8_t i = 6; i > 0; i--) {
      Serial.print(mac[i-1],HEX); Serial.print(":");
    }
    Serial.println();
    gf_wifi_scan();
    Serial.println("=================== End WiFi Status Info ===================");
  }
}

void gf_prm_cpu_info() {  // print info about ESP CPU & memory 
  Serial.println("=====================  Start MCU Info  =====================");
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  Serial.print("Chip Model      = "); Serial.println( chip_info.model);
  Serial.print("Cores           = "); Serial.println( chip_info.cores);
  Serial.print("Revision number = "); Serial.println( chip_info.revision);
  Serial.print("Full rev.number = "); Serial.println( chip_info.full_revision);
  Serial.print("Features, BIN   = "); Serial.println( chip_info.features, BIN);
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
  Serial.println("=====================   End MCU Info   =====================\n");
}

float gf_Pa2mmHg(float pressure) {  // convert Pa to mmHg
	return (float)(pressure * 0.00750061683f);
}

