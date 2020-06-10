# gnuplot script
set xlabel "Depth (cm)"
set ylabel "dE/dx (MeV/um)"
set xrange[0:4]
set yrange[0:15]
plot "output.dat" u 1:2 w points pt 3