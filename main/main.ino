#include <Preferences.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#include "config.h"
#include "lcd_print.h"
#include "wifi_connect.h"
#include "bleserver.h"
#include "blynk.h"


/*
Imported variables through config header file. Variables are ;

#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""

const char auth[] = ""; // Blynk authentication token

//GPIO pin numbers.
const uint8_t Bluetooth_Button = 22; 
const int inverter_pin = 23;
uint8_t battery_percentage = 0;
double power_consumption = 0;

bool updatingCredentials = false;

//Preferences configuration for storing in non-volatile flash storage
constexpr char DEVICE_NAME[] = ""; // Bluetooth device name
constexpr char PREF_NAMESPACE[] = ""; // Namespace for preferences library
constexpr size_t MAX_CREDENTIAL_LENGTH = ;  // Maximum characters for BLE characteristics read from the app


// UUIDs
constexpr char SERVICE_UUID[] = ""; // UUIDs can be anything you want as far as they match on the mobile application
constexpr char SSID_UUID[] = "";
constexpr char PASSPHRASE_UUID[] = "";
*/



void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }

  lcd.init();
  lcd.backlight();
  lcd_print_offline("An_D Ifidon", "Monitoring System");
  delay(1000);
  lcd.clear();

  pinMode(inverter_pin, OUTPUT);
  pinMode(current_sensor, INPUT);
  pinMode(Bluetooth_Button, INPUT);
  setuphandling();
  getWiFiCredentials(); // Pull Wi-Fi Credentials from non-volatile Flash Storage

  wifiConnect(g_ssid, g_password); // Connect to Wi-Fi network gotten from the non-volatile Flash

  if (digitalRead(Bluetooth_Button) == HIGH){ // If configuration-mode button is 
    Credentials_Change(); // Change Wi-Fi credentials using BLE and Preferences library
    esp_restart(); // restart needed to save credentials in the flash storage.
  }

  Blynk.config(auth, "blynk.cloud", 80);
  Blynk.connect();
  timer.setInterval(3000L, Status_Updater);
}


void loop() {
  if (digitalRead(Bluetooth_Button) == HIGH || updatingCredentials == true){ // If configuration-mode button is 
    Credentials_Change(); // Change Wi-Fi credentials using BLE and Preferences library
    esp_restart(); // restart needed to save credentials in the flash storage.
  }
  Blynk.run();
  timer.run();
  delay(300);
}