#pragma once

#include <frc/Servo.h>


#include "actuators/BinaryActuator.h"

namespace wml {
  namespace actuators {
    class BinaryServo : protected frc::Servo, public BinaryActuator {
     public:
      BinaryServo(int channel, int forwardPos, int reversePos, std::string name = "<Binary Servo>") : frc::Servo(channel), BinaryActuator(name), _forwardPos(forwardPos), _reversePos(reversePos) {};

      virtual void UpdateActuator(double dt) override;
      virtual void Stop() final {};
      virtual bool IsDone() override;
      
     private:
      int _forwardPos, _reversePos; // Forward and Reverse positions on the servo, in degrees
    };
  } // ns actuators
} // ns wml
