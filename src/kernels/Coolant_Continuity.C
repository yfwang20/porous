#include "Coolant_Continuity.h"
registerMooseObject("PorousApp", Coolant_Continuity);

InputParameters Coolant_Continuity::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<RealVectorValue>("v", "V vector");
    return params;
}

Coolant_Continuity::Coolant_Continuity(const InputParameters & parameters)
    :   Kernel(parameters),
        _v(getParam<RealVectorValue>("v")),
        _coolant_rho(getMaterialProperty<Real>("coolant_rho"))
{
}

Real Coolant_Continuity::computeQpResidual()
{
    return -_grad_test[_i][_qp] * _v * _u[_qp] * _coolant_rho[_qp];
}

Real Coolant_Continuity::computeQpJacobian()
{
    return -_grad_test[_i][_qp] * _v * _phi[_j][_qp] * _coolant_rho[_qp];
}