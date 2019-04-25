#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <AWS_IOT.h>
//OTA and wifi
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <Update.h>
#include "RemoteDebug.h"  //https://github.com/JoaoLopesF/RemoteDebug
//#include <iostream>
#include <string>
#include <stdio.h>
/* Time Stamp */
#include <NTPClient.h>
//#include <WiFiUdp.h>
#include <OneWire.h>
#include <DallasTemperature.h>



#define ESP32_H01 ;


int day,hours,minutes,seconds,year,month,date,minuteSave;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"europe.pool.ntp.org", 3600, 60000);


#define DHTPIN 23     // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT22     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
// ledPin refers to ESP32 GPIO 23
const int ledPin = 2;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  1200        /* Time ESP32 will go to sleep (in seconds) */

AWS_IOT hornbill;   // AWS_IOT instance

char WIFI_SSID[]="Aswin";
char WIFI_PASSWORD[]="Pi@Riya*1";
char HOST_ADDRESS[]="a1gcytxbxjm16j-ats.iot.eu-west-1.amazonaws.com";
char CLIENT_ID[]= "ESP32_02";
char TOPIC_PJ[] = "sdkTest/";
char TOPIC_NAME[] = "sdkTest/Test";

char TOPIC_NAME_debug[]= "sdkTest/debug";
String iPLocalCh;
//Remote debug
#define HOST_NAME "remotedebug"
int status = WL_IDLE_STATUS;
RemoteDebug Debug;
const char* host = "ESP32_H01";



int tick=0,msgCount=0,msgReceived = 0,publishMsg=0;;
char payload[512];
char rcvdPayload[512];

//reset after fail publish
int publicfail = 100;
int publicfailCount = 100;

//config ph meter

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 15
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);


void chipName (uint32_t chipid)
{
  chipid=ESP.getEfuseMac();//The chip ID is essentially its MAC address(length: 6 bytes).
  // Serial.printf("ESP32 Chip ID = %04X",(uint16_t)(chipid>>32));//print High 2 bytes
  // Serial.printf("%08X\n",(uint32_t)chipid);//print Low 4bytes.

}

//Chip mac

void initRemoteDebug()
{
	String hostNameWifi = HOST_NAME;
	hostNameWifi.concat(".local");
	if (MDNS.begin(HOST_NAME))
  {
			Serial.print("* MDNS responder started. Hostname -> ");
		  Serial.println(HOST_NAME);
	}
	MDNS.addService("telnet", "tcp", 23);// Telnet server RemoteDebug
	Debug.setSerialEnabled(true);
	Debug.begin(HOST_NAME);
	Debug.setResetCmdEnabled(true);
}

void initOTA ()
{
	ArduinoOTA
		.onStart([]() {
			String type;
			if (ArduinoOTA.getCommand() == U_FLASH)
				type = "sketch";
			else // U_SPIFFS
				type = "filesystem";

			// NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
			// //Serial.println("Start updating " + type);
			Debug.println("Start updating " + type);
		})
		.onEnd([]() {
			Debug.println("\nEnd");
		})
		.onProgress([](unsigned int progress, unsigned int total) {
			Debug.printf("Progress: %u%%\r", (progress / (total / 100)));

		})
		.onError([](ota_error_t error) {
			Debug.printf("Error[%u]: ", error);
			if (error == OTA_AUTH_ERROR) Debug.println("Auth Failed");
			else if (error == OTA_BEGIN_ERROR) Debug.println("Begin Failed");
			else if (error == OTA_CONNECT_ERROR) Debug.println("Connect Failed");
			else if (error == OTA_RECEIVE_ERROR) Debug.println("Receive Failed");
			else if (error == OTA_END_ERROR) Debug.println("End Failed");
		});
	ArduinoOTA.begin();
}

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
    strncpy(rcvdPayload,payLoad,payloadLen);
    rcvdPayload[payloadLen] = 0;
    msgReceived = 1;
}
void initAWS()
{
  if(hornbill.connect(HOST_ADDRESS,CLIENT_ID)== 0) // Connect to AWS using Host Address and Cliend ID
  {
      Debug.println("Connected to AWS");
      delay(1000);
      if(0==hornbill.subscribe(TOPIC_NAME,mySubCallBackHandler))
      {
          Debug.println("Subscribe Successfull");
      }
      else
      {
          Debug.println("Subscribe Failed, Check the Thing Name and Certificates");
          publicfail = publicfail -1;
          if (publicfail == 0)
          {
              publicfail = publicfailCount;
              ESP.restart();
          }
      }
  }
  else
  {
      Debug.println("AWS connection failed, Check the HOST Address");
      publicfail = publicfail -1;
      if (publicfail == 0)
      {
          publicfail = publicfailCount;
          ESP.restart();
      }
  }
}

//get Chip ID
uint32_t chipid;

