module auto_f1_fsm(
    input logic rst,
    input logic en, 
    input logic clk,
    input logic[15:0] clkdiv,
    output logic[7:0] lights
);

logic tick;

clktick prescaler(
    .rst(rst),
    .en(en),
    .clk(clk),
    .N(clkdiv),
    .tick(tick)
);

f1_fsm fsm(
    .rst(rst),
    .en(en),
    .clk(tick),
    .out(lights)
);

endmodule;
