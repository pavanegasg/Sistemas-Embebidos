#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include<SoftwareSerial.h>
SoftwareSerial SUART(5, 6); //SRX=Dpin-2; STX-DPin-3
//-------------------------
float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
int pinLM35 = 0;
//--------------------------------------------
//Variables para hacer uso del sensor de pulso
float pulso;
const int OUTPUT_TYPE = SERIAL_PLOTTER;

const int PULSE_INPUT = A1;
const int PULSE_BLINK = 13;    // Pin 13 is the on-board LED
const int PULSE_FADE = 5;
const int THRESHOLD = 507;   // Adjust this number to avoid noise when idle

PulseSensorPlayground pulseSensor;

void setup()
{
  analogReference(INTERNAL);

  Serial.begin(115200); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port
  
  
  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.blinkOnPulse(PULSE_BLINK);
  pulseSensor.fadeOnPulse(PULSE_FADE);

  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);

  if (!pulseSensor.begin()) {
  }
}



void loop()
{ 
  delay(20);

  pulseSensor.outputSample();
  if (pulseSensor.sawStartOfBeat()) {
  pulseSensor.outputBeat();
  }

  pulso=pulseSensor.getBeatsPerMinute();
  
  tempC = analogRead(pinLM35);
  // Calculamos la temperatura con la fórmula
  tempC = (1.1 * tempC * 100.0) / 1024.0;
  //tempC=random(40);
  //pulso=random(120);

  
  //
  
  Serial.print("Temperatura = "); Serial.print((int)tempC); Serial.print("°C ");
  Serial.print("Pulso = "); Serial.print((int)pulso); Serial.println("ppm");
  
  //----Send Temp and Humidity signal to NodeMCU via SUART port----
  //SUART.print('<');                   //<(start mark)
  SUART.print((int)tempC,DEC);
  SUART.print(',');                   //,(data seperator)
  SUART.print((int)pulso, DEC);
  //SUART.print('>');                   //>(end mark)
  SUART.println();

  delay(1000);
}
