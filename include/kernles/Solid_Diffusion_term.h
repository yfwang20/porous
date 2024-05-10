#pragma once

#include "Diffusion.h"

class Solid_Diffusion_term : public Diffusion
{
public:
    Solid_Diffusion_term(const InputParameters & parameters);

    static InputParameters validParams();

protected:
    virtual Real computeQpResidual() override;
    
    virtual Real computeQpJacobian() override;

private:
    const MaterialProperty<Real> & _solid_k;
};