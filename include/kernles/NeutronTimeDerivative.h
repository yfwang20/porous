#pragma once

#include "TimeDerivative.h"

class NeutronTimeDerivative : public TimeDerivative
{
public:
  NeutronTimeDerivative(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _velocity;
  // const MaterialProperty<Real> & _power_coefficient;
};