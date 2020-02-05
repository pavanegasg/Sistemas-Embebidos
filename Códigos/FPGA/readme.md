El uso de la FPGA fue la conexión entre las [celdas de carga](https://github.com/pavanegasg/Sistemas-Embebidos/tree/master/Documentaci%C3%B3n/Sensores/HX711%20y%20celda%20de%20carga) y el [microprocesador](https://github.com/pavanegasg/Sistemas-Embebidos/tree/master/Manuales/Raspberry), además del procesamiento de la señal recibida del alimento y el agua de la mascota.

### 1. Conexión Microcontrolador-FPGA:

Esta conexión permite obtener los datos provenientes de las celdas de carga y llevarlos a la FPGA. La comunicación se hace en paralelo, donde se envían 8 bits correspondientes a cada dato, 16 en total para agua y comida.
   * Primera prueba:
   La primera prueba fue recibir datos de 4 bits para enviar esos mismos datos como salida y mostrar ese valor en los leds.
   
```verilog 
// rece.v

module rece( 
	input clk,                // Declaración de variables
	input [3:0] entero,
	output [3:0] tes,
	output [3:0] leds
	);

	assign leds[3] = RD ? !entero[3] : 1'b1;      //Asignación de leds
	assign leds[2] = RD ? !entero[2] : 1'b1;
	assign leds[1] = RD ? !entero[1] : 1'b1;
	assign leds[0] = RD ? !entero[0] : 1'b1;

	assign tes[3] = RD ? entero[3] : 1'b0;        //Asignación de salida 
	assign tes[2] = RD ? entero[2] : 1'b0;
	assign tes[1] = RD ? entero[1] : 1'b0;
	assign tes[0] = RD ? entero[0] : 1'b0;

	reg RD = 1;
	reg [1:0] state = START;
	parameter START=0, S1=1, STOP=2;

	reg divisor = 0;
	wire div;
	
	divisor divI(
		.clk(clk),
		.inicio(divisor),
		.CLKOUT(div)
		);

always @ (posedge clk)        //Máquina de estados para reiniciar el valor de la salida 
begin				
	case (state)
		
		START: begin	
			RD <= 1;
			state <= STOP;
		end

		STOP: begin 
			divisor <= 1;
			if(div) begin
			divisor <= 0; 
			RD <= 0;
			state <= START;
			end 
		end
	endcase
end 

endmodule   
```   
   * Segunda prueba:
     El segundo diseño consitió en recibir un número de 4 bits, y hacer que la salida fuera ese número menos el número recibido inmediatamente anterior. Adicionalmente, se muestra el valor de la salida en los leds de la tarjeta.
     
 ```verilog
 // ardn.v
 
 module rece( 
	input clk,
	input [3:0] dato,         //Definición de variables 
	output [3:0] salida,
	output [3:0] leds
	);


	assign salida = val;            // Asignación a la salida 
  reg [3:0] val;  
	assign leds = !salida;          // Asignación a los leds

	reg [1:0] state = START;
	parameter START=0, S1=1, STOP=2;

	reg divisor = 0;
	reg [3:0] valAnt = 0;
	wire div;
	
	divisor divI(           // Divisor para enviar el dato cada que se quiera
		.clk(clk),
		.inicio(divisor),
		.CLKOUT(div)
		);

always @ (posedge clk)     // Máquina de estados para almacenar valor anterior 
  begin				
	  case (state)
		
		START: begin	
			state <= STOP;
			valAnt <= dato;
      val <= 0;
		end

		STOP: begin           // Espera para enviar el siguiente dato
			divisor <= 1;
			if(div) begin
			divisor <= 0; 
			state <= START;
      val <= valAnt-dato;
			end 
		end

		default:
			state <= START;

	endcase
end 

endmodule    
```

### 2. Conexión FPGA-Microcontrolador
  
  La segunda parte consiste en enviar datos al microcontrolador por comunicación serial, para este caso se escogió UART, dada la fácil implementación. Los datos a enviar son los referentes a la diferencia de comida y agua actual con la medida un instante antes. 
  
  * Primera prueba:
 La primera prueba para esta sección fue la implementación de un puerto UART desde la FPGA, ya que a pesar de que la BlackIceMX cuenta con puertos seriales estos no están conectados directamente a la FPGA. El puerto implementado es una adaptación del puerto disponible en [open-fpga-verilog-tutorial](https://github.com/Obijuan/open-fpga-verilog-tutorial/wiki)
 
  
```verilog
//uart_tx.v

`default_nettype none
`include "baudgen.vh"

module uart_tx 
    #(
    parameter BAUD = `B115200
    )
    (
         input wire clk,        //-- Reloj del sistema (25MHz BlackIceMx)
         input wire rstn,       //-- Reset global
         input wire start,      //-- Activar a 1 para transmitir
         input wire [7:0] data, //-- Byte a transmitir
         output reg tx,         //-- Salida de datos serie
         output wire ready      //-- Transmisor listo / ocupado
       );


reg start_r; 
wire clk_baud;

//-- Bitcounter
reg [3:0] bitc;

//-- Datos registrados
reg [7:0] data_r;


//--------- Microordenes
wire load;    //-- Carga del registro de desplazamiento. Puesta a 0 del
              //-- contador de bits
wire baud_en; //-- Habilitar el generador de baudios para la transmision

//-------------------------------------
//-- RUTA DE DATOS
//-------------------------------------

//-- Registrar la entrada start

always @(posedge clk)
  start_r <= start;

always @(posedge clk)
  if (start == 1 && state == IDLE)
    data_r <= data;

//-- Registro de 10 bits para almacenar la trama a enviar:
//-- 1 bit start + 8 bits datos + 1 bit stop
reg [9:0] shifter;

//-- Cuando la microorden load es 1 se carga la trama
//-- con load 0 se desplaza a la derecha y se envia un bit, al
//-- activarse la señal de clk_baud que marca el tiempo de bit
//-- Se introducen 1s por la izquierda

always @(posedge clk)
  //-- Reset
  if (rstn == 0)
    shifter <= 10'b11_1111_1111;

  //-- Modo carga
  else if (load == 1)
    shifter <= {data_r,2'b01};

  //-- Modo desplazamiento
  else if (load == 0 && clk_baud == 1)
    shifter <= {1'b1, shifter[9:1]};

//-- Contador de bits enviados
//-- Con la microorden load (=1) se hace un reset del contador
//-- con load = 0 se realiza la cuenta de los bits, al activarse
//-- clk_baud, que indica el tiempo de bit

always @(posedge clk)
  if (load == 1)
    bitc <= 0;
  else if (load == 0 && clk_baud == 1)
    bitc <= bitc + 1;

//-- Sacar por tx el bit menos significativo del registros de desplazamiento
//-- ES UNA SALIDA REGISTRADA, puesto que tx se conecta a un bus sincrono
//-- y hay que evitar que salgan pulsos espureos (glitches)

always @(posedge clk)
  tx <= shifter[0];

//-- Divisor para obtener el reloj de transmision
baudgen #(.BAUD(BAUD))
  BAUD0 (
    .clk(clk),
    .clk_ena(baud_en),
    .clk_out(clk_baud)
  );

//------------------------------
//-- CONTROLADOR
//------------------------------

//-- Estados del automata finito del controlador
localparam IDLE  = 0;  //-- Estado de reposo
localparam START = 1;  //-- Comienzo de transmision
localparam TRANS = 2;  //-- Estado: transmitiendo dato

//-- Estados del autómata del controlador
reg [1:0] state;

//-- Transiciones entre los estados
always @(posedge clk)

  //-- Reset del automata. Al estado inicial
  if (rstn == 0)
    state <= IDLE;

  else
    //-- Transiciones a los siguientes estados
    case (state)

      //-- Estado de reposo. Se sale cuando la señal
      //-- de start se pone a 1
      IDLE: 
        if (start_r == 1) 
          state <= START;
        else 
          state <= IDLE;

      //-- Estado de comienzo. Prepararse para empezar
      //-- a transmitir. Duracion: 1 ciclo de reloj
      START:
        state <= TRANS;

      //-- Transmitiendo. Se esta en este estado hasta
      //-- que se hayan transmitido todos los bits pendientes
      TRANS:
        if (bitc == 11)
          state <= IDLE;
        else
          state <= TRANS;

      //-- Por defecto. NO USADO. Puesto para
      //-- cubrir todos los casos y que no se generen latches
      default:
        state <= IDLE;

    endcase

//-- Generacion de las microordenes
assign load = (state == START) ? 1 : 0;
assign baud_en = (state == IDLE) ? 0 : 1;

//-- Señal de salida. Esta a 1 cuando estamos en reposo (listos
//-- para transmitir). En caso contrario esta a 0
assign ready = (state == IDLE) ? 1 : 0;

endmodule
```

* Segunda prueba
  * Primera parte:
  La segunda prueba fue incorporar los datos provenientes de las celdas de carga y el modulo `uart_tx.v`. Primero se utilizó un valor fijo para la lectura de comida y agua.
  
```verilog  
//Top.v

`include "baudgen.vh"

	module Top(					// Declaración de variables
			input clk,			//	
			input [3:0] datoAgua,		
			input [3:0] datoPeso,
			output wire tx,
			output [1:0] stat
			);

	//Cables y registros para conexión de modulos 

	parameter BAUD = `B115200;			// Definición de tasa de baudios a usar en la comunicación serial

		reg resetUart = 0;			// Cables y registros para conexión de modulos
		reg startUart;

		wire [3:0] Comida;
		wire [3:0] Agua;

		wire [7:0] comidaFinal;
		wire [7:0] aguaFinal;
		assign comidaFinal = 8'b01111011;	// Valor fijo de agua y comida
		assign aguaFinal = 8'b01111101;
		reg [7:0] data;

		reg counter;				// Contador para máquina de estado	
		reg cena;
		wire readyUart;

		reg divStart = 0;
		wire divOut;

	//Instanciación modulos

	always @(posedge clk) begin			// Inicialización puerto serial 
		resetUart <= 1;
	end

	uart_tx #(.BAUD(BAUD)) Uart_txComida(		// Instanciación de modulos
			.clk(clk),
			.rstn(resetUart),
			.start(startUart),
			.data(data),
			.tx(tx),
			.ready(readyUart)
			);

	aguaMedida medicionAgua(
			.clk(clk),
			.agua(datoAgua),
			.salidaAgua(Agua)
			);

	pesoMedida medicionComida(
			.clk(clk),
			.peso(datoPeso),
			.salidaPeso(Comida)
			);

	always @*					// Contador
  		case (counter)
    		1'b0: data <= comidaFinal;
   			1'b1: data <= aguaFinal;
    		default: data <= ".";
  		endcase


  	always @(posedge clk)
		if (resetUart == 0)
    		counter = 0;
  		else if (cena)
    		counter = counter + 1;

	divisorTop divider(
		.clk(clk),
		.inicio(divStart),
		.CLKOUT(divOut)
		);

	// Máquina de estados para el control de las señales

	reg [1:0] state = START;
	parameter START=0, S1=1, S2=2, WAIT=3;
	assign stat = state;



	always @ (posedge clk)
	begin

		case(state)
			
			START: begin 				// Espera inicial
				divStart <= 1;
				if(divOut) begin 
					state <= S1;
					divStart <= 0;
				end
				else state <= START;
			end
		
			S1:  begin				// Transmisión de comida y agua 
				if(readyUart == 1) state <= S2;
				else state <= S1;
			end

			S2: begin				// Regresar a estado anterior cuando ya se haya transmitido 
				if(counter == 1) state <= WAIT; // comida. Pasar a estado siguiente cuando se hayan 
				else state <= S1;		// transmitido los dos valores
			end

			WAIT: begin				// Espera de 10 segundos
				divStart <= 1;
				if(divOut) begin 
					state <= START;
					divStart <= 0;
				end
				else state <= WAIT;
			end

			default: state <= START;

		endcase

	end

	always @*						// Asignación de microordenes

			case(state)
				START: begin
					startUart <= 0;
					cena <= 0;
				end

				S1: begin
					startUart <= 1;
					cena <= 0;
				end

				S2: begin  
					startUart <= 0;
					cena <= 1;
				end

				WAIT: begin
					startUart <= 0;
					cena <= 0;
				end

				default: begin 
					startUart <= 0;
					cena <= 0;
				end

			endcase

endmodule

```  

  * Segunda parte:
  La parte final fue cambiar el valor fijo de agua y comida y probar la transmisión.
  
  
 ### NOTA: Las versiones finales de los archivos y modulos mencionados están disponibles.
