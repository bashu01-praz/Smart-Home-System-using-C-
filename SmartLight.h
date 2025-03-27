#pragma once
#include "SmartDevice.h"

class SmartLight : public SmartDevice 
{
private:
    int brightnessLevel;
    string colorType;
    string chosenColor;

public:
    // Constructor
    SmartLight(int id, string name, string manufacturer, bool status, int brightness, string color);

    //  Prevent Copying
    SmartLight(const SmartLight& other) = delete;
    SmartLight& operator=(const SmartLight& other) = delete;

    //  Allow Moving
    SmartLight(SmartLight&& other) noexcept = default;
    SmartLight& operator=(SmartLight&& other) noexcept = default;

    void InteractionEvent() override;
    bool CheckConnection() const override;
    void ViewInfo() const override;
};
