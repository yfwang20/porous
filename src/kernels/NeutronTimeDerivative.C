#include "NeutronTimeDerivative.h"

registerMooseObject("PorousApp", NeutronTimeDerivative);

InputParameters NeutronTimeDerivative::validParams()
{
  InputParameters params = TimeDerivative::validParams();
  return params;
}

NeutronTimeDerivative::NeutronTimeDerivative(const InputParameters & parameters)
  : TimeDerivative(parameters), _velocity(getMaterialProperty<Real>("velocity"))
    // _power_coefficient(getMaterialProperty<Real>("power_coefficient"))
{
}

Real
NeutronTimeDerivative::computeQpResidual()
{
  // return TimeDerivative::computeQpResidual() / _velocity[_qp] * _power_coefficient[_qp];
  return TimeDerivative::computeQpResidual() / _velocity[_qp];
}

Real
NeutronTimeDerivative::computeQpJacobian()
{
  // return TimeDerivative::computeQpJacobian() / _velocity[_qp] * _power_coefficient[_qp];
  return TimeDerivative::computeQpJacobian() / _velocity[_qp];
}