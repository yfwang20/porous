#pragma once

#include "TimeDerivative.h"

class DelayedNeutron_TimeDerivate : public TimeDerivative
{
public:
  DelayedNeutron_TimeDerivate(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const Real & _time_coefficient;
};