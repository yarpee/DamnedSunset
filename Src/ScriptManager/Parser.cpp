/**
@file Parser.cpp

Contiene la implementación de la clase CParser que será la encargada
de servir de interfaz de comunicación entre el parser de lua
y C++.

@author Alberto Plaza
@date Marzo, 2012
*/
#include "Parser.h"
#include "Server.h"

#include "Map\MapParser.h"

#pragma warning( disable: 4251 )
#include <luabind\luabind.hpp>

namespace ScriptManager
{
	bool _registered = false;

	CParser::CParser()
	{
		
	} // CParser

	//--------------------------------------------------------

	CParser::~CParser()
	{

	} // ~CParser

	//--------------------------------------------------------

	void CParser::registerClass()
	{
		if (!_registered)
		{
			luabind::module(CServer::getSingletonPtr()->getLuaState())
				[
					luabind::class_<CParser>("Parser")
					.def(luabind::constructor<>())
					.def("beginGrid", (void (CParser::*) (int, int)) &CParser::beginGrid)
					.def("newTile", (void (CParser::*) (const char*, int, int)) &CParser::newTile)
					.def("beginEntity", (void (CParser::*) (const char*)) &CParser::beginEntity)
					.def("newAttrib", (void (CParser::*) (const char*, const char*)) &CParser::newAttrib)
					.def("endEntity", &CParser::endEntity)
				];
			_registered = true;
		}
	} // registerClass

	//--------------------------------------------------------

	void CParser::beginGrid(int height, int width)
	{
		Map::CMapParser::getSingletonPtr()->beginGrid(height, width);
		
	} // beginGrid

	//--------------------------------------------------------

	void CParser::newTile(const char *name, int y, int x)
	{
		Map::CMapParser::getSingletonPtr()->newTile(std::string(name), y, x);
		
	} // newTileAttrib

	//--------------------------------------------------------

	void CParser::beginEntity(const char *name)
	{
		Map::CMapParser::getSingletonPtr()->beginEntity(std::string(name));
		
	} // beginEntity

	//--------------------------------------------------------

	void CParser::newAttrib(const char *name, const char *value)
	{
		if (strcmp(name, "type") == 0)
			Map::CMapParser::getSingletonPtr()->newAttribType(std::string(value));
		else
			Map::CMapParser::getSingletonPtr()->newAttrib(std::string(name), std::string(value));
		
	} // newAttrib

	//--------------------------------------------------------

	void CParser::endEntity()
	{
		Map::CMapParser::getSingletonPtr()->endEntity();
		
	} // endEntity

	//--------------------------------------------------------

} // namespace ScriptManager