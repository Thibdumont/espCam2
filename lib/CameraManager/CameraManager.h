#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <Arduino.h>
#include "esp_camera.h"
#include "RobotSettingManager.h"

#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM 15
#define XCLK_GPIO_NUM 27
#define SIOD_GPIO_NUM 22
#define SIOC_GPIO_NUM 23

#define Y9_GPIO_NUM 19
#define Y8_GPIO_NUM 36
#define Y7_GPIO_NUM 18
#define Y6_GPIO_NUM 39
#define Y5_GPIO_NUM 5
#define Y4_GPIO_NUM 34
#define Y3_GPIO_NUM 35
#define Y2_GPIO_NUM 32
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 26
#define PCLK_GPIO_NUM 21

class CameraManager
{
public:
    CameraManager(RobotSettingManager *);
    void changeResolution(int value);
    void changeQuality(int value);
    void changeContrast(int value);
    void changeBrightness(int value);
    void changeSaturation(int value);
    int getQuality();
    int getResolution();
    int getContrast();
    int getBrightness();
    int getSaturation();

private:
    void init();
    RobotSettingManager *robotSettingManager;
    int quality;
    int resolution;
    int contrast;
    int brightness;
    int saturation;
};

#endif
