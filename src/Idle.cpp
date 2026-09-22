#include <Arduino.h>
#include <Idle.h>
#include <Heater.h>
#include <Cooler.h>
#include <context.h>

extern int time_delay;
extern unsigned long count_heating;

void Idle::on_do()
{
}

void Idle::on_entry()
{
  Serial.println("Idle");
}

void Idle::on_exit()
{
  Serial.print("Idle -> ");
}

void Idle::on_too_hot()
{
  this->context_->transition_to(new Cooler());
}

void Idle::on_too_cool()
{
  if (count_heating * time_delay / 1000 >= 5 * 60)
  {
    this->context_->transition_to(new Heater());
  }
  else
  {
    Serial.println("Too cool ignored: heater must stay off for 5 minutes before restarting");
  }
}

void Idle::on_failure()
{
}

void Idle::on_failure_cleared()
{
}


