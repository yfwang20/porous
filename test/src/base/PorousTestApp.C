//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "PorousTestApp.h"
#include "PorousApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
PorousTestApp::validParams()
{
  InputParameters params = PorousApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  return params;
}

PorousTestApp::PorousTestApp(InputParameters parameters) : MooseApp(parameters)
{
  PorousTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

PorousTestApp::~PorousTestApp() {}

void
PorousTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  PorousApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"PorousTestApp"});
    Registry::registerActionsTo(af, {"PorousTestApp"});
  }
}

void
PorousTestApp::registerApps()
{
  registerApp(PorousApp);
  registerApp(PorousTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
PorousTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  PorousTestApp::registerAll(f, af, s);
}
extern "C" void
PorousTestApp__registerApps()
{
  PorousTestApp::registerApps();
}
