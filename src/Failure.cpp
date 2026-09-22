#include <Failure.h>
#include <Arduino.h>
#include <Idle.h>
#include <context.h>

void Failure::on_do()
{
}

void Failure::on_entry()
{
  Serial.println("Failure");
  Serial.println("Start Alarm");
}

void Failure::on_exit()
{
  Serial.println("Stop Alarm");
  Serial.print("Failure -> ");
}

void Failure::on_too_hot()
{
}

void Failure::on_too_cool()
{
}

void Failure::on_failure()
{
}

void Failure::on_failure_cleared()
{
  this->context_->transition_to(new Idle());
}


