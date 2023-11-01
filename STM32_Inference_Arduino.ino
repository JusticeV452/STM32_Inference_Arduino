// UART ///////////////////////////////////////////////////////////////////////
#define MY_STM32C0116_DK // using the dev board?

#ifdef MY_STM32C0116_DK
  const int _RX = PA10_R;
  const int _TX = PA9_R;
#else // custom circuit
  const int _TX = PA14;
  const int _RX = PA13;
#endif


// I2C ////////////////////////////////////////////////////////////////////////
const int _SDA = PB7;
const int _SCL = PB6;


// LED ////////////////////////////////////////////////////////////////////////

#ifdef MY_STM32C0116_DK
  // TODO: change pin: LED and SCL are on the same pin!
  const int led = PB6;
  static bool LED_ON = LOW; // inverted logic
#else // custom circuit
  const int led = PA8;      // TODO: confirm! (can also be PA9_R or PA11)
  static bool LED_ON = HIGH;
#endif

#include <EloquentTinyML.h>
#include <eloquent_tinyml/tensorflow.h>

// copy the printed code from tinymlgen into this file
#include "SineNN.h"

void setup() {
    Serial.begin(115200);

    while (!sineNN.begin()) {
        Serial.print("Error in NN initialization: ");
        Serial.println(sineNN.getErrorMessage());
    }
}

void loop() {
    for (int i = 0; i < 20; i++) {
        // pick x from 0 to PI
        float x = 3.14f * i / 20.0f;
        // even if the input vector is made of a single value
        // you ALWAYS need to create an array
        float input[1] = { x };

        float y_true = sin(x);
        // to run the network, call `predict()`
        float y_pred = sineNN.predict(input);

        Serial.print("sin(");
        Serial.print(x);
        Serial.print(") = ");
        Serial.print(y_true);
        Serial.print("\t predicted: ");
        Serial.println(y_pred);
        delay(1000);
    }
}