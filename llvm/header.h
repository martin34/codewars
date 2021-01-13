static int foo;

void blub(int i) { ++i; }

struct a {
  int b;
  int c;
};

class x {
  int y;
};

class xx

{

  int yy;
};

class MyClass {
public:
  int field;
  virtual void method() const = 0;

  static const int static_field;
  static int static_method();
};
