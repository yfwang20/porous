#include "Coolant_Momentum_u_Viscidityandg_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Momentum_u_Viscidityandg_Solidandcoolant);

InputParameters Coolant_Momentum_u_Viscidityandg_Solidandcoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Coolant_Momentum_u_Viscidityandg_Solidandcoolant::Coolant_Momentum_u_Viscidityandg_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
        _flow_resistance(getMaterialProperty<Real>("flow_resistance")),
        _coolant_rho(getMaterialProperty<Real>("coolant_rho"))
{
}

Real Coolant_Momentum_u_Viscidityandg_Solidandcoolant::computeQpResidual()
{
    return _test[_i][_qp] * (_flow_resistance[_qp] * _coolant_rho[_qp] * _u[_qp] - _porous_coefficient[_qp] * _coolant_rho[_qp] * 9.8);
}

Real Coolant_Momentum_u_Viscidityandg_Solidandcoolant::computeQpJacobian()
{
    return _test[_i][_qp] * (_flow_resistance[_qp] * _coolant_rho[_qp] * _phi[_j][_qp]);
}
