#include <iostream>
#include <cstdlib>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "vbuddy.cpp"
#include "Vlfsr.h"

int main(int argc, char* argv[])
{
    Verilated::commandArgs(argc, argv);
    Verilated::traceEverOn(true);

    auto top = new Vlfsr;
    auto logger = new VerilatedVcdC;
    top->trace(logger, 99);
    logger->open("lsfr.vcd");

    if (!vbdOpen()) {
        std::cerr << "Failed to open connection to Vbuddy; exiting" << std::endl;
        exit(EXIT_FAILURE);
    }
    vbdHeader("Lab 3: LFSR");

    for (int cycle = 0; cycle < 1000; cycle++) {
        top->rst = cycle == 0;
        top->en = 1;

        for (int i = 0; i < 2; i++) {
            top->clk = i;
            top->eval();
            logger->dump(2 * cycle + i);
        }

        vbdPlot(top->data, 0, 0xFF);
        vbdBar(top->data);
        vbdCycle(cycle + 1);

        if (Verilated::gotFinish()) {
            exit(EXIT_SUCCESS);
        }
    }

    logger->close();
    vbdClose();
    exit(EXIT_SUCCESS);
}