#include <Arduino.h>

#include <SPI.h>
#include <RH_RF95.h>

#include <Wire.h>
#include <SoftwareSerial.h>

// ===== RFM95 =====
// frequency
#define RF95_FREQ 915.0
// pins
#define RFM95_CS 4
#define RFM95_RST 2
#define RFM95_INT 3
// singleton instance of the radio driver
RH_RF95 rf95 (RFM95_CS, RFM95_INT);

void setup() {
    // put your setup code here, to run once:

    pinMode(RFM95_RST, OUTPUT);
	digitalWrite(RFM95_RST, HIGH);

	Serial.begin(9600);

    delay(1000);

    Serial.println(F("Initializing transciever..."));

	// wait for Serial to respond
	while(!Serial) {
		delay(1);
	}

	delay(100);

	// digital reset of transciever
	digitalWrite(RFM95_RST, LOW);
	delay(10);
	digitalWrite(RFM95_RST, HIGH);
	delay(10);

	// initialize transciever
	while( !rf95.init() ) {
		Serial.println(F("LoRa radio init failed!"));
	}
	Serial.println(F("LoRa radio init OK!"));

	// set frequency
	if ( !rf95.setFrequency(RF95_FREQ) ) {
		Serial.println(F("setFrequency failed"));
		while(1);
	}

	Serial.print(F("Set Freq to: "));
	Serial.println(RF95_FREQ);

	// set transmission power -- max!
	rf95.setTxPower(23, false);
}

void loop() {
    // put your main code here, to run repeatedly:
    if( rf95.available() ) {
		uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
   		uint8_t len = sizeof(buf);

		if( rf95.recv(buf, &len) ) {

			//RH_RF95::printBuffer("Received: ", buf, len);
			//Serial.print(F("Got: "));
      		Serial.println((char*)buf);

			//char * recieved;
			//recieved = (char*)buf;



			/*if ( m + 1 != MESSAGE_LENGTH ) {
				Serial.print(F("Data chunk is not of valid length! It has a length of "));
				Serial.println( (m+1) );
			} else {
				bool recievedExists = true;
				for(int a = 0; a < EEPROM.length(); a += MESSAGE_LENGTH) {
					bool chunkFound = true;
					for(int c = 0; c < MESSAGE_LENGTH; c++) {
						if (EEPROM.read(a + c) != recieved[c]) {
							chunkFound = false;
							break;
						}
					}
					if(!chunkFound) {
						recievedExists = false;
						break;
					}
				}

				if (!recievedExists) {
					for(int i = 0; i < MESSAGE_LENGTH; i++) {
						EEPROM.write(addr, recieved[i]);
						addr++;
						if ( addr >= EEPROM.length() ) {
							addr = startAddr;
						}
					}
					Serial.print(F("Wrote message: "));
					Serial.println(recieved);
				} else {
					Serial.println(F("This data chunk already exists... not gonna write it!"));
				}
			}*/
		}
	}
}
