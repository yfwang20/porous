#pragma once

#include "Function.h"

class Transientproblem2_AbsorptionCrossSection_group2 : public Function
{
public:
  Transientproblem2_AbsorptionCrossSection_group2(const InputParameters & parameters);

  static InputParameters validParams();

  virtual Real value(Real t, const Point & p) const override;
};