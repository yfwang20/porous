#pragma once

#include "Kernel.h"

class Coolant_Continuity : public Kernel
{
public:
    Coolant_Continuity(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const RealVectorValue & _v;
    const MaterialProperty<Real> & _coolant_rho;
};