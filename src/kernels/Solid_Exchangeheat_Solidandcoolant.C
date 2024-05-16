#include "Solid_Exchangeheat_Solidandcoolant.h"
registerMooseObject("PorousApp", Solid_Exchangeheat_Solidandcoolant);

InputParameters Solid_Exchangeheat_Solidandcoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("tem_coolant", "tem_coolant.");
    return params;
}

Solid_Exchangeheat_Solidandcoolant::Solid_Exchangeheat_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _coolant_alpha(getMaterialProperty<Real>("coolant_alpha")),
        _area(getMaterialProperty<Real>("area")),
        _tem_coolant(coupledValue("tem_coolant")),
        _tem_coolant_var(coupled("tem_coolant"))
{
}

Real Solid_Exchangeheat_Solidandcoolant::computeQpResidual()
{
    return -_test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * (_tem_coolant[_qp] - _u[_qp]);
}

Real Solid_Exchangeheat_Solidandcoolant::computeQpJacobian()
{
    return _test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * _phi[_j][_qp];
}

Real Solid_Exchangeheat_Solidandcoolant::computeQpOffDiagJacobian(unsigned int jvar)
{
    if(jvar == _tem_coolant_var)
    {
       return - _test[_i][_qp] * _coolant_alpha[_qp] * _area[_qp] * _phi[_j][_qp];
    }
    return 0.0;
}