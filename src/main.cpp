#include <Arduino.h>

// === Paramètres PWM ===
#define PWM_FREQ      10000
#define PWM_RES       8

// === Pins moteurs ===
#define PIN_M1  25
#define PIN_M2  26
#define PIN_M3  27
#define PIN_M4  14
#define PIN_M5  12

// === Canaux PWM ===
#define CH_M1   0
#define CH_M2   1
#define CH_M3   2
#define CH_M4   3
#define CH_M5   4

// === Bus 4 bits ===
#define PIN_BUS_0 18
#define PIN_BUS_1 5
#define PIN_BUS_2 17
#define PIN_BUS_3 16

// === Fonctions ===
uint8_t getBus4BitsValue();
void setMoteur1(uint8_t val);
void setMoteur2(uint8_t val);
void setMoteur3(uint8_t val);
void setMoteur4(uint8_t val);
void setMoteur5(uint8_t val);

uint8_t getDutyFromValue1(uint8_t val);
uint8_t getDutyFromValue(uint8_t val);

// === Setup ===
void setup() {
  Serial.begin(115200);

  pinMode(PIN_M1, OUTPUT);
  pinMode(PIN_M2, OUTPUT);
  pinMode(PIN_M3, OUTPUT);
  pinMode(PIN_M4, OUTPUT);
  pinMode(PIN_M5, OUTPUT);

  pinMode(PIN_BUS_0, INPUT_PULLDOWN);
  pinMode(PIN_BUS_1, INPUT_PULLDOWN);
  pinMode(PIN_BUS_2, INPUT_PULLDOWN);
  pinMode(PIN_BUS_3, INPUT_PULLDOWN);

  ledcSetup(CH_M1, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_M1, CH_M1);

  ledcSetup(CH_M2, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_M2, CH_M2);

  ledcSetup(CH_M3, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_M3, CH_M3);

  ledcSetup(CH_M4, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_M4, CH_M4);

  ledcSetup(CH_M5, PWM_FREQ, PWM_RES);
  ledcAttachPin(PIN_M5, CH_M5);
}

uint8_t val_precedente = 0;

void loop() {
  // if (Serial.available()) {
  //   uint8_t val = Serial.read() & 0x0F; // Lire sur 4 bits

  //   // Exemple d'appel pour tous les moteurs avec la même valeur :
  //   setMoteur1(val);
  //   setMoteur2(val);
  //   setMoteur3(val);
  //   setMoteur4(val);
  //   setMoteur5(val);
  // }
  uint8_t val = getBus4BitsValue();
  if (val != val_precedente) {
    Serial.print("val = ");
    Serial.println(val);
    val_precedente = val;
    setMoteur1(1);
    setMoteur2(val);
    setMoteur3(val);
    setMoteur4(val);
    setMoteur5(val);
  } 
}

uint8_t getBus4BitsValue() {
  uint8_t val = 0;
  val |= (digitalRead(PIN_BUS_0) << 0);
  val |= (digitalRead(PIN_BUS_1) << 1);
  val |= (digitalRead(PIN_BUS_2) << 2);
  val |= (digitalRead(PIN_BUS_3) << 3);
  // val = 1;
  return val;
}

// === Fonctions pour chaque moteur ===

void setMoteur1(uint8_t val) {
  uint8_t duty = getDutyFromValue1(val);
  ledcWrite(CH_M1, duty);
}

void setMoteur2(uint8_t val) {
  uint8_t duty = getDutyFromValue(val);
  ledcWrite(CH_M2, duty);
}

void setMoteur3(uint8_t val) {
  uint8_t duty = getDutyFromValue(val);
  ledcWrite(CH_M3, duty);
}

void setMoteur4(uint8_t val) {
  uint8_t duty = getDutyFromValue(val);
  ledcWrite(CH_M4, duty);
}

void setMoteur5(uint8_t val) {
  uint8_t duty = getDutyFromValue(val);
  ledcWrite(CH_M5, duty);
}

// === Fonction auxiliaire avec switch-case sur 4 bits ===
uint8_t getDutyFromValue(uint8_t val) {
  uint8_t duty = map(val, 0, 15, 150, 255);
  return duty;
}

uint8_t getDutyFromValue1(uint8_t val) {
  uint8_t duty = map(val, 0, 3, 150, 400);
  return duty;
}