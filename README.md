# Haptic Touch

![Img](https://github.com/tknoepff/haptic-touch/blob/master/images/image-1.jpg)
<br>
<br>

**_Description_**
<br>

This is a prototype for a communication device that wraps around your wrist. A flex sensor is attached to the finger and a haptic motor can be placed anywhere the user chooses. As one person flexes their finger (on their device), the haptic motor on the other person’s end (the other device) vibrates and vice versa. With a Photon microcontroller mounted on a soldered protoboard, the device utilizes Wi-Fi capabilities to communicate with one another through TCP connection. 

This prototype explores forms of communication via embodied technology. Like any medium, the wearable acts as an extension of the user. The device becomes a part of the user’s body so as to embody ethereal data, the packets of information that are being transferred on the network. The wearable device was specifically designed with haptic feedback to provide a feeling for the world outside of oneself. The wearable is the media technology that allows the user to transfer haptic messages to their partner. Their partner, in turn, recognizes the messages sent by transmitting their own touch.


## Materials Used
- [Photon WiFi Development Board](https://store.particle.io/products/photon)
- [Vibrating Mini Motor Disc](https://www.adafruit.com/product/1201)
- [Short Flex Sensor](https://www.adafruit.com/product/1070)
- Protoboard
- Cardboard
- Wires
- Clear Tape


## Technical Drawings

![Img](https://github.com/tknoepff/nipple-buttons/blob/master/process%20images/process-1.jpg)
![Img](https://github.com/tknoepff/nipple-buttons/blob/master/process%20images/process-2.jpg)
![Img](https://github.com/tknoepff/nipple-buttons/blob/master/process%20images/process-3.jpg)
![Img](https://github.com/tknoepff/nipple-buttons/blob/master/process%20images/process-4.jpg)


## Code Snippets

**_Server-side code_**
```c
int motorPin = D5;
int flexPin = A5;
int value;

TCPClient client;                         
byte server_ip[] = {10,23,10,60};           
byte dataBuffer[32];                       
 

void setup(){
    pinMode(motorPin, OUTPUT);
    waitFor(Serial.isConnected, 30000);
    server.begin();
}
 

void loop(){
    client = server.available();
    
    if(client)
    {
        while(!client.available());        
    
        delay(100);
        
        client.read(dataBuffer, sizeof(dataBuffer));

        if(char(dataBuffer[0]) == '1'){
            digitalWrite(motorPin, HIGH);
            
        }else{
            digitalWrite(motorPin, LOW);
            
        }
        
        value = analogRead(flexPin);

        if(value < 3500){
            client.println("1"); 

        }else{
            client.println("0");

        }
    }
}
```

**_Client-side code_**
```c
int motorPin = D5;
int flexPin = A5;
int value;

TCPClient client;                           
byte server_ip[] = {10,23,10,60};           
byte dataBuffer[32];                  
 

void setup(){
    pinMode(motorPin, OUTPUT);
}
 

void loop() 
{
    while(!client.connect(server_ip, 80)){
        Serial.println("Server connection failed. Trying again...");
    }   
    
    value = analogRead(flexPin);
    
    if(value < 3600){
        client.println("1");
    
    }else{
        client.println("0");
    }
    
    while(!client.available());
 
    client.read(dataBuffer, sizeof(dataBuffer));
    
    if(char(dataBuffer[0]) == '1'){
        digitalWrite(motorPin, HIGH);

    }else{
        digitalWrite(motorPin, LOW);

    }
    client.stop();
}
```

## Demo

![Img](https://github.com/tknoepff/nipple-buttons/blob/master/demo%20images/demo-1.jpg)
![Img](https://github.com/tknoepff/nipple-buttons/blob/master/demo%20images/demo-2.jpg)

## Credits
**Creator** • Thomas Knoepffler <br>
**Advisor** • Tega Brain <br>
**Program** • Integrated Digital Media, NYU <br>
**Semester** • Fall 2019