#include "PointerTest.h"
#include "../SmartPtr.cpp"
#include "../WeakPtr.cpp"

template class Containers::SmartPtr<Containers::Tests::PointerTest::MockChild>;
template class Containers::WeakPtr<Containers::Tests::PointerTest::MockChild>;
