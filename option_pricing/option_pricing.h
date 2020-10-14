#include <iostream>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <set>

using namespace std;

// Constants

unsigned char 
    QUIET = 0,
    INIT = 1,
    STEPS = 2,
    FINAL = 4,
    VERBOSE = 7
;

enum OptionKind {
    call=1,
    put=-1
};

unordered_map<string, OptionKind> OptionKindStringMap {
        {"call", call},
        {"put", put}
};

enum OptionStyle { 
    european=0, 
    american=1 
};

unordered_map<string, OptionStyle> OptionStyleStringMap {
        {"american", american},
        {"european", european}
};


// Classes
class OptionPricing
{
     private:

        void init(double S, double U, double D, double DeltaT, double *R);

        double      S;
        double      U;
        double      D;
        double      DeltaT;

        double      *R;

        double      K;

        unordered_map<OptionStyle, double> cache_;
        void  ClearCache();

        int Check();

        double Alpha1();
        double Alpha2();

        double Beta1(int step);
        double Beta2(int step);

        void PriceOptionHelper(OptionKind kind, OptionStyle style, double K, unsigned char opts);
        double PriceFuturesHelper(double K);
        
    public:
        OptionPricing(double S, double U, double D, double DeltaT, double *R);
        OptionPricing(double S, double U, double D, double DeltaT, double R);
        OptionPricing();
        ~OptionPricing();
        
        double      getS();
        double      getU();
        double      getD();
        double      getDeltaT();
        double*     getR();
        double     getR(int step);
        double      getK();

        void        setS(double val);
        void        setU(double val);
        void        setD(double val);
        void        setDeltaT(double val);
        void        setR(double *val);
        void        setK(double val);

        double BondRet(int step);

        double* StockPrice();
        double* BondPrice();

        double Price1(int step);
        double Price2(int step);

        double PriceSecurity(double a[], int step);

        double PriceOption(OptionKind kind, OptionStyle style, double K, unsigned char opts);
        double PriceOption(OptionKind kind, OptionStyle style, unsigned char opts);

        double PriceOption(OptionKind kind, OptionStyle style, double K);
        double PriceOption(OptionKind kind, OptionStyle style);

        double PriceFutures(double K);
        double PriceFutures();
};
