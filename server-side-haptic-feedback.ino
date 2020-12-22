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
