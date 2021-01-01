#pragma once

class B;
void AFunction(B &b);

class A {
public:
  A(B &b) : b_ref_{b}, b_pointer_{&b} {}
  void Do();

private:
  // Reference and Pointer for forward decalred type can be used, but not the
  // actual type
  B &b_ref_;
  B *b_pointer_;
};
