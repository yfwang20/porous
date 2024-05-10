#include "Solid_Exchangeheat_Onlysolid.h"
registerMooseObject("PorousApp", Solid_Exchangeheat_Onlysolid);

InputParameters Solid_Exchangeheat_Onlysolid::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Solid_Exchangeheat_Onlysolid::Solid_Exchangeheat_Onlysolid(const InputParameters & parameters)
    :   Kernel(parameters),
        _coolant_alpha(getMaterialProperty<Real>("coolant_alpha")),
        _area(getMaterialProperty<Real>("area")),
        _tem_coolant(getMaterialProperty<Real>("tem_coolant"))
{
}

Real Solid_Exchangeheat_Onlysolid::computeQpResidual()
{
    return -_test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * (_tem_coolant[_qp] - _u[_qp]);
}

Real Solid_Exchangeheat_Onlysolid::computeQpJacobian()
{
    return _test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * _phi[_j][_qp];
}