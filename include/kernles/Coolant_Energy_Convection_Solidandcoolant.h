#pragma once

#include "Kernel.h"

class Coolant_Energy_Convection_Solidandcoolant : public Kernel
{
public:
    Coolant_Energy_Convection_Solidandcoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

    virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
    const MaterialProperty<Real> & _coolant_rho;
    const MaterialProperty<Real> & _coolant_capacity;
    const VariableValue & _u_coolant;
    const VariableGradient & _grad_u_coolant;
    unsigned int _u_coolant_var;
    const VariableValue & _tem_coolant;
    const VariableGradient & _grad_tem_coolant;
    int _component;
};