#include<iostream>
#include"../ts_getters.cpp"

using namespace std;

int main() 
{

    cout << "CONST GETTER TEST: \n";
    ConstGetter<float> CGTest(0.25);
    cout << "Expected " << 0.25 << " Got: " << CGTest.getAt(5) << endl; 

    float *arrVal;
    arrVal = new float[3];
    arrVal[0] = 0.0;
    arrVal[1] = 0.25;
    arrVal[2] = 0.5;

    cout << "\n ARRAY GETTER TEST: \n";
    ArrayGetter<float> AGTest(arrVal);
    cout << "Expected " << 0.25 << " Got: " << AGTest.getAt(1) << endl; 

    map<int, float> mapVal;
    mapVal[0] = 0.0;
    mapVal[3] = 0.25;
    mapVal[5] = 0.5;

    cout << "\n MAP GETTER TEST: \n";
    MapGetter<float> MGTest(mapVal);
    cout << "Expected " << 0.25 << " Got: " << MGTest.getAt(4) << endl; 
    cout << "Expected " << 0.5 << " Got: " << MGTest.getAt(7) << endl; 

    cout << "\n FAST MAP GETTER TEST: \n";
    FastMapGetter<float> FMGTest(mapVal);
    cout << "Expected " << 0.25 << " Got: " << FMGTest.getAt(4) << endl; 
    cout << "Expected " << 0.5 << " Got: " << FMGTest.getAt(7) << endl; 

    return 0;
}
