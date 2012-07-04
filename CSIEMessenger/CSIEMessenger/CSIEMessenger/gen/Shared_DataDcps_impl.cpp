#include "Shared_DataDcps_impl.h"
#include "gapi.h"
#include "gapi_loanRegistry.h"
#include "Shared_DataSplDcps.h"
#include "ccpp_DataReader_impl.h"
#include "ccpp_DataReaderView_impl.h"


extern c_bool
__Shared_Data_DDS_int__copyIn(
    c_base base,
    struct Shared_Data::DDS_int *from,
    struct _Shared_Data_DDS_int *to);

extern void
__Shared_Data_DDS_int__copyOut(
    void *_from,
    void *_to);

// DDS Shared_Data::DDS_int TypeSupportFactory Object Body

 DDS::DataWriter_ptr 
Shared_Data::DDS_intTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new Shared_Data::DDS_intDataWriter_impl(handle);
}

 DDS::DataReader_ptr 
Shared_Data::DDS_intTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new Shared_Data::DDS_intDataReader_impl (handle);
}


 DDS::DataReaderView_ptr 
Shared_Data::DDS_intTypeSupportFactory::create_view (gapi_dataReaderView handle)
{
    return new Shared_Data::DDS_intDataReaderView_impl (handle);
}

// DDS Shared_Data::DDS_int TypeSupport Object Body

 Shared_Data::DDS_intTypeSupport::DDS_intTypeSupport(void) :
    TypeSupport_impl(
        __Shared_Data_DDS_int__name(),
        __Shared_Data_DDS_int__keys(),
        Shared_Data::DDS_intTypeSupport::metaDescriptor,
        (gapi_copyIn) __Shared_Data_DDS_int__copyIn,
        (gapi_copyOut) __Shared_Data_DDS_int__copyOut,
        (gapi_readerCopy) DDS::ccpp_DataReaderCopy<Shared_Data::DDS_intSeq, Shared_Data::DDS_int>,
        new  Shared_Data::DDS_intTypeSupportFactory())
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_intTypeSupport::~DDS_intTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

 DDS::ReturnCode_t
