#include <SoftwareSerial.h>

#include "common.hpp"

SoftwareSerial SoftSerial(7, 8);
unsigned char buffer[DATA_SIZE];

void setup() { 
    pinMode(LED_BUILTIN, OUTPUT);
    SoftSerial.begin(9600);
    Serial.begin(9600);
}
 
void loop() {
    constexpr uint64_t MAX_WAIT_TIME = 2000;
    constexpr uint64_t BLINK_TIME = 1000;

    while(!SoftSerial.available());
    if(SoftSerial.read() == 0x02) {
        int count = 0;
        while(count < DATA_SIZE) {
            while(!SoftSerial.available());
            buffer[count++] = SoftSerial.read();
        }
        while(!SoftSerial.available());
        SoftSerial.read();

        Serial.write(START_BYTE);
        Serial.write(buffer, DATA_SIZE);

        unsigned long startTime = millis();
        while(!Serial.available() && (millis() - startTime < MAX_WAIT_TIME));
        if(Serial.available() && (Serial.read() == STATUS_OK)) {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(BLINK_TIME);
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}
