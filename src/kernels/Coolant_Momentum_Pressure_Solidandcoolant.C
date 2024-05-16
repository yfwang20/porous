#include "Coolant_Momentum_Pressure_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Momentum_Pressure_Solidandcoolant);

InputParameters Coolant_Momentum_Pressure_Solidandcoolant::validParams()
{
    MooseEnum component("x=0 y=1 z=2");
    InputParameters params = Kernel::validParams();
    params.addParam<MooseEnum>("component", component, "The gradient component to compute");
    return params;
}

Coolant_Momentum_Pressure_Solidandcoolant::Coolant_Momentum_Pressure_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
        _component(getParam<MooseEnum>("component"))
{
}

Real Coolant_Momentum_Pressure_Solidandcoolant::computeQpResidual()
{
    return _test[_i][_qp] * _porous_coefficient[_qp] * _grad_u[_qp](_component);
}

Real Coolant_Momentum_Pressure_Solidandcoolant::computeQpJacobian()
{
    return _test[_i][_qp] * _porous_coefficient[_qp] * _grad_phi[_j][_qp](_component);
}
