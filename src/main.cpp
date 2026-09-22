#include <Arduino.h>
#include <avr/interrupt.h>
#include <context.h>
#include <State.h>
#include <Idle.h>
#include <Heater.h>
#include <Cooler.h>
#include <Failure.h>



// Application

Context *temp_control;

bool failure, too_cool, too_hot, failure_cleared;

int time_delay = 200;
unsigned long count_heating = 5UL*60*1000/time_delay;
int applience_time_count = 0;


int main()
{
  init(); // Sets up Timer0 so millis()/micros()/delay() actually work, since we bypass the framework's own main()
  Serial.begin(9600);
  sei(); // Interrupts must be enabled for Serial receive buffers to work

  temp_control = new Context(new Idle);

  while (true)
  {
    int c = 0; // for incoming serial data

    if (Serial.available() > 0)
    {
      c = Serial.read();
      Serial.print("I received: ");
      Serial.println((char)c);
    }

    failure = too_cool = too_hot = failure_cleared = false;

    if (c=='h')
      too_hot = true;
    else if (c=='c')
      too_cool = true;
    else if (c=='f')
      failure = true;
    else if (c=='r')
      failure_cleared = true;

    // wait for some time
    temp_control->do_work();

    // if event1 occurred
    if (too_hot)
      temp_control->on_too_hot();

    // if event2 occurred
    if (too_cool)
      temp_control->on_too_cool();

    if (failure)
      temp_control->on_failure();

    if (failure_cleared)
      temp_control->on_failure_cleared();

    delay(time_delay);
    count_heating++;
    applience_time_count++;
  }

  delete temp_control;
}

