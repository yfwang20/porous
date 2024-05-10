#include "Neutron_Vacuum_bc.h"

registerMooseObject("PorousApp", Neutron_Vacuum_bc);

InputParameters
Neutron_Vacuum_bc::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  return params;
}

Neutron_Vacuum_bc::Neutron_Vacuum_bc(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _diffusion_coefficient(getMaterialProperty<Real>("diffusion_coefficient"))
{
}

Real
Neutron_Vacuum_bc::computeQpResidual()
{
  return _test[_i][_qp] * _u[_qp] / 2 / _diffusion_coefficient[_qp];
}