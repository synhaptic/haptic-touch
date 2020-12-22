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
