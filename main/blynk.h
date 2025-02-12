#ifdef BLYNK_TEMPLATE_ID

#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

void check_current(){
  analogValue = analogRead(current_sensor) - 512;
  current_value = analogValue*Amp_per_analog;
  current_value += 37.92;
  Serial.print("Current_value : ");
  Serial.println(current_value);
}

void Status_Updater(){
  delay(2000);
  battery_percentage++;
  if(battery_percentage > 100){
    Serial.println("Battery percentage exceeds 100!");
    battery_percentage = 0;
    return;
  }

  check_current();
  lcdclear();
  lcd_print_online(g_ssid, battery_percentage, current_value);
  Blynk.virtualWrite(V3, current_value);
  Blynk.virtualWrite(V1, battery_percentage);
  Blynk.virtualWrite(V2, "Online");
}

BLYNK_WRITE(V0)
{
  if(param.asInt() == 1)
  {
    digitalWrite(inverter_pin, HIGH);
    Serial.println("Turning on Solar Inverter");
    lcdclear();
    lcd_print_offline("Turning on ", "Solar Inverter");
  } else if (param.asInt() == 0 ){
    digitalWrite(inverter_pin, LOW);
    Serial.println("Turning off Solar Inverter");
    lcdclear();
    lcd_print_offline("Turning off ", "Solar Inverter");
  } else {
    Serial.println("V0 is buggy");
  }
}

#endif