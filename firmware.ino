#include <AccelStepper.h>
#include <MultiStepper.h>
#include<LiquidCrystal.h>



#define LCD_PINS_RS 16 
#define LCD_PINS_ENABLE 17
#define LCD_PINS_D4 23
#define LCD_PINS_D5 25 
#define LCD_PINS_D6 27
#define LCD_PINS_D7 29




LiquidCrystal lcd(16, 17, 23, 25, 27, 29);

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2
#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19
#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24
#define Q_STEP_PIN         36
#define Q_DIR_PIN          34
#define Q_ENABLE_PIN       30
#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13
#define FAN_PIN            9
#define PS_ON_PIN          12
#define KILL_PIN           -1
#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN         13   // ANALOG NUMBERING
#define TEMP_1_PIN         14   // ANALOG NUMBERING

//definir motores paso a paso

//arduino mega
AccelStepper stepperX(AccelStepper::DRIVER, 54, 55); AccelStepper stepperY(AccelStepper::DRIVER, 60, 61); AccelStepper stepperZ(AccelStepper::DRIVER, 46, 48);
//arduino uno
//AccelStepper stepperX(AccelStepper::DRIVER, 13, 10); AccelStepper stepperY(AccelStepper::DRIVER, 12, 9); AccelStepper stepperZ(AccelStepper::DRIVER, 11, 8);

MultiStepper steppers;
String LCD; 
String XX,YY,ZZ;

unsigned long previousMillis = 0;        // will store last time LED was updated
// constants won't change:
const long interval = 1000;     

double moduloVector; //
int contador=0;

long positions[10]; //posiciones a ejecutar (x,y,z,m)

double alfa, beta, gamma, x, y, z; int u=0;
double sx = 800; double sy = 800; double sz = 2500; 
double ax = 1000; double ay = 1000; double az = 1250;
double maxspeedx = 800; double maxspeedy = 800;double maxspeedz = 2500;


String InX=""; int px=0; double valorX; double  X=0;
String InY=""; int py=0; double valorY; double Y=0;
String InZ=""; int pz=0; double valorZ; double Z=0;
String InM=""; int pm=0; double valorM; double M=0;
String InG=""; int pg=0; double valorG; double G=0;
String InF=""; int pf=0; double valorF; double F=0;
String InT=""; int pt=0; double valorT; double T=0;
String InS=""; int ps=0; double valorS; double S=0;
String texto = ""; 
  
int c=0;
int j=0; //jog
int gcode=0;  
double tiempo=0;
int h=0;

void setup() {
  lcd.begin(20, 4);
  lcd.print("n-cnc-v1.0");
  // Open serial communications and wait for port to open:
  pinMode(FAN_PIN , OUTPUT);  pinMode(HEATER_0_PIN , OUTPUT);  pinMode(HEATER_1_PIN , OUTPUT);  pinMode(LED_PIN  , OUTPUT);  pinMode(X_STEP_PIN  , OUTPUT);
  pinMode(X_DIR_PIN    , OUTPUT);   pinMode(X_ENABLE_PIN    , OUTPUT);  pinMode(Y_STEP_PIN  , OUTPUT);  pinMode(Y_DIR_PIN    , OUTPUT);  pinMode(Y_ENABLE_PIN    , OUTPUT);
  pinMode(Z_STEP_PIN  , OUTPUT);   pinMode(Z_DIR_PIN    , OUTPUT);  pinMode(Z_ENABLE_PIN    , OUTPUT);  pinMode(E_STEP_PIN  , OUTPUT);  pinMode(E_DIR_PIN    , OUTPUT);
  pinMode(E_ENABLE_PIN    , OUTPUT);   pinMode(Q_STEP_PIN  , OUTPUT);  pinMode(Q_DIR_PIN    , OUTPUT);  pinMode(Q_ENABLE_PIN    , OUTPUT);  digitalWrite(X_ENABLE_PIN    , LOW);
  digitalWrite(Y_ENABLE_PIN    , LOW);  digitalWrite(Z_ENABLE_PIN    , LOW);  digitalWrite(E_ENABLE_PIN    , LOW);  digitalWrite(Q_ENABLE_PIN    , LOW);
pinMode(10, OUTPUT);


  Serial.setTimeout(10000);
  alfa = 0;   beta = 0;  gamma = 0;

  steppers.addStepper(stepperX);  stepperX.setMaxSpeed(maxspeedx);   stepperX.setAcceleration(ax);  stepperX.setSpeed(sx);
  steppers.addStepper(stepperY);  stepperY.setMaxSpeed(maxspeedy);   stepperY.setAcceleration(ay);  stepperY.setSpeed(sy);
  steppers.addStepper(stepperZ);  stepperZ.setMaxSpeed(maxspeedz);   stepperZ.setAcceleration(az);  stepperZ.setSpeed(sz);  
  
 
  Serial.begin(9600); 

  while (!Serial) { }

 
  Serial.println("\n\nnepturio"); Serial.println("#");
  lcd.clear();
  lcd.print("nepturio"); 


}

