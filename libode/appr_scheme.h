#ifndef MKRB_APPR_SCHEME_H
#define MKRB_APPR_SCHEME_H

#include <string>
#include <utility>
#include <vector>

class appr_scheme {
public:
    appr_scheme() = delete;

    virtual ~appr_scheme() = default;

    virtual std::string  get_scheme_name() const;

    virtual std::vector<std::pair<double, double>> get_result(double bound_value);

    double get_error(double (*exact_solution)(double)) const;

    void clear_result_vector();

    void write_to_file() const;

    void new_split(unsigned h_num);

protected:
    appr_scheme(unsigned h_num, double (*heat_sources)(double, double));

    std::vector<std::pair<double, double>> result;
    const double left_bound_ = 0.0;
    const double right_bound_ = 1.0;

    unsigned h_num_;

    double (*heat_sources_)(double, double);

    double h_;

    std::string scheme_name_;
};

class euler_scheme : public appr_scheme {
public:
    euler_scheme(unsigned h_num, double (*heat_sources)(double, double));

    ~euler_scheme() override = default;

    std::vector<std::pair<double, double>> get_result(double boud_value) override;

    std::string get_scheme_name() const override;
};

class euler_corrected_scheme : public appr_scheme {
public:
    euler_corrected_scheme(unsigned h_num, double (*heat_sources)(double, double));

    ~euler_corrected_scheme() override = default;

    std::vector<std::pair<double, double>> get_result(double bound_value) override;

    std::string get_scheme_name() const override;
};

class runge_kutta_scheme : public appr_scheme {
public:
    runge_kutta_scheme(unsigned h_num, double (*heat_sources)(double, double));

    ~runge_kutta_scheme() override = default;

    std::vector<std::pair<double, double>> get_result(double bound_value) override;

    std::string get_scheme_name() const override;
};

class weight_scheme : public appr_scheme {
public:
    weight_scheme(unsigned h_num, double (*heat_sources)(double, double));

    ~weight_scheme() override = default;

    std::vector<std::pair<double, double>> get_result(double bound_value) override;

    std::string get_scheme_name() const override;
};

class adams_scheme : public appr_scheme {
public:
    adams_scheme(unsigned h_num, double (*heat_sources)(double, double));

    ~adams_scheme() override = default;

    std::vector<std::pair<double, double>> get_result(double bound_value) override;

    std::string get_scheme_name() const override;
};

#endif
