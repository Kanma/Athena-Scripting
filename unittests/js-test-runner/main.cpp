#include <Athena-Scripting/ScriptingManager.h>
#include <iostream>
#include <string>

using namespace Athena::Scripting;
using namespace v8;
using namespace std;


bool runTest(const std::string& strFilePath)
{
    ScriptingManager manager;
    HandleScope      handle_scope;

	Handle<Value> result = manager.executeFile(ATHENA_SCRIPTING_JS_TEST_RUNNER_PATH "tests.js");
    if (result.IsEmpty())
    {  
        cout << "Failed to load the 'tests.js' file from '" << ATHENA_SCRIPTING_JS_TEST_RUNNER_PATH << "'" << endl;
        return false;
    }

	result = manager.executeFile(strFilePath);
    if (result.IsEmpty())
    {  
        cout << strFilePath.c_str() << ": error: " << manager.getLastError().c_str() << endl;
        return false;
    }

    return true;
}


int main(int argc, char** argv)
{
    int nbTestsFailed = 0;
    string strPath;
    int start = 2;

    if (argc > 1)
    {
        strPath = argv[1];
        if (strPath[strPath.size() - 1] != '/')
        {
            strPath = "";
            start = 1;
        }
    }

    for (int i = start; i < argc; ++i)
    {
        if (!runTest(strPath + argv[i]))
            ++nbTestsFailed;
    }

    if (nbTestsFailed > 0)
        cout << "FAILURE: " << nbTestsFailed << " out of " << (argc - start) << " tests failed" << endl;
    else
        cout << "Success: " << (argc - start) << " tests passed" << endl;

    return (nbTestsFailed > 0 ? 1 : 0);
}
