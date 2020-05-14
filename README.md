# IoT-Based-Smart-Irrigation-System
Here we have build a IoT based Irrigation System using ESP8266 NodeMCU Module and DHT11 Sensor. It will not only automatically irrigate the water based on the moisture level in the soil but also send the data to a dedicated server to keep track of the land condition. 

COMPONENTS:
  1. ESP8266 WiFi module
  2. 12V dual channel Relay
  3. DC-DC Buck converter
  4. YL-38 moisture meter (soil moisture sensor)
  5. DHT-22 sensor (Digital Humidity and Temperature sensor)
  6. Solenoid valve
  7. CD74HC4067 16:1 Analog Digital Multiplexer
  
## Connection diagram  
 ![eFSI Scehmatic](https://user-images.githubusercontent.com/37745069/81949178-2d383680-9620-11ea-891c-0ea54c8dfb20.png)

### Arduino-ESP8266 And Blynk Integration

Follow instructions on http://www.blynk.cc/getting-started/
1. DOWNLOAD BLYNK APP FOR ANDROID OR IOS
2. GET THE AUTH TOKEN
3. INSTALL BLYNK LIBRARY
4. And put the code from https://examples.blynk.cc/?          board=Arduino%20Uno&shield=ESP8266%20WiFi%20Shield&example=GettingStarted%2FBlynkBlink to arduino and flash it with standard Arduino  IDE.Make sure to fill in your home wifi SSID and Password and Authkey from blynk app.

5. Comment out following line because Arduino Uno doesn't have hardware serials: #define EspSerial Serial1
   And uncomment these lines because we will use software serial: //#include <SoftwareSerial.h> 

6. Make sure your esp baud rate is correct on this line: #define ESP8266_BAUD 115200 (for me it was 9600)

7. Install Blynk app on your smartphone and add a button to it and make it turn on/off a digital pin. In my case it was D7 pin. Which      harbored the LED.

8. Once your arduino is powered it will connect to your home wifi with esp thus to internet. And when you press the button from blynk      app it will turn it on and off.

#### IFTTT - Google Assistant Integration:

First you need to get latest version of google assistant on your phone. I believe you need to have at least Marshmallow to make it work. It didnt work on my friend's KitKat. I had a Nougat rom on my Samsung J7 Phone. To get it for your Android 6+ phone,
You can follow official https://support.google.com/assistant/answer/7172657?co=GENIE.Platform%3DAndroid&hl=en
What you need To use the Google Assistant, you’ll need a phone with:

  Android 6.0 or higher
  Google app 6.13 or higher
  Google Play services
  1.5 GB of memory and 720p screen resolution
  Phone's language set to English. On Pixel phones, you can use English or German.
  Turn on

  Open the Google app Google Search.
  At the top left of the Home screen, tap Menu Menu and then Settings and then Enable Google Assistant.
  If these don't work for you, you can try the unofficial way from https://www.googleplayservicesapk.com/download-google-assistant-apk-   for-marshmallow-nougat-lollipop/ (I got mine from there)
  We added it as an IF(trigger) in IFTTT instead of Widget Button we previously tested.

  Possibilities are endless, you can put any trigger you like from IFTTT to turn on or off.

  https://ifttt.com/google_assistant Also you can make google assistant do anything you want with your custom voice commands.
