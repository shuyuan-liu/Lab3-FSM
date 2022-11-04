#!/usr/bin/sh

TOP_MODULE=auto_f1_fsm

set -e # Terminate script on any error

rm -rf obj_dir
rm -rf *.vcd

verilator --top $TOP_MODULE -Wall --cc --trace *.sv --exe ${TOP_MODULE}_tb.cpp
make -j7 -C obj_dir -f V$TOP_MODULE.mk
./obj_dir/V$TOP_MODULE
