#include "DelayedNeutron_Decay.h"
registerMooseObject("PorousApp", DelayedNeutron_Decay);

InputParameters DelayedNeutron_Decay::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

DelayedNeutron_Decay::DelayedNeutron_Decay(const InputParameters & parameters)
    :   Kernel(parameters),
        _lambda(getMaterialProperty<Real>("lambda"))
{
}

Real DelayedNeutron_Decay::computeQpResidual()
{
    return _test[_i][_qp] * _lambda[_qp] * _u[_qp];
}

Real DelayedNeutron_Decay::computeQpJacobian()
{
    return _test[_i][_qp] * _lambda[_qp] * _phi[_j][_qp];
}