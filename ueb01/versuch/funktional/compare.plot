set xlabel "x"
set ylabel "y"
set xrange [0:10]
set yrange [-0.1:0.6]

plot "sim.data"    index 0 using 1:2 smooth unique with linespoints title "sim",\
     "golden.data" index 0 using 1:2 smooth unique with linespoints title "golden"
