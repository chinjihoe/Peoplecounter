#include <SharpIR.h>

#define IR 2
#define receiver 3
#define sharpIR A0
#define model 20150
#define buzzer 4

int segments[]= {5,6,7,8,9,10,11}; //A-G segments of the 7seg. display
int displayDigits[] = {12,13}; //pins for first and second digit of the 7seg. display
SharpIR sharp(sharpIR, 10, 5, model); //Library for SharpIR module

int state = 0;      //State of the IR's
int prevState = 0;  //Previous state used for playing tune
int peopleCount[] = {0, 0, 0}; //[total, enter, exit]
int triggerTime = 0; //Time of trigger
String statusMessage = "";

//Playtune variables
bool startTune = false; //Start a tune
int startTime = 0; //Time of tune starting

void setup() 
{
  pinMode(IR, OUTPUT);
  pinMode(receiver, INPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(displayDigits[0], OUTPUT);
  pinMode(displayDigits[1], OUTPUT);
  for(int i=0; i<7; i++)
    pinMode(segments[i], OUTPUT);  
  Serial.begin(115200);

  delay(2000); //warm up
}

void loop() 
{
  //idle state, no sensors triggered
  if(state == 0) 
  {
   if(IRChecker() == true) //if first sensor is triggered, change state to 1
    {   
      state = 1;
      statusMessage = "Waiting for trigger2"; 
    }
    else if(sharpIRChecker() == true)//second sensor triggered
    {
      state = 2;
      statusMessage = "Waiting for trigger1";
    }
    else
    {
      statusMessage = "Idle";
    }

    if(state != 0) //save time of sensor trigger
    {
      triggerTime = millis();    
    }
  }
  //first sensor is triggered, waiting for second sensor to get triggered
  else if(state == 1) 
  {
    if(sharpIRChecker() == true) //second sensor triggered
    {
      peopleCount[0]++;
      peopleCount[1]++;
      
      prevState = state;
      state = 3;
    }  
    else if(millis() - triggerTime >= 500) //if 500ms has passed without triggering second sensor => reset state
    {
      state = 0;
    }
  }
  //second sensor is triggered, waiting for first sensor to get triggered
  else if(state == 2) 
  {
    if(IRChecker() == true)//first sensor triggered
    {
      peopleCount[0]++;
      peopleCount[2]++;
      
      prevState = state;
      state = 3;
    }
    else if(millis() - triggerTime >= 500)
    {
      state = 0;
    }
  }
  //if both sensor have been triggered succesfully => wait for both sensors to get untriggered
  else if(state == 3) 
  {
    statusMessage = "Waiting to idle..";
    if(IRChecker() == false && sharpIRChecker() == false)//both sensors untriggered
    {
      state = 0;
      startTune = true; //start a tune
      startTime = millis(); //save tune starting time
    }
  }

  //calculate amount of people in room by: people entering - people exiting
  int peopleInRoom = peopleCount[1] - peopleCount[2];
  if(peopleInRoom < 0)
    peopleInRoom = 0;

  //Display and sound
  displayDigit(peopleInRoom);
  play(startTune, startTime, prevState);
  startTune = false;

  printStatusMessage();
}

void printStatusMessage()
{
  Serial.print("Count: " + (String)peopleCount[0]);
  Serial.print("/" + (String)peopleCount[1]);
  Serial.print("/" + (String)peopleCount[2]);
  int dis = sharp.distance();
  if(dis<0)
    dis = 0;
  Serial.println(" State: " + statusMessage + " : " + (String)dis);
}

//Check if a person is standing infront of the second sensor
bool sharpIRChecker()
{
  int dis = sharp.distance();
  
  if(dis < 60 && dis > 0) //Person standing in door
  {
    for(int i=0;i<2;i++)
    {
      if(sharp.distance()<0 || sharp.distance() > 60)
      { 
        return false; 
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

//check if a person is standing infront of the first sensor
bool IRChecker()
{
 int val = irRead(receiver, IR);
  if(val == 1)
  {
    return true;
  }
  else
  {
    return false;
  } 
}

//send out IR waves at approximately 38.5kHz
//this is the required frequency for the IR receiver
int irRead(int readPin, int triggerPin)
{
  int halfPeriod = 13; //one period at 38.5kHz is aproximately 26 microseconds
  int cycles = 38; //26 microseconds * 38 is more or less 1 millisecond
  int i;
  for (i=0; i <=cycles; i++)
  {
    digitalWrite(triggerPin, HIGH); 
    delayMicroseconds(halfPeriod);
    digitalWrite(triggerPin, LOW); 
    delayMicroseconds(halfPeriod - 1);     // - 1 to make up for digitaWrite overhead    
  }
  return digitalRead(readPin);
}
