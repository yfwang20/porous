#include "Fission_Singlegroup_Eigen.h"
registerMooseObject("PorousApp", Fission_Singlegroup_Eigen);

InputParameters Fission_Singlegroup_Eigen::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Fission_Singlegroup_Eigen::Fission_Singlegroup_Eigen(const InputParameters & parameters)
    :   Kernel(parameters),
        _fission_cross_section_v(getMaterialProperty<Real>("fission_cross_section_v"))
        // _power_coefficient(getMaterialProperty<Real>("power_coefficient"))
{
}

Real Fission_Singlegroup_Eigen::computeQpResidual()
{
    // return -_test[_i][_qp] * _fission_cross_section_v[_qp] * _u[_qp] * _power_coefficient[_qp];
    return -_test[_i][_qp] * _fission_cross_section_v[_qp] * _u[_qp];
}

Real Fission_Singlegroup_Eigen::computeQpJacobian()
{
    // return -_test[_i][_qp] * _fission_cross_section_v[_qp] * _phi[_j][_qp] * _power_coefficient[_qp];
    return -_test[_i][_qp] * _fission_cross_section_v[_qp] * _phi[_j][_qp];
}