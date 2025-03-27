//Bashu Prajapati
//21244611

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "SmartDevice.h"
#include "SmartLight.h"
#include "Thermostat.h"
#include "SecurityCamera.h"
#include "SmartSpeaker.h"
#include "SmartHomeSystem.h"
#include "DeviceFactory.h"
#include <crtdbg.h> //memory leak detection

using namespace std;

void DisplayMenu()
{
	cout << "Bashu Prajapati\n21244611\n\n"; //Displaying my name and ID 
    cout << "====== Smart Home Automation System Menu ======\n";
    cout << "1. Show All Devices\n";
    cout << "2. Interact with Device\n";
    cout << "3. Add a new Device\n";
    cout << "4. Delete a Device\n";
    cout << "5. Edit a Device\n";
    cout << "6. Show Connected Devices\n";
    cout << "7. Show Disconnected Devices\n";
    cout << "8. Activate/Deactivate a Device\n";  
    cout << "9. Room Management\n";
    cout << "10. Load Devices from File\n";
	cout << "11. Save Devices to File\n";
    cout << "0. Exit\n";
    cout << endl;
    cout << "Please Enter your choice: ";
    
}

void RoomMenu(SmartHomeSystem& system)
{
    while (true)
    {
        cout << "\n=== Room Management ===\n";
        cout << "1. Add a new room\n";
        cout << "2. Add device to a room\n";
        cout << "3. View devices in a room\n";
        cout << "4. Activate all devices in a room\n";
        cout << "5. Deactivate all devices in a room\n";
        cout << "6. Duplicate a room\n";
        cout << "0. Return to main menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        string roomName, newRoom;
        int deviceId;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear the input buffer before taking string input
        cout << endl;
        switch (choice)
        {
        case 1:
            cout << "Adding a new room\n";
            cout << "Enter room name: ";
            getline(cin, roomName);  //use getline for string input to allow space.
			if (roomName.empty())
			{
				cout << "Room name cannot be empty. Please enter a valid room name.\n";
				break;
			}
            system.AddRoom(roomName);
            break;
        case 2:
			cout << "Adding device to a room\n";
            cout << "Enter device ID: ";
            cin >> deviceId;
            cout << "Enter room name: ";
            cin.ignore();  // Clear buffer before reading room name
            getline(cin, roomName);
            system.AddDeviceToRoom(deviceId, roomName);
            break;
        case 3:
			cout << "View devices in a room\n";
            cout << "Enter room name: ";
            cin.ignore();  // Clear buffer before reading room name
            getline(cin, roomName);
            system.ShowDevicesInRoom(roomName);
            break;
        case 4:
			cout << "Activate all devices in a room\n";
            cout << "Enter room name: ";
            cin.ignore();  // Clear buffer before reading room name
            getline(cin, roomName);
            system.ActivateAllDevicesInRoom(roomName);
            break;
        case 5:
			cout << "Deactivate all devices in a room\n";
            cout << "Enter room name: ";
            cin.ignore();  // Clear buffer before reading room name
            getline(cin, roomName);
            system.DeactivateAllDevicesInRoom(roomName);
            break;
        case 6:
			cout << "Duplicate a room\n";
            cout << "Enter existing room name to duplicate: ";
            cin.ignore();  // Clear buffer before reading room name
            getline(cin, roomName);
            cout << "Enter new room name: ";
            getline(cin, newRoom);
            system.DuplicateRoom(roomName, newRoom);
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}

// Show all devices
void ShowDevices(const vector<unique_ptr<SmartDevice>>& devices)
{
    cout << "\nSmart Home Devices:\n";
    for (const auto& device : devices)
    {
        device->ViewInfo();
        cout << endl;
    }
}

// Interact with a specific device
void InteractWithDevice(SmartHomeSystem& homeSystem)
{
    int deviceID;
    cout << "\nEnter Device ID to interact with: ";
    cin >> deviceID;

    SmartDevice* selectedDevice = homeSystem.GetDeviceByID(deviceID);
    if (!selectedDevice)
    {
        cout << "Device not found!\n";
        return;
    }

    // Show device details
    selectedDevice->ViewInfo();

    if (!selectedDevice->IsActive())
    {
        cout << "Device is inactive. Activate it first.\n";
        return;
    }

    // Proceed with interaction
    selectedDevice->InteractionEvent();
}

// Activate or Deactivate a Device
void ActivateDeactivateDevice(SmartHomeSystem& homeSystem)
{
    int deviceID;
    cout << "\nEnter Device ID: ";
    while (!(cin >> deviceID) || deviceID <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Please enter a Positive Integer: ";
    }

    SmartDevice* selectedDevice = homeSystem.GetDeviceByID(deviceID);
    if (!selectedDevice)
    {
        cout << "Device not found!\n";
        return;
    }

    // Ask user whether to activate or deactivate
    int action;
    cout << "1. Activate\n2. Deactivate\nEnter choice: ";
    cin >> action;

    if (action == 1)
    {
        selectedDevice->Activate();
        cout << "Device activated successfully!\n";
    }
    else if (action == 2)
    {
        selectedDevice->Deactivate();
        cout << "Device deactivated successfully!\n";
    }
    else
    {
        cout << "Invalid choice.\n";
    }
    cout << endl;
}

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Enable memory leak detection
    SmartHomeSystem homeSystem;
	homeSystem.LoadFromFile("devices.txt"); //if exists
    // Add devices using the DeviceFactory to create different device types
	//cout << "Bashu Prajapati\n21244611\n\n"; //Displaying the name and ID of the student
    cout << "Welcome to the Smart Home Automation System\n";

    homeSystem.AddDevice(DeviceFactory::CreateDevice(1, "SmartLight", "Living Room Light", "Philips", false));
    homeSystem.AddDevice(DeviceFactory::CreateDevice(2, "SecurityCamera", "Front Door Camera", "Sony", false));
    homeSystem.AddDevice(DeviceFactory::CreateDevice(3, "SmartSpeaker", "Kitchen Speaker", "Sonos", false));
    homeSystem.AddDevice(DeviceFactory::CreateDevice(4, "Thermostat", "Living Room Thermostat", "Honeywell", false));

    while (true)
    {
        DisplayMenu();

        int choice;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            cout << "Showing all devices\n====================\n";
            homeSystem.ShowDevices();
            break;
        case 2:
			cout << "Interacting with Device\n";
            homeSystem.InteractWithDevice();
            break;
        case 3:
        {
			cout << "Adding a New Device\n";
			cout << "=====================\n";
            int id;
            string name, manufacturer;
            bool devstatus;
            cout << "Enter device ID: ";
            while (!(cin >> id) || id <= 0) 
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid ID. Please enter a Positive Value: ";
            }

            cout << "Enter device name: ";  // Prompt the user to enter the device name

            cin.ignore();  // Clears any leftover newline character from previous input to avoid skipping getline()

            getline(cin, name);  // Reads the entire line as input, allowing spaces in the device name

            // Loop to ensure the user enters a non-empty name
            while (name.empty()) 
            {
                cout << "Device name cannot be empty. Enter again: ";  // Display an error message
                getline(cin, name);  // Read input again to get a valid device name
            }

			//Device Manufacturer
            cout << "Enter device brand/Manufacturer: ";
            cin.ignore();
            getline(cin, manufacturer);
            while (manufacturer.empty()) 
            {
                cout << "Manufacturer name cannot be empty. Enter again: ";
                getline(cin, manufacturer);
            }

            //Device Status
            cout << "Enter device status (1 for active, 0 for inactive): ";  // Prompt user to enter device status

            // Validate user input to ensure only 1 (active) or 0 (inactive) is accepted
            while (!(cin >> devstatus) || (devstatus != 0 && devstatus != 1)) 
            {
                cin.clear();   // Clear error state in case of invalid input (e.g., non-numeric input)
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input from buffer
                cout << "Invalid input. Enter 1 for active, 0 for inactive: ";  // Ask user to enter a valid input again
            }
            homeSystem.AddDevice(make_unique<SmartDevice>(id, name, manufacturer, devstatus));
			cout << "Device Added Successfully. Thank You for Adding.\n"; 
            cout << endl;//Displaying the message after adding the device
            break;
        }
        case 4:
        {
            cout << "Delete a device." << endl;
            int id;
            cout << "Enter device ID to delete: ";
            cin >> id;
            homeSystem.DeleteDevice(id);
            //cout << "Device Deleted Successfully!" << endl;
            cout << endl;
            break;
        }
        case 5:
        {
            cout << "Edit a device.\n";
            int id;
            cout << "Enter device ID to edit: ";
            cin >> id;
            homeSystem.EditDevice(id);
            cout << "Device Edited Successfully!" << endl;
            cout << endl;
            break;
        }
        case 6:
            cout << "Showing all connected devices\n====================\n";
            homeSystem.ShowConnectedDevices();
            break;
        case 7:
			cout << "Showing all disconnected devices\n====================\n";
            homeSystem.ShowDisconnectedDevices();
            break;

        case 8:
			cout << "Activate/Deactivate a Device\n";
            ActivateDeactivateDevice(homeSystem);
            cout << endl;
            break;

        case 9:
			system("cls");
            cout << "Smart Home Automation System\n";
            cout << "=============================\n";
            cout << "Room Management\n";
            RoomMenu(homeSystem);
            break;
        case 10:
        {
			cout << "Load Devices from File\n";
            string filename;
            cout << "Enter filename to load devices from: ";
            cin >> filename;
            homeSystem.LoadFromFile(filename);
            break;
        }
        case 11:
			cout << "Save Devices to File\n";
			homeSystem.SaveToFile("devices.txt");
            break;
        case 0:
			cout << "Thank you for using the Smart Home Automation System.\n";
            cout << "Exiting...BYE\n";
            return 0;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
