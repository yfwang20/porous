#include "Solid_Diffusion_term.h"
registerMooseObject("PorousApp", Solid_Diffusion_term);

InputParameters Solid_Diffusion_term::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Solid_Diffusion_term::Solid_Diffusion_term(const InputParameters & parameters)
    :   Diffusion(parameters),
        _solid_k(getMaterialProperty<Real>("solid_k"))
{
}

Real Solid_Diffusion_term::computeQpResidual()
{
    return _solid_k[_qp] * Diffusion::computeQpResidual();
}

Real Solid_Diffusion_term::computeQpJacobian()
{
    return _solid_k[_qp] * Diffusion::computeQpJacobian();
}