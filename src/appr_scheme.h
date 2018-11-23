#ifndef MKRB_APPR_SCHEME_H
#define MKRB_APPR_SCHEME_H

#include <string>
#include <utility>
#include <vector>

class appr_scheme {
public:
    appr_scheme() = default;
    ~appr_scheme() = default;

    std::string get_scheme_name() const;

    double get_error(double (*exact_solution)(double)) const;

protected:
    std::vector<std::pair<double, double>> result;
    double (*heat_sources_)(double);
    const double left_bound_ = 0.0;
    const double right_bound_ = 1.0;

    const std::string scheme_name;

    unsigned h_num_;
    double h_;
};

class euler_scheme : public appr_scheme {
public:
    explicit euler_scheme(unsigned h_num, double (*heat_sources)(double));
    std::vector<std::pair<double, double>> get_result(double bound_value);
private:
    const std::string scheme_name = "Euler scheme.";
};


#endif
