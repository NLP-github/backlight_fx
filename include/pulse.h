#ifndef PULSE_H
#define PULSE_H
#include <Homie.h>

#define ISR_PIN1 D1
#define ISR_PIN2 D2
#define ISR_PIN3 D5
#define ISR_PIN4 D6


class pulseNode : public HomieNode {
    public:
      pulseNode(const char *id, const char *name, const char *type);
      void pulseSetup();
      static void isr();

    protected:
      virtual void setup() override;
      virtual void loop() override;

    private:
      HomieSetting<long> *pulseButtons;
};

#endif
