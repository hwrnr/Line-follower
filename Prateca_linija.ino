#define STEPS 2048
#include <Stepper.h>

//int MotorApin1 = 4; //levi
//int MotorApin2 = 5; 
//int MotorApinPWM = 3;
//int MotorBpin1 = 8; //desni
//int MotorBpin2 = 7;
//int MotorBpinPWM = 9;
//int pwm = 150;    //Koliki ce pwm davati, isti na oba tocka, do 255

#define SensorLevi 12
#define SensorDesni  10
#define SensorSrednji  11

int Levo, Desno, Pravo;

#define LD 0
#define S 1
int poslednje = 0;

Stepper stepperD(STEPS, 6, 8, 7, 9);
Stepper stepperL(STEPS, 2, 4, 3, 5);


//void MotorAStop(){
// digitalWrite(MotorApin1, LOW); 
// digitalWrite(MotorApin2, LOW);
//}

void MotorLForward(){
//  MotorAStop();
//  digitalWrite(MotorApin1, HIGH);
//  analogWrite(MotorApinPWM, pwm);
  stepperL.step(STEPS/16);
}

//void MotorBStop(){
// digitalWrite(MotorBpin1, LOW); 
// digitalWrite(MotorBpin2, LOW);
//}

void MotorDForward(){
//  MotorBStop();
//  digitalWrite(MotorBpin1, HIGH);
//  analogWrite(MotorBpinPWM, pwm);
  stepperD.step(STEPS/16);
}

void BothForward(){
  for (int i = 0; i < STEPS/16; i++){
    stepperL.step(1);
    stepperD.step(1);
  }
}


void setup(){
//  pinMode(MotorApin1, OUTPUT);  
//  pinMode(MotorApin2, OUTPUT);
//  pinMode(MotorApinPWM, OUTPUT);
//  pinMode(MotorBpin1, OUTPUT);
//  pinMode(MotorBpin2, OUTPUT);
//  pinMode(MotorBpinPWM, OUTPUT);
  pinMode(SensorLevi, INPUT);
  pinMode(SensorSrednji, INPUT);
  pinMode(SensorDesni, INPUT);
  stepperL.setSpeed(6);
  stepperD.setSpeed(6);
//  MotorAStop();
//  MotorBStop();
//  MotorAForward();
//  MotorBForward();
  Serial.begin(9600);
}

void loop(){
 
  Levo = digitalRead(SensorLevi);
  Desno = digitalRead(SensorDesni);
  Pravo = digitalRead(SensorSrednji);
   
  if (Pravo == S){
    if (Levo == LD && Desno != LD){
      MotorDForward();
      poslednje = 1;
    }
    else if (Levo != LD && Desno == LD){
      MotorLForward();
      poslednje = 2; 
    }
    else{
      BothForward();
    }
  }
  else {
    if (Levo == LD && Desno != LD){
      MotorDForward();
      poslednje = 1;
    }
    else if (Levo != LD && Desno == LD){
      MotorLForward();
      poslednje = 2; 
    }
    else if (poslednje == 1){
      MotorDForward();
    }
    else if (poslednje == 2){
      MotorLForward(); 
    }
 
  }
 
 
 delay(10);
 
  
}
