#ifndef MKRB_APPR_SCHEME_H
#define MKRB_APPR_SCHEME_H

#include <string>
#include <utility>
#include <vector>

class appr_scheme {
public:
    appr_scheme() = delete;
    virtual ~appr_scheme() = default;

    appr_scheme(unsigned h_num, double (*heat_sources)(double));

    virtual std::string get_scheme_name() const;

    virtual  std::vector<std::pair<double, double>> get_result(std::vector<double> bounds);

    double get_error(double (*exact_solution)(double)) const;

protected:
    std::vector<std::pair<double, double>> result;
    const double left_bound_ = 0.0;
    const double right_bound_ = 1.0;

    unsigned h_num_;
    double (*heat_sources_)(double);
    double h_;
};

class euler_scheme : public appr_scheme {
public:
    euler_scheme(unsigned h_num, double (*heat_sources)(double)) : appr_scheme(h_num, heat_sources) {};
    ~euler_scheme() override = default;
    std::vector<std::pair<double, double>> get_result(std::vector<double> bounds) override;
    std::string get_scheme_name() const override;
};

class runge_kutta_schene : public appr_scheme {

};


#endif
