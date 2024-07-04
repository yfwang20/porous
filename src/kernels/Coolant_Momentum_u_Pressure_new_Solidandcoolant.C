#include "Coolant_Momentum_u_Pressure_new_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Momentum_u_Pressure_new_Solidandcoolant);

InputParameters Coolant_Momentum_u_Pressure_new_Solidandcoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<RealVectorValue>("v", "V vector");
    params.addRequiredCoupledVar("pressure_coolant", "pressure_coolant.");
    return params;
}

Coolant_Momentum_u_Pressure_new_Solidandcoolant::Coolant_Momentum_u_Pressure_new_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
        _v(getParam<RealVectorValue>("v")),
        _pressure_coolant(coupledValue("pressure_coolant")),
        _pressure_coolant_var(coupled("pressure_coolant"))
{
}

Real Coolant_Momentum_u_Pressure_new_Solidandcoolant::computeQpResidual()
{
    return -_grad_test[_i][_qp] * _v * _porous_coefficient[_qp] * _pressure_coolant[_qp];
}

Real Coolant_Momentum_u_Pressure_new_Solidandcoolant::computeQpJacobian()
{
    return 0.0;
}

Real Coolant_Momentum_u_Pressure_new_Solidandcoolant::computeQpOffDiagJacobian(unsigned int jvar)
{
    if(jvar == _pressure_coolant_var)
    {
       return -_grad_test[_i][_qp] * _v * _porous_coefficient[_qp] * _phi[_j][_qp];
    }
    return 0.0;
}
