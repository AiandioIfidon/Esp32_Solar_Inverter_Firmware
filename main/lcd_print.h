#pragma once

void lcd_print_online(String connected_ssid, int battery, double power){
  lcd.setCursor(0, 0);
  lcd.print(connected_ssid);
  lcd.setCursor(9, 0);
  lcd.print(" Online");
  lcd.setCursor(4, 1);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print(battery);
  lcd.setCursor(8, 1);
  lcd.print(power);
  lcd.setCursor(13, 1);
  lcd.print("Amp");
}

void lcd_print_offline(String first_line, String second_line){
  lcd.setCursor(0, 0);
  lcd.print(first_line);
  lcd.setCursor(0, 1);
  lcd.print(second_line);
}

void lcdclear(){
  lcd.clear();
}