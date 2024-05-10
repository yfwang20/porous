#pragma once

#include "IntegratedBC.h"

/**
 * Implements a simple constant Neumann BC where grad(u)=alpha * v on the boundary.
 * Uses the term produced from integrating the diffusion operator by parts.
 */
class Neutron_Vacuum_bc : public IntegratedBC
{
public:
  Neutron_Vacuum_bc(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

private:
  const MaterialProperty<Real> & _diffusion_coefficient;
};