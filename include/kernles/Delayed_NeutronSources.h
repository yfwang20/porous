#pragma once

#include "Kernel.h"

class Delayed_NeutronSources : public Kernel
{
public:
  Delayed_NeutronSources(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  const MaterialProperty<Real> & _lambda;
  const VariableValue & _delayed_c1;
  unsigned int _delayed_c1_var;
};