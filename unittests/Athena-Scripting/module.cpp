#include <v8.h>

using namespace v8;


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

Persistent<ObjectTemplate> point_template;


// Destructor
void PointWeakCallback(Persistent<Value> value, void* data)
{
    if (value.IsNearDeath())
    {
        Local<External> wrap = Local<External>::Cast(Persistent<Object>::Cast(value)->GetInternalField(0));
        Point* p = static_cast<Point*>(wrap->Value());
        delete p;
    }
}


// Constructor
Handle<Value> NewPoint(const Arguments& args)
{
    Point* p = new Point(0, 0);
    Persistent<Object> jsPoint = Persistent<Object>::New(point_template->NewInstance());
    jsPoint->SetInternalField(0, External::New(p));
    jsPoint.MakeWeak(0, PointWeakCallback);
    
    V8::AdjustAmountOfExternalAllocatedMemory(sizeof(Point));
    
    return jsPoint;
}


Handle<Value> GetPointX(Local<String> property, const AccessorInfo &info)
{
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    Point* p = static_cast<Point*>(wrap->Value());
    return Integer::New(p->x);
}


void SetPointX(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    Point* p = static_cast<Point*>(wrap->Value());
    p->x = value->Int32Value();
}


Handle<Value> GetPointY(Local<String> property, const AccessorInfo &info)
{
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    Point* p = static_cast<Point*>(wrap->Value());
    return Integer::New(p->y);
}


void SetPointY(Local<String> property, Local<Value> value, const AccessorInfo& info)
{
    Local<Object> self = info.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    Point* p = static_cast<Point*>(wrap->Value());
    p->y = value->Int32Value();
}


/*************************************** FUNCTIONS **************************************/

Handle<Value> sum(const Arguments& args)
{
    HandleScope handle_scope;

    int result = args[0]->ToInt32()->Value() + args[1]->ToInt32()->Value();
    
    return handle_scope.Close(Int32::New(result));
}


/****************************** INITIALISATION OF THE MODULE ****************************/

extern "C" {

    bool init_module(Handle<Object> parent)
    {
        HandleScope handle_scope;

        // Bind the 'sum' function
        if (!parent->Set(String::New("sum"), FunctionTemplate::New(sum)->GetFunction()))
            return false;
        
        // Bind the 'Point' class
        point_template = Persistent<ObjectTemplate>::New(ObjectTemplate::New());
        point_template->SetCallAsFunctionHandler(NewPoint);
        point_template->SetInternalFieldCount(1);

        point_template->SetAccessor(String::New("x"), GetPointX, SetPointX);
        point_template->SetAccessor(String::New("y"), GetPointY, SetPointY);

        if (!parent->Set(String::New("Point"), FunctionTemplate::New(NewPoint)->GetFunction()))
            return false;
        
        return true;
    }
}
