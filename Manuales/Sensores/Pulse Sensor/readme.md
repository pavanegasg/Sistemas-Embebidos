## ¿Qué es Pulse Sensor?

Pulse sensor es un sensor diseñado por Joel Murphy y Yury Gitman, el cual permite medir la absorción de la luz por la piel, mediante este simple principio y conociendo el hecho de que el coeficiente de absorción de la luz en la piel varia en función de la irrigación sanguínea, se puede obtener fácilmente el pulso de un ser vivo.

## Prerrequisitos

Para la utilización de este sensor se empleo uso de la libreria _PulseSensor Playground_ en el IDE de arduino

## Pruebas preliminares

Esta prueba se realizo con la finalidad de obtener una medición de la señal análoga recibida por el Arduino proveniente del sensor, la cual como se puede observar en la siguiente imagen, corresponde a la grafica del ritmo cardiaco del sujeto de prueba. 

<p align="center">
  <img src="https://github.com/pavanegasg/Sistemas-Embebidos/blob/master/Manuales/Sensores/Pulse%20Sensor/PrimerPrueba.png" width="350" title="hover text">
</p>

## Obtención del BPM en humanos 

Para la obtención de los latidos por minuto se hizo uso de la información obtenida la prueba preliminar, con esta se determino que un latido sucedía cada vez que la señal proveniente del sensor superaba un umbral, con esta información se empleo un programa que detecta el tiempo que transcurre entre latidos y con el inverso de este tiempo se obtiene la frecuencia cardiaca de la persona.
Para poder definir este umbral es necesario calibrar el sensor, esta se realiza observando el valor proveniente del sensor, en el caso del sujeto de prueba empleado se encontró que este es de 510.
