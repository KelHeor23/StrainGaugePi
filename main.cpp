#include <iostream>
#include "hx711/common.h"

#include <cmath>
#include <cstdlib>
#include <chrono>
#include <string>

using namespace HX711;
using namespace std;

std::size_t samples;
std::string unit;
double knownWeight;
Value zeroValue;
SimpleHX711* hx;

int main(int argc, char** argv)
{
    if(argc != 3) {
        cout << "Usage: hx711calibration [data pin] [clock pin]" << endl;
        return EXIT_FAILURE;
    }

    try {
        hx = new SimpleHX711(stoi(argv[1]), stoi(argv[2]), 1, 0);
    }
    catch(const GpioException& ex) {
        cerr << "Failed to connect to HX711 chip" << endl;
        return EXIT_FAILURE;
    }
    catch(const TimeoutException& ex) {
        cerr << "Failed to connect to HX711 chip" << endl;
        return EXIT_FAILURE;
    }

    //clear screen
    cout    << "\x1B[2J\x1B[H"

         //splash
         << "========================================" << endl
         << "HX711 Calibration" << endl
         << "========================================"
         << endl << endl
         << "Find an object you know the weight of. If you can't find anything, "
         << "try searching Google for your phone's specifications to find its weight. "
         << "You can then use your phone to calibrate your scale."
         << endl << endl

         //unit prompt
         << "1. Enter the unit you want to measure the object in (eg. g, kg, lb, oz): ";
    cin >> unit;
    cin.ignore();

    //known weight prompt
    cout    << endl
         << "2. Enter the weight of the object in the unit you chose (eg. "
         << "if you chose 'g', enter the weight of the object in grams): ";
    cin >> knownWeight;
    cin.ignore();

    //samples prompt
    cout    << endl
         << "3. Enter the number of samples to take from the HX711 chip (eg. 15): ";
    cin >> samples;
    cin.ignore();

    //tare prompt
    cout    << endl << "4. Remove all objects from the scale and then press enter.";
    cin.ignore();
    cout    << endl << "Working..." << flush;

    zeroValue = hx->read(Options(samples));

    //weigh prompt
    cout    << endl << endl << "5. Place object on the scale and then press enter.";
    cin.ignore();
    cout    << endl << "Working..." << flush;

    const double raw = hx->read(Options(samples));
    const double refUnitFloat = (raw - zeroValue) / knownWeight;
    Value refUnit = static_cast<Value>(round(refUnitFloat));
    delete hx;

    if(refUnit == 0) {
        refUnit = 1;
    }

    cout    << endl << endl
         << "Known weight (your object): " << knownWeight << unit << endl
         << "Raw value over " << samples << " samples: " << raw << endl
         << endl
         << "-> REFERENCE UNIT: " << refUnit << endl
         << "-> ZERO VALUE: " << zeroValue << endl
         << endl
         << "You can provide these values to the constructor when you create the "
         << "HX711 objects or later on. For example: " << endl
         << endl
         << "SimpleHX711 hx("
         << argv[1] << ", " << argv[2] << ", " << refUnit << ", " << zeroValue
         << ");" << endl
         << "OR" << endl
         << "hx.setReferenceUnit("
         << refUnit
         << "); and hx.setOffset("
         << zeroValue
         << ");" << endl
         << endl;

    return EXIT_SUCCESS;
}
