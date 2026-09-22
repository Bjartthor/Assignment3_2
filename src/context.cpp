#include "context.h"
#include "State.h"

Context::Context(State *state) : state_(nullptr)
{
  this->transition_to(state);
}

Context::~Context()
{
  delete state_;
}

void Context::transition_to(State *state)
{
  if (this->state_ != nullptr)
  {
    this->state_->on_exit();
    delete this->state_;
  }

  this->state_ = state;

  this->state_->set_context(this);

  this->state_->on_entry();
}

void Context::do_work()
{
  this->state_->on_do();
}

void Context::on_too_hot()
{
  this->state_->on_too_hot();
}

void Context::on_too_cool()
{
  this->state_->on_too_cool();
}

void Context::on_failure()
{
  this->state_->on_failure();
}

void Context::on_failure_cleared()
{
  this->state_->on_failure_cleared();
}