try
{
    module1.Point3D = function(x, y, z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
    }


    module1.Point3D.prototype.double = function()
    {
        this.x *= 2;
        this.y *= 2;
        this.z *= 2;
    }
}
catch (e)
{
}
