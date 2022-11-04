#include <iostream>
#include <cstdlib>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "vbuddy.cpp"
#include "Vauto_f1_fsm.h"

int main(int argc, char* argv[])
{
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    auto top = new Vauto_f1_fsm;
    auto logger = new VerilatedVcdC;
    top->trace(logger, 99);
    logger->open("f1_fsm.vcd");

    if (!vbdOpen()) {
        std::cerr << "Failed to open connection to Vbuddy; exiting" << std::endl;
        exit(EXIT_FAILURE);
    }
    vbdHeader("Lab 3: F1 FSM");

    for (int cycle = 0; cycle < 100000; cycle++) {
        top->rst = (cycle == 0);
        top->en = 1;
        top->clkdiv = vbdValue();

        for (int i = 0; i < 2; i++) {
            top->clk = i;
            top->eval();
            logger->dump(2 * cycle + i);
        }

        //vbdPlot(top->out, 0, 0xFF);
        vbdBar(top->lights);
        vbdCycle(cycle + 1);

        if (Verilated::gotFinish()) {
            exit(EXIT_SUCCESS);
        }
    }

    logger->close();
    vbdClose();
    exit(EXIT_SUCCESS);
}
