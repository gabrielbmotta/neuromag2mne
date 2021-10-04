#ifndef CALLBACK
#define CALLBACK

template<typename A, typename B>
struct Callback{
    Callback(A trigger, B function)
    : m_trigger(trigger)
    , m_function(function)
    { };

    A m_trigger;
    B m_function;
};


#endif

