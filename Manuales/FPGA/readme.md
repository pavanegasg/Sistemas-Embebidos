



Primeros pasos FPGA BlackIceMx
 	Esta guía provee los recursos basicos necesarios para el uso de la FPGA desde Ubuntu.

### Instalación pre requisitos

 		Para el uso del dispositivo es necesario instalar Yosys tool chain. Pero primero se hace necesario instalar los prequisitor para compilar e instalar el icestorm, Arachne-PNR y Yosys tool chain 

 		sudo apt-get install build-essential clang bison flex libreadline-dev gawk tcl-dev libffi-dev git mercurial graphviz xdot pkg-config python python3 libftdi-dev qt5-default python3-dev libboost-all-dev cmake libeigen3-dev

 		### Instalación herramientas

 		* Descarga e instalación IceStorm 


 				En un directorio vacío:
 					git clone https://github.com/cliffordwolf/icestorm.git icestorm
					cd icestorm
					make -j8
					sudo make install

		* Descarga e instalación de Arachne-pnr
				
				En el mismo directorio:
					git clone https://github.com/cseed/arachne-pnr.git arachne-pnr
					cd arachne-pnr
					make -j8
					sudo make install

		* Instalción opcional NextPNR(reemplazo Arachne-PNR)

				Desde el mismo directorio 
					git clone https://github.com/YosysHQ/nextpnr nextpnr
					cd nextpnr
					cmake -DARCH=ice40 -DCMAKE_INSTALL_PREFIX=/usr/local .
					make -j$(nproc)
					sudo make install

		*Instalación Yosys 

				En el mismo directorio 

					 git clone https://github.com/cliffordwolf/yosys.git yosys
					cd yosys
					make -j8
					sudo make install


		### Carga de primer ejemplo

			Para el primer programa usaremos un ejemplo prediseñado para la FPGA, por lo tanto, clonamos este ejemplo desde github, lo que se puede hacer con:

				git clone https://github.com/folknology/IceCore.git

			Después de copiar el contenido

				cd IceCore/Examples/blink

			En esta carpeta estará el archivo de pines(ucf), la descripción en verilog(chip.v y blink.v) y el archivo makefile, que permite sintetizar el codigo a un archivo bitstream en chip.bin. Para la sintentización usamos el comando: 

				make

		### cargando el primer diseño 

			En el terminal se ejecutan los comandos:

			sudo bash
			usermod -a -G tty yourUserName
			usermod -a -G dialout yourUserName
			stty -F /dev/ttyACM0 raw -echo
			cat /dev/ttyACM0}

			Esto se hace para dar permisos al puerto y usuario. Después de esto, abrimos un nuevo terminal y ponemos:

			cat chip.bin >/dev/ttyACM0 

			con lo que se cargará el programa 




