## ¿Que es LM35?

LM35 es un sensor de temperatura con una precisión de 1ºC, este tiene una salida lineal y cada grado centígrado equivale a 10mV, este adicionalmente tiene un rango de operación de entre -55ºC y 150ºC. Se hizo uso de este sensor en el proyecto debido a su pequeño tamaño, bajo consumo energético y facilidad para su trabajo.

## Funcionamiento del sensor.

Como se dijo en la sección anterior este sensor tiene una salida lineal donde cada grado es equivalente a 10mV y se tiene un rango de operación de entre -55ºC y 150ºC. Con base en esto podemos obtener la siguiente formula, con la que se obtiene una función que entrega voltaje en función de la temperatura. 

<p align="center">
  <img src="https://github.com/pavanegasg/Sistemas-Embebidos/blob/master/Documentación/Sensores/LM35/FormulaV.PNG" width="200" title="hover text">
</p>

## Utilización del sensor.

La temperatura obtenida con este se presenta a continuación en forma de gráfica empleando _serial plotter_ del IDE de Arduino con la finalidad de observar la velocidad con la que el sensor reacciona a cambios de temperatura.

<p align="center">
  <img src="https://github.com/pavanegasg/Sistemas-Embebidos/blob/master/Documentación/Sensores/LM35/LM35.png" width="430" title="hover text">
</p>
