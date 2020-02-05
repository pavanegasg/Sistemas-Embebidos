#include <SoftwareSerial.h>

#define rxPin 0
#define txPin 1


char datoRasp, myChar, enable, data ; 
int randomNumber;
void setup() {
  Serial.begin(9600);   
  
}

void loop(){
  while(Serial.available()){

    datoRasp= Serial.read();
    enable= datoRasp;
    
    delay(10);
    Serial.print(enable);
  

pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);

   
  
  if (enable =='m'){
        Serial.println("Mover Manualmente: ");
         moverManualmente();
         
    }
  
  if(enable=='a'){
    Serial.println("Mover Automaticamente : ");
        moverAleatoriamente();
    }
  }
}

void moverManualmente(){
       
        int x= 1;
        while(x==1){
         myChar = Serial.read();
         if(myChar=='f'||myChar=='F'){Serial.println("HACIA ADELANTE");
            digitalWrite(4, HIGH);
            digitalWrite(5, LOW);
            digitalWrite(6, HIGH);
            digitalWrite(7, LOW);
          delay(15);
        }
      
        if(myChar=='b'||myChar=='B'){Serial.println("HACIA ATRAS");
         digitalWrite(4, LOW);
         digitalWrite(5, HIGH);
         digitalWrite(6, LOW);
         digitalWrite(7, HIGH);
         delay(15);
       }
      
         if(myChar=='l' ||myChar=='L'){Serial.println("HACIA LA IZQUIERDA");
         digitalWrite(4, HIGH);
         digitalWrite(5, LOW);
         digitalWrite(6, LOW);
         digitalWrite(7, LOW);
         delay(15);
       }
         if(myChar=='r'|| myChar=='R'){Serial.println("HACIA LA DERECHA");
         digitalWrite(4, LOW);
         digitalWrite(5, LOW);
         digitalWrite(6, HIGH);
         digitalWrite(7, LOW);
         delay(15);
      
       }
       if(myChar=='s'||myChar=='S'){ Serial.println("PARAR");
         digitalWrite(4, LOW);
         digitalWrite(5, LOW);
         digitalWrite(6, LOW);
         digitalWrite(7, LOW);
         delay(15);
         
       }
       if(myChar=='e'|| myChar=='E'){Serial.println("Salir");
       x=0;
        loop();}
        }
  }
  
void moverAleatoriamente(){
      while (enable=='a'){
    //Genera un numero aleatorio entre 1 y 100
  randomNumber = random(1,6);
  if(randomNumber ==1){data= 'f';
            digitalWrite(4, HIGH);
            digitalWrite(5, LOW);
            digitalWrite(6, HIGH);
            digitalWrite(7, LOW);
          delay(15);}
  if(randomNumber ==2){data= 'b';
         digitalWrite(4, LOW);
         digitalWrite(5, HIGH);
         digitalWrite(6, LOW);
         digitalWrite(7, HIGH);
         delay(15);}
  if(randomNumber ==3){data= 'r';
         digitalWrite(4, LOW);
         digitalWrite(5, LOW);
         digitalWrite(6, HIGH);
         digitalWrite(7, LOW);
         delay(15);}
  if(randomNumber ==4){data= 'l';
         digitalWrite(4, HIGH);
         digitalWrite(5, LOW);
         digitalWrite(6, LOW);
         digitalWrite(7, LOW);
         delay(15);}
  if(randomNumber ==5){data= 's';
         digitalWrite(4, LOW);
         digitalWrite(5, LOW);
         digitalWrite(6, LOW);
         digitalWrite(7, LOW);
         delay(15);}
         myChar = Serial.read();
     if(myChar =='e'){ Serial.println("PARAR");
         digitalWrite(4, LOW);
         digitalWrite(5, LOW);
         digitalWrite(6, LOW);
         digitalWrite(7, LOW);
         delay(15);
      loop();
     }
  
  Serial.print("El comando aleatorio es = ");
  Serial.println(randomNumber);
  Serial.println(data);
 
  delay(1000);
}
}
