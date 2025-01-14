/**
 For this particular example you could try this model with JSON params pre-configured: 
    https://github.com/Rightech/ric-examples/blob/master/.ric-models/mqtt-example-003-json.ric-model.json
 Note that: 
    @node `json`        - only "must have" for this example 
                        ( although you could rename all the nodes/fields as you like )
    @node `server-info` - for connectivity debug
    @node `mqtt-last`   - for mqtt publish debug
*/

#include "Arduino.h"
#include "EspMQTTClient.h" /* https://github.com/plapointe6/EspMQTTClient */
#include "ArduinoJson.h"   /* https://github.com/bblanchon/ArduinoJson */

#define PUB_DELAY (5 * 1000) /* 5 seconds */

EspMQTTClient client(
  "<wifi-ssid>",
  "<wifi-password>",

  "sandbox.rightech.io",
  "<ric-mqtt-client-id>"
);

void setup() {
  Serial.begin(9600);  
}

void onConnectionEstablished() {
  Serial.println("connected");
}

long last = 0;
void publishTemperature() {
  long now = millis();
  if (client.isConnected() && (now - last > PUB_DELAY)) {
    StaticJsonDocument<1024> doc;
    doc["temperature"] = random(20, 30);
    doc["humidity"] = random(40, 90);
    
    String payload;
    serializeJson(doc, payload);

    client.publish("base/state", payload);
    last = now;
  }
}

void loop() {
  client.loop();
  publishTemperature();
}
