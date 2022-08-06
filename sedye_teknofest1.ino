#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <virtuabotixRTC.h>


#define relay1      0
#define relay2      1
#define relay3      2
#define relay4      3
#define relay5      4



#define rtcVCC      A5
#define rtcGND      A4
#define rtcSCLK     A3
#define rtcIO       A2
#define rtcCE       A1


virtuabotixRTC myRTC(rtcSCLK, rtcIO, rtcCE);

// keypad definitions
#define btnRIGHT    0
#define btnUP       1
#define btnDOWN     2
#define btnLEFT     3
#define btnSELECT   4
#define btnNONE     5


#define modeSETUP   1
#define modeNORMAL  2

int mode = 1;


#define adr1ON    2
#define adr1OF    4
#define adr2ON    6
#define adr2OF    8
#define adr3ON    10
#define adr3OF    12
#define adr4ON    14
#define adr4OF    16
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!#define adr5ON    18
#define adr5OF    20
#define adr6ON    22
#define adr6OF    24
#define adr7ON    26
#define adr7OF    28
#define adr8ON    30
#define adr8OF    32!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

int eepromMin = 0;
int eepromHour = 0;

int eepromHourON = 0;
int eepromHourOF = 0;
int eepromMinON = 0;
int eepromMinOF = 0;



LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;




void relayAction(int adrON, int adrOF, int pos, int pin) {
  myRTC.updateTime();
  int MinToday = (myRTC.hours * 60) + myRTC.minutes;
  int MinEprON = (EEPROM.read(adrON) * 60) + EEPROM.read(adrON + 1);
  int MinEprOF = (EEPROM.read(adrOF) * 60) + EEPROM.read(adrOF + 1);

  lcd.setCursor(pos, 1);
  if (MinEprON == MinEprOF) {  
    lcd.print(" ");
    digitalWrite(pin, LOW);
  }
  else if (MinEprON < MinEprOF) {
    if ((MinEprON <= MinToday) && (MinEprOF > MinToday)) {
      lcd.print("+");
      digitalWrite(pin, LOW);
    }
    else {
      lcd.print("-");
      digitalWrite(pin, HIGH);
    }
  }
  else if (MinEprON > MinEprOF) {  
    if ((MinEprON >= MinToday) || (MinEprOF < MinToday)) {
      lcd.print("+");
      digitalWrite(pin, LOW);
    }
    else {
      lcd.print("-");
      digitalWrite(pin, HIGH);
    }
  }
}



void setRTC() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SAATi AYARLA");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SUAN DA ");
  setup ;
  ShowValue(myRTC.hours, myRTC.minutes, 0);

  lcd.setCursor(0, 1);
  lcd.print("YENi ");

  myRTC.updateTime();
  setup (ShowValue(myRTC.hours, myRTC.minutes, 1));
  while (read_LCD_buttons() == btnNONE);
  setup ChooseValueSetRTC(myRTC.hours, myRTC.minutes, 1);
  lcd.setCursor(0,0);
  lcd.print("AYARLAR KAYDEDiLDi   ");
  delay(1000);
  lcd.clear();
}

