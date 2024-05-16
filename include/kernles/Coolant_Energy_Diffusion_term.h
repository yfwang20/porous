#pragma once

#include "Diffusion.h"

class Coolant_Energy_Diffusion_term : public Diffusion
{
public:
    Coolant_Energy_Diffusion_term(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _porous_coefficient;
    const MaterialProperty<Real> & _coolant_lambda;
};