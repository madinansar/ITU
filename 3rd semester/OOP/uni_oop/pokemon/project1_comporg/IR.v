module IR_Register (
    input wire clk,          
    input wire [7:0] I,     
    input wire L_H,         
    input wire Write_IR,    
    output reg [15:0] IR    
);


always @(posedge clk) begin
    if (Write_IR) begin
        if (L_H)         
            IR[15:8] <= I;
        else             
            IR[7:0] <= I;
    end
    else begin
        IR <= IR;
    end
end

endmodule
