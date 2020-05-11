# MPU-9250-ESP32-Library-Calibration
An easy-to-use library for the MPU-9250 that includes a straightforward calibration function and also allows you to customize magnetic declination. The calibration is saved to the device's EEPROM (or virtual EEPROM in the case of the ESP32) so you won't have to keep recalibrating every time!

This library is based on [Kris Winer's legendary MPU9250 library](https://github.com/kriswiner/MPU9250) and [hideakitai's awesome MPU9250 library here](https://github.com/hideakitai/MPU9250). 

## Usage

### Simple Measurement

```
#include "MPU9250.h"

MPU9250 mpu;

void setup()
{
    Serial.begin(115200);

    Wire.begin();

    delay(2000);
    mpu.setup();
}

void loop()
{
    /** Beyond readibility in the Serial monitor, this delays reducing the mild stutturing effect you'd see 
	from trying to get too frequent updates using this IMU. Feel free to take it off. **/
    static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 16)
    {
        mpu.update();
        mpu.print();

        Serial.print("roll  (x-forward (north)) : ");
        Serial.println(mpu.getRoll());
        Serial.print("pitch (y-right (east))    : ");
        Serial.println(mpu.getPitch());
        Serial.print("yaw   (z-down (down))     : ");
        Serial.println(mpu.getYaw());

        prev_ms = millis();
    }
}
```

### Calibration
- Begin the calibration by leaving the device completely flat during the accelerometer/gyroscope calibration stage
- For the magnetometer calibration, wave the device in a figure-8 pattern for the 15 seconds that it asks you to do so
- Done and done!


```c++
#include "MPU9250.h"

MPU9250 mpu;

void setup()
{
    Serial.begin(115200);

    Wire.begin();

    delay(2000);
    mpu.setup();

    delay(5000);

    // calibrate anytime you want to
    mpu.calibrateAccelGyro();
    mpu.calibrateMag();

    mpu.printCalibration();
}

void loop()
{
}
```

And if you want to save the calibration data to the device's EEPROM:

```c++

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


```

### 

## Other Settings

### Magnetic Declination

Magnetic declination should be set depending on where you are to get accurate data.
To set it, use this method. 

```C++
mpu.setMagneticDeclination(value);
```

You can read more about the concept [here](https://en.wikipedia.org/wiki/Magnetic_declination) and
find the magnetic declination for your particular location from [here](https://www.ngdc.noaa.gov/geomag/calculators/magcalc.shtml#declination). The
US NOAA (National Oceanic and Atmospheric Administration) website has a ton of free and awesome tools that are super useful for any project dealing
with magnetometers and sensors of the like. Check them out!



