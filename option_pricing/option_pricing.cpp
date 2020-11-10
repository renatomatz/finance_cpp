#include <iostream>

#include"option_pricing.h"

// Constructor
void OptionPricing::init(double S, 
                         OptionPricing::FloatGetter U, 
                         OptionPricing::FloatGetter D, 
                         double DeltaT, 
                         OptionPricing::FloatGetter R)
{
    this->setS(S);
    this->setU(U);
    this->setD(D);
    this->setDeltaT(DeltaT);
    this->setR(R);
}
OptionPricing::OptionPricing(double S, 
                             OptionPricing::FloatGetter U, 
                             OptionPricing::FloatGetter D, 
                             double DeltaT, 
                             OptionPricing::FloatGetter R)
{
    this->init(S, U, D, DeltaT, R);
}
OptionPricing::~OptionPricing()
{
    delete this->U;
    delete this->D;
    delete this->R;
}

// Base Asset Coefficients
double OptionPricing::Alpha1(int step)
{
    return -1/(this->getS()*(this->getU(step) - this->getD(step)));
}
double OptionPricing::Alpha2(int step)
{
    return -this->Alpha1(step);
}
double OptionPricing::Beta1(int step)
{
    return (this->BondRet(step)*this->getU(step))/(this->getU(step) - this->getD(step));
}
double OptionPricing::Beta2(int step)
{
    return -(this->BondRet(step)*this->getD(step))/(this->getU(step) - this->getD(step));
}

// Getters
double OptionPricing::getS()
{
    return S;
}
double OptionPricing::getU(int step)
{
    return U->getAt(step);
}
double OptionPricing::getD(int step)
{
    return D->getAt(step);
}
double OptionPricing::getDeltaT()
{
    return DeltaT;
}
double OptionPricing::getR(int step)
{
    return R->getAt(step);
}
double OptionPricing::getK()
{
    return K;
}

// Setters
void OptionPricing::setS(double val)
{
    S = val;
}
void OptionPricing::setU(OptionPricing::FloatGetter val)
{
    U = val;
}
void OptionPricing::setD(OptionPricing::FloatGetter val)
{
    D = val;
}
void OptionPricing::setDeltaT(double val)
{
    DeltaT = val;
}
void OptionPricing::setR(OptionPricing::FloatGetter val)
{
    R = val;
}
void OptionPricing::setK(double val)
{
    K = val;
}

// Basic Returns
double OptionPricing::BondRet(int step)
{
    return exp(-this->getR(step)*this->getDeltaT());
}

// Stock Prices
double * OptionPricing::StockPrice()
{
    double *currStep, *nextStep;
    int steps;

    steps = int(round(1/this->getDeltaT()));

    currStep = new double[1];
    currStep[0] = this->getS();

    for (int i = 0; i < steps; i++) {

        nextStep = new double[i+2];

        for (int j = 0; j <= i; j++) {
            nextStep[j] = currStep[j]*this->getU(i);
        }

        nextStep[i+1] = currStep[i]*this->getD(i);

        delete[] currStep;
        currStep = nextStep;

    }

    return currStep;
}
double * OptionPricing::BondPrice() 
{ 
    double *bondPrices;
    int steps;

    steps = int(round(1/this->getDeltaT()));

    bondPrices = new double[steps+1];
    fill_n(bondPrices, steps+1, 1.0);

    return bondPrices; 
}

// Returns

double OptionPricing::Price1(int step)
{
    //return this->Alpha1()*this->StockPrice() + this->Beta1()*this->BondPrice();
    return (exp(-this->getR(step)*this->getDeltaT())*this->getU(step)-1)/(this->getU(step)-this->getD(step));
}
double OptionPricing::Price2(int step)
{
    // return this->Alpha2()*this->StockPrice() + this->Beta2()*this->BondPrice();
    return (1-exp(-this->getR(step)*this->getDeltaT())*this->getD(step))/(this->getU(step)-this->getD(step));
}

double OptionPricing::PriceSecurity(double a[], int step)
{
    return a[0]*this->Price1(step) + a[1]*this->Price2(step);
}

