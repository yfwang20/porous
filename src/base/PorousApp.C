#include "PorousApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
PorousApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  return params;
}

PorousApp::PorousApp(InputParameters parameters) : MooseApp(parameters)
{
  PorousApp::registerAll(_factory, _action_factory, _syntax);
}

PorousApp::~PorousApp() {}

void 
PorousApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAllObjects<PorousApp>(f, af, s);
  Registry::registerObjectsTo(f, {"PorousApp"});
  Registry::registerActionsTo(af, {"PorousApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
PorousApp::registerApps()
{
  registerApp(PorousApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
PorousApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  PorousApp::registerAll(f, af, s);
}
extern "C" void
PorousApp__registerApps()
{
  PorousApp::registerApps();
}
