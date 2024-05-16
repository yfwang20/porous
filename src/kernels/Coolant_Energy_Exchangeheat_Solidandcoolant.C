#include "Coolant_Energy_Exchangeheat_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Energy_Exchangeheat_Solidandcoolant);

InputParameters Coolant_Energy_Exchangeheat_Solidandcoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("tem_solid", "tem_solid.");
    return params;
}

Coolant_Energy_Exchangeheat_Solidandcoolant::Coolant_Energy_Exchangeheat_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _coolant_alpha(getMaterialProperty<Real>("coolant_alpha")),
        _area(getMaterialProperty<Real>("area")),
        _tem_solid(coupledValue("tem_solid")),
        _tem_solid_var(coupled("tem_solid"))
{
}

Real Coolant_Energy_Exchangeheat_Solidandcoolant::computeQpResidual()
{
    return _test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * (_u[_qp] - _tem_solid[_qp]);
}

Real Coolant_Energy_Exchangeheat_Solidandcoolant::computeQpJacobian()
{
    return _test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * _phi[_j][_qp];
}

Real Coolant_Energy_Exchangeheat_Solidandcoolant::computeQpOffDiagJacobian(unsigned int jvar)
{
    if(jvar == _tem_solid_var)
    {
       return -_test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * _phi[_j][_qp];
    }
    return 0.0;
}