// Pricing Helpers
void OptionPricing::PriceOptionHelper(OptionKind kind, OptionStyle style, double K, unsigned char opts)
{
    double *currStock, *currEU, *currAM,
           *prevStock, *prevEU, *prevAM,
           exNow, exLat;
    int steps;
    set<int, greater<int>> exSteps;

    steps = int(round(1/this->getDeltaT()));

    currStock = this->StockPrice();
    
    currEU = new double[steps+1];
    currAM = new double[steps+1];
    for (int i = 0; i <= steps; i++) {
        currEU[i] = fmax(kind*((currStock[i])-K), 0);
        currAM[i] = fmax(kind*((currStock[i])-K), 0);
    }
    exSteps.insert(steps);

    if ((opts&INIT)==INIT) {

        cout << "INIT VALS";

        cout << "\nINIT STOCK PRICES: " << endl;
        for (int k = 0; k <= steps; k++)
            cout << currStock[k] << ", ";

        cout << "\nINIT EU OPTION PRICES: " << endl;
        for (int k = 0; k <= steps; k++)
            cout << currEU[k] << ", ";

        cout << "\nINIT AM OPTION PRICES: " << endl;
        for (int k = 0; k <= steps; k++)
            cout << currAM[k] << ", ";

    }

    for (int i = steps; i > 0; i--) {

        prevStock = new double[i];
        prevEU = new double[i];
        prevAM = new double[i];

        for (int j = 0; j < i; j++) {

            prevStock[j] = currStock[j]/this->getU(i);
            prevEU[j] = this->Price2(i-1)*currEU[j]+this->Price1(i-1)*currEU[j+1];

            exNow = kind*(prevStock[j]-K);
            exLat = this->Price2(i-1)*currAM[j]+this->Price1(i-1)*currAM[j+1];

            prevAM[j] = fmax(fmax(prevEU[j], exNow), exLat);
            if (exNow == prevAM[j]) 
                exSteps.insert(i-1);

        }

        if ((opts&STEPS)==STEPS) {

            cout << "\n\n" << i-1 << "DT RESULTS:" << endl;

            cout << "STOCK PRICES: " << endl;
            for (int k = 0; k < i; k++)
                cout << prevStock[k] << ", ";

            cout << "\nEU OPTION PRICES: " << endl;
            for (int k = 0; k < i; k++)
                cout << prevEU[k] << ", ";

            cout << "\nAM OPTION PRICES: " << endl;
            for (int k = 0; k < i; k++)
                cout << prevAM[k] << ", ";

        }

        delete[] currStock;
        delete[] currEU;
        delete[] currAM;

        currStock = prevStock;
        currEU = prevEU;
        currAM = prevAM;

    }

    if ((opts&FINAL)==FINAL) {

        cout << "\n\n\b FINAL RESULTS:" << endl;
        cout << "EUROPEAN OPTION PRICE: " << currEU[0] << endl;
        cout << "AMERICAN OPTION PRICE: " << currAM[0]
             << "\tEXERCISED ON " << "DT: {";

        set <int, greater<int>> :: iterator stepItr;
        for (stepItr = exSteps.begin(); stepItr != exSteps.end(); ++stepItr)
            cout << *stepItr << ", ";

        cout << "}\n\n";

    }

    this->cache_[european] = currEU[0];
    this->cache_[american] = currAM[0];

    delete[] currStock;
    delete[] currEU;
    delete[] currAM;

}
double OptionPricing::PriceFuturesHelper(double K)
{
    return 1.0;
}

// Asset Pricing

double OptionPricing::PriceOption(OptionKind kind, OptionStyle style, double K, unsigned char opts)
{
    this->PriceOptionHelper(kind, style, K, opts);
    return this->cache_[style];
}
double OptionPricing::PriceOption(OptionKind kind, OptionStyle style, unsigned char opts)
{
    if (this->cache_.find(style) == this->cache_.end()) {
        this->PriceOptionHelper(kind, style, this->K, opts);
    }

    return this->cache_[style];
}
double OptionPricing::PriceOption(OptionKind kind, OptionStyle style, double K)
{
    return this->PriceOption(kind, style, K, QUIET);
}
double OptionPricing::PriceOption(OptionKind kind, OptionStyle style)
{
    return this->PriceOption(kind, style, this->K, QUIET);
}

double OptionPricing::PriceFutures()
{
    return this->PriceFuturesHelper(this->K);
}
double OptionPricing::PriceFutures(double K)
{
    return this->PriceFuturesHelper(K);
}
