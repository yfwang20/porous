#include "Solid_Fissionheat.h"
registerMooseObject("PorousApp", Solid_Fissionheat);

InputParameters Solid_Fissionheat::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("flux", "Flux.");
    return params;
}

Solid_Fissionheat::Solid_Fissionheat(const InputParameters & parameters)
    :   Kernel(parameters),
        _Eeff(getMaterialProperty<Real>("Eeff")),
        _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
        _fission_cross_section(getMaterialProperty<Real>("fission_cross_section")),
        _power_coefficient(getMaterialProperty<Real>("power_coefficient")),
        _flux(coupledValue("flux")),
        _flux_var(coupled("flux"))
{
}

Real Solid_Fissionheat::computeQpResidual()
{
    return -_test[_i][_qp] * _Eeff[_qp] * (1 - _porous_coefficient[_qp]) * _fission_cross_section[_qp] * _flux[_qp] * _power_coefficient[_qp];
}

Real Solid_Fissionheat::computeQpJacobian()
{
    return 0.0;
}

Real Solid_Fissionheat::computeQpOffDiagJacobian(unsigned int jvar)
{
  if(jvar == _flux_var)
  {
    return -_test[_i][_qp] * _Eeff[_qp] * (1 - _porous_coefficient[_qp])  * _fission_cross_section[_qp] * _phi[_j][_qp] * _power_coefficient[_qp];
  }
  return 0.0;
}