#pragma once
#include "SmartDevice.h"

class SecurityCamera : public SmartDevice 
{
private:
    string cameraQuality;
    string powerSource;

public:
    // Constructor
    SecurityCamera(int id, string name, string manuf, bool status, string quality, string power);

    // Prevent Copying
    SecurityCamera(const SecurityCamera& other) = delete;
    SecurityCamera& operator=(const SecurityCamera& other) = delete;

    // Allow Moving
    SecurityCamera(SecurityCamera&& other) noexcept = default;
    SecurityCamera& operator=(SecurityCamera&& other) noexcept = default;

    void InteractionEvent() override;
    bool CheckConnection() const override;
    void ViewInfo() const override;
};
