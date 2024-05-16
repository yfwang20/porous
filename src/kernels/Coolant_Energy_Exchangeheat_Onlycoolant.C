#include "Coolant_Energy_Exchangeheat_Onlycoolant.h"
registerMooseObject("PorousApp", Coolant_Energy_Exchangeheat_Onlycoolant);

InputParameters Coolant_Energy_Exchangeheat_Onlycoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Coolant_Energy_Exchangeheat_Onlycoolant::Coolant_Energy_Exchangeheat_Onlycoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _coolant_alpha(getMaterialProperty<Real>("coolant_alpha")),
        _area(getMaterialProperty<Real>("area")),
        _tem_solid(getMaterialProperty<Real>("tem_solid"))
{
}

Real Coolant_Energy_Exchangeheat_Onlycoolant::computeQpResidual()
{
    return _test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * (_u[_qp] - _tem_solid[_qp]);
}

Real Coolant_Energy_Exchangeheat_Onlycoolant::computeQpJacobian()
{
    return _test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * _phi[_j][_qp];
}