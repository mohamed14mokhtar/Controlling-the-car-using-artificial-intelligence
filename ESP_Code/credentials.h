#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// MQTT
const char *mqtt_server = "34.165.24.252";
const char *mqtt_user = "root";
const char *mqtt_password = "debian22_25";
const int mqtt_port = 1883;

const char* mqtt_topic_sub = "car/movement/commands";
const char* mqtt_topic_pub = "esp8266/feedback";

String clientID = "ESP8266-";
WiFiClient espClient;
PubSubClient client(espClient);

// Access Point
const char* ssid     = "Galal";
const char* password = "600070000";

#endif