#pragma once

#include "Kernel.h"

class Coolant_Momentum_Viscidityandg_Solidandcoolant : public Kernel
{
public:
    Coolant_Momentum_Viscidityandg_Solidandcoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

    virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
    const MaterialProperty<Real> & _porous_coefficient;
    const MaterialProperty<Real> & _flow_resistance;
    const MaterialProperty<Real> & _coolant_rho;
    const VariableValue & _u_coolant;
    unsigned int _u_coolant_var;
};