#include "SecurityCamera.h"

#include "SecurityCamera.h"

// Constructor definition
SecurityCamera::SecurityCamera(int id, string name, string manuf, bool status, string quality, string power)
    : SmartDevice(id, name, manuf, status), cameraQuality(quality), powerSource(power) {}

void SecurityCamera::InteractionEvent()
{
    if (devstatus)
    {
        cout << "Now viewing camera: " << deviceName << " in " << cameraQuality << " quality.\n";
    }
    else
    {
        cout << "Device is inactive. Activate it first.\n";
    }
}

void SecurityCamera::ViewInfo() const
{
    SmartDevice::ViewInfo();
    cout << "Camera Quality: " << cameraQuality << endl;
    cout << "Power Source: " << powerSource << "\n";
    cout << endl;
    cout << "======================================" << endl;

}

bool SecurityCamera::CheckConnection() const
{
    return true;  // simulating successful connection.
}
