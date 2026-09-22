#include <Arduino.h>
#include <Idle.h>
#include <Heater.h>
#include <Cooler.h>
#include <context.h>
#include <Failure.h>

extern int time_delay;
extern int applience_time_count;
extern unsigned long count_heating;


void Heater::on_do()
{
  if (applience_time_count*time_delay/1000>=3){
    this->context_->transition_to(new Idle());
  }
}

void Heater::on_entry()
{
  Serial.println("Heating");
  Serial.println("Heating startup");
  applience_time_count = 0;
}

void Heater::on_exit()
{
  Serial.println("Heating shutdown");
  Serial.println("Heating restart timer");
  count_heating = 0;
  Serial.print("Heating -> ");
}

void Heater::on_too_hot()
{
}

void Heater::on_too_cool()
{
}

void Heater::on_failure()
{
  this->context_->transition_to(new Failure());
}

void Heater::on_failure_cleared()
{
}


