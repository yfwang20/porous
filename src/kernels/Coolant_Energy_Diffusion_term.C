#include "Coolant_Energy_Diffusion_term.h"
registerMooseObject("PorousApp", Coolant_Energy_Diffusion_term);

InputParameters Coolant_Energy_Diffusion_term::validParams()
{
    InputParameters params = Kernel::validParams();
    return params;
}

Coolant_Energy_Diffusion_term::Coolant_Energy_Diffusion_term(const InputParameters & parameters)
    :   Diffusion(parameters),
        _porous_coefficient(getMaterialProperty<Real>("porous_coefficient")),
        _coolant_lambda(getMaterialProperty<Real>("coolant_lambda"))
{
}

Real Coolant_Energy_Diffusion_term::computeQpResidual()
{
    return _porous_coefficient[_qp] * _coolant_lambda[_qp] * Diffusion::computeQpResidual();
}

Real Coolant_Energy_Diffusion_term::computeQpJacobian()
{
    return _porous_coefficient[_qp] * _coolant_lambda[_qp] * Diffusion::computeQpJacobian();
}