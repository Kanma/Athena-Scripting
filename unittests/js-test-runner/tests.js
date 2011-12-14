function CHECK(test, message)
{
    if (!test)
        throw message;
}


function CHECK_EQUAL(wanted, value)
{
    if (value != wanted)
        throw "Expected " + wanted + ", got " + value;
}


function CHECK_CLOSE(wanted, value, epsilon)
{
    if (epsilon == undefined)
        epsilon = 1e-6;
    
    if ((value < wanted - epsilon) || (value > wanted + epsilon))
        throw "Expected " + wanted + " +/- " + epsilon + ", got " + value;
}
