#ifndef SHARED_DATADCPS_IMPL_H_
#define SHARED_DATADCPS_IMPL_H_

#include "ccpp.h"
#include "ccpp_Shared_Data.h"
#include "ccpp_TypeSupport_impl.h"
#include "ccpp_DataWriter_impl.h"
#include "ccpp_DataReader_impl.h"
#include "ccpp_DataReaderView_impl.h"


namespace Shared_Data {

    class  DDS_intTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
    {
    public:
        DDS_intTypeSupportFactory() {}
        virtual ~DDS_intTypeSupportFactory() {}
    private:
        ::DDS::DataWriter_ptr 
        create_datawriter (gapi_dataWriter handle);
    
        ::DDS::DataReader_ptr 
        create_datareader (gapi_dataReader handle);
    
        ::DDS::DataReaderView_ptr 
        create_view (gapi_dataReaderView handle);
    };
    
    class  DDS_intTypeSupport : public virtual DDS_intTypeSupportInterface,
                                   public ::DDS::TypeSupport_impl
    {
    public:
        virtual ::DDS::ReturnCode_t register_type(
            ::DDS::DomainParticipant_ptr participant,
            const char * type_name) THROW_ORB_EXCEPTIONS;
    
        virtual char * get_type_name() THROW_ORB_EXCEPTIONS;    
    
        DDS_intTypeSupport (void);
        virtual ~DDS_intTypeSupport (void);
    
    private:
        DDS_intTypeSupport (const DDS_intTypeSupport &);
        void operator= (const DDS_intTypeSupport &);
    
        static const char *metaDescriptor;
    };
    
    typedef DDS_intTypeSupportInterface_var DDS_intTypeSupport_var;
    typedef DDS_intTypeSupportInterface_ptr DDS_intTypeSupport_ptr;
    
