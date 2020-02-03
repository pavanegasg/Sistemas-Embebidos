## Inicio y pasos iniciales Raspberry Pi

En este documento se presentan los pasos y recursos iniciales para iniciar con la Raspberry Pi.

### Para iniciar todo:

* Descargar el archivo .img del sistema operativo (Raspbian Lite) desde https://www.raspberrypi.org/downloads/raspbian/, la guía de instalación se encuentra en https://www.raspberrypi.org/documentation/installation/installing-images/linux.md
* Correr el comando 

	lsblk

para saber donde está ubicada la memoria SD donde se va a instalar el .img (será algo como /dev/sdX, donde X es una letra).
* Correr el siguiente comando teniendo mucho cuidado de elegir bien el disco: sudo dd if=nombreIMG of=/ubicaciónDisco bs=8M
	
Ejemplo:

	sudo dd bs=8M if=2019-07-10-raspbian-buster-lite.img of=/dev/sdb status=progress conv=fsync
	
* Cuando haya finalizado la instalación, ir a la carpeta boot y modificar:
	- config.txt: agregar enable_uart=1 al final
	- cmdline.txt: se elimina la palabra “quiet”

Crear un archivo vacio con el nombre "ssh" en la carpeta raiz, usar el comando:
	
	sudo echo "" > ssh
	
* Insertar la microSD en la RPI y conectar con cable ethernet al PC

* Si se desea ingresar por puerto serial, correr:
	- Para configurar minicom: sudo minicom -s, configuración de la puerta serial, elegir bien donde está conectado el conversor ttl (ttyUSB0 generalmente) y que la velocidad sea 115200.
	- Para conectarse: minicom.
* Para conectarse con ethernet, correr sudo nm-connection-editor, ir a conexión cableada, ajustes de ipv4 y habilitar compartir con otros equipos.
* Con la raspberry conectada por ethernet correr en el computador:

Para conocer la dirección del PC:

	ifconfig
	
La primera dirección que aparece es la del PC, por ejemplo 10.42.0.1. Para buscar la dirección asignada a la RasPi:

	nmap -sT 10.42.0.2-254 

Los primeros 3 números son los primeros 3 de la dirección IP del PC, por ejemplo 10.42.0.29. Para conectarse a la Raspberry:

	ssh pi@10.42.0.29
	contraseña: raspberry

Finalmente, para actualizar paquetes: 
	
	sudo apt update
	sudo apt upgrade

### Para instalar los servidores:

* Servidor de paginas web:

Instalar con: 
	
	sudo apt install apache2

Se puede verificar la instalación ingresando la dirección ip en un navegador. Las páginas se encuentran en la ubicación var/www/html. Se puede eliminar la página por defecto con:
	
	sudo mv index.html index.old
	
Para escribir una nueva: 
	
	sudo nano index.html

* Servidor de bases de datos:

Instalar con:
	
	sudo apt install mariadb-client mariadb-server
	
Para entrar a la base de datos desde bash:

	sudo mysql -u root -p
	
Para instalar phpmyadmin, el manejador html de base de datos que combina servidor de paginas y de base de datos (conexión de capa baja entre base y páginas): 
		
	sudo apt install phpmyadmin
		
En la dirección IP_rasp/phpmyadmin se encuentra la página web para manejar las bases de datos desde un navegador. Si no se encuentra, intentar (https://askubuntu.com/questions/387062/how-to-solve-the-phpmyadmin-not-found-issue-after-upgrading-php-and-apache): 

Abrir el archivo de configuración con:

	sudo nano /etc/apache2/apache2.conf
			
Agregar al final del archivo y guardar: 

	Include /etc/phpmyadmin/apache.conf

Reiniciar apache con: 

	/etc/init.d/apache2 restart
			
- Para poder acceder, seguir (https://stackoverflow.com/questions/5908752/can-anyone-confirm-that-phpmyadmin-allownopassword-works-with-mysql-databases y https://www.iven.in/2016/11/solved-phpmyadmin-1698-access-denied.html):

Para ir al archivo de configuración de phpmyadmin:

	sudo nano /etc/phpmyadmin/config.inc.php 

Buscar la siguiente línea, descomentarla y guardar el archivo:

	$cfg['Servers'][$i]['AllowNoPassword'] = TRUE; 
 Luego:
	
	sudo mysql -u root
	use mysql;
	update user set plugin='' where User='root';
	flush privileges;
	\q

### Configuración del access point:

* Seguir el tutorial: https://www.raspberrypi.org/documentation/configuration/wireless/access-point.md
	- NOTA: evitar agregar denyinterfaces eth0, vuelve la raspberry indetectable con ethernet.
Para reiniciar:

	sudo service dhcpcd restart
	sudo service hostapd restart
	sudo systemctl reload dnsmasq

Para verificar si está funcionando:

	sudo service hostapd status
	sudo service dnsmasq status
	sudo systemctl status dnsmasq
	sudo systemctl status hostapd
	
Para verificar el estado del punto de acceso: 

	sudo tail -f /var/log/syslog

Si el tutorial no funciona, instalar create_ap:
	- Leer README en https://github.com/oblique/create_ap
	- Luego correr:
	
	git clone https://github.com/oblique/create_ap
	cd create_ap
	make install
	
- El archivo de configuración está en la ubicación: /etc/create_ap.conf

El punto de acceso se inicia con: 

	sudo create_ap --config /etc/create_ap.conf

Para que se inicie en boot usar systemd: 

	sudo systemctl start create_ap
	sudo systemctl enable create_ap

### Instalación de node-RED:

- Seguir https://nodered.org/docs/getting-started/raspberrypi:

Script para instalación y actualización: 

	bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered) 

Instalar mosquitto-mqtt (protocolo de mensajeria usando un modelo de publicación/susbcripción: https://mosquitto.org/) con:

	sudo apt install mosquitto

### Comandos utiles:

Permite ver algunas líneas de algún archivo log (reemplazar logFILE): 
	
	sudo tail -f /var/log/logFILE
	
Uso del disco en tamaños de bloque: 

	df -k
	
Uso del disco en múltiplos de 1024: 

	df -h
	
En el PC permite ver si hay conexión por ssh con la Raspberryv (reemplazar ip_rasp): 

	ping ip_rasp 

En la Raspberry permite ver si hay conexión por ssh con el pc (reemplazar ip_rasp): 
	
	ping ip_pc

En el PC, ver donde está montado el disco de la Raspberry: 

	lsblk

Para hacer una copia de seguridad del disco de la raspberry en el pc: 
	
	sudo dd bs=8M if=/dev/sdX of=backup_rpi.img status=progress conv=fsync count=used/8000
	
- X es la letra donde esté montada la memoria, ver lsblk
- used/8000 es para que dd no copie toda la memoria, used será la cantidad de disco usada por la raspberry (ver df -k), aproximar la división hacia arriba.

Configuraciones varias de la raspberry

	sudo raspi-config
	
Para buscar todos los archivos bajo algún nombre (reemplazar quest): 

	sudo find | grep quest

