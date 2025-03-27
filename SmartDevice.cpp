#include "SmartDevice.h"

// Constructor - Initializes device attributes
SmartDevice::SmartDevice(int id, string name, string manuf, bool status)
    : deviceID(id), deviceName(move(name)), manufacturer(move(manuf)), devstatus(status) {}

// Activates the device
void SmartDevice::Activate() 
{
    devstatus = true;
    cout << deviceName << " is now active.\n";
}

// Deactivates the device
void SmartDevice::Deactivate() 
{
    devstatus = false;
    cout << deviceName << " is now inactive.\n";
}

// Displays device information
void SmartDevice::ViewInfo() const 
{
    cout << "Device ID: " << deviceID << endl;
    cout << "Name: " << deviceName << endl;
    cout << "Manufacturer: " << manufacturer << endl;
    cout << "Status: " << (devstatus ? "Active" : "Inactive") << endl;
}

// Defines interaction behavior (to be overridden in derived classes)
void SmartDevice::InteractionEvent() 
{
    cout << "Interacting with " << deviceName << ".\n";
}

// Simulates checking if the device is connected
bool SmartDevice::CheckConnection() const 
{
    return devstatus; // Assuming connection status is same as activation status
}
