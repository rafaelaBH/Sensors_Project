#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include "Controller.h"

using namespace std;

// Fluctuating sensors
class FluctuatingTemperatureSensor : public TemperatureSensor {
public:
    void readValue() override {
        try {
            static random_device rd;
            static mt19937 gen(rd());
            uniform_real_distribution<> dis(-5.0, 5.0);
            setValue(25.0 + dis(gen));
        } catch (...) {} // catch everything to prevent thread termination
    }
};

class FluctuatingHumiditySensor : public HumiditySensor {
public:
    void readValue() override {
        try {
            static random_device rd;
            static mt19937 gen(rd());
            uniform_real_distribution<> dis(-20.0, 20.0);
            setValue(50.0 + dis(gen));
        } catch (...) {}
    }
};

int main() {
    cout << "--- Starting stress test ---\n";

    Controller ctrl(5, 5);

    // Start threads before doing replacements
    ctrl.runSensorThreads();
    ctrl.startMainThread();

    // Let sensors run for 1 second to stabilize
    this_thread::sleep_for(chrono::seconds(1));

    // Safe replacement mid-run
    cout << "--- Replacing temp sensor 1 mid-run ---\n";
    ctrl.replaceSensor(0, 0, 26.0);

    cout << "--- Replacing humidity sensor 5 mid-run ---\n";
    ctrl.replaceSensor(4, 9, 48.0);

    // Let the system run for 5 more seconds
    this_thread::sleep_for(chrono::seconds(5));

    cout << "--- Stopping all threads ---\n";
    ctrl.stopThreads();

    cout << "Stress test completed successfully.\n";
    return 0;
}
