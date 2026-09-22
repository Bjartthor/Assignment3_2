#pragma once
#include "State.h"

class Idle : public State
{
public:
  void on_do() override;
  void on_entry() override;
  void on_exit() override;

  void on_too_hot() override;
  void on_too_cool() override;
  void on_failure() override;
  void on_failure_cleared() override;
};