#include "DelayedNeutron_Fission.h"
registerMooseObject("PorousApp", DelayedNeutron_Fission);

InputParameters DelayedNeutron_Fission::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("flux", "Flux.");
    return params;
}

DelayedNeutron_Fission::DelayedNeutron_Fission(const InputParameters & parameters)
    :   Kernel(parameters),
        _beta(getMaterialProperty<Real>("beta")),
        _fission_cross_section_v(getMaterialProperty<Real>("fission_cross_section_v")),
        // _power_coefficient(getMaterialProperty<Real>("power_coefficient")),
        _flux(coupledValue("flux")),
        _flux_var(coupled("flux"))
{
}

Real DelayedNeutron_Fission::computeQpResidual()
{
    // return -_test[_i][_qp] * _beta[_qp] * _flux[_qp] * _power_coefficient[_qp] * _fission_cross_section_v[_qp];
    return -_test[_i][_qp] * _beta[_qp] * _flux[_qp] * _fission_cross_section_v[_qp];
}

Real DelayedNeutron_Fission::computeQpJacobian()
{
    return 0.0;
}

Real DelayedNeutron_Fission::computeQpOffDiagJacobian(unsigned int jvar)
{
  if(jvar == _flux_var)
  {
    // return -_test[_i][_qp] * _beta[_qp] * _fission_cross_section_v[_qp] * _phi[_j][_qp] * _power_coefficient[_qp];
    return -_test[_i][_qp] * _beta[_qp] * _fission_cross_section_v[_qp] * _phi[_j][_qp];
  }
  return 0.0;
}