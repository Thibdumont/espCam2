#include "CameraManager.h"

CameraManager::CameraManager()
{
    init();
}

void CameraManager::init()
{
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;

    // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
    //                      for larger pre-allocated frame buffer.
    if (psramFound())
    {
        config.frame_size = FRAMESIZE_UXGA;
        config.jpeg_quality = 10;
        config.fb_count = 2;
    }
    else
    {
        config.frame_size = FRAMESIZE_SVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
    }

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    sensor_t *cameraSensor = esp_camera_sensor_get();

    cameraSensor->set_framesize(cameraSensor, (framesize_t)8);
    cameraSensor->set_quality(cameraSensor, 10);
    cameraSensor->set_vflip(cameraSensor, 0);
    cameraSensor->set_hmirror(cameraSensor, 0);
}

void CameraManager::changeResolution(int value)
{
    if (resolution != value)
    {
        resolution = value;
        sensor_t *cameraSensor = esp_camera_sensor_get();
        cameraSensor->set_framesize(cameraSensor, (framesize_t)value);
    }
}

void CameraManager::changeQuality(int value)
{
    if (quality != value)
    {
        quality = value;
        sensor_t *cameraSensor = esp_camera_sensor_get();
        cameraSensor->set_quality(cameraSensor, value);
    }
}
