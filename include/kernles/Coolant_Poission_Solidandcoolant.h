#pragma once

#include "Kernel.h"

class Coolant_Poission_Solidandcoolant : public Kernel
{
public:
    Coolant_Poission_Solidandcoolant(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _coolant_rho;
    const MaterialProperty<Real> & _porous_coefficient;
    const MaterialProperty<Real> & _flow_resistance;
    const RealVectorValue & _v1;
    const RealVectorValue & _v2;
};