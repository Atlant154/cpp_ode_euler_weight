# Numeric ODE solution.

![logo](doc/logo.png)

## Requirements

* Compiler supporting C++ 17.
* CMake.
* Bash and Gnuplot for visualization.

## How to

1. Clone the repo `git clone https://github.com/Atlant154/cpp_ode_euler_weight.git`
2. Change `exact_solution` and `rh_function`(source function). 
3. Build the project `cmake . && make`
4. Plot result of calculation `sh visualization.sh`

Note than in the specifics of the test function,
you may have to change the function bodies(delete `- 2 * result.back().right`).

## Main features

* **Euler method**.

* **Weight scheme**.

* **Runge-Kutta method**.

## Speed

This implementation uses STL-containers abd calculates the error in separate function.
For this reason, this implementation is 34-40% slower than the C-code. If you want to
increase the performance, you can replace `.at()` with `[]` and calculate the error in the
solution finding cycle.