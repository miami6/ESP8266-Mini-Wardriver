#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <ESP8266WiFi.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <TimeLib.h>   

#define UTC_offset -7  // PDT
#define SD_CS      D8

String logFileName = "";
int networks = 0;

#define LOG_RATE 500
char currentTime[5];

SoftwareSerial ss(D4, D3); // RX, TX
TinyGPSPlus tinyGPS;

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  WiFi.mode(WIFI_STA); WiFi.disconnect();
  Serial.println("* ESP8266 WarDriver *\n");

  /* initialize SD card */
  Serial.print("SD Card: ");
  if (!SD.begin(SD_CS)) {
    Serial.println("not found");
    while (!SD.begin(SD_CS));
  }
  Serial.println("found");
  initializeSD();

  /* initialize GPS */
  delay(500);
  Serial.println();
  if (ss.available() > 0) {
    Serial.println("GPS: found");
    Serial.println("Waiting on fix...");
  }
  else {
    Serial.println("GPS: not found");
    Serial.println("Check wiring & reset.");
  }
  while (!tinyGPS.location.isValid()) {
    delay(0);
    smartDelay(500);
  }
  Serial.println("(" + String(tinyGPS.location.lat(), 5) + "," + String(tinyGPS.location.lng(), 5) + ")");
}

void lookForNetworks() {
  int n = WiFi.scanNetworks();
  if (n == 0) {
    Serial.println("No networks found");
  }
  else {
    for (int i = 0; i < n; ++i) {
      if ((WiFi.channel(i) > 0) && (WiFi.channel(i) < 15)) {
        networks++;
        File logFile = SD.open(logFileName, FILE_WRITE);
        logFile.print(WiFi.BSSIDstr(i));
        logFile.print(',');
        logFile.print(WiFi.SSID(i));
        logFile.print(',');

        Serial.print("SSID: ");
        if (WiFi.SSID(i).length() > 20) {
          Serial.println(WiFi.SSID(i).substring(0, 18) + "...");
        }
        else {
          Serial.println(WiFi.SSID(i));
        }

        String bssid = WiFi.BSSIDstr(i);
        bssid.replace(":", "");
        Serial.println(bssid + "    (" + WiFi.RSSI(i) + ")");

        logFile.print(getEncryption(i, ""));
        logFile.print(',');

        Serial.print("Enc: " + getEncryption(i, "screen"));
        Serial.println("   Ch: " + String(WiFi.channel(i)));

        logFile.print(WiFi.channel(i));
        logFile.print(',');

        logFile.print(WiFi.RSSI(i));
        logFile.print(',');

        logFile.print(tinyGPS.location.lat(), 6);
        logFile.print(',');

        logFile.print(tinyGPS.location.lng(), 6);
        logFile.print(',');

        logFile.print(tinyGPS.altitude.meters(), 1);
        logFile.print(',');

        logFile.print(tinyGPS.hdop.value(), 1);
        logFile.print(',');

        logFile.println("WIFI");
        logFile.close();

        if (getEncryption(i, "") == "[WEP][ESS]") {  // flash if WEP detected
          Serial.println("WEP detected");
          delay(200);
        }
      }
    }
  }
}

void loop() {
  if (tinyGPS.location.isValid()) {
    setTime(tinyGPS.time.hour(), tinyGPS.time.minute(), tinyGPS.time.second(), tinyGPS.date.day(), tinyGPS.date.month(), tinyGPS.date.year());
    adjustTime(UTC_offset * SECS_PER_HOUR);
    lookForNetworks();
  }
  smartDelay(LOG_RATE);
  if (millis() > 5000 && tinyGPS.charsProcessed() < 10)
    Serial.println("No GPS data received: check wiring");
}

static void smartDelay(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (ss.available())
      tinyGPS.encode(ss.read());
  } while (millis() - start < ms);
}

void initializeSD() { // create new CSV file and add WiGLE headers
  int i = 0;
  logFileName = "log0.csv";
  while (SD.exists(logFileName)) {
    i++;
    logFileName = "log" + String(i) + ".csv";
  }
  File logFile = SD.open(logFileName, FILE_WRITE);
  Serial.println("Created: " + logFileName);
  if (logFile) {
    logFile.println("WigleWifi-1.4,appRelease=2.53,model=D1-Mini-Pro,release=0.0.0,device=NetDash,display=SSD1306,board=ESP8266,brand=Wemos");
    logFile.println("MAC,SSID,AuthMode,FirstSeen,Channel,RSSI,CurrentLatitude,CurrentLongitude,AltitudeMeters,AccuracyMeters,Type");
  }
  logFile.close();
}

String getEncryption(uint8_t network, String src) { // return encryption for WiGLE or print
  byte encryption = WiFi.encryptionType(network);
  switch (encryption) {
    case 2:
      if (src == "screen") {
        return "WPA";
      }
      return "[WPA-PSK-CCMP+TKIP][ESS]";
    case 5:
      if (src == "screen") {
        return "WEP";
      }
      return "[WEP][ESS]";
    case 4:
      if (src == "screen") {
        return "WPA2";
      }
      return "[WPA2-PSK-CCMP+TKIP][ESS]";
    case 7:
      if (src == "screen") {
        return "NONE";
      }
      return "[ESS]";
  }
  if (src == "screen") {
    return "AUTO";
  }
  return "[WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][ESS]";
}
