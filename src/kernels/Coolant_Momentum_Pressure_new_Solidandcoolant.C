#include "Coolant_Momentum_Pressure_new_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Momentum_Pressure_new_Solidandcoolant);

InputParameters Coolant_Momentum_Pressure_new_Solidandcoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<RealVectorValue>("v", "V vector");
    return params;
}

Coolant_Momentum_Pressure_new_Solidandcoolant::Coolant_Momentum_Pressure_new_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
        _v(getParam<RealVectorValue>("v"))
{
}

Real Coolant_Momentum_Pressure_new_Solidandcoolant::computeQpResidual()
{
    return -_grad_test[_i][_qp] * _v * _porous_coefficient[_qp] * _u[_qp];
}

Real Coolant_Momentum_Pressure_new_Solidandcoolant::computeQpJacobian()
{
    return -_grad_test[_i][_qp] * _v * _porous_coefficient[_qp] * _phi[_j][_qp];
}
