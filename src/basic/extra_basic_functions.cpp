#include <my_basic.h>

static int _foo(struct mb_interpreter_t* s, void** l, mb_value_t* va, unsigned ca, void* r, mb_has_routine_arg_func_t has, mb_pop_routine_arg_func_t pop) {
    int result = MB_FUNC_OK;
    mb_value_t val;
    unsigned ia = 0;

    mb_assert(s && l);

    mb_check(mb_attempt_open_bracket(s, l));

    mb_make_nil(val);
    if(has(s, l, va, ca, &ia, r)) {
        mb_check(pop(s, l, va, ca, &ia, r, &val));
    }

    mb_check(mb_attempt_close_bracket(s, l));

    printf("%d\n", val.value.integer);

    return result;
}

static int _test(struct mb_interpreter_t* s, void** l) {
    int result = MB_FUNC_OK;

    mb_assert(s && l);

    mb_check(mb_attempt_func_begin(s, l));
    mb_check(mb_attempt_func_end(s, l));

    mb_set_routine(s, l, "FOO", _foo, true); /* Define a routine named "FOO" */

    return result;
}