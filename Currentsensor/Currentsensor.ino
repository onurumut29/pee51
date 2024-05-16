
unsigned int x=0;

float AcsValue=0.0;   // Uitgelezen leesspanning uit de sensor
float Samples=0.0;    
float AvgAcs=0.0;     // gemiddelde leesspanning
float AcsValueF=0.0;  // gemiddelde leesspanning omzetten in een stroom

void setup() {

  Serial.begin(9600); //Start Serial Monitor to display current read value on Serial monitor
  
}

void loop() {
  


  for (int x = 0; x < 150; x++){  //150 samples
  AcsValue = analogRead(A0);      //uitlezen van de sensor   
  Samples = Samples + AcsValue;   //samples bij elkaar zetten
  delay (3);                      
}
AvgAcs=Samples/150.0;             //De gemiddeldes bij elkaar zetten

//((AvgAcs * (5.0 / 1024.0)) is converitng the read voltage in 0-5 volts
//2.5 is offset(I assumed that arduino is working on 5v so the viout at no current comes
//out to be 2.5 which is out offset. If your arduino is working on different voltage than 
//you must change the offset according to the input voltage)
//0.185v(185mV) is rise in output voltage when 1A current flows at input

AcsValueF = (2.5 - (AvgAcs * (5.0 / 1024.0)) )/0.185;

Serial.print(AcsValueF);//Print the read current on Serial monitor
delay(50);
}
