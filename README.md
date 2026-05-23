# PetGuardian-IoT

Sistema inteligente de monitoramento pet utilizando ESP32, MQTT, Node-RED e dashboard em tempo real.

---

# Objetivo

O projeto PetGuardian-IoT foi desenvolvido com o objetivo de monitorar pets em tempo real utilizando conceitos de Internet das Coisas (IoT). O sistema permite acompanhar temperatura, nível de bateria, status de segurança e acionamento de emergência SOS através de sensores e dashboard web.

---

# Tecnologias Utilizadas

- ESP32
- Wokwi Simulator
- MQTT
- Node-RED
- Dashboard Node-RED
- OLED SSD1306
- GitHub

---

# Componentes Utilizados

- ESP32
- Sensor DHT22
- Display OLED SSD1306
- LEDs de alerta
- Buzzer
- Push Button (SOS)
- Potenciômetro
- Broker MQTT HiveMQ
- Dashboard Node-RED

---

# Funcionalidades

## Monitoramento de Temperatura

O sensor DHT22 realiza a leitura da temperatura do ambiente/pet em tempo real.

---

## Sistema SOS

Ao pressionar o botão SOS:

- LED vermelho é acionado;
- buzzer emite alerta sonoro;
- dashboard recebe alerta em tempo real;
- OLED exibe mensagem de emergência.

---

## Monitoramento de Bateria

O potenciômetro simula o nível de bateria do rastreador pet.

---

## GPS Simulado

O sistema realiza simulação de geolocalização para identificar:

- área segura;
- área perigosa.

Quando o pet sai da área segura:

- LED vermelho é acionado;
- buzzer dispara;
- dashboard recebe alerta.

---

## Dashboard em Tempo Real

O Node-RED exibe:

- temperatura;
- gráfico de temperatura;
- nível de bateria;
- status do pet.

---

# Arquitetura do Projeto

ESP32 → MQTT Broker → Node-RED → Dashboard

---

# Comunicação MQTT

## Tópicos utilizados

petguardian/status

petguardian/temperatura

petguardian/bateria

---

# Estrutura do Projeto

PetGuardian-IoT/

│

├── codigo/

│ └── petguardian.ino

│

├── fluxos/

│ └── node-red-flow.json

│

├── imagens/

│ ├── circuito.png

│ ├── dashboard.png

│ ├── node-red.png

│ └── oled.png

│

└── README.md

---

# Como Executar

## 1. Abrir projeto no Wokwi

Importar o circuito e o código da ESP32.

---

## 2. Instalar bibliotecas

Bibliotecas utilizadas:

- PubSubClient
- Adafruit SSD1306
- Adafruit GFX
- DHT sensor library
- Adafruit Unified Sensor

---

## 3. Executar Node-RED

Instalar:

npm install -g --unsafe-perm node-red

Executar:

node-red

Abrir:

http://127.0.0.1:1880

Dashboard:

http://127.0.0.1:1880/ui

---

# Demonstração

## Área segura

- LED verde ligado;
- buzzer desligado;
- dashboard indicando operação normal.

---

## Área perigosa

- LED vermelho ligado;
- buzzer acionado;
- dashboard exibe alerta.

---

## SOS acionado

- alerta sonoro ativado;
- dashboard atualizado em tempo real;
- OLED exibe emergência.

---

# Resultados Obtidos

O projeto conseguiu integrar sensores físicos, comunicação MQTT e dashboard web em tempo real, demonstrando uma solução funcional de monitoramento pet baseada em IoT.

---

# Integrantes

- Maria Luiza Alves de Aquino
- João Victor Gomes de Souza
- Lucas Barranha Giannini

---

# Repositório

https://github.com/Malualvess-dev/PetGuardian-IoT
