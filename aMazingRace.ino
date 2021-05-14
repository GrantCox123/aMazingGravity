#include "Engine.h"

Engine engine = Engine();

void setup() {

  engine.startUpSequence();}

void loop() {

  engine.handleInput();
  if (engine.resetMode) engine.controlMotor();
  if (engine.on && !engine.previouslyOn) {
    engine.previouslyOn = true;
    if (engine.scoreObtained == 3) {
      engine.highSequence();
    } else if (engine.scoreObtained == 2) {
      engine.medSequence();
    } else if (engine.scoreObtained == 1) {
      engine.lowSequence();
    }
  }
  if (!engine.on && engine.previouslyOn) engine.previouslyOn = false;
  if (engine.doTimer) engine.timer();
}
