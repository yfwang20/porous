#include "DelayedNucleus_one.h"

registerMooseObject("PorousApp", DelayedNucleus_one);

InputParameters DelayedNucleus_one::validParams()
{
  InputParameters params = AuxKernel::validParams();
  params.addRequiredCoupledVar("delayed_nucleus_1", "Delayed nucleus 1");
  // params.addRequiredCoupledVar("delayed_nucleus_2", "Delayed nucleus 2");
  // params.addRequiredCoupledVar("delayed_nucleus_3", "Delayed nucleus 3");
  // params.addRequiredCoupledVar("delayed_nucleus_4", "Delayed nucleus 4");
  // params.addRequiredCoupledVar("delayed_nucleus_5", "Delayed nucleus 5");
  // params.addRequiredCoupledVar("delayed_nucleus_6", "Delayed nucleus 6");
  return params;
}

DelayedNucleus_one::DelayedNucleus_one(const InputParameters & parameters)
  : AuxKernel(parameters),
    _delayed_nucleus_1(coupledValue("delayed_nucleus_1")),
    // _delayed_nucleus_2(coupledValue("delayed_nucleus_2")),
    // _delayed_nucleus_3(coupledValue("delayed_nucleus_3")),
    // _delayed_nucleus_4(coupledValue("delayed_nucleus_4")),
    // _delayed_nucleus_5(coupledValue("delayed_nucleus_5")),
    // _delayed_nucleus_6(coupledValue("delayed_nucleus_6")),

    _lambda_1(getMaterialProperty<Real>("lambda_1"))
    // _lambda_2(getMaterialProperty<Real>("lambda_2")),
    // _lambda_3(getMaterialProperty<Real>("lambda_3")),
    // _lambda_4(getMaterialProperty<Real>("lambda_4")),
    // _lambda_5(getMaterialProperty<Real>("lambda_5")),
    // _lambda_6(getMaterialProperty<Real>("lambda_6"))
{
}
Real DelayedNucleus_one::computeValue()
{
  return _delayed_nucleus_1[_qp] * _lambda_1[_qp];
        // _delayed_nucleus_2[_qp] * _lambda_2[_qp] + 
        // _delayed_nucleus_3[_qp] * _lambda_3[_qp] + 
        // _delayed_nucleus_4[_qp] * _lambda_4[_qp] + 
        // _delayed_nucleus_5[_qp] * _lambda_5[_qp] + 
        // _delayed_nucleus_6[_qp] * _lambda_6[_qp];
}