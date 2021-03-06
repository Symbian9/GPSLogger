#include <Adafruit_SSD1306_STM32.h>
#include <NMEAGPS.h>

#include "CurrentTimeScreen.h"
#include "TimeZoneScreen.h"
#include "TimeFont.h"
#include "GPSDataModel.h"
#include "Utils.h"

extern Adafruit_SSD1306 display;

TimeZoneScreen timeZoneScreen; //TODO Move it to CurrentTimeScreen class

void CurrentTimeScreen::drawScreen() const
{
	// Get the date/time adjusted by selected timezone value
	gps_fix gpsFix = gpsDataModel.getGPSFix();
	NeoGPS::time_t dateTime = gpsFix.dateTime + timeZoneScreen.getCurrentTimeZone() * 60; //timeZone is in minutes

	// TODO: display approximate time even if GPS is not available

	display.setFont(&TimeFont);
	display.setCursor(0,31);

	// Draw a '~' symbol if no time is available from GPS.
	display.print(gpsFix.valid.time ? '<' : ';'); // '<' is remapeed to space, ';' is remapped to '~'
	display.print(TimePrinter(dateTime));
}

CurrentTimeScreen::CurrentTimeScreen()
{
	addChildScreen(&timeZoneScreen);
}

