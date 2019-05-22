module multiplier(
			input [3:0] rData,
			input [3:0] gData,
			input [3:0] bData,
			input alu_en,
			output [11:0] m1,
			output [11:0] m2,
			output [11:0] m3,
			output alu_enOut
		);
		
		assign alu_enOut = ~(~(~(~alu_en)));
		
		reg [5:0] rWeight = 6'b001110;//=.21875
		reg [5:0] gWeight = 6'b101110;//=.71875
		reg [5:0] bWeight = 6'b000101;//=.078125
		reg [11:0] result1;
		reg [11:0] result2;
		reg [11:0] result3;
		
		always @(*)begin
			if(alu_en == 1'b1)begin//do multiplication
				result1[11:0] = {2'b00,rData}*rWeight;
				result2[11:0] = {2'b00,gData}*gWeight;
				result3[11:0] = {2'b00,bData}*bWeight;
			end
			else begin
				result1[11:0] = {2'b00,rData,6'b000_000};
				result2[11:0] = {2'b00,gData,6'b000_000};
				result3[11:0] = {2'b00,bData,6'b000_000};
			end
		
		end
		
		assign m1 = result1;
		assign m2 = result2;
		assign m3 = result3;
		
		
endmodule



module adder(
			input [11:0] m1,
			input [11:0] m2,
			input [11:0] m3,
			input alu_en,
			output [3:0] rData,
			output [3:0] gData,
			output [3:0] bData
		);
		
		reg [11:0] point5 = 12'b000000_100000;//=.5
		reg [11:0] a1;
		reg [11:0] a2;
		reg [11:0] a3;
		
		always @(*)begin
			if(alu_en ==1'b1)begin//Do addition
				a1[11:0] = m1 + m2 +m3 + point5;
				a2 = a1;
				a3 = a1;
			end
			else begin
				a1 = m1;
				a2 = m2;
				a3 = m3;
			end
		end
		
		assign rData = a1[9:6];
		assign gData = a2[9:6];
		assign bData = a3[9:6];
		
endmodule

