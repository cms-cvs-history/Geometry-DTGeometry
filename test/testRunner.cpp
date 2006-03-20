/*
  Generic test runner for CppUnit based tests. No modifications needed

  \author CppUnit Cookbook
 */

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

int main()
{
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry& registry = 
    CppUnit::TestFactoryRegistry::getRegistry();

  runner.addTest( registry.makeTest() );

  bool ret = runner.run("", false);
  return ret ? 0 : 1;
}


