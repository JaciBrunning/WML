#pragma once

#include <networktables/NetworkTable.h>

namespace wml {
class NTBoundDouble {
 public:
  NTBoundDouble(std::shared_ptr<nt::NetworkTable> table, std::string name, double *value);
  NTBoundDouble(const NTBoundDouble &other) : NTBoundDouble(other._table, other._name, other._val) {}
  ~NTBoundDouble();

  void Override(double newVal);
  
 private:
  std::shared_ptr<nt::NetworkTable> _table;
  nt::NetworkTableEntry _entry;
  NT_EntryListener _listener;
  std::string _name;
  double *_val;
};
}  // namespace wml