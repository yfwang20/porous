#include "Coolant_Energy_TimeDerivate.h"

registerMooseObject("PorousApp", Coolant_Energy_TimeDerivate);

InputParameters Coolant_Energy_TimeDerivate::validParams()
{
  InputParameters params = TimeDerivative::validParams();
  return params;
}

Coolant_Energy_TimeDerivate::Coolant_Energy_TimeDerivate(const InputParameters & parameters)
  : TimeDerivative(parameters),
    _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
    _coolant_rho(getMaterialProperty<Real>("coolant_rho")),
    _coolant_capacity(getMaterialProperty<Real>("coolant_capacity"))
{
}

Real
Coolant_Energy_TimeDerivate::computeQpResidual()
{
  return TimeDerivative::computeQpResidual() * _porous_coefficient[_qp] * _coolant_rho[_qp] * _coolant_capacity[_qp];
}

Real
Coolant_Energy_TimeDerivate::computeQpJacobian()
{
  return TimeDerivative::computeQpJacobian() * _porous_coefficient[_qp] * _coolant_rho[_qp] * _coolant_capacity[_qp];
}