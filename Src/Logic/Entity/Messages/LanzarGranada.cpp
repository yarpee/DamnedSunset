#ifndef __Logic_LanzarGranada_CPP
#define __Logic_LanzarGranada_CPP

#include "LanzarGranada.h"

namespace Logic
{
	MLanzarGranada::MLanzarGranada()
	{
		IMessage();
		_position = NULL;
		_type = "MLanzarGranada";
	}
	MLanzarGranada::~MLanzarGranada() 
	{
		delete _position;
	}
}
#endif