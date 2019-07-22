#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include "node.h"

int main(int argc, char** argv) {
  Catch::Session session;
  // Let Catch (using Clara) parse the command line
  int returnCode = session.applyCommandLine(argc, argv);
  if (returnCode != 0)  // Indicates a command line error
    return returnCode;

  return session.run();
}
