#include "Delayed_NeutronSources.h"
registerMooseObject("PorousApp", Delayed_NeutronSources);

InputParameters Delayed_NeutronSources::validParams()
{
    InputParameters params = Kernel::validParams();
    params.addRequiredCoupledVar("delayed_c1", "Delayed nucleus auxvariable.");
    return params;
}

Delayed_NeutronSources::Delayed_NeutronSources(const InputParameters & parameters)
    :   Kernel(parameters),
        _lambda(getMaterialProperty<Real>("lambda")),
        _delayed_c1(coupledValue("delayed_c1")),
        _delayed_c1_var(coupled("delayed_c1"))
{
}

Real Delayed_NeutronSources::computeQpResidual()
{
    return -_test[_i][_qp] * _lambda[_qp] * _delayed_c1[_qp];
}

Real Delayed_NeutronSources::computeQpJacobian()
{
    return 0.0;
}

Real Delayed_NeutronSources::computeQpOffDiagJacobian(unsigned int jvar)
{
  if(jvar == _delayed_c1_var)
  {
    return -_test[_i][_qp] * _lambda[_qp] * _phi[_j][_qp];
  }
  return 0.0;
}