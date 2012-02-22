import_module('module1');

base = new module1.Base(10);
CHECK_CLOSE(10, base.a);

base.a = 20;
CHECK_CLOSE(20, base.a);

base.f();
CHECK_CLOSE(40, base.a);

base.g();
CHECK_CLOSE(100, base.a);
