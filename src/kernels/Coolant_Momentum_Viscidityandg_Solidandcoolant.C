#include "Coolant_Momentum_Viscidityandg_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Momentum_Viscidityandg_Solidandcoolant);

InputParameters Coolant_Momentum_Viscidityandg_Solidandcoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("u_coolant", "u_coolant.");
    return params;
}

Coolant_Momentum_Viscidityandg_Solidandcoolant::Coolant_Momentum_Viscidityandg_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
        _flow_resistance(getMaterialProperty<Real>("flow_resistance")),
        _coolant_rho(getMaterialProperty<Real>("coolant_rho")),
        _u_coolant(coupledValue("u_coolant")),
        _u_coolant_var(coupled("u_coolant"))
{
}

Real Coolant_Momentum_Viscidityandg_Solidandcoolant::computeQpResidual()
{
    return _test[_i][_qp] * (_coolant_rho[_qp] * _u_coolant[_qp] - _porous_coefficient[_qp] * _coolant_rho[_qp] * 9.8);
}

Real Coolant_Momentum_Viscidityandg_Solidandcoolant::computeQpJacobian()
{
    return 0;
}

Real Coolant_Momentum_Viscidityandg_Solidandcoolant::computeQpOffDiagJacobian(unsigned int jvar)
{
    if(jvar == _u_coolant_var)
    {
       return _test[_i][_qp] * _coolant_rho[_qp] * _phi[_j][_qp];
    }
    return 0.0;
}