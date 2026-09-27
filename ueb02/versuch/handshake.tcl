############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project handshake
set_top EquationSolver
add_files -tb tb.cc
add_files -tb stimuli.h
add_files EquationSolver.cc

open_solution "handshake"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 20 -name default
csim_design
#csynth_design
#cosim_design
#export_design -format ip_catalog


exit
