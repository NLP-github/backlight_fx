#include "pulse.h"

volatile uint8_t statePinFlag = 0;

  pulseNode::pulseNode(const char* id, const char* name, const char* type): HomieNode(id, name, type){
    pulseButtons = new HomieSetting<long>("pulseButtons", "Buttons (range: 0-4)");
  }

void pulseNode::pulseSetup(){
    pulseButtons->setDefaultValue(0).setValidator([](long candidate) {
    return (candidate >= 0 &&  candidate <= 4 );
  });
}

void pulseNode::setup(){
  pinMode(ISR_PIN1, INPUT_PULLUP);
  pinMode(ISR_PIN2, INPUT_PULLUP);
  pinMode(ISR_PIN3, INPUT_PULLUP);
  pinMode(ISR_PIN4, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ISR_PIN1), isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(ISR_PIN2), isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(ISR_PIN3), isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(ISR_PIN4), isr, FALLING);

  advertise("btn").setRetained(true).setFormat("0-4");
}

void IRAM_ATTR pulseNode::isr() {
    ETS_GPIO_INTR_DISABLE();
    if( digitalRead(ISR_PIN1) == 0 ) { statePinFlag = 1; };
    if( digitalRead(ISR_PIN2) == 0 ) { statePinFlag = 2; };
    if( digitalRead(ISR_PIN3) == 0 ) { statePinFlag = 3; };
    if( digitalRead(ISR_PIN4) == 0 ) { statePinFlag = 4; };
}

void pulseNode::loop(){
    if( statePinFlag != 0 ){
      setProperty("btn").send(String(statePinFlag));
      statePinFlag = 0;
      setProperty("btn").send(String(0));
      ETS_GPIO_INTR_ENABLE();
    }
}
