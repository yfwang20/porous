#include "Coolant_Energy_Convection_new_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Energy_Convection_new_Solidandcoolant);

InputParameters Coolant_Energy_Convection_new_Solidandcoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("u_coolant", "u_coolant.");
    params.addRequiredCoupledVar("tem_coolant", "tem_coolant.");
    params.addRequiredParam<RealVectorValue>("v", "V vector");
    return params;
}

Coolant_Energy_Convection_new_Solidandcoolant::Coolant_Energy_Convection_new_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _coolant_rho(getMaterialProperty<Real>("coolant_rho")),
        _coolant_capacity(getMaterialProperty<Real>("coolant_capacity")),
        _u_coolant(coupledValue("u_coolant")),
        _u_coolant_var(coupled("u_coolant")),
        _tem_coolant(coupledValue("tem_coolant")),
        _v(getParam<RealVectorValue>("v"))
{
}

Real Coolant_Energy_Convection_new_Solidandcoolant::computeQpResidual()
{
    return -_grad_test[_i][_qp]  * _v * _coolant_rho[_qp] * _coolant_capacity[_qp] * _u[_qp] *  _u_coolant[_qp];
}

Real Coolant_Energy_Convection_new_Solidandcoolant::computeQpJacobian()
{
    return -_grad_test[_i][_qp]  * _v * _coolant_rho[_qp] * _coolant_capacity[_qp] * _phi[_j][_qp] *  _u_coolant[_qp];
}

Real Coolant_Energy_Convection_new_Solidandcoolant::computeQpOffDiagJacobian(unsigned int jvar)
{
    if(jvar == _u_coolant_var)
    {
       return -_grad_test[_i][_qp]  * _v * _coolant_rho[_qp] * _coolant_capacity[_qp] * _tem_coolant[_qp] *  _phi[_j][_qp];
    }
    return 0.0;
}