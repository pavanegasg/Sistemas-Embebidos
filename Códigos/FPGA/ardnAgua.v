
module aguaMedida( 
	input clk,
	input [7:0] agua,     //Entrada 0-5000
	output [7:0] salidaAgua
	);


	assign salidaAgua = RD ? valAnt-agua : agua;

	reg RD = 0;
	reg [1:0] state = START;
	parameter START=0, S1=1, STOP=2;

	reg divisor = 0;
	reg [7:0] valAnt = 0;
	wire div;
	
	divisor divI(
		.clk(clk),
		.inicio(divisor),
		.CLKOUT(div)
		);

always @ (posedge clk)
begin				
	case (state)
		
		START: begin	
			state <= STOP;
			valAnt <= agua;
		end

		STOP: begin 
			divisor <= 1;
			if(div) begin
			divisor <= 0; 
			state <= START;
			end 
		end

		default:
			state <= START;

	endcase
end 

endmodule 