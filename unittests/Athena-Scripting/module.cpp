#include <v8.h>
#include <Athena-Scripting/Utils.h>


using namespace v8;
using namespace Athena::Scripting;


/************************************** CLASS Point *************************************/

class Point
{
public:
    Point(int x, int y)
    : x(x), y(y)
    {
    }
    
    int x, y;
};


/************************************ BINDING OF Point **********************************/

#define CastJSPoint(HANDLE) CastJSObject<Point>(HANDLE, 1)


Persistent<ObjectTemplate> point_template;


// Destructor
void PointWeakCallback(Persistent<Value> value, void* data)
{
    if (value.IsNearDeath())
    {
        Point* p = CastJSPoint(value);
        delete p;
    }
}


// Constructor
Handle<Value> NewPoint(const Arguments& args)
{
    return createJSObject(point_template, PointWeakCallback, new Point(0, 0), sizeof(Point), 1);
}


Handle<Value> GetPointX(Local<String> property, const AccessorInfo &info)
{
    Point* p = CastJSPoint(info.Holder());
    return Integer::New(p->x);
}


void SetPointX(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    Point* p = CastJSPoint(info.Holder());
    p->x = value->Int32Value();
}


Handle<Value> GetPointY(Local<String> property, const AccessorInfo &info)
{
    Point* p = CastJSPoint(info.Holder());
    return Integer::New(p->y);
}


void SetPointY(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    Point* p = CastJSPoint(info.Holder());
    p->y = value->Int32Value();
}


/*************************************** FUNCTIONS **************************************/

Handle<Value> sum(const Arguments& args)
{
    HandleScope handle_scope;

    int result = args[0]->ToInt32()->Value() + args[1]->ToInt32()->Value();
    
    return handle_scope.Close(Int32::New(result));
}


Handle<Value> raiseException(const Arguments& args)
{
    return ThrowException(String::New("Something bad happened!"));
}


/****************************** INITIALISATION OF THE MODULE ****************************/

extern "C" {

    bool init_module(Handle<Object> parent)
    {
        HandleScope handle_scope;

        // Bind the 'sum' function
        if (!parent->Set(String::New("sum"), FunctionTemplate::New(sum)->GetFunction()) ||
            !parent->Set(String::New("raiseException"), FunctionTemplate::New(raiseException)->GetFunction()))
            return false;
        
        // Bind the 'Point' class
        point_template = Persistent<ObjectTemplate>::New(ObjectTemplate::New());
        point_template->SetCallAsFunctionHandler(NewPoint);
        point_template->SetInternalFieldCount(2);

        point_template->SetAccessor(String::New("x"), GetPointX, SetPointX);
        point_template->SetAccessor(String::New("y"), GetPointY, SetPointY);

        if (!parent->Set(String::New("Point"), FunctionTemplate::New(NewPoint)->GetFunction()))
            return false;
        
        return true;
    }
}
