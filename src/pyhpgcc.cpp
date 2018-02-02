#include <iostream>

#include "hpgcc.h"
#include <boost/python.hpp>

namespace hpgcc {
namespace python {

void exportPythonModule() {

  boost::python::class_<hpgcc::HPGCC>("HPGCC", boost::python::init<>())
      .def("read", &hpgcc::HPGCC::read)
      .def("shuffle", &hpgcc::HPGCC::shuffle)
      .def("colorGreedy", &hpgcc::HPGCC::colorGreedy)
      .def_readwrite("filename", &hpgcc::HPGCC::filename)
      .def_readwrite("shuffled", &hpgcc::HPGCC::shuffled);
}

// define python package
BOOST_PYTHON_MODULE(pyhpgcc) {

  namespace py = boost::python;
  // specify that this module is actually a package
  boost::python::object package = boost::python::scope();
  package.attr("__path__") = "pyhpgcc";

  // export submodules
  exportPythonModule();
}
}
}