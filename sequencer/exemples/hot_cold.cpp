#include <iostream>

#include <json/json.h>
#include <CSIEMessenger.h>

#ifdef _WIN32
#define DLLAPI  __declspec(dllexport)
#else
#define DLLAPI
#endif

int hotCold;
float temperature;
std::string event;

extern "C" {
int DLLAPI onstart( char* p_configuration )
{
	// config file reading
	Json::Reader _reader;
	Json::Value _config;

	bool _parsingSuccessful = _reader.parse( p_configuration, _config );
	if ( !_parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cout << "Failed to parse configuration: " << _reader.getFormatedErrorMessages() << std::endl;
		return 1;
	}

	CSIEMessenger_init( (char*)_config["domain"].asString().c_str(), (char*)_config["name"].asString().c_str() );

	hotCold=0;
	CSIEMessenger_regProduceSampling( (char*)_config["variable_hotcold"].asString().c_str(), (void*)&hotCold, TYPE_INT );
	CSIEMessenger_regConsumSampling( (char*)_config["variable_temperature"].asString().c_str(), (void*)&temperature, TYPE_FLOAT );

	event = _config["event"].asString();
	
	return 0;
}


/**
 * onupdate
 * Function called for each cycle
 */
int DLLAPI onupdate( )
{
	int _hotCold = hotCold;
	CSIEMessenger_update();
	
	if (temperature > 0) {
		hotCold = 1;
	} else {
		hotCold = 0;
	}
	
	if (_hotCold != hotCold) { 
		CSIEMessenger_trigger( event, "" );
	}
	
	return 0;
}

/*
 * Stop
 */
int DLLAPI onstop( )
{
	CSIEMessenger_unreg();
	return 0;
}

} // extern "C"
