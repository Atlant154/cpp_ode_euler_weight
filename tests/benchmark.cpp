#include <benchmark/benchmark.h>
#include "../src/appr_scheme.h"

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
    auto euler = std::make_unique<euler_scheme>(state.range_x(), heat_sources);
    for(auto _ : state)
        euler -> get_result(0.0);
    state.SetComplexityN(state.range_x());
}

BENCHMARK(Euler)->RangeMultiplier(2)->Range(1024, 1024<<7)->Complexity(benchmark::oN);

void Runge(benchmark::State& state){
    auto runge = std::make_unique<runge_kutta_scheme>(state.range_x(), heat_sources);
    for(auto _ : state)
        runge -> get_result(0.0);
    state.SetComplexityN(state.range_x());
}

BENCHMARK(Runge)->RangeMultiplier(2)->Range(1024, 1024<<7)->Complexity(benchmark::oN);

void Weight(benchmark::State& state){
    auto weight = std::make_unique<weight_scheme>(state.range_x(), heat_sources);
    for(auto _ : state)
        weight -> get_result(0.0);
    state.SetComplexityN(state.range_x());
}

BENCHMARK(Weight)->RangeMultiplier(2)->Range(1024, 1024<<7)->Complexity(benchmark::oN);

BENCHMARK_MAIN();
