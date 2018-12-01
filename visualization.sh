#!/bin/bash

gnuplot -persist <<- EOF
    set terminal wxt size 800,600
    set termoption dashed
    set title "Euler method."
    set xlabel "X"
    set ylabel "Y"
    FILES = system("ls -1 euler_result_*.txt")
    LABEL = system("ls -1 euler_result_*.txt | sed -e 's/euler_result_//' -e 's/.txt//'")

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
    FILES = system("ls -1 runge_kutta_*.txt")
    LABEL = system("ls -1 runge_kutta_*.txt | sed -e 's/runge_kutta_//' -e 's/.txt//'")

    plot for [i=1:words(FILES)] word(FILES,i) u 1:2 title word(LABEL,i)  with lines
EOF