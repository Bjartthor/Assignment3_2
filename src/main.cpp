#include <Arduino.h>
#include <avr/interrupt.h>

enum State
{
  Idle,
  Heating,
  Cooling,
  Failure
};

State state = State::Idle; // Define state variable and set the initial state

bool failure, ok, too_cool, too_hot, failure_cleared;

int time_delay = 200;
unsigned long count_heating = 1*60*1000/time_delay; // so it can start heating as soon as the program is run


int main()
{
  init(); // Sets up Timer0 so millis()/micros()/delay() actually work, since we bypass the framework's own main()
  Serial.begin(9600);
  sei(); // Interrupts must be enabled for Serial receive buffers to work


  while (1)
  {
    int c = 0; // for incoming serial data

    failure = ok = too_cool = too_hot = failure_cleared = false;
    
    if (Serial.available() > 0)
    {
      c = Serial.read();
      Serial.print("I received: ");
      Serial.println((char)c);
    }


    if (c=='h')
      too_hot = true;
    else if (c=='c')
      too_cool = true;
    else if (c=='f')
      failure = true;
    else if (c=='o')
      ok = true;
    else if (c=='r')
      failure_cleared = true;

      // you can compare the value received to a character constant, like 'h'.
    switch (state)
  {


  case State::Idle:
    if (too_cool)
    {
      // State::A exit action
      // event1 transition action
      // set new target state
      if (count_heating*time_delay/1000 >= 1*60)
      {
        Serial.println("Idle -> Heating");
        state = State::Heating;
      }
      else
      {
        Serial.println("Too cool ignored: heater must stay off for 5 minutes before restarting");
      }

      // target state entry action
    }
    
    if (too_hot)
    {
      // State::A exit action
      // event1 transition action
      // set new target state
      Serial.println("Idle -> Cooling");
      state = State::Cooling;
      // target state entry action
    }
    break;

  case State::Heating:
    if (ok)
    {
      // State::A exit action
      count_heating = 0;
      // event1 transition action
      // set new target state
      Serial.println("Heating -> Idle");
      state = State::Idle;
      // target state entry action
    }
    
    if (failure)
    {
      // State::A exit action
      count_heating = 0;
      // event1 transition action
      // set new target state
      Serial.println("Heating -> Failure");
      state = State::Failure;
      // target state entry action
    }
    break;
  
  case State::Cooling:
    if (ok)
    {
      // State::A exit action
      // event1 transition action
      // set new target state
      Serial.println("Cooling -> Idle");
      state = State::Idle;
      // target state entry action
    }

    if (failure)
    {
      // State::A exit action
      // event1 transition action
      // set new target state
      Serial.println("Cooling -> Failure");
      state = State::Failure;
      // target state entry action
    }
    break;
  
  case State::Failure:
    if (failure_cleared)
    {
      // State::A exit action
      // event1 transition action
      // set new target state
      Serial.println("Failure -> Idle");
      state = State::Idle;
      // target state entry action
    }
    break;
  }
  delay(time_delay);
  count_heating++;
  }
}