// the setup function runs once when you press reset or power the board
void setup()
{

    // initialize digital pin ledPin as an output.
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);

    delay(2000);

    while (status != WL_CONNECTED)
    {
        Debug.print("Attempting to connect to SSID: ");
        Debug.println(WIFI_SSID);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        // wait 5 seconds for connection:
        delay(5000);
    }
    Debug.println("Connected to wifi");
    delay(2000);
    dht.begin();
    Debug.println(F("DHTxx Unified Sensor Example"));
    // Print temperature sensor details.
    Debug.println(F("------------------------------------"));
    Debug.println(F("Temperature Sensor"));
    Debug.println(F("------------------------------------"));
    // Print humidity sensor details.
    Debug.println(F("Humidity Sensor"));
    Debug.println(F("------------------------------------"));
    // Set delay between sensor readings based on sensor details.
    //ph meter setup
    // adc1_config_width(ADC_WIDTH_BIT_12);
    // adc1_config_channel_atten(ADC1_CHANNEL_6,ADC_ATTEN_DB_0);
    //ADC_0db = 0 to 1.0V
    //ADC2_5db = 0 to 1.5V
    //ADC_6db = 0 to 1.8V
    //ADC_11db = 0 to 3.1V

    analogSetPinAttenuation (34, ADC_11db);
    initRemoteDebug();

    sensors.begin();     //dallas start
  //  initOTA ();
    initAWS();
    Debug.println("Setup Ok");
}
// the loop function runs over and over again forever
void loop()
{
  Debug.handle();
  ArduinoOTA.handle();
  timeClient.update();
  timeClient.forceUpdate();
  String dayStamp;
  String formattedDate;
  // hours = timeClient.getHours();
  minutes = timeClient.getMinutes();
  // seconds = timeClient.getSeconds();
  // year = timeClient.getYear();
  // month = timeClient.getMonth();
  // date = timeClient.getDate();
  //start OTA server
  delay (10000);

  String formattedTime = timeClient.getTimeStampString();
  if(msgReceived == 1)
  {
      msgReceived = 0;
      Debug.print("Received Message:");
      Debug.println(rcvdPayload);
  }
  if(tick >= 5)   // publish to topic every 5seconds
  {
      tick=0;
      sprintf(payload,"Hello from hornbill ESP32 : %d",msgCount++);
      if(hornbill.publish(TOPIC_NAME,payload) == 0)
      {
          //Serial.print("Publish Message:");
        //  Serial.println(payload);
          Debug.print("Publish Message:");
          Debug.println(payload);
      }
      else
      {
          publicfail = publicfail -1;
        //  Serial.print("Publish Fail: ");
        //  Serial.println(publicfail);
          Debug.print("Publish Fail: ");
          Debug.println(publicfail);
          if (publicfail == 0)
          {
              publicfail = publicfailCount;
              ESP.restart();
          }
      }
  }
  vTaskDelay(1000 / portTICK_RATE_MS);
  tick++;
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1);
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);
    // Check if any reads failed and exit early (to try again).

    if (isnan(h) || isnan(t) || isnan(f)) {
        Debug.println("Failed to read from DHT sensor!");
    }
    else
    {
        // Create the payload for publishing
        snprintf(payload,sizeof(payload),"{\n \"thingid\":\"DHT22\", \"Temperature\":%.2f, \"Humidity\":%.2f, \"datetime\":\"%s\" \n}" ,t,h,formattedTime.c_str() );
        publishMsg =1;
    }
    if ((minutes != minuteSave) && (publishMsg == 1))
    {
          Debug.println("Sending Response");
          if(hornbill.publish(TOPIC_NAME,payload) == 0)   // Publish the message(Temp and humidity)
          {
            Debug.print("Publish Message:");
            Debug.println(payload);
            publishMsg =0;
            minuteSave = timeClient.getMinutes();
          }
          else
          {
              publicfail = publicfail -1;
              Debug.print("Publish Fail:");
              Debug.println(publicfail);
              publishMsg =0;
              if (publicfail == 0)
              {
                  publicfail = publicfailCount;
                  ESP.restart();
              }
          }
    }
    // publish the temp and humidity every 5 seconds.
    Debug.print(F("Temperature: "));
    Debug.print(t);
    Debug.println(F("°C"));
    Debug.print(F("Humidity: "));
    Debug.print(h);
    Debug.println(F("%"));
    Debug.print(F("dateTime: "));
    Debug.print(formattedTime);
    Debug.println();
    Debug.print(F("TimeMinute: "));
    Debug.print(minutes);
    Debug.println();
    sensors.requestTemperatures(); // Send the command to get temperatures
    // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    float tempC = sensors.getTempCByIndex(0);
    if(tempC != DEVICE_DISCONNECTED_C)
    {
      Debug.println("Temperature for the device 1 (index 0) is: ");
      Debug.println(tempC);
    }
    else
    {
      Debug.println("Error: Could not read temperature data");
    }
    digitalWrite(ledPin,  LOW);    // turn the LED off by making the voltage LOW
    delay(10000);                  // wait for a second

    Debug.println(WiFi.localIP());
    Debug.println(WiFi.macAddress());

}
