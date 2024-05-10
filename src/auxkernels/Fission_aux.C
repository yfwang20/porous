#include "Fission_aux.h"

registerMooseObject("PorousApp", Fission_aux);

InputParameters Fission_aux::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("flux_group1", "Flux of group1");
  params.addRequiredCoupledVar("flux_group2", "Flux of group2");
  return params;
}

Fission_aux::Fission_aux(const InputParameters & parameters)
  : AuxKernel(parameters),
    _flux_group1(coupledValue("flux_group1")),
    _flux_group2(coupledValue("flux_group2")),
    _fission_cross_section_v_group1(getMaterialProperty<Real>("fission_cross_section_v_group1")),
    _fission_cross_section_v_group2(getMaterialProperty<Real>("fission_cross_section_v_group2"))
{
}
Real Fission_aux::computeValue()
{
  return _flux_group1[_qp] * _fission_cross_section_v_group1[_qp] + _flux_group2[_qp] * _fission_cross_section_v_group2[_qp];
}