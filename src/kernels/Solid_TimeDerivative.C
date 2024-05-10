#include "Solid_TimeDerivative.h"

registerMooseObject("PorousApp", Solid_TimeDerivative);

InputParameters Solid_TimeDerivative::validParams()
{
  InputParameters params = TimeDerivative::validParams();
  return params;
}

Solid_TimeDerivative::Solid_TimeDerivative(const InputParameters & parameters)
  : TimeDerivative(parameters),
    _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
    _solid_rho(getMaterialProperty<Real>("solid_rho")),
    _solid_capacity(getMaterialProperty<Real>("solid_capacity"))
{
}

Real
Solid_TimeDerivative::computeQpResidual()
{
  return TimeDerivative::computeQpResidual() * (1 - _porous_coefficient[_qp]) * _solid_rho[_qp] * _solid_capacity[_qp];
}

Real
Solid_TimeDerivative::computeQpJacobian()
{
  return TimeDerivative::computeQpJacobian() * (1 - _porous_coefficient[_qp]) * _solid_rho[_qp] * _solid_capacity[_qp];
}