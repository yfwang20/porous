#include "Coolant_Energy_Convection_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Energy_Convection_Solidandcoolant);

InputParameters Coolant_Energy_Convection_Solidandcoolant::validParams()
{
    MooseEnum component("x=0 y=1 z=2");
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("u_coolant", "u_coolant.");
    params.addRequiredCoupledVar("tem_coolant", "tem_coolant.");
    params.addParam<MooseEnum>("component", component, "The gradient component to compute");
    return params;
}

Coolant_Energy_Convection_Solidandcoolant::Coolant_Energy_Convection_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _coolant_rho(getMaterialProperty<Real>("coolant_rho")),
        _coolant_capacity(getMaterialProperty<Real>("coolant_capacity")),
        _u_coolant(coupledValue("u_coolant")),
        _grad_u_coolant(coupledGradient("u_coolant")),
        _u_coolant_var(coupled("u_coolant")),
        _tem_coolant(coupledValue("tem_coolant")),
        _grad_tem_coolant(coupledGradient("tem_coolant")),
        _component(getParam<MooseEnum>("component"))
{
}

Real Coolant_Energy_Convection_Solidandcoolant::computeQpResidual()
{
    return _test[_i][_qp] * _coolant_rho[_qp] * _coolant_capacity[_qp] * (_u[_qp] *  _grad_u_coolant[_qp](_component) + _grad_u[_qp](_component) * _u_coolant[_qp]);
}

Real Coolant_Energy_Convection_Solidandcoolant::computeQpJacobian()
{
    return _test[_i][_qp] * _coolant_rho[_qp] * _coolant_capacity[_qp] * (_phi[_j][_qp] *  _grad_u_coolant[_qp](_component) + _grad_phi[_j][_qp](_component) * _u_coolant[_qp]);
}

Real Coolant_Energy_Convection_Solidandcoolant::computeQpOffDiagJacobian(unsigned int jvar)
{
    if(jvar == _u_coolant_var)
    {
       return _test[_i][_qp] * _coolant_rho[_qp] * _coolant_capacity[_qp] * (_tem_coolant[_qp] *  _grad_phi[_j][_qp](_component) + _grad_tem_coolant[_qp](_component) * _phi[_j][_qp]);
    }
    return 0.0;
}