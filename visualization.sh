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
    FILES = system("ls -1 'Weight scheme.'*.txt")
    LABEL = system("ls -1 'Weight scheme.'*.txt | sed -e 's/Weight scheme.//' -e 's/.txt//'")

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

gnuplot -persist <<- EOF
    set terminal wxt size 800,600
    set termoption dashed
    set title "Euler midpoint method."
    set xlabel "X"
    set ylabel "Y"
    FILES = system("ls -1 'Euler_midpoint_method.'*.txt")
    LABEL = system("ls -1 'Euler_midpoint_method.'*.txt | sed -e 's/'Euler_midpoint_method.'//' -e 's/.txt//'")

    plot for [i=1:words(FILES)] word(FILES,i) u 1:2 title word(LABEL,i)  with lines
EOF