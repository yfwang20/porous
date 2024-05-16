#include "Coolant_Continuity_Fake.h"
registerMooseObject("PorousApp", Coolant_Continuity_Fake);

InputParameters Coolant_Continuity_Fake::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredParam<Real>("tem_coolant_topboundary", "tem_coolant_topboundary");
     params.addRequiredParam<Real>("u_coolant_topboundary", "u_coolant_topboundary");
    return params;
}

Coolant_Continuity_Fake::Coolant_Continuity_Fake(const InputParameters & parameters)
    :   Kernel(parameters),
        _tem_coolant_topboundary(getParam<Real>("tem_coolant_topboundary")),
        _u_coolant_topboundary(getParam<Real>("u_coolant_topboundary")),
        _coolant_rho(getMaterialProperty<Real>("coolant_rho"))
{
}

Real Coolant_Continuity_Fake::computeQpResidual()
{
    return _test[_i][_qp] * (_coolant_rho[_qp] * _u[_qp] - (598.24 + 2.93 * _tem_coolant_topboundary - 0.836E-2 * _tem_coolant_topboundary * _tem_coolant_topboundary) * _u_coolant_topboundary);
}

Real Coolant_Continuity_Fake::computeQpJacobian()
{
    return _test[_i][_qp] * (_coolant_rho[_qp] * _phi[_j][_qp]);
}