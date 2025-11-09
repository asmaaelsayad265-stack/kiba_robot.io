#include "DHT.h"
#include <WiFi.h>

// معلومات شبكة الواي فاي
const char* ssid = "2030";     // غير هذه لاسم شبكتك
const char* password = "ENG12345***"; // غير هذه لكلمة مرور شبكتك

// تعريفات مستشعر DHT11
#define DPIN 4         // دبوس البيانات المتصل بالـ ESP32 (GPIO 4)
#define DTYPE DHT11     // نوع المستشعر
DHT dht(DPIN, DTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // 1. الاتصال بشبكة الواي فاي
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // الانتظار حتى يتم الاتصال
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // 2. طباعة حالة الاتصال وعنوان IP
  Serial.println("");
  Serial.println("WiFi connected successfully!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("-------------------------");
}

void loop() {
  // تأخير بين القراءات (2 ثانية)
  delay(2000);

  // قراءة البيانات
  float tc = dht.readTemperature(false);  // قراءة درجة الحرارة في C
  float hu = dht.readHumidity();          // قراءة الرطوبة

  // التحقق من صلاحية القراءات
  if (isnan(tc) || isnan(hu)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // طباعة القراءات
  Serial.print("Temp: ");
  Serial.print(tc);
  Serial.print(" C, Hum: ");
  Serial.print(hu);
  Serial.println("%");
}