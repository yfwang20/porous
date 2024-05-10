#include "Transientproblem2_AbsorptionCrossSection_group2.h"

registerMooseObject("PorousApp", Transientproblem2_AbsorptionCrossSection_group2);

InputParameters
Transientproblem2_AbsorptionCrossSection_group2::validParams()
{
  InputParameters params = Function::validParams();
  return params;
}

Transientproblem2_AbsorptionCrossSection_group2::Transientproblem2_AbsorptionCrossSection_group2(const InputParameters & parameters)
  : Function(parameters)
{
}

Real Transientproblem2_AbsorptionCrossSection_group2::value(Real t, const Point & p) const
{
    if(t <= 0.2)
    {
        return 0.15 - 0.0035 / 0.2 * t;
    }
    return 0.1465;
}