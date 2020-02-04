/*Divisor
*/
module divisor(
				input           clk,
				input 		inicio,
				output	reg	CLKOUT	
			);
       	        
       	parameter nciclos=250000000;
		reg [29:0] contador=0;
	
	always @(posedge clk) 
	begin
		if(inicio==1) 
		begin
			if(contador >nciclos)
			begin
				contador<=0;
				CLKOUT <= 1;
			end
			else 
			begin
				contador <=contador + 1;
				CLKOUT <= 0;
			end			
		end 
		else begin 
		contador <=0;
		CLKOUT <=0;
		end
	end

endmodule
