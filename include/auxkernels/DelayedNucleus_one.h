#pragma once

#include "AuxKernel.h"

class DelayedNucleus_one : public AuxKernel
{
public:
  static InputParameters validParams();

  DelayedNucleus_one(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _delayed_nucleus_1;
  // const VariableValue & _delayed_nucleus_2;
  // const VariableValue & _delayed_nucleus_3;
  // const VariableValue & _delayed_nucleus_4;
  // const VariableValue & _delayed_nucleus_5;
  // const VariableValue & _delayed_nucleus_6;

  const MaterialProperty<Real> & _lambda_1;
  // const MaterialProperty<Real> & _lambda_2;
  // const MaterialProperty<Real> & _lambda_3;
  // const MaterialProperty<Real> & _lambda_4;
  // const MaterialProperty<Real> & _lambda_5;
  // const MaterialProperty<Real> & _lambda_6;
};