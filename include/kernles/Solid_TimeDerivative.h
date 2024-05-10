#pragma once

#include "TimeDerivative.h"

class Solid_TimeDerivative : public TimeDerivative
{
public:
  Solid_TimeDerivative(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _porous_coefficient;
  const MaterialProperty<Real> & _solid_rho;
  const MaterialProperty<Real> & _solid_capacity;
};