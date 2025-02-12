#ifdef BLYNK_TEMPLATE_ID

#include <WiFi.h>


void wifiConnect(String ssid, String password) {
  if (digitalRead(Bluetooth_Button) == HIGH) {
    return;
  };
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    if (digitalRead(Bluetooth_Button) == HIGH) {
      updatingCredentials = true;
      return;
    }
    delay(1000);
    Serial.println("Connecting to ");
    Serial.println(ssid);
    lcdclear();
    lcd_print_offline("Connecting to", ssid);
  }

  Serial.println("Successfully connected to ");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  lcdclear();
  lcd_print_offline("Connected to :", ssid);
  delay(1500);
}

#endif