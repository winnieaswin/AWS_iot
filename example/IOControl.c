#include <AWS_IOT.h>
#include <WiFi.h>
#include <Hornbill_IO.h>

AWS_IOT AWS_CLIENT;

char WIFI_SSID[]="your Wifi SSID";
char WIFI_PASSWORD[]="Wifi Password";
char HOST_ADDRESS[]="AWS host address";
char CLIENT_ID[]= "client id";
char TOPIC_NAME[]= "your thing/topic name";


int status = WL_IDLE_STATUS;
int tick=0,msgReceived=0, publishMsg=0;
char payload[512];
char rcvdPayload[512];
hornbill_IO_type_t ioReq;
int returnCode;

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
    strncpy(rcvdPayload,payLoad,payloadLen);
    rcvdPayload[payloadLen] = 0;
    msgReceived = 1;
}



void setup() {
    Serial.begin(115200);
    delay(2000);

    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(WIFI_SSID);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        // wait 5 seconds for connection:
        delay(5000);
    }

    Serial.println("Connected to wifi");

    if(AWS_CLIENT.connect(HOST_ADDRESS,CLIENT_ID)== 0)
    {
        Serial.println("Connected to AWS");
        delay(1000);

        if(0==AWS_CLIENT.subscribe(TOPIC_NAME,mySubCallBackHandler))
        {
            Serial.println("Subscribe Successfull");
        }
        else
        {
            Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
            while(1);
        }
    }
    else
    {
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }

    delay(2000);
}



void loop() {

    if(msgReceived == 1)
    {
        msgReceived = 0;  // Process the newly received message
        returnCode = Hornbill_IO.parseRequest(rcvdPayload,&ioReq);

        switch(returnCode)
        {
        case HORNBILL_IO_REQUEST_VALID: // Valid Json frame, process the request
            Serial.println("Processing Request");
            if(Hornbill_IO.processRequest(&ioReq) == 0)
            {
                Hornbill_IO.createPayload(payload,&ioReq); //Create the response payload
                publishMsg = 1; // Action taken, now send the response back
                Serial.print("payload msg:");
                Serial.print(payload);
            }
            break;

        case HORNBILL_IO_REQUEST_JSON_INVALID:
            Serial.println("Wrong JSON Format");
            break;

        default:
            // Do nothing
            break;
        }
    }

    if(publishMsg == 1)
    {
        Serial.println("Sending Response");
        if(AWS_CLIENT.publish(TOPIC_NAME,payload) == 0)
        {
            Serial.print("Publish Message:");
            Serial.println(payload);
            publishMsg = 0; // Publish successfull, clear the flag
        }
        else
        {
            Serial.println("Publish failed, Will try again after 1sec");
        }
    }

    vTaskDelay(1000 / portTICK_RATE_MS);
}
