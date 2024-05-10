#pragma once

#include "AuxKernel.h"

class Fission_aux : public AuxKernel
{
public:
  static InputParameters validParams();

  Fission_aux(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _flux_group1;
  const VariableValue & _flux_group2;

  const MaterialProperty<Real> & _fission_cross_section_v_group1;
  const MaterialProperty<Real> & _fission_cross_section_v_group2;
};