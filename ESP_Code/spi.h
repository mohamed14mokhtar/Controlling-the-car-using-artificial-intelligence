#ifndef SPI_H
#define SPI_H

#include <Arduino.h>
#include <SPI.h>

#define SPI_CS 15  // Or whatever GPIO you're using for CS

// SPI communication function
uint8_t spiTransfer(uint8_t command) {
  digitalWrite(SPI_CS, LOW);
  delayMicroseconds(10);
  uint8_t response = SPI.transfer(command);
  delayMicroseconds(10);
  digitalWrite(SPI_CS, HIGH);
  return response;
}

#endif