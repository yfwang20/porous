#include "Power.h"

registerMooseObject("PorousApp", Power);

InputParameters Power::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("flux", "Flux of group1");
  return params;
}

Power::Power(const InputParameters & parameters)
  : AuxKernel(parameters),
    _flux(coupledValue("flux")),
    _fission_cross_section(getMaterialProperty<Real>("fission_cross_section")),
    _Eeff(getMaterialProperty<Real>("Eeff"))
{
}
Real Power::computeValue()
{
  return _flux[_qp] * _fission_cross_section[_qp] * _Eeff[_qp];
}