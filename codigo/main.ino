#include <WiFi.h>
#include <PubSubClient.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

#define BOTAO_SOS 15

#define LED_VERDE 18
#define LED_VERMELHO 19

#define BUZZER 5

#define POT_BATERIA 34

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

float latitude = -23.5505;

bool areaSegura = true;

void setup_wifi() {

  delay(10);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
}

void reconnect() {

  while (!client.connected()) {

    Serial.println("Conectando MQTT...");

    String clientId = "PetGuardianESP32-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {

      Serial.println("MQTT conectado");

    } else {

      Serial.print("Falhou. Estado: ");
      Serial.println(client.state());

      delay(2000);
    }
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(BOTAO_SOS, INPUT_PULLUP);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  dht.begin();

  Wire.begin(21, 22);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();

  display.setTextColor(WHITE);

  display.setTextSize(1);

  display.setCursor(0, 10);
  display.println("PETGUARDIAN");

  display.setCursor(0, 30);
  display.println("INICIANDO...");

  display.display();

  setup_wifi();

  client.setServer(mqtt_server, 1883);

  delay(2000);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  float temperatura = dht.readTemperature();

  int valorPot = analogRead(POT_BATERIA);

  int bateria = map(valorPot, 0, 4095, 100, 0);

  latitude += 0.0001;

  if (latitude > -23.5490) {
    areaSegura = false;
  } else {
    areaSegura = true;
  }

  String statusPet;

  if (digitalRead(BOTAO_SOS) == LOW) {

    statusPet = "SOS ACIONADO";

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    tone(BUZZER, 1000);
  }

  else if (temperatura >= 39.0) {

    statusPet = "TEMPERATURA ALTA";

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    tone(BUZZER, 1200);
  }

  else if (!areaSegura) {

    statusPet = "AREA PERIGOSA";

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    tone(BUZZER, 800);
  }

  else {

    statusPet = "AREA SEGURA";

    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);

    noTone(BUZZER);
  }

  String temperaturaString = String(temperatura, 1);

  String bateriaString = String(bateria);

  client.publish("petguardian/status", statusPet.c_str());

  client.publish("petguardian/temperatura", temperaturaString.c_str());

  client.publish("petguardian/bateria", bateriaString.c_str());

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println(statusPet);

  display.setCursor(0, 18);
  display.print("TEMP: ");
  display.print(temperatura);
  display.println(" C");

  display.setCursor(0, 36);
  display.print("BAT: ");
  display.print(bateria);
  display.println("%");

  display.display();

  Serial.println("-----------------------");

  Serial.print("Status: ");
  Serial.println(statusPet);

  Serial.print("Temperatura: ");
  Serial.println(temperatura);

  Serial.print("Bateria: ");
  Serial.println(bateria);

  delay(2000);
}
