#pragma once

#include "Kernel.h"

class DelayedNeutron_Decay : public Kernel
{
public:
  DelayedNeutron_Decay(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  const MaterialProperty<Real> & _lambda;
};