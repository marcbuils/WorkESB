#include "Shared_DataSplDcps.h"
#include "ccpp_Shared_Data.h"

char *
__Shared_Data_DDS_int__name(void)
{
    return CORBA::string_dup("Shared_Data::DDS_int");
}

char *
__Shared_Data_DDS_int__keys(void)
{
    return CORBA::string_dup("");
}

char *
__Shared_Data_DDS_float__name(void)
{
    return CORBA::string_dup("Shared_Data::DDS_float");
}

char *
__Shared_Data_DDS_float__keys(void)
{
    return CORBA::string_dup("");
}

char *
__Shared_Data_DDS_string__name(void)
{
    return CORBA::string_dup("Shared_Data::DDS_string");
}

char *
__Shared_Data_DDS_string__keys(void)
{
    return CORBA::string_dup("");
}

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>

c_bool
__Shared_Data_DDS_int__copyIn(
    c_base base,
    struct ::Shared_Data::DDS_int *from,
    struct _Shared_Data_DDS_int *to)
{
    c_bool result = TRUE;

    to->data = (c_long)from->data;
    to->time = (c_long)from->time;
    to->timems = (c_long)from->timems;
    to->valid = (c_bool)from->valid;
    return result;
}

c_bool
__Shared_Data_DDS_float__copyIn(
    c_base base,
    struct ::Shared_Data::DDS_float *from,
    struct _Shared_Data_DDS_float *to)
{
    c_bool result = TRUE;

    to->data = (c_float)from->data;
    to->time = (c_long)from->time;
    to->timems = (c_long)from->timems;
    to->valid = (c_bool)from->valid;
    return result;
}

c_bool
__Shared_Data_DDS_string__copyIn(
    c_base base,
    struct ::Shared_Data::DDS_string *from,
    struct _Shared_Data_DDS_string *to)
{
    c_bool result = TRUE;

#ifdef OSPL_BOUNDS_CHECK
    if(from->data){
        to->data = c_stringNew(base, from->data);
    } else {
        result = FALSE;
    }
#else
    to->data = c_stringNew(base, from->data);
#endif
    to->time = (c_long)from->time;
    to->timems = (c_long)from->timems;
    to->valid = (c_bool)from->valid;
    return result;
}

void
__Shared_Data_DDS_int__copyOut(
    void *_from,
    void *_to)
{
    struct _Shared_Data_DDS_int *from = (struct _Shared_Data_DDS_int *)_from;
    struct ::Shared_Data::DDS_int *to = (struct ::Shared_Data::DDS_int *)_to;
    to->data = (::DDS::Long)from->data;
    to->time = (::DDS::Long)from->time;
    to->timems = (::DDS::Long)from->timems;
    to->valid = (::DDS::Boolean)from->valid;
}

void
__Shared_Data_DDS_float__copyOut(
    void *_from,
    void *_to)
{
    struct _Shared_Data_DDS_float *from = (struct _Shared_Data_DDS_float *)_from;
    struct ::Shared_Data::DDS_float *to = (struct ::Shared_Data::DDS_float *)_to;
    to->data = (::DDS::Float)from->data;
    to->time = (::DDS::Long)from->time;
    to->timems = (::DDS::Long)from->timems;
    to->valid = (::DDS::Boolean)from->valid;
}

void
__Shared_Data_DDS_string__copyOut(
    void *_from,
    void *_to)
{
    struct _Shared_Data_DDS_string *from = (struct _Shared_Data_DDS_string *)_from;
    struct ::Shared_Data::DDS_string *to = (struct ::Shared_Data::DDS_string *)_to;
    to->data = CORBA::string_dup(from->data);
    to->time = (::DDS::Long)from->time;
    to->timems = (::DDS::Long)from->timems;
    to->valid = (::DDS::Boolean)from->valid;
}

