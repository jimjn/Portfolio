module rowColGen(
		input dispen,
		input h_sync,
		input [9:0] col_c,
		input [7:0] cnt_c,
		output [9:0] col,
		output [7:0] cnt
	);
	
	reg [9:0] colReg;
	reg [7:0] cntReg;
	
	/*always @(posedge h_sync)begin
		cntReg = 8'd0;
		colReg = 10'd0;
	end*/
	
	//16+96+48 = 160
	//length of pipeline = 5;
	//start when cnt gets to 155
	always @(*)begin
		colReg = col_c + 10'd1;
		cntReg = cnt_c + 8'd1;
		
		if(cntReg == 8'd43 && dispen == 1'b0)begin
				colReg = 10'd0;
		end
			
			
		if(h_sync==1'b0)begin//reset counter
			cntReg = 8'd0;
			colReg = 10'd0;
		end	
			
		
	end
	
	assign col = colReg;
	assign cnt = cntReg;
endmodule
//------------------------------------------------------
module inst_gen(
		input [2:0] state,
		output R_enO,
		output G_enO,
		output B_enO,
		output alu_enO,
		output [1:0] zoomO
		);
		
		parameter NORMAL = 3'b000,RED = 3'b001,GREEN=3'b010,BLUE=3'b011,
						GSCALE=3'b100,ZOOM2=3'b101,ZOOM3=3'b110,ZOOM4=3'b111;
						
		reg R_en,G_en,B_en,alu_en;
		reg [1:0] zoom;
		
		assign R_enO = R_en;
		assign G_enO = G_en;
		assign B_enO = B_en;
		assign alu_enO = alu_en;
		assign zoomO = zoom;
		
		always@(*)begin
				case(state)
					NORMAL:begin
						R_en = 1'b1;
						G_en = 1'b1;
						B_en = 1'b1;
						alu_en = 1'b0;
						zoom = 2'b00;
						end
					RED:begin
						R_en = 1'b0;
						G_en = 1'b1;
						B_en = 1'b1;
						alu_en = 1'b0;
						zoom = 2'b00;
						end
					GREEN: begin
						R_en = 1'b1;
						G_en = 1'b0;
						B_en = 1'b1;
						alu_en = 1'b0;
						zoom = 2'b00;
						end
					BLUE:begin
						R_en = 1'b1;
						G_en = 1'b1;
						B_en = 1'b0;
						alu_en = 1'b0;
						zoom = 2'b00;
						end
					GSCALE:begin
						R_en = 1'b1;
						G_en = 1'b1;
						B_en = 1'b1;
						alu_en = 1'b1;
						zoom = 2'b00;
						end
					ZOOM2:begin
						R_en = 1'b1;
						G_en = 1'b1;
						B_en = 1'b1;
						alu_en = 1'b0;
						zoom = 2'b01;
						end
					ZOOM3:begin
						R_en = 1'b1;
						G_en = 1'b1;
						B_en = 1'b1;
						alu_en = 1'b0;
						zoom = 2'b10;
						end
					ZOOM4:begin
						R_en = 1'b1;
						G_en = 1'b1;
						B_en = 1'b1;
						alu_en = 1'b0;
						zoom = 2'b11;
						end
					default:begin
						R_en = 1'b1;
						G_en = 1'b1;
						B_en = 1'b1;
						alu_en = 1'b0;
						zoom = 2'b00;
						end
				endcase
		end
endmodule

//----------------------------------------------------------------------------
module inst_decode(
		input R_en,
		input G_en,
		input B_en,
		input alu_en,
		input [1:0] zoom,
		input [8:0] row,
		input [9:0] col,
		input [1:0] zoomCnt_c,
		output R_enOut,
		output G_enOut,
		output B_enOut,
		output alu_enOut,
		output [1:0] zoomCnt,
		output [13:0] addrOut
	);

	reg [13:0] addr;
	reg [1:0] zoomCntReg = 2'b00;
	reg [8:0] rowReg;
	reg [9:0] colReg;
	assign R_enOut = ~(~(~(~R_en)));
	assign G_enOut = ~(~(~(~G_en)));
	assign B_enOut = ~(~(~(~B_en)));
	assign alu_enOut = ~(~(~(~alu_en)));
	assign addrOut = addr;
	assign zoomCnt = zoomCntReg;

	always@(*)begin
		if(zoom == 2'b00)begin//Normal
			if(row >= 7'd0 && row<= 7'd127 && col>=7'd0 &&col<=7'd127)
				addr[13:0] = row[6:0]*8'd128 + col[6:0];
			else
				addr[13:0] = 14'd0;
		end
		else if(zoom == 2'b01)begin//Zoomx2
			if(row >= 7'd0 && row<= 8'd255 && col>=7'd0 &&col<=8'd255)begin
				addr[13:0] = (row[8:0]>>1)*8'd128 + (col[9:0]>>1);
				end
			else
				addr[13:0] = 14'd0;
		
		end
		else if(zoom == 2'b10)begin//Zoomx3
			if(row >= 7'd0 && row<= 9'd383 && col>=7'd0 &&col<=10'd383)
				addr[13:0] = (row[8:0]/3)*8'd128 + (col[9:0]/3);
			else
				addr[13:0] = 14'd0;
		
		end
		else if(zoom == 2'b11)begin//Zoomx4
			if(row >= 7'd0 && row<= 9'd479 && col>=7'd0 &&col<=10'd511)
				addr[13:0] = (row[8:0]>>2)*8'd128 + (col[9:0]>>2);
			else
				addr[13:0] = 14'd0;
		
		end
	end

endmodule

