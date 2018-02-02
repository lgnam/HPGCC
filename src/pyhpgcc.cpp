#include <iostream>

#include "hpgcc.hpp"
#include <boost/python.hpp>

namespace hpgcc {
namespace python {

void exportPythonModule() {

  boost::python::class_<HPGCC>("HPGCC", boost::python::init<>())
      .def("Read", &HPGCC::Read)
      //.def("shuffle", &hpgcc::HPGCC::shuffle)
      .def("Greedy", &HPGCC::Greedy);
      //.def_readwrite("filename", &hpgcc::HPGCC::filename)
      //.def_readwrite("shuffled", &hpgcc::HPGCC::shuffled);
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