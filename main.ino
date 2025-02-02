#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

// #define FIREBASE_AUTH ""
// #define FIREBASE_HOST ""

#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h>
#include <WiFiClient.h>
// #include <Firebase_ESP_Client.h>
// #include <NTPClient.h>
// #include <WiFiUdp.h>

// FirebaseData firebaseData;  // Firebase instance
// FirebaseAuth auth;
// FirebaseConfig config;

char blynk_auth[] = BLYNK_AUTH_TOKEN;

const char* ssid = "Note9S";     // Hotspot name (SSID)
const char* pass = "123456700";  // Hotspot password

int counter;

int DRY_1;
int DRY_2;

const int DRY_SEN_PIN_1 = 35;
const int PUMP_PIN_1 = 32;

const int DRY_SEN_PIN_2 = 34;
const int PUMP_PIN_2 = 33;

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);

// String getTimestamp() {
//   timeClient.update();
//   unsigned long epochTime = timeClient.getEpochTime();

//   struct tm* timeinfo;
//   time_t now = epochTime;
//   timeinfo = localtime(&now);

//   char buffer[20];
//   sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
//           timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
//           timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

//   return String(buffer);
// }

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  pinMode(PUMP_PIN_1, OUTPUT);
  pinMode(DRY_SEN_PIN_1, INPUT);

  pinMode(PUMP_PIN_2, OUTPUT);
  pinMode(DRY_SEN_PIN_2, INPUT);

  Blynk.begin(blynk_auth, ssid, pass, "blynk.cloud", 80);
  // String timestamp = getTimestamp();
  // Serial.println("first timestamp");
  // Serial.println(timestamp);

  // Initialize NTP
  // timeClient.begin();
  // Serial.println("2nd timestamp");
  // Serial.println(timestamp);
  // timeClient.update();
  // Serial.println("3rd timestamp");
  // Serial.println(timestamp);

  // firebase setup
  // config.host = FIREBASE_HOST;
  // config.signer.tokens.legacy_token = FIREBASE_AUTH;
  // Firebase.begin(&config, &auth);
  // Firebase.reconnectWiFi(true);

  delay(2000);

  // if (Firebase.RTDB.setString(&firebaseData, "/Example/myString", "Hello World!")) {
  //   Serial.println("Push successful");
  // } else {
  //   Serial.println("Firebase push failed: " + firebaseData.errorReason());
  // }
}
void loop() {
  Blynk.run();

  DRY_1 = analogRead(DRY_SEN_PIN_1);
  // Serial.println("DRY_1");
  // Serial.println(DRY_1);

  DRY_2 = analogRead(DRY_SEN_PIN_2);
  // Serial.println("DRY_2");
  // Serial.println(DRY_2);

  // Pump 1
  if (DRY_1 >= 2350) {
    digitalWrite(PUMP_PIN_1, LOW);
    // Serial.println("Pump 1 Started, Water Flowing");
    Blynk.virtualWrite(V1, 1);
    Blynk.virtualWrite(V2, DRY_1);
    delay(400);
  } else if (DRY_1 <= 1100) {
    digitalWrite(PUMP_PIN_1, HIGH);
    // Serial.println("Pump 1 Stopped, Water Not Flowing");
    Blynk.virtualWrite(V1, 0);
    Blynk.virtualWrite(V2, DRY_1);
    delay(400);
  }

  // pump 2
  if (DRY_2 >= 2350) {
    digitalWrite(PUMP_PIN_2, LOW);
    // Serial.println("Pump 2 Started, Water Flowing");
    Blynk.virtualWrite(V3, 1);
    Blynk.virtualWrite(V4, DRY_2);
    delay(400);
  } else if (DRY_2 <= 1100) {
    digitalWrite(PUMP_PIN_2, HIGH);
    // Serial.println("Pump 2 Stopped, Water Not Flowing");
    Blynk.virtualWrite(V3, 0);
    Blynk.virtualWrite(V4, DRY_2);
    delay(400);
  }

  // Blynk.virtualWrite(V0, counter);
  counter++;
  if (counter > 100) {
    counter = 0;
  }

  delay(100);
}