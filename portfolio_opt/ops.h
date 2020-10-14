
double mean(double rets[]);
double mean(double rets[][], double weights[]);

double var(double rets[]);
double var(double rets[][], double weights[]);

double std(double var);
double std(double rets[]);
double std(double rets[][], double weights[]);

double  cov(double rets1[], double rets2[]);
double* cov(double rets[][]);

double  corr(double rets1[], double rets2[]);
double* corr(double rets[][]);

double risk_premeum(double Er, double rf);
double risk_premeum(double rets[][], double weights[], double rf);

double ra_utility(double Er, double std, double A);
double ra_utility(double rets[][], double weights[], double A);

double CAL(double Er_p, double std_c, double std_p, double rf);
double CAL(double Er_p, double std_p, double y, double rf);
double CAL(double rets[][], double weights[],  double y, double rf);

double opt_y(double Er_p, double std_p, double rf, double A);
double opt_y(double rets[][], double weights[], double rf, double A);

double sharpe_ratio(double Er_p, double std_p, double rf);
double sharpe_ratio(double rets[][]. double weights[], double rf);

double beta(double var_m, double cov_im);
double beta(double betas[], double weights[]);
double beta(double rets[][], double weights[]);

double SML(double beta, double Er_m, double rf);
double SML(double Er_i, double Er_m, double var_m, double cov_im, double rf);
double SML(double rets_i[], rets_m[], double rf);
double SML(double rets_i[][]. double weights_i[], rets_m[], double rf);

double SIM(double alpha_i, double beta_i, RP_m, double e_i);
