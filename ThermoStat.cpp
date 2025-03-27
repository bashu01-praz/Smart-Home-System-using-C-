#include "Thermostat.h"
#include <iostream>

using namespace std;

// Constructor with status fix
Thermostat::Thermostat(int id, string name, string manuf, bool status, double temp)
    : SmartDevice(id, name, manuf, status), targetTemperature(temp) {}

void Thermostat::InteractionEvent()
{
    if (IsActive())  // Use getter instead of direct `devstatus` access
    {
        cout << "Enter target temperature: ";
        cin >> targetTemperature;

        // Ensure temperature is within a reasonable range
        if (targetTemperature < 10) targetTemperature = 10;
        if (targetTemperature > 30) targetTemperature = 30;

        cout << "Target Temperature set to: " << targetTemperature << "°C" << endl;
    }
    else
    {
        cout << "Activate the Thermostat first." << endl;
    }
}

void Thermostat::ViewInfo() const
{
    SmartDevice::ViewInfo();
    cout << "Target Temperature: " << targetTemperature << "°<degrees> C" << endl;
    cout << endl;
    cout << "======================================" << endl;

}

bool Thermostat::CheckConnection() const
{
    // Simulate a connection check
    return true;
}
