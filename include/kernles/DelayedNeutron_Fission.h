#pragma once

#include "Kernel.h"

class DelayedNeutron_Fission : public Kernel
{
public:
  DelayedNeutron_Fission(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  const MaterialProperty<Real> & _beta;
  const MaterialProperty<Real> & _fission_cross_section_v;
  // const MaterialProperty<Real> & _power_coefficient;
  const VariableValue & _flux;
  unsigned int _flux_var;
};