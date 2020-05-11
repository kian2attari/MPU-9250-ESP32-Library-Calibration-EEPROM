#include "MPU9250.h"
#include "eeprom_utils.h"

MPU9250 mpu;

void setup()
{
    Serial.begin(115200);

    Wire.begin();

    delay(2000);
    mpu.setup(Wire);

    delay(5000);
	
	/** If you are using an ESP32 board 
		you need to uncomment the next line
		so that the data would actually be written to the
		EEPROM**/
	// EEPROM.begin(EEPROM_SIZE);

    // calibrate when you want to
    mpu.calibrateAccelGyro();
    mpu.calibrateMag();

    // save to eeprom
    saveCalibration();

    // load from eeprom
    loadCalibration();

    mpu.printCalibration();
}

void loop()
{
}
