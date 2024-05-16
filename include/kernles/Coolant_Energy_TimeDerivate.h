#pragma once

#include "TimeDerivative.h"

class Coolant_Energy_TimeDerivate : public TimeDerivative
{
public:
  Coolant_Energy_TimeDerivate(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _porous_coefficient;
  const MaterialProperty<Real> & _coolant_rho;
  const MaterialProperty<Real> & _coolant_capacity;
};