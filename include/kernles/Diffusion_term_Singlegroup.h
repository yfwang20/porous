#pragma once

#include "Diffusion.h"

class Diffusion_term_Singlegroup : public Diffusion
{
public:
    Diffusion_term_Singlegroup(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _diffusion_coefficient;
    // const MaterialProperty<Real> & _power_coefficient;
};