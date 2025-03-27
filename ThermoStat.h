#pragma once
#include "SmartDevice.h"

class Thermostat : public SmartDevice 
{
private:
    double targetTemperature;

public:
    // Constructor
    Thermostat(int id, string name, string manuf, bool status, double temp);

    // Prevent Copying
    Thermostat(const Thermostat& other) = delete;
    Thermostat& operator=(const Thermostat& other) = delete;

    // Allow Moving
    Thermostat(Thermostat&& other) noexcept = default;
    Thermostat& operator=(Thermostat&& other) noexcept = default;

    void InteractionEvent() override;
    bool CheckConnection() const override;
    void ViewInfo() const override;
};
