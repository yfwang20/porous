#pragma once

#include "Kernel.h"

class Coolant_Momentum_Pressure_Solidandcoolant : public Kernel
{
public:
    Coolant_Momentum_Pressure_Solidandcoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _porous_coefficient;
    int _component;
};