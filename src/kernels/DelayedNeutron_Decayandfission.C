#include "DelayedNeutron_Decayandfission.h"
registerMooseObject("PorousApp", DelayedNeutron_Decayandfission);

InputParameters DelayedNeutron_Decayandfission::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<Real>("keff", "keff.");
    params.addRequiredCoupledVar("flux", "Flux.");
    return params;
}

DelayedNeutron_Decayandfission::DelayedNeutron_Decayandfission(const InputParameters & parameters)
    :   Kernel(parameters),
        _keff(getParam<Real>("keff")),
        _lambda(getMaterialProperty<Real>("lambda")),
        _beta(getMaterialProperty<Real>("beta")),
        _fission_cross_section_v(getMaterialProperty<Real>("fission_cross_section_v")),
        // _power_coefficient(getMaterialProperty<Real>("power_coefficient")),
        _flux(coupledValue("flux")),
        _flux_var(coupled("flux"))
{
}

Real DelayedNeutron_Decayandfission::computeQpResidual()
{
    // return _test[_i][_qp] * (_lambda[_qp] * _u[_qp] - _beta[_qp] * _flux[_qp] * _power_coefficient[_qp] * _fission_cross_section_v[_qp] / _keff);
    return _test[_i][_qp] * (_lambda[_qp] * _u[_qp] - _beta[_qp] * _flux[_qp] * _fission_cross_section_v[_qp] / _keff);
}

Real DelayedNeutron_Decayandfission::computeQpJacobian()
{
    return _test[_i][_qp] * _lambda[_qp] * _phi[_j][_qp];
}

Real DelayedNeutron_Decayandfission::computeQpOffDiagJacobian(unsigned int jvar)
{
  if(jvar == _flux_var)
  {
    // return -_test[_i][_qp] * _beta[_qp] * _fission_cross_section_v[_qp] * _phi[_j][_qp] * _power_coefficient[_qp] / _keff;
    return -_test[_i][_qp] * _beta[_qp] * _fission_cross_section_v[_qp] * _phi[_j][_qp] / _keff;
  }
  return 0.0;
}