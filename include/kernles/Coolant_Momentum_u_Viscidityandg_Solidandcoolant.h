#pragma once

#include "Kernel.h"

class Coolant_Momentum_u_Viscidityandg_Solidandcoolant : public Kernel
{
public:
    Coolant_Momentum_u_Viscidityandg_Solidandcoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _porous_coefficient;
    const MaterialProperty<Real> & _flow_resistance;
    const MaterialProperty<Real> & _coolant_rho;
};