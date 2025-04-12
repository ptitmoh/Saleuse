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

uint8_t val_pour_test = 0;
bool augmente = true; // true = augmente, false = diminue

void loop() {
  static unsigned long previousMillis = 0; // Stocke le temps précédent
  const unsigned long interval = 100;     // Intervalle en millisecondes

  unsigned long currentMillis = millis(); // Temps actuel

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Met à jour le temps précédent

    // Gestion de l'évolution de la vitesse
    if (augmente) {
      val_pour_test++;
      if (val_pour_test >= 15) {
        augmente = false;
      }
    } else {
      val_pour_test--;
      if (val_pour_test <= 0) {
        augmente = true;
      }
    }

    // Mise à jour des moteurs
    setMoteur1(1);
    setMoteur2(val_pour_test);
    setMoteur3(val_pour_test);
    setMoteur4(val_pour_test);
    setMoteur5(val_pour_test);
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