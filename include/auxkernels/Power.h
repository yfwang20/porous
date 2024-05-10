#pragma once

#include "AuxKernel.h"

class Power : public AuxKernel
{
public:
  static InputParameters validParams();

  Power(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _flux;

  const MaterialProperty<Real> & _fission_cross_section;
  const MaterialProperty<Real> & _Eeff;
};