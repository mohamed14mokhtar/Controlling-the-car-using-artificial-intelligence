/*   
   ____   _____   _       _____   _      
  / ___| |  _  | | |     |  _  | | |     
 | |  _  | |_| | | |     | |_| | | |     
 | |_| | |  _  | | |     |  _  | | |     
  \___/  | | | | | |___  | | | | | |___  
         |_| |_| |_____| |_| |_| |_____|
*/

#include "wifimqtt.h"

void setup() 
{
  Serial.begin(115200);

  // Setup SPI
  SPI.begin(); // Uses default pins (SCK=D5, MOSI=D7, MISO=D6)
  pinMode(SPI_CS, OUTPUT);
  digitalWrite(SPI_CS, HIGH);

  // Connect to Wi-Fi
  connectAP();

  // Setup MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if(!client.connected())
  {
    reconnect();
  }
  if(!client.loop())
  {
    client.connect("ESP8266-");
  }

  // // Poll STM32 for data
  // uint8_t receivedData = spiTransfer(0x00);
  // if (receivedData != 0x00 && receivedData != 0xFF) {
  //   Serial.print("Received from STM32 via SPI: ");
  //   Serial.println((char)receivedData);

  //   // Publish STM32 response
  //   String msg = "STM32 Response: ";
  //   msg += (char)receivedData;
  //   client.publish(mqtt_topic_pub, msg.c_str());
  // }

  delay(500); // Adjust polling frequency

}
