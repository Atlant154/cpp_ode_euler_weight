#include <benchmark/benchmark.h>
#include "../appr_scheme.h"

#include <memory>
#include <iostream>
#include <cmath>

inline double heat_sources(double x, double y)
{
    double p = 0.5;
    return cos(x) - x * sin(x) + p * pow(y - x * cos(x), 4);
}

inline double exact_solution(double x)
{
    return x * cos(x);
}

void Euler(benchmark::State& state){
    euler_scheme euler(state.range(0), heat_sources);
    for(auto _ : state)
        euler.get_result(0.0);
    state.SetComplexityN(state.range(0));
}

BENCHMARK(Euler)->RangeMultiplier(2)->Range(1024, 1024<<7)->Complexity(benchmark::oN);

void Runge(benchmark::State& state){
    runge_kutta_scheme runge(state.range(0), heat_sources);
    for(auto _ : state)
        runge.get_result(0.0);
    state.SetComplexityN(state.range(0));
}

BENCHMARK(Runge)->RangeMultiplier(2)->Range(1024, 1024<<7)->Complexity(benchmark::oN);

void Weight(benchmark::State& state){
    weight_scheme weight(state.range(0), heat_sources);
    for(auto _ : state)
        weight.get_result(0.0);
    state.SetComplexityN(state.range(0));
}

BENCHMARK(Weight)->RangeMultiplier(2)->Range(1024, 1024<<7)->Complexity(benchmark::oN);

void EulerCorrected(benchmark::State& state){
    euler_corrected_scheme euler_corrected(state.range(0), heat_sources);
    for(auto _ : state)
        euler_corrected.get_result(0.0);
    state.SetComplexityN(state.range(0));
}

BENCHMARK(EulerCorrected)->RangeMultiplier(2)->Range(1024, 1024<<7)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
