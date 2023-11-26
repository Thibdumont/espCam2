# espCam2

This code is for the ESP32 part of the project.
It works with these 2 other projects :

1. The "client" part : [https://github.com/Thibdumont/RobotCarUI](https://github.com/Thibdumont/RobotCarUI)
2. The Arduino part : [https://github.com/Thibdumont/RobotCar2](https://github.com/Thibdumont/RobotCar2)

- [espCam2](#espcam2)
  - [Requirements](#requirements)
  - [Key features](#key-features)
  - [Installation instructions](#installation-instructions)
    - [Configuration](#configuration)
    - [Uploading](#uploading)
  - [Work in progress](#work-in-progress)

## Requirements

- You need to have a `Elegoo Smart robot car v4` kit or build some equivalent.

## Key features

- Handle communication with Arduino through JSON based messages
- Host a web server to communicate with the client part
- Receive commands to control the car/camera/settings
- Can connect to the LAN or switch to SoftAP mode
- Persist every setting change in memory so the user config is still the same after restarting the robot
- Synchronize state with Arduino when booting/rebooting
- See the client part project for the full list of user features : [https://github.com/Thibdumont/RobotCarUI](https://github.com/Thibdumont/RobotCarUI)

## Installation instructions

### Configuration

You have to edit the `data/settings.json` file to update some network settings :

```json
{
    ...
    "wifiLanSSID": "lan-SSID",
    "wifiLanPassword": "lan-password",
    "wifiSoftApSSID": "ESP32 AP",
    "wifiSoftApPassword": "esp-password"
}
```

Property names are self explanatory.
You can switch between LAN/SoftAP mode by pressing the arduino shield button. LED will switch from green (LAN mode) to blue (SoftAP mode). You should prefer LAN mode if possible because SoftAP mode is less performant and become unstable beyond 10 meters.

### Uploading

1. Install `VSCode`
2. Install `PlatformIO IDE` extension
3. Clone this repository and go to the `espCam2` folder
4. Plug an USB cable to your ESP32
5. Click the `upload` button of PlatformIO IDE extension to start the upload (trigger the upload of the ESP32, see ESP32 documentation to know how)

You also have to upload the data folder to the ESP32 filesystem :

1. open a new PIO terminal by going to PlatformIO > Miscellaneous > New Terminal
2. Run `pio run -t uploadfs` command in this terminal

Every time you change the "client" part, you should upload the new build to the ESP32 this way. Copy the artifacts in the data folder, then upload to ESP32 filesystem.

## Work in progress

This project is still work in progress. Any suggestion, advice, pull request is welcome.
