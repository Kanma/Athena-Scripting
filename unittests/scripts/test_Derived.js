import_module('module1');

derived = new module1.Derived(10, 5);
CHECK_CLOSE(10, derived.a);
CHECK_CLOSE(5, derived.b);

derived.a = 20;
derived.b = 10;
CHECK_CLOSE(20, derived.a);
CHECK_CLOSE(10, derived.b);

derived.f();
CHECK_CLOSE(60, derived.a);
CHECK_CLOSE(20, derived.b);

derived.g();
CHECK_CLOSE(100, derived.a);
CHECK_CLOSE(20, derived.b);

derived.h();
CHECK_CLOSE(100, derived.a);
CHECK_CLOSE(200, derived.b);
