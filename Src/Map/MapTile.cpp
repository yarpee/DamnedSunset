/**
@file MapTile.cpp

Contiene la implementación de la clase que representa una celda del mapa leida 
del fichero del mapa.

@author Alberto Plaza
@date Marzo, 2012
*/
#include "MapTile.h"

#include <cassert>

namespace Map {
	
	typedef std::pair<std::string, std::string> TSSPar;

	void CTile::setAttribute(const std::string &attr, const std::string &value)
	{
		TSSPar elem(attr,value);
		if(_attributes.count(attr))
			_attributes.erase(attr);
		_attributes.insert(elem);

	} // setAttribute

	//--------------------------------------------------------

	bool CTile::hasAttribute(const std::string &attr) const
	{
		// Casos especiales
		if(!attr.compare("type"))
			return true;
		if(_attributes.count(attr))
			return true;
		return false;

	} // hasAttribute

	//--------------------------------------------------------

	const std::string &CTile::getStringAttribute(const std::string &attr) const
	{
		// Casos especiales
		if(!attr.compare("type"))
			return _type;
		return (*_attributes.find(attr)).second;

	} // getStringAttribute

	//--------------------------------------------------------

	int CTile::getIntAttribute(const std::string &attr) const
	{
		return atoi((*_attributes.find(attr)).second.c_str());

	} // getIntAttribute

	//--------------------------------------------------------

	float CTile::getFloatAttribute(const std::string &attr) const
	{
		return (float)atof((*_attributes.find(attr)).second.c_str());

	} // getFloatAttribute

	//--------------------------------------------------------

	double CTile::getDoubleAttribute(const std::string &attr) const
	{
		return atof((*_attributes.find(attr)).second.c_str());

	} // getDoubleAttribute

	//--------------------------------------------------------

	bool CTile::getBoolAttribute(const std::string &attr) const
	{
		if(!(*_attributes.find(attr)).second.compare("true"))
			return true;
		else if(!(*_attributes.find(attr)).second.compare("false"))
			return false;
		throw new std::exception("Leido archivo booleano que no es ni true ni false.");

	} // getBoolAttribute

	//--------------------------------------------------------

	const Vector3 CTile::getVector3Attribute(const std::string &attr) const
	{
		// Recuperamos la cadena  "x y z"
		std::string position = (*_attributes.find(attr)).second;
		int space1 = position.find(' ');
		float x = (float)atof(position.substr(0,space1).c_str());
		int space2 = position.find(' ',space1+1);
		float y = (float)atof(position.substr(space1+1,space2-(space1+1)).c_str());
		float z = (float)atof(position.substr(space2+1,position.size()-(space2+1)).c_str());

		return Vector3(x,y,z);

	} // getVector3Attribute

	//--------------------------------------------------------

	const Vector2 CTile::getVector2Attribute(const std::string &attr) const
	{
		// Recuperamos la cadena  "x y"
		std::string position = (*_attributes.find(attr)).second;
		int space1 = position.find(' ');
		float x = (float)atof(position.substr(0,space1).c_str());
		float y = (float)atof(position.substr(space1+1,position.size()-(space1+1)).c_str());

		return Vector2(x,y);

	} // getVector2Attribute

	//--------------------------------------------------------

} // namespace Map
