module lfsr(
    input logic rst,
    input logic en,
    input logic clk,
    output logic[7:0] data
);

always_ff @(posedge clk) begin
    if (rst) begin
        data <= 8'b1;
    end else if (en) begin
        for (int i = 7; i >= 1; i--) begin
            data[i] <= data[i-1];
        end
        data[0] <= data[7] ^ data[5] ^ data[4] ^ data[2];
    end
end

endmodule
