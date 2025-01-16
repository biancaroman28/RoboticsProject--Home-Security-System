#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include "ScioSense_ENS160.h"
#include <LiquidCrystal_I2C.h>
#include <UrlEncode.h>
#include <MFRC522.h>

// ENS160 configuration
ScioSense_ENS160 ens160(ENS160_I2CADDR_1); // ENS160 address: 0x53

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address: 0x27

// AHT20 sensor
Adafruit_AHTX0 aht;

// PIR, LED, and Buzzer configuration
#define PIR_PIN 27
#define LED_PIN 26
#define BUZZER_PIN 4

// RFID configuration
#define RST_PIN 17
#define SDA_PIN 5
MFRC522 rfid(SDA_PIN, RST_PIN);

// Button configuration
#define BUTTON_PIN 32

// Wi-Fi credentials
const char* ssid = "Alexandru";
const char* password = "apartamentul13";

// CallMeBot configuration
String phoneNumber = "40770603079";
String apiKey = "1734854";

// Mode states
bool secureMode = true;
unsigned long lastMotionTime = 0;
unsigned long lastMessageTime = 0;
unsigned long lastRFIDScanTime = 0;
unsigned long lastSensorReadTime = 0;
const unsigned long messageCooldown = 60000; // 1 minute
const unsigned long rfidCooldown = 5000;    // 5 seconds
const unsigned long sensorReadInterval = 2000; // 2 seconds for sensor readings

// Debouncing
unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 300; // Debounce delay for button press


int dataIndex = 0;
String dataLabels[] = {"Temp:", "Humidity:", "Gas:"};
float dataValues[3];

// Function to send WhatsApp messages
void sendMessage(String message) {
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.println("WhatsApp message sent successfully!");
  } else {
    Serial.println("Error sending WhatsApp message.");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

// Read sensor data with timing control
void readSensors() {
  sensors_event_t temp, humidity;
  aht.getEvent(&humidity, &temp);
  dataValues[0] = temp.temperature;
  dataValues[1] = humidity.relative_humidity;
  dataValues[2] = analogRead(A0); // Read MQ2 sensor gas level
}

// Initialize hardware
void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  if (!aht.begin()) {
    Serial.println("Failed to initialize AHT sensor!");
    while (1);
  }

  if (!ens160.begin()) {
    Serial.println("Failed to initialize ENS160 sensor!");
    while (1);
  }

  SPI.begin();
  rfid.PCD_Init();
}

// Secure mode logic
void handleSecureMode() {
  if (digitalRead(PIR_PIN) == HIGH) {
    lastMotionTime = millis();
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);

    if (millis() - lastMessageTime > messageCooldown) {
      sendMessage("Motion detected in Secure Mode!");
      lastMessageTime = millis();
    }
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    secureMode = false;
    lastRFIDScanTime = millis();
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    lcd.clear();
    lcd.print("Normal Mode");
    delay(2000);
    lcd.clear();
  }
}

// Normal mode logic
void handleNormalMode() {
  // Check if it's time to read sensors (timed with millis())
  if (millis() - lastSensorReadTime > sensorReadInterval) {
    readSensors();
    lastSensorReadTime = millis();
  }

  lcd.clear(); // Clear the display before showing new data
  lcd.setCursor(0, 0);
  lcd.print(dataLabels[dataIndex]);
  lcd.setCursor(0, 1);
  lcd.print(dataValues[dataIndex]);
  lcd.print(dataIndex == 2 ? " PPM" : "");

  // Button press handling with debounce
  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastButtonPressTime > debounceDelay) {
    lastButtonPressTime = millis();
    dataIndex = (dataIndex + 1) % 3;
  }

  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    if (millis() - lastRFIDScanTime > rfidCooldown) {
      secureMode = true;
      lcd.clear();
      lcd.print("Secure Mode");
      delay(2000);
      lcd.clear();
    }
  }
}

void loop() {
  if (secureMode) {
    handleSecureMode();
  } else {
    handleNormalMode();
  }
}
