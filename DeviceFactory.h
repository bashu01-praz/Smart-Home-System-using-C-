#pragma once
#include "SmartDevice.h"
#include "SmartLight.h"
#include "SecurityCamera.h"
#include "SmartSpeaker.h"
#include "Thermostat.h"


//Logic is to centralise device creation in a single place, so that we can easily add new devices in the future.
//avoids repetition and load in main().

class DeviceFactory  //since our function is static, the implementation is already included within the header file itself.
{
public:
    // Static method to create a device based on the type provided
    static unique_ptr<SmartDevice> CreateDevice(int id, const string& type, const string& name, const string& manufacturer, bool status) {
        // Checking the device type and returning the appropriate device
        if (type == "SecurityCamera")
        {
            return make_unique<SecurityCamera>(id, name, manufacturer, status, "1080p", "Battery-Operated");
        }

        else if (type == "SmartLight")
        {
            return make_unique<SmartLight>(id, name, manufacturer, status, 60, "Warm White");
        }
        else if (type == "SmartSpeaker")
        {
            return make_unique<SmartSpeaker>(id, name, manufacturer, status, 50, "Pompeii");
        }
        else if (type == "Thermostat")
        {
            return make_unique<Thermostat>(id, name, manufacturer, status, 22.0);
        }
        return nullptr;  // If the device type is invalid, return nullptr
    }
};

