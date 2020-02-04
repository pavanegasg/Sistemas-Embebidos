## ¿Qué es NodeMCU?
El NodeMCU es una plataforma IoT de código abierto basado en el chip ESP8266 (ESP-12E), siendo un entorno propicio para aplicaciones que requieran conectividad WiFi, de manera que es posible enviar y recibir datos e incluso controlas pines de entrada y salida de forma remota, de esta misma manera también es posible por medio de comunicación serial obtener los datos de los sensores recopilados por el arduino.

<p align="center">
  <img src="https://github.com/pavanegasgSistemas-Embebidos/Documentación/Comunicación/NodeMCU/NodeMCU.jpg" width="550" title="hover text">
</p>

## Específicaciones técnicas

    -Procesador: ESP8266 @ 80MHz (3.3V) (ESP-12E)
    -4MB de memoria FLASH (32 MBit)
    -WiFi 802.11 b/g/n
    -Regulador 3.3V integrado (500mA)
    -Conversor USB-Serial CH340G / CH340G
    -Función Auto-reset 
    -9 pines GPIO con I2C y SPI
    -1 entrada analógica (1.0V max)
    -4 agujeros de montaje (3mm)
    -Pulsador de RESET
    -Entrada alimentación externa VIN (20V max)

## Prerrequisitos
Para realizar la respectiva utilización de este modulo, especialmente si se quiere utilizar un entorno conocido de programación se hace necesario instalar el pluggin del ESP8266 en el IDE de Arduino con el fin de evitar montar un entorno de desarrollo para utilizar la SDK de Espressif y posteriormente de la misma forma en que se procede en Arduino instalar la libreria PubSubClient, con el fin de convertir dicho módulo en el cliente del servidor ubicado en la Raspberry Pi.
