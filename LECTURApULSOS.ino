/********************************************************************
*     ENCODER JGY370          ESP32-38PINES                         *
*   M1 Motor-         ->    GND                                     *
*   GND               ->    GND                                     *
*   Encoder A phase   ->    Pin digital 1 GIOP1 TX0                 *
*   Encoder B phase   ->    Pin digital 3 GIOP3 RX0                 *
*   3V3 Encoder+      ->    3.3V                                    *
*   M1 motor+         ->    Conexión alimentación adecuada          *
********************************************************************/


// Librerías necesarias
#include <Arduino.h>

// Definiciones de pines
#define ENCODER_PIN_A 1
#define ENCODER_PIN_B 3

// Variables globales
volatile long pulses = 0;
float distance = 0;
const float TARGET_DISTANCE = 10.0;  // Distancia objetivo en centímetros
const float DISTANCE_PER_PULSE = 0.00203913;

void setup() {
  // Inicialización de pines
  pinMode(ENCODER_PIN_A, INPUT_PULLUP);
  pinMode(ENCODER_PIN_B, INPUT_PULLUP);

  // Attach interrupt to both A and B encoder pins
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_A), updatePulses, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_B), updatePulses, CHANGE);

  // Inicialización de puerto serie para la comunicación
  Serial.begin(9600);
}

void loop() {
  // Calcular la distancia recorrida
  distance = pulses * DISTANCE_PER_PULSE;

  // Mostrar resultados por puerto serie
  Serial.print("Pulsos: ");
  Serial.print(pulses);
  Serial.print(" - Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Comprobar si se ha alcanzado la distancia objetivo
  if (distance >= TARGET_DISTANCE) {
    Serial.println("¡Se ha alcanzado la distancia objetivo!");
    // Detener el motor u otra acción
    // Aquí puedes agregar la lógica para detener el motor o cualquier otra acción
    // Por ejemplo:
    // detenerMotor();
    // break; // Si deseas salir del bucle
  }

  delay(500);  // Espera para no saturar el puerto serie
}

// Función de interrupción para contar pulsos del encoder
void updatePulses() {
  if (digitalRead(ENCODER_PIN_A) == digitalRead(ENCODER_PIN_B)) {
    pulses++;
  } else {
    pulses--;
  }
}
