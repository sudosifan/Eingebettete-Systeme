############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Vivado_RTL
set_top EquationSolver
add_files -tb tb.cc
add_files -tb stimuli.h
add_files EquationSolver.cc

open_solution "project_bare"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 10 -name default
csim_design
csynth_design
#cosim_design
export_design -format ip_catalog


open_solution "project_pipelined"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 10 -name default
csim_design
set_directive_pipeline -II 1 "EquationSolver::thread0/datapath_loop"
csynth_design
#cosim_design
export_design -format ip_catalog


open_solution "project_pipelined_faster_clk"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 10 -name default
csim_design
set_directive_pipeline -II 1 "EquationSolver::thread0/datapath_loop"
csynth_design
#cosim_design
export_design -format ip_catalog


open_solution "project_area_mapping111"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 10 -name default
csim_design
set_directive_allocation -limit 1 -type operation "EquationSolver::thread0/datapath_loop" mul
set_directive_allocation -limit 1 -type operation "EquationSolver::thread0/datapath_loop" add
set_directive_allocation -limit 1 -type operation "EquationSolver::thread0/datapath_loop" sub
csynth_design
config_bind -effort high
config_schedule -effort high    
#cosim_design
export_design -format ip_catalog



open_solution "project_area_mapping222"
set_part {xc7z010clg400-1} -tool vivado
create_clock -period 10 -name default
csim_design
set_directive_allocation -limit 4 -type operation "EquationSolver::thread0/datapath_loop" mul
set_directive_allocation -limit 4 -type operation "EquationSolver::thread0/datapath_loop" add
set_directive_allocation -limit 4 -type operation "EquationSolver::thread0/datapath_loop" sub
csynth_design
#cosim_design
export_design -format ip_catalog

exit
