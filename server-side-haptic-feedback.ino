// We are utilizing these pins for anoloug readings and digital output.
int motorPin = D5;
int flexPin = A5;


// This will be a continuous values read from the flex sensor.
int value;


// DISCLAIEMR: Much of this code is modified from the server-client code by maker.io staff from
// https://www.digikey.com/en/maker/blogs/2019/how-to-get-two-photons-to-talk

TCPClient client;                           // Create TCP Client object
byte server_ip[] = {10,23,10,60};           // IP Address for the Sandbox370 network
byte dataBuffer[32];                        // Data buffer that holds andreceived strings
 

// Initial setup.
void setup() 
{
    // Designates pin D6 as digital output.
    pinMode(motorPin, OUTPUT);


    // Wait for a USB serial connection for up to 30 seconds.
    waitFor(Serial.isConnected, 30000);


    // Start the TCP Server.
    server.begin();
}
 

// Loops indefinitley.
void loop() 
{
    // Pass a requesting client to the client object.
    client = server.available();
    
    // Execute code once a client is detected and accepted.
    if(client)
    {
        // Wait for a response before proceeding.
        while(!client.available());        
    
        //Short delay.
        delay(100);
        
        // Read data from the buffer.
        client.read(dataBuffer, sizeof(dataBuffer));


        // Checks to see if the server sends either on ('1') or off ('0') and allows the motor to activate accordingly.
        if(char(dataBuffer[0]) == '1'){
            digitalWrite(motorPin, HIGH);
        }else{
            digitalWrite(motorPin, LOW);
        }
        

        // Reads the values of the flex sensor.
        value = analogRead(flexPin);

        // If the user is flexing, then it sends a "1" string, else it sends a "0" string to the server.
        if(value < 3500){
            client.println("1"); 

        }else{
            client.println("0");

        }
    }
}