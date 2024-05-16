#pragma once

#include "Kernel.h"

class Coolant_Continuity_Fake : public Kernel
{
public:
    Coolant_Continuity_Fake(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const Real & _tem_coolant_topboundary;
    const Real & _u_coolant_topboundary;
    
    const MaterialProperty<Real> & _coolant_rho;
};