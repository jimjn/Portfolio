/*module rowColGenReg(
			input vga_clk,
			input [8:0] row_c,
			input [8]
		);

		
endmodule*/
//---------------------------------------------------------------------
module plReg0(
		input vga_clk,
		input [8:0] row_c,
		input [9:0] col_c,
		input [7:0] cnt_c,
		output [8:0] row,
		output [9:0] col,
		output [7:0] cnt
	);
	
	reg [8:0] rowReg;
	reg [9:0] colReg;
	reg [7:0] cntReg;
	
	always @(posedge vga_clk)begin
		rowReg <= #1 row_c; 
		colReg <= #1 col_c;
		cntReg <= #1 cnt_c;
	end
	
	assign row = rowReg;
	assign col = colReg;
	assign cnt = cntReg;
endmodule
//---------------------------------------------------------------------
module plReg1(
			input vga_clk,
			input R_en_c,
			input G_en_c,
			input B_en_c,
			input alu_en_c,
			input [13:0] addr_c,
			input [1:0] zoom_c,
			output R_en,
			output G_en,
			output B_en,
			output alu_en,
			output [13:0] addr,
			output [1:0] zoom
		);
		
		reg RReg,GReg,BReg,aluReg;
		reg [13:0] addrReg;
		reg [1:0] zoomReg;

		
		always @(posedge vga_clk)begin
			RReg <= #1 R_en_c;
			GReg <= #1 G_en_c;
			BReg <= #1 B_en_c;
			addrReg <= #1 addr_c;
			zoomReg <= #1 zoom_c;
			aluReg <= #1 alu_en_c;
		end
		
		assign R_en = RReg;
		assign G_en = GReg;
		assign B_en = BReg;
		assign addr = addrReg;
		assign zoom = zoomReg;
		assign alu_en = aluReg;
endmodule

//------------------------------------------------------------------------
module plReg2(
		input vga_clk,
		input [3:0] rData_c,
		input [3:0] gData_c,
		input [3:0] bData_c,
		input alu_en_c,
		output [3:0] rData,
		output [3:0] gData,
		output [3:0] bData,
		output alu_en
	);

	reg [3:0] rReg;
	reg [3:0] gReg;
	reg [3:0] bReg;
	reg alu_enReg;
	
	always @(posedge vga_clk)begin
		rReg <= #1 rData_c;
		gReg <= #1 gData_c;
		bReg <= #1 bData_c;
		alu_enReg <= #1 alu_en_c;
	end
	
	assign rData = rReg;
	assign gData = gReg;
	assign bData = bReg;
	assign alu_en = alu_enReg;
	
endmodule
//------------------------------------------------------------------------
module plReg3(
		input vga_clk,
		input [11:0] m1_c,
		input [11:0] m2_c,
		input [11:0] m3_c,
		input alu_en_c,
		output [11:0] m1,
		output [11:0] m2,
		output [11:0] m3,
		output alu_en
	);
	
	reg [11:0] m1Reg;
	reg [11:0] m2Reg;
	reg [11:0] m3Reg;
	reg alu_enReg;
	
	always @(posedge vga_clk)begin
		m1Reg <= #1 m1_c;
		m2Reg <= #1 m2_c;
		m3Reg <= #1 m3_c;
		alu_enReg <= #1 alu_en_c;
	end
	
	
	assign m1 = m1Reg;
	assign m2 = m2Reg;
	assign m3 = m3Reg;
	assign alu_en = alu_enReg;
endmodule
//------------------------------------------------------------------------
module plReg4(
		input vga_clk,
		input [3:0] rData_c,
		input [3:0] gData_c,
		input [3:0] bData_c,
		output [3:0] rData,
		output [3:0] gData,
		output [3:0] bData
	);
	
	reg [3:0] rReg;
	reg [3:0] gReg;
	reg [3:0] bReg;
	
	always @(posedge vga_clk)begin
		rReg <= #1 rData_c;
		gReg <= #1 gData_c;
		bReg <= #1 bData_c;
	end
	
	assign rData = rReg;
	assign gData = gReg;
	assign bData = bReg;
endmodule
//------------------------------------------------------------------------
module stateReg(
		input vSync,
		input [2:0] state_c,
		output [2:0] state
	);
	
	reg [2:0] stateTemp = 3'b000;
	
	always @(posedge vSync)begin
			stateTemp <= #1 state_c;
	end
	
	assign state = stateTemp;
endmodule
//-------------------------------------------------------------------------
