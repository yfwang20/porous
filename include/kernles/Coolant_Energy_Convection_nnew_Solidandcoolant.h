#pragma once

#include "Kernel.h"

class Coolant_Energy_Convection_nnew_Solidandcoolant : public Kernel
{
public:
    Coolant_Energy_Convection_nnew_Solidandcoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;


private:
    const MaterialProperty<Real> & _coolant_capacity;
    const Real & _rhou;
    const RealVectorValue & _v;
};