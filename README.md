# ESP8266-Mini-Wardriver


# Project Title
ESP8266 Mini Driver


A brief description of what this project does and who it's for


A arduino sketch in th eino format to get your hardware going wardriving on the ESP8266 WiFi microcontroller 

Documentation on this page is still in development. CREDIT to Alex Lynd for the Idea. 

Components
Any ESP8266-based board should work with the basic required components, but the D1 mini form factor is highly recommended since using modules (such as for SD logging + battery management) can be done using plug-and-play hardware in a small footprint. All linked components are D1 mini compatible.

Required Components:

Component	Purpose
ESP8266	Gather WiFi data & control hardware modules






SD Reader	Store data that we can analyze with WiGLE / Python
GPS Module	Grab geolocation data + timestamp
Optional Components:

Component	Purpose
128x64 OLED	Get a visual display of WiFi data being captured
LiPo Battery	Power your ESP8266 for portable applications
Battery Module	Manage power for your ESP8266 w/ a LiPo battery
100K Ω Resistor	Optional to read in battery level w/ the D1 Mini
Hardware Setup
SD Reader Module

SD Reader Pin	ESP8266 GPIO	D1 Mini Pin
MISO	GPIO12	D6
MOSI	GPIO13	D7
SCK	GPIO14	D5
CS	GPIO15	D8
GPS Module

GPS Pin	ESP8266 GPIO	D1 Mini Pin
TX	GPIO2	D4
RX	GPIO0	D3

## Acknowledgements

 - [Awesome Readme Templates](https://awesomeopensource.com/project/elangosundar/awesome-README-templates)
 - [Awesome README](https://github.com/matiassingers/awesome-readme)
 - [How to write a Good readme](https://bulldogjob.com/news/449-how-to-write-a-good-readme-for-your-github-project)


## Badges

Add badges from somewhere like: [shields.io](https://shields.io/)

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)
[![AGPL License](https://img.shields.io/badge/license-AGPL-blue.svg)](http://www.gnu.org/licenses/agpl-3.0)


## Screenshots
GPS Wiring

<img src=" https://i.imgur.com/6uUIQhl.png)">

<img src=" https://i.imgur.com/6uUIQhl.png)">

<img src=" https://i.imgur.com/6uUIQhl.png)">

SD Card Wiring
<img src="https://imgur.com/a/0XDCpHK">


Wemos D1 Pinout
<img src="https://imgur.com/a/POuHgwD">


Wemos D1 Product 

<img src="https://imgur.com/a/GisMFY7">


Display 128x64

https://imgur.com/a/UG9nVmJ
<img src="https://i.imgur.com/R6ObnGg.png">







<img src="https://i.imgur.com/6uUIQhl.png">


<img src="https://i.imgur.com/6uUIQhl.png">




