############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project ESPraktArea
set_top EquationSolver
add_files -tb tb.cc
add_files -tb stimuli.h
add_files EquationSolver.cc

open_solution "area1"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 20 -name default
source "configs/area1_directives.tcl"
#csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog

open_solution "area2"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 20 -name default
source "configs/area2_directives.tcl"
#csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog

open_solution "area3"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 20 -name default
source "configs/area3_directives.tcl"
#csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog


open_solution "area4"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 4 -name default
source "configs/area4_directives.tcl"
#csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog

exit
