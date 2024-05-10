#include "Absorption_Singlegroup.h"
registerMooseObject("PorousApp", Absorption_Singlegroup);

InputParameters Absorption_Singlegroup::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Absorption_Singlegroup::Absorption_Singlegroup(const InputParameters & parameters)
    :   Kernel(parameters),
        _absorption_cross_section(getMaterialProperty<Real>("absorption_cross_section"))
        // _power_coefficient(getMaterialProperty<Real>("power_coefficient"))
{
}

Real Absorption_Singlegroup::computeQpResidual()
{
    // return _test[_i][_qp] * (_absorption_cross_section[_qp] * _u[_qp] * _power_coefficient[_qp]);

    return _test[_i][_qp] * (_absorption_cross_section[_qp] * _u[_qp]);
}

Real Absorption_Singlegroup::computeQpJacobian()
{
    // return _test[_i][_qp] * (_absorption_cross_section[_qp] * _phi[_j][_qp] * _power_coefficient[_qp]);
    return _test[_i][_qp] * (_absorption_cross_section[_qp] * _phi[_j][_qp]);
}