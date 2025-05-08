#ifndef WIFIMQTT_H
#define WIFIMQTT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "credentials.h"
#include "spi.h"

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Connecting to MQTT...");
    clientID += String(random(0xffff), HEX);
    if (client.connect(clientID.c_str(), mqtt_user, mqtt_password))
    {
      Serial.println("");
      Serial.println("Connected to MQTT");
      client.subscribe(mqtt_topic_sub);
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      Serial.println("Trying again in 5 seconds.");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  if (String(topic) == mqtt_topic_sub)
  {
    Serial.println(" MQTT arrived");
    uint8_t response = spiTransfer((uint8_t)messageTemp[0]);
    Serial.print("Sent to STM32: ");
    Serial.println(messageTemp[0]);
  }
}

void connectAP()
{
  Serial.println("Connect to my Wi-Fi");
  WiFi.begin(ssid, password);
  byte cnt=0;

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    cnt++;

    if (cnt>30)
    {
      ESP.restart();
    }
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

#endif