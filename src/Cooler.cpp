#include <Arduino.h>
#include <Idle.h>
#include <Heater.h>
#include <Cooler.h>
#include <context.h>
#include <Failure.h>

extern int time_delay;
extern int applience_time_count;


void Cooler::on_do()
{
  if (applience_time_count*time_delay/1000>=2){
    this->context_->transition_to(new Idle());
  }
}

void Cooler::on_entry()
{
  Serial.println("Cooling");
  Serial.println("Cooler startup");
  applience_time_count = 0;
}

void Cooler::on_exit()
{
  Serial.println("Cooler shutdown");
  Serial.print("Cooling -> ");
}

void Cooler::on_too_hot()
{
}

void Cooler::on_too_cool()
{
}

void Cooler::on_failure()
{
  this->context_->transition_to(new Failure());
}

void Cooler::on_failure_cleared()
{
}


