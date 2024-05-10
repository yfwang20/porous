#include "Diffusion_term_Singlegroup.h"
registerMooseObject("PorousApp", Diffusion_term_Singlegroup);

InputParameters Diffusion_term_Singlegroup::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Diffusion_term_Singlegroup::Diffusion_term_Singlegroup(const InputParameters & parameters)
    :   Diffusion(parameters),
        _diffusion_coefficient(getMaterialProperty<Real>("diffusion_coefficient"))
        // _power_coefficient(getMaterialProperty<Real>("power_coefficient"))
{
}

Real Diffusion_term_Singlegroup::computeQpResidual()
{
    // return _diffusion_coefficient[_qp] * Diffusion::computeQpResidual() * _power_coefficient[_qp];
    return _diffusion_coefficient[_qp] * Diffusion::computeQpResidual();
}

Real Diffusion_term_Singlegroup::computeQpJacobian()
{
    // return _diffusion_coefficient[_qp] * Diffusion::computeQpJacobian() * _power_coefficient[_qp];
    return _diffusion_coefficient[_qp] * Diffusion::computeQpJacobian();
}