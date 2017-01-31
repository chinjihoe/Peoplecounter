#include <SharpIR.h>

#define sharpIR A0
#define model 20150

SharpIR sharp(sharpIR, 40, 5, model);

void setup() 
{
  Serial.begin(9600);

}

void loop() 
{
  voltageToDistance();      
}

//calculate Vout of the Sharp IR and print the results
void voltageToDistance()
{
  int sensorValue = analogRead(sharpIR);
  int dis = sharp.distance();

  if(dis>0) //only get the positive values. Im using an unsigned integer, so an overflow can occur.
  {
    float voltage = sensorValue * (5.0 / 1023.0);
    Serial.print(dis);
    Serial.print(" ");
    Serial.println(voltage);

  }
}
