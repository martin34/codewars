#include "a.h"
#include "b.h"

void AFunction(B &b) { b.Do(); }

void A::Do() {
  AFunction(b_ref_);
  AFunction(*b_pointer_);
}
