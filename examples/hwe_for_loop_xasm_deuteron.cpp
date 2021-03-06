#include "qcor.hpp"

int main(int argc, char **argv) {

  qcor::Initialize(argc, argv);

  auto ansatz = [&](qbit q, std::vector<double> x) {
    for (auto i = 0; i < 2; i++) {
        Rx(q[i],x[i]);
        Rz(q[i],x[2+i]);
    }
    CX(q[1],q[0]);
    for (auto i = 0; i < 2; i++) {
        Rx(q[i], x[i+4]);
        Rz(q[i], x[i+4+2]);
        Rx(q[i], x[i+4+4]);
    }
  };

  auto optimizer =
      qcor::getOptimizer("nlopt", {std::make_pair("nlopt-optimizer", "cobyla"),
                                   std::make_pair("nlopt-maxeval", 100)});

  auto observable =
      qcor::getObservable("pauli", std::string("5.907 - 2.1433 X0X1 "
                                               "- 2.1433 Y0Y1"
                                               "+ .21829 Z0 - 6.125 Z1"));
  auto handle = qcor::taskInitiate(ansatz, "vqe", optimizer, observable, std::vector<double>{});
  auto results = qcor::sync(handle);
}
