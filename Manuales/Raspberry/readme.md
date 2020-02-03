### Para iniciar todo:
- Descargar .img (Raspbian Lite) de https://www.raspberrypi.org/downloads/raspbian/, guía de instalación en https://www.raspberrypi.org/documentation/installation/installing-images/linux.md
- Correr el comando lsblk para saber donde está ubicada la memoria (algo como /dev/sdX, X es una letra)
- Correr sudo dd if=nombreIMG of=/ubicaciónDisco bs=8M, tener MUCHO cuidado con elegir bien el disco
	sudo dd bs=8M if=2019-07-10-raspbian-buster-lite.img of=/dev/sdb status=progress conv=fsync
- En la carpeta boot modificar:
	- config.txt: agregar enable_uart=1 al final
	- cmdline.txt: se le quita la palabra “quiet”
	- Crear un archivo vacio con el nombre "ssh", usar el comando sudo echo "" > ssh en la carpeta
- Poner la microSD en la RPI y conectar con ethernet al PC
- Por puerto serial, correr:
	- Para configurar minicom: sudo minicom -s, configuración de la puerta serial, elegir bien donde está conectado el conversor ttl (ttyUSB0 generalmente) y que la velocidad sea 115200.
	- Para conectarse: minicom 
- Por ethernet, correr sudo nm-connection-editor, ir a conexión cableada, ajustes de ipv4 y habilitar compartir con otros equipos
- Con la raspberry conectada por ethernet correr:
	- ifconfig: la primera dirección que aparece es la del PC, en este caso 10.42.0.1
	- nmap -sT 10.42.0.2-254 (los primeros 3 números son los primeros 3 de la dirección IP del PC): busca la dirección de la raspberry conectada, en este caso 10.42.0.29
	- ssh pi@10.42.0.29: para conectarse a la raspberry
	- contraseña: raspberry
- Finalmente, sudo apt update y sudo apt upgrade para actualizar paquetes

Para instalar los servidores:

- Servidor de paginas:
	- Instalar con: sudo apt install apache2
	- Se puede verificar ingresando la dirección ip en un navegador
	- En cd var/www/html se encuentran las páginas
	- Para eliminar la página por defecto: sudo mv index.html index.old
	- Para escribir una nueva: sudo nano index.html

- Servidor de bases de datos:
	- Instalar con: sudo apt install mariadb-client mariadb-server
	- Para entrar a la base de datos: sudo mysql -u root -p
	- Para instalar phpmyadmin, manejador html de base de datos, combina servidor de paginas y de base de datos (conexión de capa baja entre base y páginas): sudo apt install phpmyadmin
		- contraseña: ServerPassword
	- en IP_rasp/phpmyadmin se encuentra la página
		- Si no se encuentra, intentar (https://askubuntu.com/questions/387062/how-to-solve-the-phpmyadmin-not-found-issue-after-upgrading-php-and-apache): 
			* Abrir el archivo de configuración: sudo nano /etc/apache2/apache2.conf
			* Agregar al final del archivo: Include /etc/phpmyadmin/apache.conf
			* Reiniciar apache con: /etc/init.d/apache2 restart
		- Para poder acceder, seguir: (https://stackoverflow.com/questions/5908752/can-anyone-confirm-that-phpmyadmin-allownopassword-works-with-mysql-databases y https://www.iven.in/2016/11/solved-phpmyadmin-1698-access-denied.html)
			* sudo nano /etc/phpmyadmin/config.inc.php para ir al archivo de configuración de phpmyadmin
			* Buscar la línea $cfg['Servers'][$i]['AllowNoPassword'] = TRUE; descomentarla y guardar el archivo
			* sudo mysql -u root
			* use mysql;
			* update user set plugin='' where User='root';
			* flush privileges;
			* \q

Configuración del access point:

- Seguir el tutorial: https://www.raspberrypi.org/documentation/configuration/wireless/access-point.md
	- NOTA: evitar agregar denyinterfaces eth0, vuelve la raspberry indetectable con ethernet.
- Para reiniciar:
	sudo service dhcpcd restart
	sudo service hostapd restart
	sudo systemctl reload dnsmasq
- Para verificar si está funcionando:
	sudo service hostapd status
	sudo service dnsmasq status
	sudo systemctl status dnsmasq
	sudo systemctl status hostapd
- Para verificar el estado del punto de acceso: sudo tail -f /var/log/syslog
- Si el tutorial no funciona, instalar create_ap:
	- Leer README en https://github.com/oblique/create_ap
	- Luego correr:
	git clone https://github.com/oblique/create_ap
	cd create_ap
	make install
	- El archivo de configuración está en: /etc/create_ap.conf (sudo nano /etc/create_ap.conf)
	- El punto de acceso se inicia con: sudo create_ap --config /etc/create_ap.conf
	- Para que se inicie con systemd: 
	sudo systemctl start create_ap
	sudo systemctl enable create_ap

Instalación de node-RED:

- Seguir https://nodered.org/docs/getting-started/raspberrypi:
	- Script para instalación y actualización: bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered) 
- Instalar mosquitto-mqtt con, protocolo de mensajeria usando un modelo de publicación/susbcripción (https://mosquitto.org/): sudo apt install mosquitto

Handy commands:

- Permite ver algunas líneas de algún archivo log (reemplazar logFILE): sudo tail -f /var/log/logFILE
- Uso del disco en tamaños de bloque: df -k
- Uso del disco en múltiplos de 1024: df -h 
- En PC permite ver si hay conexión por ssh con la raspberry: ping ip_rasp 
- En la raspberry permite ver si hay conexión por ssh con el pc: ping ip_pc
- En el pc, ver donde está montado el disco de la raspberry: lsblk
- Para hacer una copia de seguridad del disco de la raspberry en el pc: sudo dd bs=8M if=/dev/sdX of=backup_rpi.img status=progress conv=fsync count=used/8000
	- X es la letra donde esté montada la memoria, ver lsblk
	- used/8000 es para que dd no copie toda la memoria, used será la cantidad de disco usada por la raspberry (ver df -k), aproximar la división hacia arriba
- Configuraciones varias de la raspberry: sudo raspi-config
- Para buscar todos los archivos bajo algún nombre (reemplazar quest): sudo find | grep quest

