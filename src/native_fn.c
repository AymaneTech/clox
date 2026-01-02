#include "native_fn.h"
#include <time.h>

Value clock_native(int arg_count, Value* args)
{
    return NUMBER_VAL((double)clock() / CLOCKS_PER_SEC);
}
