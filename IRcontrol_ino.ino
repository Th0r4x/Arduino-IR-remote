#include <IRremote.h>
#include <vector>

const int RECV_PIN = 50;
const int BROJ_DIODA = 3;
int led1 = 10;
int led2 = 11;
int led3 = 12;



IRrecv irrecv(RECV_PIN);

decode_results results;

class Dioda {
  public:
    boolean state;
    int rBr;
    int code1;
    int code2;
    
    Dioda() {
    }
    
    Dioda(int broj) {
     rBr = broj;
     state = false;
    }
    
    void setDiode(int broj, boolean stanje, int kod1, int kod2) {
      rBr = broj;
      state = stanje;
      code1 = kod1;
      code2 = kod2;   
      if(stanje == true) {
        digitalWrite(rBr, HIGH);
        state = true;
      }   
    }
    
    void toggleState() {
      if(state == false) {
        digitalWrite(rBr, HIGH);
        state = true;
      }
      else {
        digitalWrite(rBr, LOW);
        state = false;
      }
      
      Serial.println(state);
    }
};

Dioda dioda1 = Dioda(led1);
Dioda polje[3];




void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);
  pinMode(RECV_PIN, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  polje[0].setDiode(led1, false, 0x001, 0x801);
  polje[1].setDiode(led2, true, 0x002, 0x802);
  polje[2].setDiode(led3, false, 0x003, 0x803);
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
//  switch(results.value)
//{
// case 0x001: dioda1.toggleState(); break; // 10
//case 0x002: pinOn(11); break; // 11
//case 0x003: pinOn(12); break; // 12
//case 0x801: dioda1.toggleState(); break; // 10
//case 0x802: pinOff(11); break; // 11
//case 0x803: pinOff(12); break; // 12
//}
for(int i=0; i < BROJ_DIODA; i++) {
 if(polje[i].code1 == results.value || polje[i].code2 == results.value) {
   polje[i].toggleState();
 } 
}
     }
   
    irrecv.resume(); // Receive the next value
  }
  }


}



