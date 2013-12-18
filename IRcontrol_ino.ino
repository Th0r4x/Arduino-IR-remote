#include <IRremote.h>

const int RECV_PIN = 50;
int led1 = 10;
int led2 = 11;
int led3 = 12;


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  pinMode(RECV_PIN, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  
}

void pinOn(int z) // turns on digital pin "pin" for 1 second
{
digitalWrite(z, HIGH);
}
 void pinOff(int z)
 {
digitalWrite(z, LOW);
}

void loop() {
  if (irrecv.decode(&results)) {
    
    
{
    
     if (results.decode_type == RC5) {
      Serial.print("RC5: ");
      Serial.println(results.value, HEX);
  switch(results.value)
{
 case 0x001: pinOn(10); break; // 10
case 0x002: pinOn(11); break; // 11
case 0x003: pinOn(12); break; // 12
case 0x801: pinOff(10); break; // 10
case 0x802: pinOff(11); break; // 11
case 0x803: pinOff(12); break; // 12
}
     }

 
 
    
      

    
   
    irrecv.resume(); // Receive the next value
  }
  }

}



