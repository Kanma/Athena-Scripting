import_module('module1');

p = new module1.Point();
p.x = 10;
p.y = p.x * 2;


p = new module1.Point3D(1, 2, 3);
p.double()
CHECK_CLOSE(2, p.x);
CHECK_CLOSE(4, p.y);
CHECK_CLOSE(6, p.z);
