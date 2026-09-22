#pragma once

class Context;
class State
{
  /**
   * @var Context
   */

protected:
  Context *context_;

public:
  virtual ~State()
  {
  }

  void set_context(Context *context)
  {
    this->context_ = context;
  }

  virtual void on_do() = 0;

  virtual void on_entry() = 0;

  virtual void on_exit() = 0;

  virtual void on_too_hot() = 0;

  virtual void on_too_cool() = 0;

  virtual void on_failure() = 0;

  virtual void on_failure_cleared() = 0;

  // ...

}; 