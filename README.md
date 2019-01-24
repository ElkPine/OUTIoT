# OUTIoT
## What Is It?
OUTIoT is a module that plugs into your wallsocket and is turned on/off by a webapp.

## Contents
 - [How it works](#how-it-works)
 - [Quick start](#quick-start)
   - [Installing](#installing)
   - [Using](#using)
 - [Troubleshooting](#troubleshooting)
 - [Releases](#releases)


## How It Works
The OUTIoT uses an ESP8266 WiFi Chip. ElkPine uses this chip to host a SoftAP WiFi network for SSID credential input. The ESP8266 then hosts a server that communicates with our HUBIoT. We listen for switch RESTful requests to toggle a 3v Relay.

## Quick Start

### Installing
1. Plug OUTIoT into wall socket and hold toggle button for 5 seconds to put module into WiFi Setup Mode. The LED should begin to blink.
2. Connect to the 'OUTIoT' SSID. 
3. A webpage should open. Enter in your WiFi network details into the fields.
4. That's it! The OUTIoT will automatically connect to the HUBIoT!

### Using
Open the webapp on the HUBIoT. A panel should exist under the OUTIoTs tab. Figure

#### LED Indicator
- Solid *ON*
  - Outlet is powered.
- Solid *OFF*
  - Outlet is *not* powered.
- Blinking (On/Off Consistently for 10 seconds)
  - The module is in Identification mode. A user has selected the indentify button for the module within the WebApp.
- Double Blink
  - The module is in WiFi Setup Mode.

## Troubleshooting
WIP

## Releases
#### 0.1a (Unreleased)
- Initial release
