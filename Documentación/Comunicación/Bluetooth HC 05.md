## Bluetooth HC 05
El módulo Bluetooth HC-05 permite conectar el proyecto con Arduino nano a un celular de manera inalámbrica (Bluetooth). La comunicación
Bluetooth se da entre dos tipos de dispositivos: Maestro y Esclavo.  El módulo Bluetooth HC-05 viene configurado de fábrica para trabajar 
como esclavo, es decir, preparado para escuchar peticiones de conexión; lo cual es conveniente en este caso ya que el celular se comportará
como maestro.

 <p align="center">
  <img src="https://github.com/pavanegasg/Sistemas-Embebidos/blob/master/Documentos/Imagenes/modulo-bluetooth-hc05.jpg" width="550" title="hover text">
</p>
Este módulo cumple con las especificaciones del estándar Bluetooth 2.0 que es perfectamente compatible con celulares o smartphones Android, 
más no con los Iphone. 

## Especificaciones Técnicas

     -Voltaje de operación: 3.6V - 6V DC
     -Consumo corriente: 50mA
     -Alcance 10 metros
     -Interface comunicación: Serial TTL
     -Baudrate por defecto: 9600.
     -Temperatura de trabajo: -20C a +75C
     -Compatible con Android

## Estados del módulo 

 **Estado conectado**
 
 - Entra a este estado una vez se ha alimentao el módulo no se ha establecido una conexión bluetooth con ningún otro dispositivo.
 - EL LED del módulo en este estado parpadea rápidamente
 
 **Estado desconectado**
 
 - Entra a este estado cuando se establece una conexión con otro dispositivo bluetooth.
 - El LED hace un doble parpadeo.
 
 ## Conexión con el celular
 
El celular como se había mencionado anteriormente funciona en este caso coo maestro, para ello se hace uso del Bluetooth que posee el
mismo y la conexión se realiza mediante la app creada con ayuda del SDK de código abierto, Ionic. La cual posee un complemente llamado 
**Bluetooth Serial**, a cual facilita la comunicación

    **// Write a string
     this.bluetoothSerial.write('hello world').then(success, failure)**
     
  