void reiniciarvariables() {

  if (px != 0) { InX= ""; px=0;  } //si es igual a cero indica que no asumió el valor del contador c, por lo tanto no hubo cambios en esa coordenada
  if (py != 0) { InY= ""; py=0; } 
  if (pz != 0) { InZ= ""; pz=0; } 
  if (pm != 0) { InM= ""; pm=0; } 
  if (pg != 0) { InG= ""; pg=0; } 


  c=0; //contador posicion de caracter
  texto = ""; 
  gcode=0; 
  contador=0;
  
}

void lecturaSerial() {
  
  while (Serial.available() > 0) {
   
    
  int inChar = Serial.read();
    texto += (char)inChar;  c=c+1;

    
    if (isDigit(inChar) || inChar == '-' || inChar == '.') { //si la entrada es un digito, punto o signo - entonces lo guardamos en la respectiva variable
      
         if (gcode == 1) { InX += (char)inChar; }
         if (gcode == 2) { InY += (char)inChar; }
         if (gcode == 3) { InZ += (char)inChar; }
         if (gcode == 4) { InM += (char)inChar; }
         if (gcode == 5) { InG += (char)inChar; }
         if (gcode == 6) { InF += (char)inChar; }    
         if (gcode == 7) { InT += (char)inChar; } 
         if (gcode == 8) { InS += (char)inChar; }    
    }

    //COMANDOS G-CODE
    
    {
         if (inChar == 'x' || inChar == 'X') { px=c; gcode = 1;}
         if (inChar == 'y' || inChar =='Y') { py=c; gcode = 2;}
         if (inChar == 'z' || inChar =='Z') { pz=c; gcode = 3;}
         if (inChar == 'm' || inChar =='M') { pm=c; gcode = 4;}
         if (inChar == 'g' || inChar =='G') { pg=c; gcode = 5;} 

    //COMANDOS JOG
    
      if (inChar == 'd') {     j = 1;   X = X+1;          }   // +x 1mm
      if (inChar == 'a') {     j = 1;   X = X-1;          }   // -x 1mm
      if (inChar == 'w') {     j = 1;   Y = Y+1;          }   // +y 1mm
      if (inChar == 's') {     j = 1;   Y  = Y-1;         }   // -y 1mm
      if (inChar == 'b') {     j = 1;   Z = Z+1;          }   // +z 
      if (inChar == 'h') {     j = 1;   Z = Z-1;          }   // -z 
      
      if (inChar == 'D') {     j = 1;   X = X+10;         }   // +x 10mm
      if (inChar == 'A') {     j = 1;   X= X-10;          }   // -x 10mm
      if (inChar == 'W') {     j = 1;   Y = Y+10;         }   // +y 10mm
      if (inChar == 'S') {     j = 1;   Y = Y-10;         }   // -y 10mm
      if (inChar == 'B') {     j = 1;   Z = Z+10;        }   // +z  
      if (inChar == 'H') {     j = 1;   Z = Z-10;        }   // -z 

   
    
    if (inChar == '\n') {  //

      h=1; //para indicar envio de simbolo $ o #
      
      //Serial.print("Texto entrada:");  
      //Serial.println(texto);
     // Serial.print("Longitud texto:");   Serial.println(texto.length()-1); 

      valorX=InX.toFloat(); valorY=InY.toFloat(); valorZ=InZ.toFloat(); valorM=InM.toFloat();valorG=InG.toFloat(); //valor# indica el valor que introduce la linea gcode
/*
      Serial.print("valorX:");   Serial.println(valorX);
      Serial.print("valorY:");   Serial.println(valorY);
      Serial.print("valorZ:");   Serial.println(valorZ);
      Serial.print("valorM:");   Serial.println(valorM);
      Serial.print("valorG:");   Serial.println(valorG);
*/
      //mostrar posición nueva

      if ( j == 0) {

      if ( px != 0) {  X   = valorX;}
      if ( py != 0) {  Y   = valorY;}
      if ( pz != 0) {  Z   = valorZ;}
      if ( pm != 0) {  M   = valorM;}
      if ( pg != 0) {  G   = valorG;}
      }

      if ( j == 1) { //Jog
        
           if ( px != 0) {  X   = X;}
           if ( py != 0) {  Y   = Y;}
           if ( pz != 0) {  Z   = Z;}
           j = 0;
           //stepperX.setMaxSpeed(maxspeedx);   stepperX.setAcceleration(ax);  stepperX.setSpeed(sx);
           //stepperY.setMaxSpeed(maxspeedy);   stepperY.setAcceleration(ay);  stepperY.setSpeed(sy);
      
      } 

      

      Serial.print("X:");   Serial.println(X);
      Serial.print("Y:");   Serial.println(Y);
      Serial.print("Z:");   Serial.println(Z);
      Serial.print("M:");   Serial.println(M);
      Serial.print("G:");   Serial.println(G);
      
      
      //mover motores
      alfa=X;       x=alfa; //guardar alfa, beta, gamma para calculo de velocidades para llegar los dos motores al mismo tiempo.
      beta=Y;      y=beta;
      gamma=Z;      z=gamma;

      moduloVector=sqrt(alfa*alfa+beta*beta); tiempo=1000*moduloVector/750; 
      

      Serial.print("tiempo(ms):");   Serial.println(tiempo); 
      

  positions[0] = -alfa*40.24;
  positions[1] = -beta*40.24;
  positions[2] = -gamma*375;
  
  steppers.moveTo(positions);

   if(M==3)    {        Serial.println("$red26_ON#") ;         digitalWrite(13, 1);      } //plasma/router ON
   if(M==5)    {        Serial.println("$red26_OFF#") ;        digitalWrite(13, 0);      } //plasma/router OFF
      
      //stepperX.moveTo(-alfa);   stepperY.moveTo(-beta);  stepperZ.moveTo(-gamma);

  XX=InX;YY=InY;ZZ=InZ;
  

  lcd.clear();
  
  LCD=("[n-cnc-v1.0]        x("+XX+")y("+YY+")z("+ZZ+")"); lcd.print(LCD);
  

      reiniciarvariables();    

    
    
    }
    
    }
    
    }



}

void loop() {

// 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

  }


  // Read serial input:
  //stepperX.run();  stepperY.run(); stepperZ.run();
  steppers.runSpeedToPosition();    //{Serial.println("$");}
  if(h==1) {Serial.println("$");}
  lecturaSerial();  
  if (stepperX.distanceToGo() == 0 && stepperY.distanceToGo() == 0 && stepperZ.distanceToGo() == 0 ) { h=0;}
    
    //Serial.println("#");}
//stepperX.moveTo(-alfa);   stepperY.moveTo(-beta);  stepperZ.moveTo(-gamma);
//}
  
  }
