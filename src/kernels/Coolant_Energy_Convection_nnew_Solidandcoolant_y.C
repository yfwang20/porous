#include "Coolant_Energy_Convection_nnew_Solidandcoolant_y.h"
registerMooseObject("PorousApp", Coolant_Energy_Convection_nnew_Solidandcoolant_y);

InputParameters Coolant_Energy_Convection_nnew_Solidandcoolant_y::validParams()
{
    MooseEnum component("x=0 y=1 z=2");
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<Real>("tem_coolant_topboundary", "tem_coolant_topboundary");
    params.addRequiredParam<Real>("u_coolant_topboundary", "u_coolant_topboundary");
    params.addParam<MooseEnum>("component", component, "The gradient component to compute");
    return params;
}

Coolant_Energy_Convection_nnew_Solidandcoolant_y::Coolant_Energy_Convection_nnew_Solidandcoolant_y(const InputParameters & parameters)
    :   Kernel(parameters),
        _coolant_capacity(getMaterialProperty<Real>("coolant_capacity")),
        _tem_coolant_topboundary(getParam<Real>("tem_coolant_topboundary")),
        _u_coolant_topboundary(getParam<Real>("u_coolant_topboundary")),
        _component(getParam<MooseEnum>("component"))
{
}

Real Coolant_Energy_Convection_nnew_Solidandcoolant_y::computeQpResidual()
{
    return _test[_i][_qp] * (598.24 + 2.93 * _tem_coolant_topboundary - 0.836E-2 * _tem_coolant_topboundary * _tem_coolant_topboundary) * _u_coolant_topboundary * _coolant_capacity[_qp] * _grad_u[_qp](_component);
}

Real Coolant_Energy_Convection_nnew_Solidandcoolant_y::computeQpJacobian()
{
    return _test[_i][_qp] * (598.24 + 2.93 * _tem_coolant_topboundary - 0.836E-2 * _tem_coolant_topboundary * _tem_coolant_topboundary) * _u_coolant_topboundary * _coolant_capacity[_qp] * _grad_phi[_j][_qp](_component);
}