    class  DDS_intDataWriter_impl : public virtual DDS_intDataWriter,
                                        public ::DDS::DataWriter_impl
    {
    public:
    
        virtual ::DDS::InstanceHandle_t register_instance(
            const DDS_int & instance_data) THROW_ORB_EXCEPTIONS;
            
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
            const DDS_int & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
            
        virtual ::DDS::ReturnCode_t unregister_instance(
            const DDS_int & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
            const DDS_int & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write(
            const DDS_int & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp(
            const DDS_int & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose(
            const DDS_int & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp(
            const DDS_int & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose(
            const DDS_int & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
            const DDS_int & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            DDS_int & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const DDS_int & instance_data) THROW_ORB_EXCEPTIONS;
    
    
        DDS_intDataWriter_impl (
            gapi_dataWriter handle
        );
    
        virtual ~DDS_intDataWriter_impl (void);
    
    private:
        DDS_intDataWriter_impl(const DDS_intDataWriter_impl &);
        void operator= (const DDS_intDataWriter &);
    };
    
    class  DDS_intDataReader_impl : public virtual DDS_intDataReader,
                                        public ::DDS::DataReader_impl
    {
        friend class DDS_intDataReaderView_impl;
    public:
        virtual ::DDS::ReturnCode_t read(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_w_condition(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_w_condition(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            DDS_int & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            DDS_int & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_instance(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_instance(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_next_instance(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t get_key_value(
            DDS_int & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const DDS_int & instance) THROW_ORB_EXCEPTIONS;
    
        DDS_intDataReader_impl (
            gapi_dataReader handle
        );
    
        virtual ~DDS_intDataReader_impl(void);
    
    private:
        DDS_intDataReader_impl(const DDS_intDataReader &);
        void operator= (const DDS_intDataReader &);
    
        static ::DDS::ReturnCode_t check_preconditions(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples
        );
    };
    
    class  DDS_intDataReaderView_impl : public virtual DDS_intDataReaderView,
                                        public ::DDS::DataReaderView_impl
    {
    public:
        virtual ::DDS::ReturnCode_t read(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_w_condition(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_w_condition(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            DDS_int & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            DDS_int & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_instance(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_instance(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_next_instance(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            DDS_intSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t get_key_value(
            DDS_int & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const DDS_int & instance) THROW_ORB_EXCEPTIONS;
    
        DDS_intDataReaderView_impl (
            gapi_dataReader handle
        );
    
        virtual ~DDS_intDataReaderView_impl(void);
    
    private:
        DDS_intDataReaderView_impl(const DDS_intDataReaderView &);
        void operator= (const DDS_intDataReaderView &);
    };
    
    class  DDS_floatTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
    {
    public:
        DDS_floatTypeSupportFactory() {}
        virtual ~DDS_floatTypeSupportFactory() {}
    private:
        ::DDS::DataWriter_ptr 
        create_datawriter (gapi_dataWriter handle);
    
        ::DDS::DataReader_ptr 
        create_datareader (gapi_dataReader handle);
    
        ::DDS::DataReaderView_ptr 
        create_view (gapi_dataReaderView handle);
    };
    
    class  DDS_floatTypeSupport : public virtual DDS_floatTypeSupportInterface,
                                   public ::DDS::TypeSupport_impl
    {
    public:
        virtual ::DDS::ReturnCode_t register_type(
            ::DDS::DomainParticipant_ptr participant,
            const char * type_name) THROW_ORB_EXCEPTIONS;
    
        virtual char * get_type_name() THROW_ORB_EXCEPTIONS;    
    
        DDS_floatTypeSupport (void);
        virtual ~DDS_floatTypeSupport (void);
    
    private:
        DDS_floatTypeSupport (const DDS_floatTypeSupport &);
        void operator= (const DDS_floatTypeSupport &);
    
        static const char *metaDescriptor;
    };
    
    typedef DDS_floatTypeSupportInterface_var DDS_floatTypeSupport_var;
    typedef DDS_floatTypeSupportInterface_ptr DDS_floatTypeSupport_ptr;
    
    class  DDS_floatDataWriter_impl : public virtual DDS_floatDataWriter,
                                        public ::DDS::DataWriter_impl
    {
    public:
    
        virtual ::DDS::InstanceHandle_t register_instance(
            const DDS_float & instance_data) THROW_ORB_EXCEPTIONS;
            
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
            const DDS_float & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
            
        virtual ::DDS::ReturnCode_t unregister_instance(
            const DDS_float & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
            const DDS_float & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write(
            const DDS_float & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp(
            const DDS_float & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose(
            const DDS_float & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp(
            const DDS_float & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose(
            const DDS_float & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
            const DDS_float & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            DDS_float & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const DDS_float & instance_data) THROW_ORB_EXCEPTIONS;
    
    
        DDS_floatDataWriter_impl (
            gapi_dataWriter handle
        );
    
        virtual ~DDS_floatDataWriter_impl (void);
    
    private:
        DDS_floatDataWriter_impl(const DDS_floatDataWriter_impl &);
        void operator= (const DDS_floatDataWriter &);
    };
    
    class  DDS_floatDataReader_impl : public virtual DDS_floatDataReader,
                                        public ::DDS::DataReader_impl
    {
        friend class DDS_floatDataReaderView_impl;
    public:
        virtual ::DDS::ReturnCode_t read(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_w_condition(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_w_condition(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            DDS_float & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            DDS_float & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_instance(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_instance(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_next_instance(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t get_key_value(
            DDS_float & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const DDS_float & instance) THROW_ORB_EXCEPTIONS;
    
        DDS_floatDataReader_impl (
            gapi_dataReader handle
        );
    
        virtual ~DDS_floatDataReader_impl(void);
    
    private:
        DDS_floatDataReader_impl(const DDS_floatDataReader &);
        void operator= (const DDS_floatDataReader &);
    
        static ::DDS::ReturnCode_t check_preconditions(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples
        );
    };
    
    class  DDS_floatDataReaderView_impl : public virtual DDS_floatDataReaderView,
                                        public ::DDS::DataReaderView_impl
    {
    public:
        virtual ::DDS::ReturnCode_t read(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_w_condition(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_w_condition(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            DDS_float & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            DDS_float & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_instance(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_instance(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_next_instance(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            DDS_floatSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t get_key_value(
            DDS_float & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const DDS_float & instance) THROW_ORB_EXCEPTIONS;
    
        DDS_floatDataReaderView_impl (
            gapi_dataReader handle
        );
    
        virtual ~DDS_floatDataReaderView_impl(void);
    
    private:
        DDS_floatDataReaderView_impl(const DDS_floatDataReaderView &);
        void operator= (const DDS_floatDataReaderView &);
    };
    
    class  DDS_stringTypeSupportFactory : public ::DDS::TypeSupportFactory_impl
    {
    public:
        DDS_stringTypeSupportFactory() {}
        virtual ~DDS_stringTypeSupportFactory() {}
    private:
        ::DDS::DataWriter_ptr 
        create_datawriter (gapi_dataWriter handle);
    
        ::DDS::DataReader_ptr 
        create_datareader (gapi_dataReader handle);
    
        ::DDS::DataReaderView_ptr 
        create_view (gapi_dataReaderView handle);
    };
    
    class  DDS_stringTypeSupport : public virtual DDS_stringTypeSupportInterface,
                                   public ::DDS::TypeSupport_impl
    {
    public:
        virtual ::DDS::ReturnCode_t register_type(
            ::DDS::DomainParticipant_ptr participant,
            const char * type_name) THROW_ORB_EXCEPTIONS;
    
        virtual char * get_type_name() THROW_ORB_EXCEPTIONS;    
    
        DDS_stringTypeSupport (void);
        virtual ~DDS_stringTypeSupport (void);
    
    private:
        DDS_stringTypeSupport (const DDS_stringTypeSupport &);
        void operator= (const DDS_stringTypeSupport &);
    
        static const char *metaDescriptor;
    };
    
    typedef DDS_stringTypeSupportInterface_var DDS_stringTypeSupport_var;
    typedef DDS_stringTypeSupportInterface_ptr DDS_stringTypeSupport_ptr;
    
    class  DDS_stringDataWriter_impl : public virtual DDS_stringDataWriter,
                                        public ::DDS::DataWriter_impl
    {
    public:
    
        virtual ::DDS::InstanceHandle_t register_instance(
            const DDS_string & instance_data) THROW_ORB_EXCEPTIONS;
            
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp(
            const DDS_string & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
            
        virtual ::DDS::ReturnCode_t unregister_instance(
            const DDS_string & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp(
            const DDS_string & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write(
            const DDS_string & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp(
            const DDS_string & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose(
            const DDS_string & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp(
            const DDS_string & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose(
            const DDS_string & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp(
            const DDS_string & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value(
            DDS_string & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const DDS_string & instance_data) THROW_ORB_EXCEPTIONS;
    
    
        DDS_stringDataWriter_impl (
            gapi_dataWriter handle
        );
    
        virtual ~DDS_stringDataWriter_impl (void);
    
    private:
        DDS_stringDataWriter_impl(const DDS_stringDataWriter_impl &);
        void operator= (const DDS_stringDataWriter &);
    };
    
    class  DDS_stringDataReader_impl : public virtual DDS_stringDataReader,
                                        public ::DDS::DataReader_impl
    {
        friend class DDS_stringDataReaderView_impl;
    public:
        virtual ::DDS::ReturnCode_t read(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_w_condition(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_w_condition(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            DDS_string & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            DDS_string & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_instance(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_instance(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_next_instance(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t get_key_value(
            DDS_string & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const DDS_string & instance) THROW_ORB_EXCEPTIONS;
    
        DDS_stringDataReader_impl (
            gapi_dataReader handle
        );
    
        virtual ~DDS_stringDataReader_impl(void);
    
    private:
        DDS_stringDataReader_impl(const DDS_stringDataReader &);
        void operator= (const DDS_stringDataReader &);
    
        static ::DDS::ReturnCode_t check_preconditions(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples
        );
    };
    
    class  DDS_stringDataReaderView_impl : public virtual DDS_stringDataReaderView,
                                        public ::DDS::DataReaderView_impl
    {
    public:
        virtual ::DDS::ReturnCode_t read(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_w_condition(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_w_condition(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample(
            DDS_string & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample(
            DDS_string & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_instance(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_instance(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t take_next_instance(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            CORBA::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan(
            DDS_stringSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::ReturnCode_t get_key_value(
            DDS_string & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
        
        virtual ::DDS::InstanceHandle_t lookup_instance(
            const DDS_string & instance) THROW_ORB_EXCEPTIONS;
    
        DDS_stringDataReaderView_impl (
            gapi_dataReader handle
        );
    
        virtual ~DDS_stringDataReaderView_impl(void);
    
    private:
        DDS_stringDataReaderView_impl(const DDS_stringDataReaderView &);
        void operator= (const DDS_stringDataReaderView &);
    };
    
}

#endif
