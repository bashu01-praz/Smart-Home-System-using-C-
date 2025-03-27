#pragma once

#include <iostream>
#include <string>
using namespace std;

class SmartDevice //base class
{
protected: //protected, private (encapsulation applied) 
    int deviceID;
    string deviceName;
    string manufacturer;
    bool devstatus;

public:
    // Constructor
    SmartDevice(int id, string name, string manuf, bool status);

    // Encapulation & Memory Safety: Prevent Copying of SmartDevice to ensure safe ownership with unique_ptr
    SmartDevice(const SmartDevice& other) = delete;
    SmartDevice& operator=(const SmartDevice& other) = delete;

    //  Allow Moving of SmartDevice for efficient transfer of ownership
    SmartDevice(SmartDevice&& other) noexcept = default;
    SmartDevice& operator=(SmartDevice&& other) noexcept = default;

    //  Destructor
    virtual ~SmartDevice() {}

    // Getter Methods
    int GetID() const { return deviceID; }
    string GetName() const { return deviceName; }
    string GetManufacturer() const { return manufacturer; }
    bool GetStatus() const { return devstatus; }
    bool IsActive() const { return devstatus; }   

    //  Setter Methods
    void SetId(int id) { deviceID = id; }
    void SetName(string name) { deviceName = name; }
    void SetManufacturer(string manuf) { manufacturer = manuf; }
    void SetStatus(bool status) { devstatus = status; }

    // Virtual Methods
    virtual void Activate();
    virtual void Deactivate();
    virtual void ViewInfo() const;
    virtual void InteractionEvent();
    virtual bool CheckConnection() const;
};
