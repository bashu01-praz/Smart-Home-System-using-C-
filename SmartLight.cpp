#include "SmartLight.h"
#include <iostream>

using namespace std;

SmartLight::SmartLight(int id, string name, string manufacturer, bool status, int brightness, string color)
    : SmartDevice(id, move(name), move(manufacturer), status), brightnessLevel(brightness), colorType(move(color))
{
    if (brightnessLevel < 0) brightnessLevel = 0;
    if (brightnessLevel > 100) brightnessLevel = 100;

    if (colorType != "Warm White" && colorType != "Cool White" && colorType != "RGB")
    {
        colorType = "Warm White";
    }
}

void SmartLight::ViewInfo() const
{
    SmartDevice::ViewInfo();
    cout << "Brightness Level: " << brightnessLevel << endl;
    cout << "Colour Type: " << colorType << endl;
    cout << endl;
    cout << "======================================" << endl;

    if (colorType == "RGB")
    {
        cout << "  Selected RGB Colour: " << (chosenColor.empty() ? "None" : chosenColor) << endl;
    }
}

void SmartLight::InteractionEvent()
{
    if (IsActive())  // Use IsActive() to check if device is active
    {
        int choice;
        cout << "1. Change Brightness\n2. Change Colour (RGB Mode Only)\n3. Enter your Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Change Brightness" << endl;
            int newBrightness;
            cout << "Enter new brightness level (0 - 100): ";
            cin >> newBrightness;

            if (newBrightness < 0) newBrightness = 0;
            if (newBrightness > 100) newBrightness = 100;
            cout << endl;
            brightnessLevel = newBrightness;
            cout << "Brightness level changed to " << brightnessLevel <<" lumen(lux)."<< endl;
            cout << endl;
        }
        else if (choice == 2 && colorType == "RGB")
        {
            cout << "Change Colour (RBG ONLY)" << endl;
            string newColor;
            cout << "Enter new RGB color (e.g., Red, Green, Blue): ";
            cin >> newColor;

            chosenColor = newColor;  // Fix: Set chosenColor instead of colorType
            cout << "Colour changed to " << newColor << endl;
        }
        else
        {
            cout << "Invalid Colour Choice!\n";
        }
    }
    else
    {
        cout << "Device is inactive. Activate it first.\n";
    }
}

bool SmartLight::CheckConnection() const
{
    return SmartDevice::CheckConnection() && brightnessLevel > 0 && IsActive(); // Fix: Added IsActive check
}
