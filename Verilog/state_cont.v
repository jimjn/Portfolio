module state_cont(
		input [9:0] SW,
		input [2:0] state_c,
		output [2:0] state

	);
	
	parameter NORMAL = 3'b000,RED = 3'b001,GREEN=3'b010,BLUE=3'b011,
						GSCALE=3'b100,ZOOM2=3'b101,ZOOM3=3'b110,ZOOM4=3'b111;
						
	reg [2:0] next_state;
	
	always@(*)begin
		case(state_c)
			NORMAL:begin
				next_state = NORMAL;
				if(SW[7] == 1'b1)
					next_state = RED;
				if(SW[6] == 1'b1)
					next_state = GREEN;
				if(SW[5] == 1'b1)
					next_state = BLUE;
				if(SW[4] == 1'b1)
					next_state = GSCALE;
				if(SW[9:8] == 2'b01)
					next_state = ZOOM2;
				if(SW[9:8] == 2'b10)
					next_state = ZOOM3;
				if(SW[9:8] == 2'b11)
					next_state = ZOOM4;
					
			end
			RED:begin
				next_state = RED;
				if(SW[7] == 1'b0)
					next_state = NORMAL;
			end
			GREEN:begin
				next_state = GREEN;
				if(SW[6] == 1'b0)
					next_state = NORMAL;
			end
			BLUE:begin
				next_state = BLUE;
				if(SW[5] == 1'b0)
					next_state = NORMAL;
			end
			GSCALE:begin
				next_state = GSCALE;
				if(SW[4] == 1'b0)
					next_state = NORMAL;
			end
			ZOOM2:begin
				next_state = ZOOM2;
				if(SW[9:8] == 2'b00)
					next_state = NORMAL;
			end
			ZOOM3:begin
				next_state = ZOOM3;
				if(SW[9:8] == 2'b00)
					next_state = NORMAL;
			end
			ZOOM4:begin
				next_state = ZOOM4;
				if(SW[9:8] == 2'b00)
					next_state = NORMAL;
			end
			default:begin
				next_state = NORMAL; 
			end
		endcase
	end
	
	assign state = next_state;
endmodule	