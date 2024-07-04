#include "Coolant_Energy_Convection_nnew_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Energy_Convection_nnew_Solidandcoolant);

InputParameters Coolant_Energy_Convection_nnew_Solidandcoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<Real>("rhou", "rhou");
    params.addRequiredParam<RealVectorValue>("v", "V vector");
    return params;
}

Coolant_Energy_Convection_nnew_Solidandcoolant::Coolant_Energy_Convection_nnew_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _coolant_capacity(getMaterialProperty<Real>("coolant_capacity")),
        _rhou(getParam<Real>("rhou")),
        _v(getParam<RealVectorValue>("v"))
{
}

Real Coolant_Energy_Convection_nnew_Solidandcoolant::computeQpResidual()
{
    return -_grad_test[_i][_qp]  * _v * _rhou * _coolant_capacity[_qp] * _u[_qp];
}

Real Coolant_Energy_Convection_nnew_Solidandcoolant::computeQpJacobian()
{
    return -_grad_test[_i][_qp]  * _v * _rhou * _coolant_capacity[_qp] * _phi[_j][_qp];
}