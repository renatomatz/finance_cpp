#include <iostream>
#include "../option_pricing.h"

using namespace std;

int main(int argc, char* argv[])
{
    /*
     * TEST 1
     */

    cout << "SLIDES TEST \n\n";

    ConstGetter<float> U1(1.1);
    ConstGetter<float> D1(0.9);
    ConstGetter<float> R1(0.0);

    OptionPricing option1(100, &U1, &D1, 1.0, &R1);

    cout << "p1: \n"
        << "\tResult: " << option1.Price1(0) << '\n'
        << "\tCorrect: " << 0.5 << '\n';

    cout << "p2: \n"
        << "\tResult: " << option1.Price2(0) << '\n'
        << "\tCorrect: " << 0.5 << '\n';

    double *states1;
    states1 = option1.StockPrice();

    cout << "Stock Price States: \n" 
        << "\tResult: " << states1[0] << ", " << states1[1]  << '\n'
        << "\tCorrect: " << "110, 90" << '\n';                       

    delete[] states1;

    cout << "european call K=100: \n" 
        << "\tResult: " << option1.PriceOption(call, european,  100.0) << '\n'
        << "\tCorrect: " << 5 << '\n';                       
                                                             
    cout << "european put K=100: \n"                         
        << "\tResult: " << option1.PriceOption(put, european, 100.0) << '\n'
        << "\tCorrect: " << 5 << '\n';                       
                                                             
    cout << "american call K=90: \n"                         
        << "\tResult: " << option1.PriceOption(call, american,  90.0) << '\n'
        << "\tCorrect: " << 10 << '\n';                       
                                                             
    cout << "american put K=110: \n"                         
        << "\tResult: " << option1.PriceOption(put, american, 110.0) << '\n'
        << "\tCorrect: " << 10 << '\n';

    /*
     * TEST 2
     */

    cout << "\nEXCEL TEST \n\n";

    ConstGetter<float> U2(1.05);
    ConstGetter<float> D2(1/1.05);
    ConstGetter<float> R2(0.02);

    OptionPricing option2(100, &U2, &D2, 1.0, &R2);

    cout << "p1: \n"
        << "\tResult: " << option2.Price1(0) << '\n'
        << "\tCorrect: " << 0.40517016 << '\n';

    cout << "p2: \n"
        << "\tResult: " << option2.Price2(0) << '\n'
        << "\tCorrect: " << 0.58487967 << '\n';

    double *states2;
    states2 = option2.StockPrice();

    cout << "Stock Price States: \n" 
        << "\tResult: " << states2[0] << ", " << states2[1]  << ", " << states2[2] << '\n'
        << "\tCorrect: " << "110.25, 100, 90.7029478" << '\n';                       

    delete[] states2;

    cout << "european call K=110: \n" 
        << "\tResult: " << option2.PriceOption(call, european,  110.0) << '\n'
        << "\tCorrect: " << 0.08552106 << '\n';                       
                                                             
    cout << "european put K=110: \n"                         
        << "\tResult: " << option2.PriceOption(put, european, 110.0) << '\n'
        << "\tCorrect: " << 7.90737512 << '\n';                       
                                                             
    cout << "american call K=110: \n"                         
        << "\tResult: " << option2.PriceOption(call, american,  110.0) << '\n'
        << "\tCorrect: " << 0.08552106 << '\n';                       
                                                             
    cout << "american put K=110: \n"                         
        << "\tResult: " << option2.PriceOption(put, american, 110.0) << '\n'
        << "\tCorrect: " << 10 << '\n';


    return 0;
}
