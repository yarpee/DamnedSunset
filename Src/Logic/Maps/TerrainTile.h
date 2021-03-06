
/**
@file TerrainTile.h

Contiene la declaraci�n de la clase CTerrainTile que contiene
la informacion de una celda del terreno.

@see Logic::TerrainTile

@author Daniel Flamenco
@date Abril, 2012
*/
#ifndef __Logic_TerrainTile_H
#define __Logic_TerrainTile_H

#include "Logic/Entity/Entity.h"

namespace Map
{
	class CEntity;
	class CTile;
}

// Declaraci�n de la clase
namespace Logic
{

	/**
	Clase que contiene el tipo de datos de un tile del mapa.
	Tiene una serie de atributos que se utilizan para almacenar
	las entidades y el terreno que tiene cada casilla del mapa.

	@author Daniel Flamenco Gonz�lez
	@date Febrero, 2012
	*/
	class CTerrainTile
	{
	public:
		/**
		Constructor.
		*/
		CTerrainTile (std::string name) : _name(name) {}

		/**
		Destructor.
		*/
		~CTerrainTile() {}

		/**
		Devuelve el nombre del tipo de terreno.
		*/
		std::string getName();

		/**
		Recoge la informaci�n del terreno del mapa y lo guarda en el objeto.
		Tiene que tener los atributos:
		<li>Cost</li>
		<li>Difuse_texture</li>
		<li>Normal_texture</li>
		*/
		void FillData(Map::CEntity* terrain_info);

		void FillData(Map::CTile* terrain_info);

		/**
		Coste que tiene el A* para atravesar una casilla de este tipo.

		Si el coste es -1, no se puede pasar por esta casilla.
		*/
		int getAStarCost();

		/**
		Mapa de textura que tiene la casilla del terreno.
		*/
		std::string getDifuseMap();

		/**
		Mapa de normales que tiene la casilla del terreno.
		*/
		std::string getNormalMap();

		/**
		Tama�o de la textura que tiene la casilla del terreno.
		*/
		int getTextureSize();

		/**
		Devuelve true si es un obstaculo y necesita una caja f�sica
		de su tama�o para no poder atravesar esta casilla.
		*/
		bool isObstacle();

		/**
		Devuelve la altura a partir de la cual se tiene que empezar a
		pintar la textura de este terreno.
		*/
		float getBlendHeight();

		/**
		Devuelve la altura maxima hasta la cual se va a pintar la
		textura de este terreno.
		*/
		float getBlendHeightMax();

		/**
		Devuelve true si la textura que contiene este terreno debe ser
		usada como textura base del terreno generado.
		*/
		bool isBaseTexture();

	private:

		/**
		Nombre del tipo de celda del terreno.
		*/
		std::string _name;

		/**
		Coste que tiene el A* para atravesar una casilla de este tipo.

		Si el coste es -1, no se puede pasar por esta casilla.
		*/
		int _aStarCost;

		/**
		Mapa de textura que tiene la casilla del terreno.
		Difuso y mapa de normales.
		*/
		std::string _difuseMap, _normalMap;

		/**
		Tama�o de la textura que tiene la casilla del terreno.
		*/
		int _textureSize;

		/**
		Alturas minima y maxima entre las cuales se tiene que pintar
		la textura que lleva este terreno.
		*/
		float _blendHeight, _blendHeightMax;

		/**
		Atributo que indica si la textura que contiene este terreno
		se debe utilizar como textura base al aplicar el blending
		de texturas al generar el terreno.
		*/
		bool _baseTexture;
	};

}

#endif // __Logic_TerrainTile_H