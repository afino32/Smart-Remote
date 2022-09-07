# Smart Remote


## Description
* This smart remote allows you to be able to control any device that makes use of an infrared remote control (e.g. TV, speaker, etc.) from any other device with a web browser (e.g. phone, computer, etc.) which is connected to the same WiFi as the smart remote. The smart remote is set up to point at your devices that you wish to control and is not meant to be moved around. Your device that you wish to function as a remote control will communicate with the smart remote and the smart remote will then send out the appropriate signals to the device that you wish to control. Currently, not many types of remote controls are supported.

## Setup

*  You must first connect the smart remote to your WiFi. It is important that the smart remote is connected to the same WiFi as the device that you wish to use as a remote control. To do so, begin by plugging in the smart remote. The red LED indicates that the smart remote is not connected to WiFi. Similarly, the green LED indicates that the smart remote is connected to WiFi. If the red LED indicator is on and the green LED indicator is off, then you should notice that a new WiFi network that you can connect to has appeared (ssid: "smart-remote", password: 0825). This WiFi network may take up to 30 seconds to appear. Connect to this network. Once connected to this network simply navigate to [http://192.168.4.1](192.168.4.1) in your web browser and enter your WiFi credentials. The smart remote will restart and attempt to connect. The green LED indicator should be on once connected. Now point the smart remote in the direction of the devices that you want to control and set it up so that it will not be disturbed. You may now open the web browser on your device and navigate to [smart-remote.local](smart-remote.local) (Note: Does not work for Android devices) and enjoy having your device work as a remote control.

### Pages
* The [smart remote home page](./images/pages/index.png) looks like this.
* The [connection page](./images/pages/connectPage.png), where you provide your WiFi credentials, looks like this.

### Schematics

* If you wish to build this with an ESP-32 Development board then you should wire it according this [schematic](./images/schematics/schematic_with_dev_board.PNG).

* If you wish to have a standalone PCB then you should create it according to this schematic  [schematic](./images/schematics/schematic_with_standalone_pcb.PNG) (work in progress).
    * Note: values that read "TBD" (to be determined) need to be determined after taking some measurements as this will vary based on PCB traces and component placements.