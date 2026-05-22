#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BOTAO_SOS 15

#define LED_VERDE 18
#define LED_VERMELHO 19

#define BUZZER 5

void setup() {

  Serial.begin(115200);

  pinMode(BOTAO_SOS, INPUT_PULLUP);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  Wire.begin(21, 22);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erro no display");
    while(true);
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
}

void loop() {

  int estado = digitalRead(BOTAO_SOS);

  display.clearDisplay();

  if (estado == LOW) {

    Serial.println("SOS ACIONADO");

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    tone(BUZZER, 1000);

    display.setCursor(0, 10);
    display.println("PERIGO!");

    display.setCursor(0, 40);
    display.println("SOS");

  } else {

    Serial.println("AREA SEGURA");

    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);

    noTone(BUZZER);

    display.setCursor(0, 20);
    display.println("SEGURA");
  }

  display.display();

  delay(300);
}
