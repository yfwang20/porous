#include "Coolant_Poission_Solidandcoolant.h"
registerMooseObject("PorousApp", Coolant_Poission_Solidandcoolant);

InputParameters Coolant_Poission_Solidandcoolant::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<RealVectorValue>("v1", "V1 vector");
    params.addRequiredParam<RealVectorValue>("v2", "V2 vector");
    return params;
}

Coolant_Poission_Solidandcoolant::Coolant_Poission_Solidandcoolant(const InputParameters & parameters)
    :   Kernel(parameters),
        _coolant_rho(getMaterialProperty<Real>("coolant_rho")),
        _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
        _flow_resistance(getMaterialProperty<Real>("flow_resistance")),
        _v1(getParam<RealVectorValue>("v1")),
        _v2(getParam<RealVectorValue>("v2"))
{
}

Real Coolant_Poission_Solidandcoolant::computeQpResidual()
{
    return -_grad_test[_i][_qp]  * _v1 * (_porous_coefficient[_qp] * _porous_coefficient[_qp] / _flow_resistance[_qp] * _v2 * _grad_u[_qp] + _porous_coefficient[_qp] * _porous_coefficient[_qp] * _coolant_rho[_qp] * 9.8 / _flow_resistance[_qp]);
}

Real Coolant_Poission_Solidandcoolant::computeQpJacobian()
{
    return -_grad_test[_i][_qp]  * _v1 * (_porous_coefficient[_qp] * _porous_coefficient[_qp] / _flow_resistance[_qp] * _v2 * _grad_phi[_j][_qp]);
}
