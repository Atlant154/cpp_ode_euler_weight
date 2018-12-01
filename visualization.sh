#!/bin/bash

gnuplot -persist <<- EOF
    set terminal wxt size 800,600
    set termoption dashed
    set title "Euler method."
    set xlabel "X"
    set ylabel "Y"
    FILES = system("ls -1 'Euler_method'.*.txt")
    LABEL = system("ls -1 'Euler_method'.*.txt | sed -e 's/Euler_method.//' -e 's/.txt//'")

    plot for [i=1:words(FILES)] word(FILES,i) u 1:2 title word(LABEL,i)  with lines
EOF

gnuplot -persist <<- EOF
    set terminal wxt size 800,600
    set termoption dashed
    set title "Weight method."
    set xlabel "X"
    set ylabel "Y"
    FILES = system("ls -1 weight_scheme_*.txt")
    LABEL = system("ls -1 weight_scheme_*.txt | sed -e 's/weight_scheme_//' -e 's/.txt//'")

    plot for [i=1:words(FILES)] word(FILES,i) u 1:2 title word(LABEL,i)  with lines
EOF

gnuplot -persist <<- EOF
    set terminal wxt size 800,600
    set termoption dashed
    set title "Runge-Kutta method."
    set xlabel "X"
    set ylabel "Y"
    FILES = system("ls -1 Runge-Kutta_method.*.txt")
    LABEL = system("ls -1 Runge-Kutta_method.*.txt | sed -e 's/Runge-Kutta_method.//' -e 's/.txt//'")

    plot for [i=1:words(FILES)] word(FILES,i) u 1:2 title word(LABEL,i)  with lines
EOF