Shared_Data::DDS_intTypeSupport::register_type(
    DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

 char *
Shared_Data::DDS_intTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS Shared_Data::DDS_int DataWriter_impl Object Body

 Shared_Data::DDS_intDataWriter_impl::DDS_intDataWriter_impl (
    gapi_dataWriter handle
) : DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_intDataWriter_impl::~DDS_intDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

 DDS::InstanceHandle_t
Shared_Data::DDS_intDataWriter_impl::register_instance(
    const Shared_Data::DDS_int & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_intDataWriter_impl::register_instance_w_timestamp(
    const DDS_int & instance_data,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataWriter_impl::unregister_instance(
    const Shared_Data::DDS_int & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_intDataWriter_impl::unregister_instance_w_timestamp(
    const DDS_int & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataWriter_impl::write(
    const Shared_Data::DDS_int & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataWriter_impl::write_w_timestamp(
    const DDS_int & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataWriter_impl::dispose(
    const Shared_Data::DDS_int & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_intDataWriter_impl::dispose_w_timestamp(
    const DDS_int & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataWriter_impl::writedispose(
    const Shared_Data::DDS_int & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataWriter_impl::writedispose_w_timestamp(
    const DDS_int & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_intDataWriter_impl::get_key_value(
    DDS_int & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_intDataWriter_impl::lookup_instance(
	const Shared_Data::DDS_int & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS Shared_Data::DDS_int DataReader_impl Object Body

 Shared_Data::DDS_intDataReader_impl::DDS_intDataReader_impl (
    gapi_dataReader handle
) : DDS::DataReader_impl(handle)
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_intDataReader_impl::~DDS_intDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
Shared_Data::DDS_intDataReader_impl::read(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReader_impl::take(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReader_impl::read_w_condition(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReader_impl::take_w_condition(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReader_impl::read_next_sample(
    Shared_Data::DDS_int & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReader_impl::take_next_sample(
    Shared_Data::DDS_int & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
Shared_Data::DDS_intDataReader_impl::read_instance(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReader_impl::take_instance(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReader_impl::read_next_instance(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReader_impl::take_next_instance(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReader_impl::read_next_instance_w_condition(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReader_impl::take_next_instance_w_condition(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t
Shared_Data::DDS_intDataReader_impl::return_loan(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReader_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        Shared_Data::DDS_intSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReader_impl::get_key_value(
    Shared_Data::DDS_int & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_intDataReader_impl::lookup_instance(
    const Shared_Data::DDS_int & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReader_impl::check_preconditions(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples)
{
    DDS::ReturnCode_t status = DDS::RETCODE_PRECONDITION_NOT_MET;
    
    if ( received_data.length() == info_seq.length() &&
         received_data.maximum() == info_seq.maximum() &&
         received_data.release() == info_seq.release() ) {
        if ( received_data.maximum() == 0 || received_data.release() ) {
            if (received_data.maximum() == 0 ||
				max_samples <= static_cast<CORBA::Long>(received_data.maximum()) ||
				max_samples == DDS::LENGTH_UNLIMITED ) {
                status = DDS::RETCODE_OK;
            }
        }
    }
    return status;
}


// DDS Shared_Data::DDS_int DataReaderView_impl Object Body

 Shared_Data::DDS_intDataReaderView_impl::DDS_intDataReaderView_impl (
    gapi_dataReaderView handle
) : DDS::DataReaderView_impl(handle)
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_intDataReaderView_impl::~DDS_intDataReaderView_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
Shared_Data::DDS_intDataReaderView_impl::read(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReaderView_impl::take(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReaderView_impl::read_w_condition(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReaderView_impl::take_w_condition(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReaderView_impl::read_next_sample(
    Shared_Data::DDS_int & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReaderView_impl::take_next_sample(
    Shared_Data::DDS_int & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
Shared_Data::DDS_intDataReaderView_impl::read_instance(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReaderView_impl::take_instance(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReaderView_impl::read_next_instance(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_intDataReaderView_impl::take_next_instance(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReaderView_impl::read_next_instance_w_condition(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReaderView_impl::take_next_instance_w_condition(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_intDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t
Shared_Data::DDS_intDataReaderView_impl::return_loan(
    Shared_Data::DDS_intSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReaderView_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        Shared_Data::DDS_intSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_intDataReaderView_impl::get_key_value(
    Shared_Data::DDS_int & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_intDataReaderView_impl::lookup_instance(
    const Shared_Data::DDS_int & instance) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::lookup_instance(&instance);
}



extern c_bool
__Shared_Data_DDS_float__copyIn(
    c_base base,
    struct Shared_Data::DDS_float *from,
    struct _Shared_Data_DDS_float *to);

extern void
__Shared_Data_DDS_float__copyOut(
    void *_from,
    void *_to);

// DDS Shared_Data::DDS_float TypeSupportFactory Object Body

 DDS::DataWriter_ptr 
Shared_Data::DDS_floatTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new Shared_Data::DDS_floatDataWriter_impl(handle);
}

 DDS::DataReader_ptr 
Shared_Data::DDS_floatTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new Shared_Data::DDS_floatDataReader_impl (handle);
}


 DDS::DataReaderView_ptr 
Shared_Data::DDS_floatTypeSupportFactory::create_view (gapi_dataReaderView handle)
{
    return new Shared_Data::DDS_floatDataReaderView_impl (handle);
}

// DDS Shared_Data::DDS_float TypeSupport Object Body

 Shared_Data::DDS_floatTypeSupport::DDS_floatTypeSupport(void) :
    TypeSupport_impl(
        __Shared_Data_DDS_float__name(),
        __Shared_Data_DDS_float__keys(),
        Shared_Data::DDS_floatTypeSupport::metaDescriptor,
        (gapi_copyIn) __Shared_Data_DDS_float__copyIn,
        (gapi_copyOut) __Shared_Data_DDS_float__copyOut,
        (gapi_readerCopy) DDS::ccpp_DataReaderCopy<Shared_Data::DDS_floatSeq, Shared_Data::DDS_float>,
        new  Shared_Data::DDS_floatTypeSupportFactory())
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_floatTypeSupport::~DDS_floatTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatTypeSupport::register_type(
    DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

 char *
Shared_Data::DDS_floatTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS Shared_Data::DDS_float DataWriter_impl Object Body

 Shared_Data::DDS_floatDataWriter_impl::DDS_floatDataWriter_impl (
    gapi_dataWriter handle
) : DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_floatDataWriter_impl::~DDS_floatDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

 DDS::InstanceHandle_t
Shared_Data::DDS_floatDataWriter_impl::register_instance(
    const Shared_Data::DDS_float & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_floatDataWriter_impl::register_instance_w_timestamp(
    const DDS_float & instance_data,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataWriter_impl::unregister_instance(
    const Shared_Data::DDS_float & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataWriter_impl::unregister_instance_w_timestamp(
    const DDS_float & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataWriter_impl::write(
    const Shared_Data::DDS_float & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataWriter_impl::write_w_timestamp(
    const DDS_float & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataWriter_impl::dispose(
    const Shared_Data::DDS_float & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataWriter_impl::dispose_w_timestamp(
    const DDS_float & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataWriter_impl::writedispose(
    const Shared_Data::DDS_float & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataWriter_impl::writedispose_w_timestamp(
    const DDS_float & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataWriter_impl::get_key_value(
    DDS_float & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_floatDataWriter_impl::lookup_instance(
	const Shared_Data::DDS_float & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS Shared_Data::DDS_float DataReader_impl Object Body

 Shared_Data::DDS_floatDataReader_impl::DDS_floatDataReader_impl (
    gapi_dataReader handle
) : DDS::DataReader_impl(handle)
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_floatDataReader_impl::~DDS_floatDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReader_impl::read(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReader_impl::take(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReader_impl::read_w_condition(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReader_impl::take_w_condition(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReader_impl::read_next_sample(
    Shared_Data::DDS_float & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReader_impl::take_next_sample(
    Shared_Data::DDS_float & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReader_impl::read_instance(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReader_impl::take_instance(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReader_impl::read_next_instance(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReader_impl::take_next_instance(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReader_impl::read_next_instance_w_condition(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReader_impl::take_next_instance_w_condition(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReader_impl::return_loan(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReader_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        Shared_Data::DDS_floatSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReader_impl::get_key_value(
    Shared_Data::DDS_float & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_floatDataReader_impl::lookup_instance(
    const Shared_Data::DDS_float & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReader_impl::check_preconditions(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples)
{
    DDS::ReturnCode_t status = DDS::RETCODE_PRECONDITION_NOT_MET;
    
    if ( received_data.length() == info_seq.length() &&
         received_data.maximum() == info_seq.maximum() &&
         received_data.release() == info_seq.release() ) {
        if ( received_data.maximum() == 0 || received_data.release() ) {
            if (received_data.maximum() == 0 ||
				max_samples <= static_cast<CORBA::Long>(received_data.maximum()) ||
				max_samples == DDS::LENGTH_UNLIMITED ) {
                status = DDS::RETCODE_OK;
            }
        }
    }
    return status;
}


// DDS Shared_Data::DDS_float DataReaderView_impl Object Body

 Shared_Data::DDS_floatDataReaderView_impl::DDS_floatDataReaderView_impl (
    gapi_dataReaderView handle
) : DDS::DataReaderView_impl(handle)
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_floatDataReaderView_impl::~DDS_floatDataReaderView_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReaderView_impl::read(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReaderView_impl::take(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReaderView_impl::read_w_condition(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReaderView_impl::take_w_condition(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReaderView_impl::read_next_sample(
    Shared_Data::DDS_float & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReaderView_impl::take_next_sample(
    Shared_Data::DDS_float & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReaderView_impl::read_instance(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReaderView_impl::take_instance(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReaderView_impl::read_next_instance(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReaderView_impl::take_next_instance(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReaderView_impl::read_next_instance_w_condition(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReaderView_impl::take_next_instance_w_condition(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_floatDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t
Shared_Data::DDS_floatDataReaderView_impl::return_loan(
    Shared_Data::DDS_floatSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReaderView_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        Shared_Data::DDS_floatSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_floatDataReaderView_impl::get_key_value(
    Shared_Data::DDS_float & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_floatDataReaderView_impl::lookup_instance(
    const Shared_Data::DDS_float & instance) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::lookup_instance(&instance);
}



extern c_bool
__Shared_Data_DDS_string__copyIn(
    c_base base,
    struct Shared_Data::DDS_string *from,
    struct _Shared_Data_DDS_string *to);

extern void
__Shared_Data_DDS_string__copyOut(
    void *_from,
    void *_to);

// DDS Shared_Data::DDS_string TypeSupportFactory Object Body

 DDS::DataWriter_ptr 
Shared_Data::DDS_stringTypeSupportFactory::create_datawriter (gapi_dataWriter handle)
{
    return new Shared_Data::DDS_stringDataWriter_impl(handle);
}

 DDS::DataReader_ptr 
Shared_Data::DDS_stringTypeSupportFactory::create_datareader (gapi_dataReader handle)
{
    return new Shared_Data::DDS_stringDataReader_impl (handle);
}


 DDS::DataReaderView_ptr 
Shared_Data::DDS_stringTypeSupportFactory::create_view (gapi_dataReaderView handle)
{
    return new Shared_Data::DDS_stringDataReaderView_impl (handle);
}

// DDS Shared_Data::DDS_string TypeSupport Object Body

 Shared_Data::DDS_stringTypeSupport::DDS_stringTypeSupport(void) :
    TypeSupport_impl(
        __Shared_Data_DDS_string__name(),
        __Shared_Data_DDS_string__keys(),
        Shared_Data::DDS_stringTypeSupport::metaDescriptor,
        (gapi_copyIn) __Shared_Data_DDS_string__copyIn,
        (gapi_copyOut) __Shared_Data_DDS_string__copyOut,
        (gapi_readerCopy) DDS::ccpp_DataReaderCopy<Shared_Data::DDS_stringSeq, Shared_Data::DDS_string>,
        new  Shared_Data::DDS_stringTypeSupportFactory())
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_stringTypeSupport::~DDS_stringTypeSupport(void)
{
    // Parent destructor takes care of everything.
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringTypeSupport::register_type(
    DDS::DomainParticipant_ptr domain,
    const char * type_name) THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::register_type(domain, type_name);
}

 char *
Shared_Data::DDS_stringTypeSupport::get_type_name() THROW_ORB_EXCEPTIONS
{
    return TypeSupport_impl::get_type_name();
}

// DDS Shared_Data::DDS_string DataWriter_impl Object Body

 Shared_Data::DDS_stringDataWriter_impl::DDS_stringDataWriter_impl (
    gapi_dataWriter handle
) : DDS::DataWriter_impl(handle)
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_stringDataWriter_impl::~DDS_stringDataWriter_impl(void)
{
    // Parent destructor takes care of everything.
}

 DDS::InstanceHandle_t
Shared_Data::DDS_stringDataWriter_impl::register_instance(
    const Shared_Data::DDS_string & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance(&instance_data);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_stringDataWriter_impl::register_instance_w_timestamp(
    const DDS_string & instance_data,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataWriter_impl::unregister_instance(
    const Shared_Data::DDS_string & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance(&instance_data, handle);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataWriter_impl::unregister_instance_w_timestamp(
    const DDS_string & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataWriter_impl::write(
    const Shared_Data::DDS_string & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write(&instance_data, handle);
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataWriter_impl::write_w_timestamp(
    const DDS_string & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataWriter_impl::dispose(
    const Shared_Data::DDS_string & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose(&instance_data, handle);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataWriter_impl::dispose_w_timestamp(
    const DDS_string & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataWriter_impl::writedispose(
    const Shared_Data::DDS_string & instance_data,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose(&instance_data, handle);
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataWriter_impl::writedispose_w_timestamp(
    const DDS_string & instance_data,
    DDS::InstanceHandle_t handle,
    const DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataWriter_impl::get_key_value(
    DDS_string & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_stringDataWriter_impl::lookup_instance(
	const Shared_Data::DDS_string & instance_data) THROW_ORB_EXCEPTIONS
{
    return DataWriter_impl::lookup_instance(&instance_data);
}

// DDS Shared_Data::DDS_string DataReader_impl Object Body

 Shared_Data::DDS_stringDataReader_impl::DDS_stringDataReader_impl (
    gapi_dataReader handle
) : DDS::DataReader_impl(handle)
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_stringDataReader_impl::~DDS_stringDataReader_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReader_impl::read(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReader_impl::take(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReader_impl::read_w_condition(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReader_impl::take_w_condition(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReader_impl::read_next_sample(
    Shared_Data::DDS_string & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReader_impl::take_next_sample(
    Shared_Data::DDS_string & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReader_impl::read_instance(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReader_impl::take_instance(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReader_impl::read_next_instance(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReader_impl::take_next_instance(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReader_impl::read_next_instance_w_condition(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReader_impl::take_next_instance_w_condition(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReader_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReader_impl::return_loan(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReader_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        Shared_Data::DDS_stringSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReader_impl::get_key_value(
    Shared_Data::DDS_string & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_stringDataReader_impl::lookup_instance(
    const Shared_Data::DDS_string & instance) THROW_ORB_EXCEPTIONS
{
    return DataReader_impl::lookup_instance(&instance);
}

 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReader_impl::check_preconditions(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples)
{
    DDS::ReturnCode_t status = DDS::RETCODE_PRECONDITION_NOT_MET;
    
    if ( received_data.length() == info_seq.length() &&
         received_data.maximum() == info_seq.maximum() &&
         received_data.release() == info_seq.release() ) {
        if ( received_data.maximum() == 0 || received_data.release() ) {
            if (received_data.maximum() == 0 ||
				max_samples <= static_cast<CORBA::Long>(received_data.maximum()) ||
				max_samples == DDS::LENGTH_UNLIMITED ) {
                status = DDS::RETCODE_OK;
            }
        }
    }
    return status;
}


// DDS Shared_Data::DDS_string DataReaderView_impl Object Body

 Shared_Data::DDS_stringDataReaderView_impl::DDS_stringDataReaderView_impl (
    gapi_dataReaderView handle
) : DDS::DataReaderView_impl(handle)
{
    // Parent constructor takes care of everything.
}

 Shared_Data::DDS_stringDataReaderView_impl::~DDS_stringDataReaderView_impl(void)
{
    // Parent destructor takes care of everything.
}


 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReaderView_impl::read(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReaderView_impl::take(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReaderView_impl::read_w_condition(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReaderView_impl::take_w_condition(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReaderView_impl::read_next_sample(
    Shared_Data::DDS_string & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::read_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReaderView_impl::take_next_sample(
    Shared_Data::DDS_string & received_data,
    DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::take_next_sample(&received_data, sample_info);
}


 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReaderView_impl::read_instance(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReaderView_impl::take_instance(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReaderView_impl::read_next_instance(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReaderView_impl::take_next_instance(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::SampleStateMask sample_states,
    DDS::ViewStateMask view_states,
    DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReaderView_impl::read_next_instance_w_condition(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReaderView_impl::take_next_instance_w_condition(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq,
    CORBA::Long max_samples,
    DDS::InstanceHandle_t a_handle,
    DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status;
    
    status = Shared_Data::DDS_stringDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == DDS::RETCODE_OK ) {
        status = DataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}


 DDS::ReturnCode_t
Shared_Data::DDS_stringDataReaderView_impl::return_loan(
    Shared_Data::DDS_stringSeq & received_data,
    DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    DDS::ReturnCode_t status = DDS::RETCODE_OK;

    if ( received_data.length() > 0 ) {
        if (received_data.length() == info_seq.length() && 
            received_data.release() == info_seq.release() ) {
            if (!received_data.release()) {
                status = DataReaderView_impl::return_loan( received_data.get_buffer(),
                                                       info_seq.get_buffer() );

                if ( status == DDS::RETCODE_OK ) {
                    if ( !received_data.release() ) {
                        Shared_Data::DDS_stringSeq::freebuf( received_data.get_buffer(false) );
                        received_data.replace(0, 0, NULL, false);
                        DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                        info_seq.replace(0, 0, NULL, false);
                    }
                } else if ( status == DDS::RETCODE_NO_DATA ) {
                    if ( received_data.release() ) {
                        status = DDS::RETCODE_OK;
                    } else {
                        status = DDS::RETCODE_PRECONDITION_NOT_MET;
                    }
                }
            }
        } else {
            status = DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }
    return status;
}


 DDS::ReturnCode_t 
Shared_Data::DDS_stringDataReaderView_impl::get_key_value(
    Shared_Data::DDS_string & key_holder,
    DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::get_key_value(&key_holder, handle);
}

 DDS::InstanceHandle_t 
Shared_Data::DDS_stringDataReaderView_impl::lookup_instance(
    const Shared_Data::DDS_string & instance) THROW_ORB_EXCEPTIONS
{
    return DataReaderView_impl::lookup_instance(&instance);
}



const char * ::Shared_Data::DDS_intTypeSupport::metaDescriptor = "<MetaData version=\"1.0.0\"><Module name=\"Shared_Data\"><Struct name=\"DDS_int\"><Member name=\"data\"><Long/></Member><Member name=\"time\"><Long/></Member><Member name=\"timems\"><Long/></Member><Member name=\"valid\"><Boolean/></Member></Struct></Module></MetaData>";
const char * ::Shared_Data::DDS_floatTypeSupport::metaDescriptor = "<MetaData version=\"1.0.0\"><Module name=\"Shared_Data\"><Struct name=\"DDS_float\"><Member name=\"data\"><Float/></Member><Member name=\"time\"><Long/></Member><Member name=\"timems\"><Long/></Member><Member name=\"valid\"><Boolean/></Member></Struct></Module></MetaData>";
const char * ::Shared_Data::DDS_stringTypeSupport::metaDescriptor = "<MetaData version=\"1.0.0\"><Module name=\"Shared_Data\"><Struct name=\"DDS_string\"><Member name=\"data\"><String/></Member><Member name=\"time\"><Long/></Member><Member name=\"timems\"><Long/></Member><Member name=\"valid\"><Boolean/></Member></Struct></Module></MetaData>";
