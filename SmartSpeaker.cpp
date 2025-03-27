#include "SmartSpeaker.h"
#include <iostream>

SmartSpeaker::SmartSpeaker(int id, string name, string manufacturer, bool status, int volume, string song)
    : SmartDevice(id, move(name), move(manufacturer), status), volumeLevel(volume), currentSong(move(song)) {}

void SmartSpeaker::ViewInfo() const
{
    SmartDevice::ViewInfo();
    cout << "Volume Level: " << volumeLevel << endl;
    cout << "Current Song: " << currentSong << endl;
    cout << endl;
    cout << "======================================" << endl;

}

bool SmartSpeaker::CheckConnection() const
{
    return true;  // Assume always connected.
}

void SmartSpeaker::InteractionEvent()
{
    if (IsActive())
    {
        int choice;
        cout << "1. Change Volume\n2. Change Song\n3. Enter your Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int newVolume;
            cout << "Enter new volume level: ";
            cin >> newVolume;
            volumeLevel = newVolume;
            cout << "Volume level changed to " << volumeLevel << endl;
        }
        if (choice == 2)
        {
            string newSong;
            cout << "Enter new song: ";
            cin >> newSong;
            currentSong = newSong;
            cout << "Song changed to " << currentSong << endl;
        }
    }
}
