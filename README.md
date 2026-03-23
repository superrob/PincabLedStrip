# What is it ?
Firmware for common microcontrollers to drive adressable LEDs together with DOF for virtual pinball.

# Supported Microcontrollers
- ESP8266 (Wemos D1 Mini)
- ESP32 (Wemos S2 Mini)
- RP2040 (Raspberry Pi Pico)
- Teensy

Look into [Settings.h](Settings.h) for information about the default pin configurations for each micro.

# Compiling
Download the repository and open PincapLedStrip.ino in the Arduino IDE.
You will need to download the board definitions for your chosen microcontroller and the following libaries:
- FastLED
- elapsedMillis

# Important cabinet.xml notes
The firmware uses the WemosD1MPStripController in DirectOutput.
In you **cabinet.xml**, you'll have to change the **\<TeensyStripController>\</TeesyStripController>** headers to **\<WemosD1MPStripController>\</WemosD1MPStripController>** to make it work.

Your **cabinet.xml** file needs also to be adapted to use a 2Mbs serial connection & to activate a new feature (PerLedstripLength)

    <ComPortBaudRate>2000000</ComPortBaudRate>
	<SendPerLedstripLength>true</SendPerLedstripLength>

There is also now the possibility to use compressed ledstrip data sent to the micro, optimizing the bandwith used for data transmission.
	Just add this setup to the WemosD1MPStripController to activate it.

	<UseCompression>true</UseCompression>

### Ledstrip brightness

You can also set the brightness values per ledstrips with the new DirectOutput.dll provided.
Just add this setup to any of your \<LedStrip> descriptors in cabinet .xml
You don't need to change any brightness anymore in the firmware.

\<Brightness>value\</Brightness> where value is the brightness in percent, so 0 to 100 values are accepted, default is 100
	
### Test Command

The usual RGB test at boot can now be triggered in other ways
- enabling the TEST_ON_RESET define in PincabLedstrip.ino to have it trigerred on each Wemos reset
- using a switch between TEST_PIN and GND
- when connected to DirectOutput by setting \<TestOnConnect>true\</TestOnConnect> in the WemosD1MPStripController descriptor in cabinet.xml

# EEPROM SETTINGS
ESP8266 and ESP32 supports changing settings in EEPROM.

Up to 8 firmware settings are now configurable through EEProm data patching.
You have to set READ_EEPROM_SETTINGS to 1 to enable this feature
There are 8 available settings, 3 used for now.

Current used settings are : 
	-	Test On Reset : will make an RGB sequence each time the Wemos is powered or when the reset button is pressed.
	- 	Test Switch : Arnoz' new Pinmos has a button wired on D0, enable this setting to use it, disable it if D0 is not wired or you'll have issues.
	-	Activity Led : activity led is using D4, if your setup use this output, disable this setting to avoid interferences.

All other settings are free for future firmware customization.

To patch your settings in the EEprom, you'll have to flash an 8 bytes file containing your settings at the 0x3FB000 address.
esptool command line example (Windows version) : 

	esptool.exe -cp <COMPORT> -cd nodemcu -cb 921600 -cf <FirmwareFile> -ca 0x3FB000 -cf <SettingsFile>


	




	
	
