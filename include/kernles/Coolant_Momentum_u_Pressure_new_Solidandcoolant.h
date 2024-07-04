#pragma once

#include "Kernel.h"

class Coolant_Momentum_u_Pressure_new_Solidandcoolant : public Kernel
{
public:
    Coolant_Momentum_u_Pressure_new_Solidandcoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

    virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
    const MaterialProperty<Real> & _porous_coefficient;
    const RealVectorValue & _v;
    const VariableValue & _pressure_coolant;
    unsigned int _pressure_coolant_var;
};