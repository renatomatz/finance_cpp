#pragma once

#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <set>

#include "ts_getters.h"

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
struct OptionPricing
{

 typedef _TSGetter<float> *FloatGetter;

 private:

    void init(double S, FloatGetter U, FloatGetter D, double DeltaT, FloatGetter R);

    double          S;
    FloatGetter     U;
    FloatGetter     D;
    double          DeltaT;
    FloatGetter     R;
    double          K;

    unordered_map<OptionStyle, double> cache_;
    void  ClearCache();

    int Check();

    double Alpha1(int step);
    double Alpha2(int step);

    double Beta1(int step);
    double Beta2(int step);

    void PriceOptionHelper(OptionKind kind, OptionStyle style, double K, unsigned char opts);
    double PriceFuturesHelper(double K);
    
public:

    OptionPricing(double S, FloatGetter U, FloatGetter D, double DeltaT, FloatGetter R);
    OptionPricing();
    ~OptionPricing();
    
    double      getS();
    double      getU(int step);
    double      getD(int step);
    double      getR(int step);
    double      getDeltaT();
    double      getK();

    void        setS(double val);
    void        setU(FloatGetter val);
    void        setD(FloatGetter val);
    void        setDeltaT(double val);
    void        setR(FloatGetter val);
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
