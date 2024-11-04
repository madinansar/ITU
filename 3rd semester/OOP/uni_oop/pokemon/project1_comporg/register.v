module register_16bit (
    input wire [2:0] control,
    input wire [15:0] data_in,
    input wire clock,
    input wire reset,
    output reg [15:0] data_out
);

always @(posedge clock or posedge reset) begin
    if (reset) begin
        data_out <= 16'b0;
    end else begin
        case (control)
            3'b000: data_out <= data_out
            3'b001: data_out <= data_out - 1; 
            3'b010: data_out <= data_in;
            3'b011: data_out <= 16'b0; 
            3'b100: data_out <= {8'b0, data_in[7:0]}; 
            3'b101: data_out[7:0] <= data_in[7:0]; 
            3'b110: data_out[15:8] <= data_in[7:0]; 
            3'b111: begin 
                data_out[15:8] <= {data_in[7], data_in[7], data_in[7], data_in[7], data_in[7], data_in[7], data_in[7], data_in[7]};
                data_out[7:0] <= data_in[7:0];
            end
            default: data_out <= data_out; 
        endcase
    end
end

endmodule
