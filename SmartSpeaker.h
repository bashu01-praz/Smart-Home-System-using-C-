#pragma once
#include "SmartDevice.h"

class SmartSpeaker : public SmartDevice 
{
private:
    int volumeLevel;
    string currentSong;

public:
    // Constructor
    SmartSpeaker(int id, string name, string manufacturer, bool status, int volume, string song);

    //  Prevent Copying
    SmartSpeaker(const SmartSpeaker& other) = delete;
    SmartSpeaker& operator=(const SmartSpeaker& other) = delete;

    //  Allow Moving
    SmartSpeaker(SmartSpeaker&& other) noexcept = default;
    SmartSpeaker& operator=(SmartSpeaker&& other) noexcept = default;

    void ViewInfo() const override;
    bool CheckConnection() const override;
    void InteractionEvent() override;
};
