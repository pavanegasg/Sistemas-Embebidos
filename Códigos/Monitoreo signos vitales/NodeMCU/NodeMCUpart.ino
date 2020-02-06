#define DEBUG_ARRAY(a) {for (int index = 0; index < sizeof(a) / sizeof(a[0]); index++)    {Serial.print(a[index]); Serial.print('\t');} Serial.println();};
#include<SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

SoftwareSerial SUART(D6, D5); //SRX=Dpin-D2; STX-DPin-D1

// Variables para la conexion WiFI
const char* ssid = "EmPetAP";
const char* password = "12345678";
const char* mqtt_server = "10.42.0.29";

WiFiClient espClient;
PubSubClient client(espClient);

//Variables para subir datos al servidor.
long lastMsg = 0;
int msg0;
int msg1;
char msg[50];
char char0[50];
char char1[50];
int value = 0;

//Variables recuperación datos.
int tempC;
int pulso;
String str;
const char separador = ',';
const int dataLong = 2;
int data[dataLong];

//--------------------------------------------

void setup()
{
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("/sensor/temp", "Enviando");
      // ... and resubscribe
      client.subscribe("/test/test2");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop()
{

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
    
  byte n = SUART.available(); //n != 0 means a character has arrived
  if (n != 0)
  {
   if (SUART.available())
   {
      str = SUART.readStringUntil('\n');
      for (int i = 0; i < dataLong ; i++)
      {
         int index = str.indexOf(separador);
         data[i] = str.substring(0, index).toInt();
         str = str.substring(index + 1);
      }
      DEBUG_ARRAY(data);
  }
  }
  msg0=data[0];
  msg1=data[1];
  
  //msg0.toCharArray(char0, 50)
  //msg1.toCharArray(char1,50)
  if (now - lastMsg > 1000) {
    lastMsg = now;
    //++value;
    itoa(msg0, char0, 10);
    itoa(msg0, char0, 10);
    Serial.print("Publish message: ");
    Serial.print(msg0);
    Serial.print("      ");
    Serial.print(msg1);
    client.publish("/sensor/temp", char0);
    client.publish("/sensor/pulso", char1);
  }


}
