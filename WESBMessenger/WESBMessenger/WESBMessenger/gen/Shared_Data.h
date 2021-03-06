//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: Shared_Data.h
//  Source: Shared_Data.idl
//  Generated: Wed Dec 28 14:17:28 2011
//  OpenSplice V5.4.1OSS
//  
//******************************************************************
#ifndef _SHARED_DATA_H_
#define _SHARED_DATA_H_

#include "sacpp_mapping.h"
#include "sacpp_DDS_DCPS.h"

namespace Shared_Data
{
   struct DDS_int;
   struct DDS_float;
   struct DDS_string;

   struct DDS_int
   {
      DDS::Long data;
      DDS::Long time;
      DDS::Long timems;
      DDS::Boolean valid;
   };

   typedef DDS_DCPSStruct_var < DDS_int> DDS_int_var;
   typedef DDS_int&DDS_int_out;

   struct DDS_float
   {
      DDS::Float data;
      DDS::Long time;
      DDS::Long timems;
      DDS::Boolean valid;
   };

   typedef DDS_DCPSStruct_var < DDS_float> DDS_float_var;
   typedef DDS_float&DDS_float_out;

   struct DDS_string
   {
      DDS::String_mgr data;
      DDS::Long time;
      DDS::Long timems;
      DDS::Boolean valid;
   };

   typedef DDS_DCPSStruct_var < DDS_string> DDS_string_var;
   typedef DDS_DCPSStruct_out < DDS_string> DDS_string_out;
}




#endif 