void setPin() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARM AYARI");
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARM 1 AC");
  eepromHour = EEPROM.read(adr1ON);
  eepromMin = EEPROM.read(adr1ON + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setup;
  ShowValue(eepromHour, eepromMin, 0);
  while (read_LCD_buttons() == btnNONE);
  setup ChooseValue(eepromHour, eepromMin, adr1ON, 0);

  lcd.setCursor(0, 1);
  lcd.print("ALARM 1 KAPAT");
  eepromHour = EEPROM.read(adr1OF);
  eepromMin = EEPROM.read(adr1OF + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setup ;
  ShowValue(eepromHour, eepromMin, 1);
  while (read_LCD_buttons() == btnNONE);
  setup ChooseValue(eepromHour, eepromMin, adr1OF, 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARM 2 AC");
  eepromHour = EEPROM.read(adr2ON);
  eepromMin = EEPROM.read(adr2ON + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setup;
  ShowValue(eepromHour, eepromMin, 0);
  while (read_LCD_buttons() == btnNONE);
  setup ChooseValue(eepromHour, eepromMin, adr2ON, 0);

  lcd.setCursor(0, 1);
  lcd.print("ALARM 2 KAPAT");
  eepromHour = EEPROM.read(adr2OF);
  eepromMin = EEPROM.read(adr2OF + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setup ;
  ShowValue(eepromHour, eepromMin, 1);
  while (read_LCD_buttons() == btnNONE);
  setup ChooseValue(eepromHour, eepromMin, adr2OF, 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARM 3 AC");
  eepromHour = EEPROM.read(adr3ON);
  eepromMin = EEPROM.read(adr3ON + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setup ;
  ShowValue(eepromHour, eepromMin, 0);
  while (read_LCD_buttons() == btnNONE);
  setup ChooseValue(eepromHour, eepromMin, adr3ON, 0);

  lcd.setCursor(0, 1);
  lcd.print("ALARM 3 KAPAT");
  eepromHour = EEPROM.read(adr3OF);
  eepromMin = EEPROM.read(adr3OF + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setup ;
  ShowValue(eepromHour, eepromMin, 1);
  while (read_LCD_buttons() == btnNONE);
  setup ChooseValue(eepromHour, eepromMin, adr3OF, 1);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARM 4 AC");
  eepromHour = EEPROM.read(adr4ON);
  eepromMin = EEPROM.read(adr4ON + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setup ;
  ShowValue(eepromHour, eepromMin, 0);
  while (read_LCD_buttons() == btnNONE);
  setup ChooseValue(eepromHour, eepromMin, adr4ON, 0);

  lcd.setCursor(0, 1);
  lcd.print("ALARM 4 KAPAT");
  eepromHour = EEPROM.read(adr4OF);
  eepromMin = EEPROM.read(adr4OF + 1);
  if (eepromHour >= 24) eepromHour = 0;
  if (eepromMin  >= 60) eepromMin  = 0;
  setup ;
  ShowValue(eepromHour, eepromMin, 1);
  while (read_LCD_buttons() == btnNONE);
  setup ChooseValue(eepromHour, eepromMin, adr4OF, 1);



  lcd.clear();
}

void setup ChooseValue(int HourNew, int MinNew, byte Address, byte Pos);
{
  while (read_LCD_buttons() != btnSELECT) {
    if (read_LCD_buttons() == btnRIGHT) {
      if (HourNew < 23) {
        HourNew++;
      }
    }
    else if (read_LCD_buttons() == btnLEFT) {
      if (HourNew > 0) {
        HourNew--;
      }
    }
    else if (read_LCD_buttons() == btnUP) {
      if (MinNew < 59) {
        MinNew++;
      }
    }
    else if (read_LCD_buttons() == btnDOWN) {
      if (MinNew > 0) {
        MinNew--;
      }
    }
    setup ShowValue(HourNew, MinNew, Pos);
    delay(150);
  }
  while (read_LCD_buttons() != btnNONE);  
  EEPROM.write(Address, HourNew);
  EEPROM.write(Address + 1, MinNew);
  delay(150);
}

void setup ChooseValueSetRTC(int HourNew, int MinNew, byte Pos);
{
  while (read_LCD_buttons() != btnSELECT) {
    if (read_LCD_buttons() == btnRIGHT) {
      if (HourNew < 23) {
        HourNew++;
      }
    }
    else if (read_LCD_buttons() == btnLEFT) {
      if (HourNew > 0) {
        HourNew--;
      }
    }
    else if (read_LCD_buttons() == btnUP) {
      if (MinNew < 59) {
        MinNew++;
      }
    }
    else if (read_LCD_buttons() == btnDOWN) {
      if (MinNew > 0) {
        MinNew--;
      }
    }
    setup ShowValue(HourNew, MinNew, Pos);
    delay(150);
  }
  while (read_LCD_buttons() != btnNONE);  
  myRTC.setDS1302Time(00, MinNew, HourNew, 6, 10, 1, 2014);
  delay(150);
}

void setup ShowValue(int Hour, int Min, int Pos);
{
  lcd.setCursor(11, Pos);
  print2digits(Hour);
  lcd.print(":");
  print2digits(Min);
}


int read_LCD_buttons()
{
  adc_key_in = analogRead(0);    

  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 150)  return btnUP;
  if (adc_key_in < 300)  return btnDOWN;
  if (adc_key_in < 500)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT;  
  return btnNONE;              
}

void eeprom_write_int(int p_address, int p_value) {
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);

  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}

unsigned int eeprom_read_int(int p_address) {
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);

  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}

void displayTime() {
  myRTC.updateTime();
  print2digits(myRTC.hours);
  lcd.print(":");
  print2digits(myRTC.minutes);
  lcd.print(":");
  print2digits(myRTC.seconds);
}

void print2digits(int number) {
  if (number >= 0 && number < 10)
    lcd.print('0');
  lcd.print(number, DEC);
}

void setup() {
 

digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, HIGH);
digitalWrite(relay4, HIGH);
 

  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }

 

  pinMode(rtcVCC,  OUTPUT);
  pinMode(rtcGND,  OUTPUT);
  pinMode(rtcSCLK, OUTPUT);
  pinMode(rtcIO,   OUTPUT);
  pinMode(rtcCE,   OUTPUT);
  digitalWrite(rtcVCC, HIGH);
  digitalWrite(rtcGND, LOW);
 digitalWrite(relay5, HIGH);
  delay(500);
digitalWrite(relay1, HIGH);
digitalWrite(relay2, HIGH);
digitalWrite(relay3, HIGH);
digitalWrite(relay4, HIGH);

 

  lcd.begin(16, 2);
  lcd.setCursor(5, 0);
  lcd.print("SiSTEM");
  lcd.setCursor(2, 1);
  lcd.print("HAZIRLANIYOR");
  delay(5500);
  //digitalWrite(9,LOW);//Buna comment kim atmış aq
    lcd.clear();
}

void loop() {

  lcd.setCursor(4, 0);
 

  displayTime();

 

  lcd.setCursor(2, 1);
  lcd.print("1");
  relayAction(adr1ON, adr1OF, 1, relay1);
  lcd.setCursor(4, 1);
  lcd.print("2");
  relayAction(adr2ON, adr2OF, 3, relay2);
  lcd.setCursor(6, 1);
  lcd.print("3");
  relayAction(adr3ON, adr3OF, 5, relay3);
  lcd.setCursor(8, 1);
  lcd.print("4");
  relayAction(adr4ON, adr4OF, 7, relay4);



  // jika user menekan tombol SELECT, masuk menu setting

  if (read_LCD_buttons() == btnSELECT) {
    while (read_LCD_buttons() == btnSELECT);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SAAT AYARI");
    lcd.setCursor(0, 1);
    lcd.print("ALARM AYARLA");
    while (read_LCD_buttons() == btnNONE);
    if (read_LCD_buttons() == btnUP) {
      while (read_LCD_buttons() == btnUP);
      setRTC();  
    }
    else if (read_LCD_buttons() == btnDOWN) {
      while (read_LCD_buttons() == btnDOWN);
      setPin();  
  }
}
}
