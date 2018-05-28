#include <SharpIR.h>
#define ir A0
#define model 20150
// ir: the pin where your sensor is attached
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)
char distance[6];
char existence[2];
int exist;
int count=0;
int onoff;
SharpIR SharpIR(ir, model);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Particle.function("switch",Toggle);
  onoff=1;
}
void loop() {
  delay(2000);
  

  unsigned long pepe1=millis();  // takes the time before the loop on the library begins

  int dis=SharpIR.distance();  // this returns the distance to the object you're measuring
  
  itoa(dis, distance, 10);
  if(onoff=1){
  Particle.publish("distance", distance, PRIVATE);
  
  if(dis<35)
  {
      exist = 1;
      count++;
  }
  else{
  exist = 0;}
  itoa(exist,existence,10);
  Particle.publish("existence", existence, PRIVATE);
  if(count>=10)
  {
      Particle.publish("EVENT_PREFIX",PRIVATE);
      count=0;
  }
  Serial.print("Mean distance: ");  // returns it to the serial monitor
  Serial.println(dis);
  }

}
int Toggle(String command)
{
  // look for the matching argument "coffee" <-- max of 64 characters long
  if(command == "ON")
  {
    onoff=1;
    return 1;
  }
  else if (command=="OFF") {
        onoff=0;
        return 0;
    }
  else return -1;
}