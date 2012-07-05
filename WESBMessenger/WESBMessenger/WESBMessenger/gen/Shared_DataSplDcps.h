#ifndef SHARED_DATASPLTYPES_H
#define SHARED_DATASPLTYPES_H

#include "ccpp_Shared_Data.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __Shared_Data_Shared_Data__load (c_base base);

extern c_metaObject __Shared_Data_DDS_int__load (c_base base);
extern char * __Shared_Data_DDS_int__keys (void);
extern char * __Shared_Data_DDS_int__name (void);
struct _Shared_Data_DDS_int ;
extern  c_bool __Shared_Data_DDS_int__copyIn(c_base base, struct Shared_Data::DDS_int *from, struct _Shared_Data_DDS_int *to);
extern  void __Shared_Data_DDS_int__copyOut(void *_from, void *_to);
struct _Shared_Data_DDS_int {
    c_long data;
    c_long time;
    c_long timems;
    c_bool valid;
};

extern c_metaObject __Shared_Data_DDS_float__load (c_base base);
extern char * __Shared_Data_DDS_float__keys (void);
extern char * __Shared_Data_DDS_float__name (void);
struct _Shared_Data_DDS_float ;
extern  c_bool __Shared_Data_DDS_float__copyIn(c_base base, struct Shared_Data::DDS_float *from, struct _Shared_Data_DDS_float *to);
extern  void __Shared_Data_DDS_float__copyOut(void *_from, void *_to);
struct _Shared_Data_DDS_float {
    c_float data;
    c_long time;
    c_long timems;
    c_bool valid;
};

extern c_metaObject __Shared_Data_DDS_string__load (c_base base);
extern char * __Shared_Data_DDS_string__keys (void);
extern char * __Shared_Data_DDS_string__name (void);
struct _Shared_Data_DDS_string ;
extern  c_bool __Shared_Data_DDS_string__copyIn(c_base base, struct Shared_Data::DDS_string *from, struct _Shared_Data_DDS_string *to);
extern  void __Shared_Data_DDS_string__copyOut(void *_from, void *_to);
struct _Shared_Data_DDS_string {
    c_string data;
    c_long time;
    c_long timems;
    c_bool valid;
};

#endif
