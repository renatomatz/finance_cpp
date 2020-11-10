#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

double mean(VectorXd rets);
double mean(MatrixXd rets, VectorXd weights);

double var(VectorXd rets);
double var(MatrixXd rets, VectorXd weights);

double std(double var);
double std(VectorXd rets);
double std(MatrixXd rets, VectorXd weights[]);

double  cov(VectorXd rets1, VectorXd rets2);
double* cov(MatrixXd rets);

double  corr(VectorXd rets1, VectorXd rets2);
double* corr(MatrixXd rets);

double risk_premeum(double Er, double rf);
double risk_premeum(MatrixXd rets, VectorXd weights, double rf);

double ra_utility(double Er, double std, double A);
double ra_utility(MatrixXd rets, VectorXd weights, double A);

double CAL(double Er_p, double std_c, double std_p, double rf);
double CAL(double Er_p, double std_p, double y, double rf);
double CAL(MatrixXd rets, VectorXd weights,  double y, double rf);

double opt_y(double Er_p, double std_p, double rf, double A);
double opt_y(MatrixXd rets, VectorXd weights, double rf, double A);

double sharpe_ratio(double Er_p, double std_p, double rf);
double sharpe_ratio(MatrixXd rets. VectorXd weights, double rf);

double beta(double var_m, double cov_im);
double beta(VectorXd betas, VectorXd weights);
double beta(MatrixXd rets, VectorXd weights);

double SML(double beta, double Er_m, double rf);
double SML(double Er_i, double Er_m, double var_m, double cov_im, double rf);
double SML(VectorXd rets_i, VectorXd rets_m, double rf);
double SML(MatrixXd rets_i. VectorXd weights_i, VectorXd rets_m, double rf);

double SIM(double alpha_i, double beta_i, RP_m, double e_i);

double two_stock_min_var(double var_1, double var_2, double cov);
double two_stock_min_var(VectorXd rets1, VectorXd rets2);

double two_stock_max_sharpe(double Er_1, double Er_2, double rf, double var_1, double var_2, double cov);
double two_stock_max_sharpe(VectorXd rets1, VectorXd rets2, double rf);
