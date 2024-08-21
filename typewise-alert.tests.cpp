#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite,InfersBreachAccordingToLimits) {
      
    // Test the inferBreach function
    assert(inferBreach(25.0, 0.0, 30.0) == NORMAL);
    assert(inferBreach(-5.0, 0.0, 30.0) == TOO_LOW);
    assert(inferBreach(35.0, 0.0, 30.0) == TOO_HIGH);

  
    // Test the classifyTemperatureBreach function
    assert(classifyTemperatureBreach(PASSIVE_COOLING, 30.0) == NORMAL);
    assert(classifyTemperatureBreach(PASSIVE_COOLING, 36.0) == TOO_HIGH);
    assert(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46.0) == TOO_HIGH);
    assert(classifyTemperatureBreach(MED_ACTIVE_COOLING, 39.0) == NORMAL);
    assert(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1.0) == TOO_LOW);

    // Test the checkAndAlert function
    // Test case 1: Alert to controller for normal temperature
    BatteryCharacter battery = { PASSIVE_COOLING, "BrandA" };
    checkAndAlert(TO_CONTROLLER, battery, 25.0);  // Expected to call sendToController(NORMAL)

    // Test case 2: Alert to email for high temperature
    battery.coolingType = HI_ACTIVE_COOLING;
    checkAndAlert(TO_EMAIL, battery, 50.0);  // Expected to call sendToEmail(TOO_HIGH)

}
