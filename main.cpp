#include <iostream>
#include "hx711/common.h"

int main()
{
    /*startWiringPi();

    pinMode(5, INPUT);
    pullUpDnControl(5, PUD_DOWN);

    while (true) {
        if (digitalRead(5) == HIGH)
            std::cout << "active" << std::endl;
    }*/

    using namespace HX711;
    using std::chrono::seconds;

    AdvancedHX711 hx(2, 3, -370, -367471, Rate::HZ_80);

    // constantly output weights using the median of all samples
    // obtained within 1 second
    for(;;) std::cout << hx.weight(seconds(1)) << std::endl; //eg. 0.03 g

    return 0;
}
