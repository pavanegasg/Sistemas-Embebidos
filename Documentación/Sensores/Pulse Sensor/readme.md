## ¿Qué es Pulse Sensor?

Pulse sensor es un sensor diseñado por Joel Murphy y Yury Gitman, el cual permite medir la absorción de la luz por la piel, mediante este simple principio y conociendo el hecho de que el coeficiente de absorción de la luz en la piel varia en función de la irrigación sanguínea, se puede obtener fácilmente el pulso de un ser vivo.

## Prerrequisitos

Para la utilización de este sensor se empleo la libreria _PulseSensor Playground_ la cual se puede descargar en el IDE de Arduino.

## Pruebas preliminares

Esta prueba se realizo con la finalidad de obtener una medición de la señal análoga recibida por el Arduino proveniente del sensor, la cual como se puede observar en la siguiente imagen, corresponde a la grafica del ritmo cardiaco del sujeto de prueba. 

<p align="center">
  <img src="https://github.com/pavanegasg/Sistemas-Embebidos/blob/master/Documentación/Sensores/Pulse%20Sensor/PrimerPrueba.png" width="350" title="hover text">
</p>

## Obtención del BPM en humanos 

Para la obtención de los latidos por minuto se hizo uso de la información obtenida la prueba preliminar, con esta se determino que un latido sucedía cada vez que la señal proveniente del sensor superaba un umbral, con esta información se empleo un programa que detecta el tiempo que transcurre entre latidos y con el inverso de este tiempo se obtiene la frecuencia cardiaca de la persona.

Para poder definir este umbral es necesario calibrar el sensor, esta se realiza observando el valor proveniente del sensor, en el caso del sujeto de prueba empleado se encontró que este es de 520.

<p align="center">
  <img src="https://github.com/pavanegasg/Sistemas-Embebidos/blob/master/Documentación/Sensores/Pulse%20Sensor/BPM.jpeg" width="550" title="hover text">
</p>

En la imagen anterior se presenta lo obtenido por el programa, donde el primer valor presentado es la frecuencia cardiaca (en latidos por minuto), y el ultimo es el valor entregado por el sensor.

## Obtención del BPM en perros

Para la obtención de esta se emplea el mismo programa que en la sección anterior, sin embargo de debe realizar una nueva calibración, en este caso el sujeto de prueba fue un labrador dorado adulto, el sensor se ubico en la ingle del perro debido a la poca cantidad de pelo y la presencia de venas y arterias cercanas a la piel, en este caso el valor de calibración fue de 507. 
