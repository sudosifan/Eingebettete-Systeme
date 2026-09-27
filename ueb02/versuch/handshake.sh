#!/bin/bash
#set -x #echo on

echo "Compiling EquationSolver...."
rm -r handshake
vivado_hls -f handshake.tcl



echo "*******************************"
echo " Plotting and comparing results ... "
echo "*******************************"
gnuplot -p -e "plot [-0.5:10.5] [-0.1:0.6] 'golden/sim_out.log' smooth unique with linespoints, 'handshake/handshake/csim/build/sim_out.log' smooth unique with linespoints"

cmp -s ./golden/sim_out.log ./handshake/handshake/csim/build/sim_out.log
result=$?
if [ $result = '0' ]; then
  echo "Euler Approximation is correct!"
else
  echo "Euler Approximation is wrong!"
fi
