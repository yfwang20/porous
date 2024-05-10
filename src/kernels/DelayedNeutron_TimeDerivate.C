#include "DelayedNeutron_TimeDerivate.h"

registerMooseObject("PorousApp", DelayedNeutron_TimeDerivate);

InputParameters
DelayedNeutron_TimeDerivate::validParams()
{
  InputParameters params = TimeDerivative::validParams();
  params.addParam<Real>("time_coefficient", 1.0, "Time Coefficient");
  return params;
}

DelayedNeutron_TimeDerivate::DelayedNeutron_TimeDerivate(const InputParameters & parameters)
  : TimeDerivative(parameters), _time_coefficient(getParam<Real>("time_coefficient"))
{
}

Real
DelayedNeutron_TimeDerivate::computeQpResidual()
{
  return _time_coefficient * TimeDerivative::computeQpResidual();
}

Real
DelayedNeutron_TimeDerivate::computeQpJacobian()
{
  return _time_coefficient * TimeDerivative::computeQpJacobian();
}