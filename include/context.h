#pragma once

class State;

class Context
{
private:
  State *state_;

public:
  Context(State *state);
  ~Context();

  void transition_to(State *state);

  void do_work();
  void on_too_hot();
  void on_too_cool();
  void on_failure();
  void on_failure_cleared();
};