#include "Fission_Singlegroup_Transient.h"
registerMooseObject("PorousApp", Fission_Singlegroup_Transient);

InputParameters Fission_Singlegroup_Transient::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<Real>("keff", "keff");
    return params;
}

Fission_Singlegroup_Transient::Fission_Singlegroup_Transient(const InputParameters & parameters)
    :   Kernel(parameters),
        _keff(getParam<Real>("keff")),
        _fission_cross_section_v(getMaterialProperty<Real>("fission_cross_section_v")),
        _beta(getMaterialProperty<Real>("beta"))
{
}

Real Fission_Singlegroup_Transient::computeQpResidual()
{
    return -_test[_i][_qp] * (1 - _beta[_qp]) * _fission_cross_section_v[_qp] * _u[_qp] / _keff;
}

Real Fission_Singlegroup_Transient::computeQpJacobian()
{
    return -_test[_i][_qp] * (1 - _beta[_qp]) * _fission_cross_section_v[_qp] * _phi[_j][_qp] / _keff;
}