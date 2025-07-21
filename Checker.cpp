#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>
using namespace std;


struct Limit {
    string name;
    float minVal;
    float maxVal;
};


struct CheckResult {
    bool isOk;
    string param;
    string breachType; // "low" or "high"
};


CheckResult checkLimit(const Limit& limit, float value) {
    if (value < limit.minVal) {
        return {false, limit.name, "low"};
    }
    if (value > limit.maxVal) {
        return {false, limit.name, "high"};
    }
    return {true, "", ""};
}


CheckResult batteryIsOk(float temperature, float soc, float chargeRate) {
    
    static const Limit limits[] = {
        {"Temperature", 0, 45},
        {"State of Charge", 20, 80},
        {"Charge Rate", 0, 0.8}
    };

   
    float values[] = {temperature, soc, chargeRate};

    for (int i = 0; i < 3; i++) {
        CheckResult res = checkLimit(limits[i], values[i]);
        if (!res.isOk) {
            return res; 
        }
    }
    return {true, "", ""}; 
}


void printBatteryStatus(float temperature, float soc, float chargeRate) {
    CheckResult res = batteryIsOk(temperature, soc, chargeRate);
    if (res.isOk) {
        cout << "Battery is OK.\n";
    } else {
        cout << res.param << " out of range! Breach type: " << res.breachType << "\n";
    }
}


void runTests() {
    
    assert(batteryIsOk(25, 70, 0.7).isOk == true);

    
    assert(batteryIsOk(-1, 50, 0.7).isOk == false);
    assert(batteryIsOk(-1, 50, 0.7).breachType == "low");
    assert(batteryIsOk(46, 50, 0.7).isOk == false);
    assert(batteryIsOk(46, 50, 0.7).breachType == "high");

   
    assert(batteryIsOk(25, 19, 0.7).isOk == false);
    assert(batteryIsOk(25, 19, 0.7).breachType == "low");
    assert(batteryIsOk(25, 81, 0.7).isOk == false);
    assert(batteryIsOk(25, 81, 0.7).breachType == "high");

    
    assert(batteryIsOk(25, 70, 0.9).isOk == false);
    assert(batteryIsOk(25, 70, 0.9).breachType == "high");

   
    assert(batteryIsOk(0, 20, 0.8).isOk == true);
    assert(batteryIsOk(45, 80, 0.8).isOk == true);
}

int main() {
    runTests();

    printBatteryStatus(25, 70, 0.7); 
    printBatteryStatus(50, 85, 0);     
    printBatteryStatus(-5, 50, 0.5);   
    printBatteryStatus(25, 10, 0.5);   
    printBatteryStatus(25, 50, 0.9);  
    
    return 0;
}
