#include "SmartHomeSystem.h"
#include "SmartDevice.h"
#include <fstream>
#include <iostream>
#include <algorithm>

// Add a new device to the system
void SmartHomeSystem::AddDevice(unique_ptr<SmartDevice> device)
{
    devices.push_back(move(device));   //smart pointer transfter ownership safely.
}

// Show all devices
void SmartHomeSystem::ShowDevices() const
{
    if (devices.empty()) {
        cout << "No devices available.\n";
        return;
    }

    cout << "Smart Home Devices:\n";
    for (const auto& device : devices)
    {
        device->ViewInfo();
    }
}

// Interact with a specific device
void SmartHomeSystem::InteractWithDevice()
{
    int deviceID;
    cout << "Enter Device ID to interact with: ";
    cin >> deviceID;

    SmartDevice* device = GetDeviceByID(deviceID);
    if (!device)
    {
        cout << "Device not found!\n";
        return;
    }

    device->ViewInfo();
    if (!device->IsActive())
    {
        cout << "Device is inactive. Activate it first.\n";
        return;
    }

    device->InteractionEvent();
}

// Show all connected devices
void SmartHomeSystem::ShowConnectedDevices() const
{
    bool found = false;
    for (const auto& device : devices)
    {
        if (device->CheckConnection())
        {
            device->ViewInfo();
            cout << "-----------------------------------\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No connected devices.\n";
    }
}

// Show all disconnected devices
void SmartHomeSystem::ShowDisconnectedDevices() const
{
    bool found = false;
    for (const auto& device : devices)
    {
        if (!device->CheckConnection())
        {
            device->ViewInfo();
            cout << "-----------------------------------\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "No disconnected devices.\n";
    }
}

// Delete a device by its ID
void SmartHomeSystem::DeleteDevice(int ID)
{
    auto it = find_if(devices.begin(), devices.end(), [ID](const unique_ptr<SmartDevice>& device) 
        {
        return device->GetID() == ID;
        });

    if (it != devices.end())
    {
        devices.erase(it);
        cout << "Device deleted successfully.\n";
    }
    else
    {
        cout << "Device not found.\n";
    }
}

// Edit an existing device by its ID
void SmartHomeSystem::EditDevice(int ID)
{
    SmartDevice* device = GetDeviceByID(ID);
    if (!device)
    {
        cout << "Device not found!\n";
        return;
    }

    int choice;
    cout << "1. Change Name\n2. Change Manufacturer\n3. Change Status\n4. Change ID\nEnter your choice: ";
    cin >> choice;

    string name, manufacturer;
    bool status;
    int id;

    switch (choice)
    {
    case 1:
        cout << "Enter new device name: ";
        cin >> name;
        device->SetName(name);
        break;
    case 2:
        cout << "Enter new manufacturer: ";
        cin >> manufacturer;
        device->SetManufacturer(manufacturer);
        break;
    case 3:
        cout << "Enter new status (1 for Active, 0 for Inactive): ";
        cin >> status;
        device->SetStatus(status);
        break;
    case 4:
        cout << "Enter new ID: ";
        cin >> id;
        device->SetId(id);
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }
}

// Add a deleted device back to the system
void SmartHomeSystem::AddDeletedDevice(int deviceID, string deviceName, string manufacturer, bool status)
{
    unique_ptr<SmartDevice> restoredDevice = make_unique<SmartDevice>(deviceID, deviceName, manufacturer, status);
    devices.push_back(move(restoredDevice));
    cout << "Device re-added successfully.\n";
}

// Get a device by its ID
SmartDevice* SmartHomeSystem::GetDeviceByID(int ID)
{
    for (auto& device : devices)
    {
        if (device->GetID() == ID)
        {
            return device.get();
        }
    }
    return nullptr; // Return nullptr if device is not found
}

//ROOM MANAGEMENT//==================================//
// Add a room to the system
void SmartHomeSystem::AddRoom(string roomName)
{
    if (roomName.empty())
    {
        cout<<"Room name cannot be empty.\n";
    }
    rooms[roomName] = {};  // Create a new room
    cout << "Room added successfully.\n";
}

// Add a device to a specific room
void SmartHomeSystem::AddDeviceToRoom(int deviceId, string roomName)
{
    SmartDevice* device = GetDeviceByID(deviceId);
    if (device)
    {
        rooms[roomName].push_back(device);
        cout << "Device added to " << roomName << ".\n";
    }
    else
    {
        cout << "Device not found.\n";
    }
}

// Show all devices in a specific room
void SmartHomeSystem::ShowDevicesInRoom(string roomName) const
{
    if (rooms.find(roomName) == rooms.end())
    {
        cout << "Room not found.\n";
        return;
    }

    cout << "Devices in " << roomName << ":\n";
    for (const auto& device : rooms.at(roomName))
    {
        device->ViewInfo();
    }
}

// Activate all devices in a room
void SmartHomeSystem::ActivateAllDevicesInRoom(string roomName)
{
    if (rooms.find(roomName) == rooms.end())
    {
        cout << "Room not found.\n";
        return;
    }

    for (auto& device : rooms[roomName])
    {
        device->Activate();
    }
}

// Deactivate all devices in a room
void SmartHomeSystem::DeactivateAllDevicesInRoom(string roomName)
{
    if (rooms.find(roomName) == rooms.end())
    {
        cout << "Room not found.\n";
        return;
    }

    for (auto& device : rooms[roomName])
    {
        device->Deactivate();
    }
}

// Duplicate an existing room
void SmartHomeSystem::DuplicateRoom(string oldRoomName, string newRoomName)
{
    if (rooms.find(oldRoomName) == rooms.end())
    {
        cout << "Room not found.\n";
        return;
    }

    rooms[newRoomName] = rooms[oldRoomName];  // Copy devices to new room
    cout << "Room duplicated successfully.\n";
}

// Save the current devices to a file
void SmartHomeSystem::SaveToFile(string filename)
{
    ofstream file(filename);
    if (!file)
    {
        cout << "Error opening file.\n";
        return;
    }

    for (const auto& device : devices)
    {
        file << device->GetID() << " "
            << device->GetName() << " "
            << device->GetManufacturer() << " "
            << device->IsActive() << "\n";
    }

    cout << "Devices saved to file successfully.\n";
}

// Load devices from a file
void SmartHomeSystem::LoadFromFile(string filename)
{
    ifstream file(filename);  
    if (!file)   //enture the file exists before reading to prevent crashes.
    {
        cout << "Error opening file. File doesn't exist.\n";
        return;
    }

    int id;
    string name, manufacturer;
    bool status;
    while (file >> id >> name >> manufacturer >> status)
    {
        //use smartpointer to ensure no memory leaks during reallocation
        unique_ptr<SmartDevice> device = make_unique<SmartDevice>(id, name, manufacturer, status);
        devices.push_back(move(device));
    }

    cout << "Devices loaded from file successfully.\n";
}
