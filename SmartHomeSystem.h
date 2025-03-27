
#pragma once
#include "SmartDevice.h"
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <fstream>  // For file operations
#include <unordered_map>

class SmartHomeSystem // manages all devices and rooms in the system
    //central manager class.
{
private:
    // Collection of unique pointers to SmartDevice objects, uniquw point vector automatic memory clean up when system shuts down.
    vector<unique_ptr<SmartDevice>> devices;

    // Rooms with devices (a map where the room name is the key, and the devices are stored in a vector)
    map<string, vector<SmartDevice*>> rooms;

//private:
//    unordered_map<string, vector<shared_ptr<SmartDevice>>>rooms;

public:
    SmartHomeSystem(){}

    //Prevent accidenta; copying of the entire SmartHomeSystem.
	SmartHomeSystem(const SmartHomeSystem& other) = delete;
	SmartDevice& operator=(const SmartHomeSystem& other) = delete;
    // Add a new device to the system
    void AddDevice(unique_ptr<SmartDevice> device);

    // Show all devices in the system
    void ShowDevices() const;

    // Interact with a specific device
    void InteractWithDevice();

    // Show all connected devices
    void ShowConnectedDevices() const;

    // Show all disconnected devices
    void ShowDisconnectedDevices() const;

    // Delete a device by its ID
    void DeleteDevice(int ID);

    // Edit an existing device by its ID
    void EditDevice(int ID);

    // Add a deleted device back to the system
    void AddDeletedDevice(int deviceID, string deviceName, string manufacturer, bool status);

    // Get a device by its ID
    SmartDevice* GetDeviceByID(int ID);

    // Add a device to a specific room
    void AddDeviceToRoom(int deviceId, string roomName);

    // Add a room to the system
    void AddRoom(string roomName);

    // Show all devices in a specific room
    void ShowDevicesInRoom(string roomName) const;

    // Activate all devices in a room
    void ActivateAllDevicesInRoom(string roomName);

    // Deactivate all devices in a room
    void DeactivateAllDevicesInRoom(string roomName);

    // Duplicate an existing room
    void DuplicateRoom(string oldRoomName, string newRoomName);

    // Save the current devices to a file
    void SaveToFile(string filename);

    // Load devices from a file
    void LoadFromFile(string filename);
};

