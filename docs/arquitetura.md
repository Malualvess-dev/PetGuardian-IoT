# Arquitetura do Projeto

O PetGuardian IoT utiliza uma ESP32 como controladora principal.

## Componentes
- ESP32
- Botão SOS
- Display OLED SSD1306
- LED verde
- LED vermelho
- Buzzer

## Funcionamento
O sistema monitora o estado do pet e apresenta alertas visuais, sonoros e textuais.

- LED verde: área segura
- LED vermelho: área perigosa ou SOS
- Buzzer: alerta sonoro
- Display OLED: mostra o status do sistema

## Próximas etapas
- Integração com GPS
- Comunicação MQTT
- Dashboard IoT
