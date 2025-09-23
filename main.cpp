#include <iostream>
#include <wiringPi.h>

using namespace std;

void startWiringPi()
{
    if (wiringPiSetup() == -1) {
        std::cerr << "Ошибка инициализации WiringPi." << std::endl;
        return;
    }
}

int main()
{
    startWiringPi();
    pinMode(5, INPUT);
    pullUpDnControl(5, PUD_DOWN);

    while (true) {
        if (digitalRead(5) == HIGH)
            std::cout << "active" << std::endl;
    }
    cout << "Hello World!" << endl;
    return 0;
}
