## ¿Que es HX711?

El modulo HX711 es un dispositivo que actúa como conversor analógico a digital de 24 bits de precisión diseñado para trabajar con sensores tipo puente como las celdas de carga para medición de peso. Este está compuesto básicamente por un multiplexor, un PGA (amplificador de ganancia programable), un conversor analógico digital y una interfaz digital que permite la conexión digital con el Arduino.

## ¿Que es una celda de carga?

Una celda de carga es un puente de Wheastone el cual emplea resistencias que varían su valor en función de la deformación mecánica que sufre la celda cuando esta es sometida a una fuerza, en este caso el peso de un objeto. 

## Prerrequisitos

Para la utilización de este sensor se empleo de la libreria _HX_711_ la cual se puede descargar en el IDE de Arduino.

## Calibración

Para la calibración de este se empleo un programa en el cual se ingresa el peso en gramos del objeto que se posiciona en la celda de carga, en el caso de la celda de carga numero 1 se encontró que el valor de calibración es -391.55.

<p align="center">
  <img src="https://github.com/pavanegasg/Sistemas-Embebidos/blob/master/Manuales/Sensores/HX711%20y%20celda%20de%20carga/CeldaCalibracion.jpeg" width="550" title="hover text">
</p>
