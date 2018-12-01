# Numeric ODE solution.

![logo](doc/logo.png)

## Requirements

* Compiler supporting C++ 17.
* CMake.
* Bash and Gnuplot for visualization.

## How to

1. Clone the repo `git clone https://github.com/Atlant154/cm_numeric_ode.git`
2. Change `exact_solution` and `rh_function`(source function) in `main.cpp`. 
3. Build the project by cmake with required options.
4. Plot result of calculation `sh visualization.sh`

## Main features

* **Euler method**.

* **Euler midpoint method**

* **Weight scheme**.

* **Runge-Kutta method**.

## Speed

Performance is inferior to a similar program written in C by 4-7 percent.
In the `libode/benchmarks` you can find benchmarks.