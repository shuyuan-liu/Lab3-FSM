module lfsr(
    input logic rst,
    input logic en,
    input logic clk,
    output logic [6:0] data_out
);

always_ff @(posedge clk) begin
    if (rst) begin
        data_out <= 7'b1;
    end else if (en) begin
        for (int i = 6; i >= 1; i--) begin
            data_out[i] <= data_out[i-1];
        end
        data_out[0] <= data_out[2] ^ data_out[6];
    end
end

endmodule
