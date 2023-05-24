#define volumregister A1
#define sensor 2
int clap = 0;
int status_sensor;
int val=0;
int j=-1;
int j1=-1;
byte ledPin[] = {3,5,6,9,10,11}; 
byte pinCount; 
long detection_range_start = 0;
long detection_range = 0;
long sta;
boolean mode1= false;
boolean mode2= false;
boolean s=true;
char k=0;

void setup() {

sta=millis();
pinMode(volumregister,INPUT);
pinMode(sensor,INPUT);
pinCount = sizeof(ledPin); 
for (int i=0;i<pinCount;i++)
{
    pinMode(ledPin[i],OUTPUT);  
}                 
}

void loop() 
{ 
if (digitalRead(sensor) == 0)
{
if (clap == 0)
{
detection_range_start = detection_range = millis();
clap++;
}

else if (clap > 0 && millis()-detection_range >= 50)
{
detection_range = millis();
clap++;
}
}


if (millis()-detection_range_start >= 400)
{ 
if (clap == 2)
{
  
if (!mode1)
{
  if (!mode2)
  { 
    mode2=true;
    k=1; 
  }
  else if (mode2)  {  
         mode1 = true;
         mode2=false;
         k=2;
         j=-1;
         for (int i=0;i<=pinCount;i++){
           analogWrite(ledPin[pinCount-i],0);
          }
       }
}
  else if (mode1)
{
     if (!mode2) {
        mode2=true;
        k=3;
        j1=-1;
        for (int i=0;i<=pinCount;i++){
           analogWrite(ledPin[pinCount-i],0);
         }
     }
     else if (mode2){
          mode1 = false;
          mode2=false;
          k=4;
     }
}
}
clap = 0;
}


val=map(analogRead(volumregister),0,1023,1,255);

if (k==1){
  if (millis()-sta>=500){
    if (s){
    analogWrite(3,0);analogWrite(5,val);
    analogWrite(6,0);analogWrite(9,val);
    analogWrite(10,0);analogWrite(11,val);
    s=false;
    sta=millis();
    }
    else if (!s){
      analogWrite(3,val);analogWrite(5,0);
      analogWrite(6,val);analogWrite(9,0);
      analogWrite(10,val);analogWrite(11,0);
      sta=millis();
      s=true;
      }
   }
} 
  else if (k==2){
     if (millis()-sta>=25){
        if (s){
             j++;
             for (int i=0;i<=2;i++){
             analogWrite(ledPin[i],255-j);
             if (255-j==0){s=false;j=-1;for (int i=0;i<=2;i++){analogWrite(ledPin[i],0);}}
              }
             sta=millis(); 
            }      
        else if (!s){
             j++; 
             for (int i=3;i<=5;i++){
             analogWrite(ledPin[i],255-j);
             if (255-j==0){s=true;j=-1;for (int i=3;i<=5;i++){analogWrite(ledPin[i],0);}}
              }
             sta=millis();
          }
      }
   }
    else if (k==3){
      if (millis()-sta>=200){
        if (s){
            j1++;
            analogWrite(ledPin[j1],val);
            if (j1==6){j1=-1;}
            s=false;  
            sta=millis();
        }
        else if (!s){
             //j1;
             analogWrite(ledPin[j1],0);  
             if(j1==5){j1=-1;}
             s=true;
             sta=millis();
          }
      }
}
      else if (k==4) {
            if (millis()-sta>=500){
               if (s){
                  for (int i=0;i<=pinCount;i++){
                     analogWrite(ledPin[pinCount-i],val);
                     delay(35);
                  }
                  s=false;
                  sta=millis();
                }
               else if (!s){
                  for (int i=0;i<=pinCount;i++){
                     analogWrite(ledPin[pinCount-i],0);
                     delay(35);
                  }
                  s=true ;
                  sta=millis();
               }
            }
      } 
}
