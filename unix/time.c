#include <string.h>
#include <time.h>

#include "misc.h"
#include "mpconfig.h"
#include "qstr.h"
#include "obj.h"
#include "runtime.h"

static mp_obj_t mod_time_time() {
    return mp_obj_new_int((machine_int_t)time(NULL));
}
static MP_DEFINE_CONST_FUN_OBJ_0(mod_time_time_obj, mod_time_time);

// Note: this is deprecated since CPy3.3, but pystone still uses it.
static mp_obj_t mod_time_clock() {
//    return mp_obj_new_int((machine_int_t)clock());
    // POSIX requires CLOCKS_PER_SEC equals 1000000, so that's what we assume
    // float cannot represent full range of int32 precisely, so we pre-divide
    // int to reduce resolution, and then actually do float division hoping
    // to preserve integer part resolution.
    return mp_obj_new_float((float)(clock() / 1000) / 1000.0);
}
static MP_DEFINE_CONST_FUN_OBJ_0(mod_time_clock_obj, mod_time_clock);

void time_init() {
    mp_obj_t m = mp_obj_new_module(QSTR_FROM_STR_STATIC("time"));
    rt_store_attr(m, QSTR_FROM_STR_STATIC("time"), (mp_obj_t)&mod_time_time_obj);
    rt_store_attr(m, QSTR_FROM_STR_STATIC("clock"), (mp_obj_t)&mod_time_clock_obj);
}
