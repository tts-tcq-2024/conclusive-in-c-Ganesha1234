#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  BreachType RetSts = NORMAL; 
  if(value < lowerLimit) {
    RetSts =  TOO_LOW;
  }
  if(value > upperLimit) {
    RetSts =   TOO_HIGH;
  }
  return RetSts;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  int lowerlimitvalues [3] =  {0,0,0};
  int Higherlimitvalues [3] =  {35,45,40};
  int lowerLimit = 0;
  int upperLimit = 0;
  if(coolingType == PASSIVE_COOLING || coolingType == HI_ACTIVE_COOLING || coolingType == MED_ACTIVE_COOLING)   
  {
   lowerLimit = lowerlimitvalues[coolingType];
   upperLimit = Higherlimitvalues[coolingType];
    
  }
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );
  
   if ( alertTarget == TO_CONTROLLER)
   {
      sendToController(breachType);
   }
   else if ( alertTarget ==  TO_EMAIL)
   {
      sendToEmail(breachType);
    
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if (breachType == TOO_LOW) {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
  }
   else if (breachType == TOO_HIGH)
   {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
   }
}
