/**
@file GridMap.h

Contiene la implementaci�n de la clase CGridMap, Un mapa de celdas l�gico.

@see Logic::GridMap

@author Daniel Flamenco
@date Febrero, 2012
*/

#include "GridMap.h"

#include "Logic/Entity/Entity.h"

// HACK. Deber�a leerse de alg�n fichero de configuraci�n
const int GRID_SIZE = 10;
const float MAP_WIDTH = 200.0f;
const float MAP_HEIGHT = 200.0f;
const int MAP_HGRIDS = (int)MAP_WIDTH / GRID_SIZE;
const int MAP_VGRIDS = (int)MAP_HEIGHT / GRID_SIZE;

namespace Logic {

	CGridMap::CGridMap()
	{
		// Reserva memoria para almacenar el mapa l�gico y inicializa cada casilla.
		_gridMap = new TGridTile*[MAP_VGRIDS];
		for (int i = 0; i < MAP_VGRIDS; ++i)
		{
			_gridMap[i] = new TGridTile[MAP_HGRIDS];
			for (int j = 0; j < MAP_HGRIDS; ++j)
				_gridMap[i][j] = new CGridTile(i, j);
		}

	} // CGridMap

	//--------------------------------------------------------

	CGridMap::~CGridMap()
	{
		// Libera la memoria utilizada para almacenar el mapa l�gico.
		for (int i = 0; i < MAP_VGRIDS; ++i)
		{
			for (int j = 0; j < MAP_HGRIDS; ++j)
				delete(_gridMap[i][j]);
			delete(_gridMap[i]);
		}
		delete(_gridMap);
	}

	//--------------------------------------------------------

	const Vector2 CGridMap::getAbsoluteGridPos(const Vector2 pos)
	{
		Vector2 modulePos;
		modulePos.x = ( (int)pos.x / GRID_SIZE - 0.5 ) * GRID_SIZE;
		modulePos.y = ( (int)pos.y / GRID_SIZE - 0.5 ) * GRID_SIZE;

		return modulePos;

	} // getAbsoluteGridPos

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromPosition(const float x, const float y)
	{
		int row = (int)(x + MAP_WIDTH / 2) / GRID_SIZE;
		int col = (int)(y + MAP_HEIGHT / 2) / GRID_SIZE;

		assert(row >= 0 && row < MAP_HGRIDS && col >= 0 && col < MAP_VGRIDS);

		return getTileFromCoord(row, col);

	} // getGridFromPosition

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromCoord(const int row, const int col)
	{
		return _gridMap[row][col];

	} // getTileFromCoord

	//--------------------------------------------------------

	int CGridMap::getIndexTileFromCoord( Vector3 position )
	{
		TGridTile tile = getTileFromPosition(position.x, position.z);

		return tile->GetRow() * MAP_HGRIDS + tile->GetCol();
	}

	//--------------------------------------------------------

	const TGridTile CGridMap::getTileFromIndex(const unsigned int index)
	{
		int row = index / MAP_HGRIDS;
		int col = index % MAP_HGRIDS;

		assert(row >= 0 && row < MAP_HGRIDS && col >= 0 && col < MAP_VGRIDS);

		return _gridMap[row][col];

	} // getTileFromIndex

	//--------------------------------------------------------

	Vector3 CGridMap::getTilePositionFromIndex(const unsigned int index)
	{
		int row = index / MAP_HGRIDS;
		int col = index % MAP_HGRIDS;

		Vector3 tilePos;
		tilePos.x = col * GRID_SIZE + 0.5 * GRID_SIZE - MAP_WIDTH / 2;
		tilePos.y = 1.0f;
		tilePos.z = row * GRID_SIZE + 0.5 * GRID_SIZE - MAP_HEIGHT / 2;

		return tilePos;

	} // getTilePositionFromIndex

	//--------------------------------------------------------

	std::list<unsigned int> CGridMap::getAdjacencyGrids(const int index)
	{
		std::list<unsigned int>* neighbours = new std::list<unsigned int>();
		if (index >= MAP_HGRIDS)
			neighbours->push_back(index - MAP_HGRIDS);
		if (index % MAP_HGRIDS > 0)
			neighbours->push_back(index - 1);
		if (index % MAP_HGRIDS < MAP_HGRIDS - 1)
			neighbours->push_back(index + 1);
		if (index / MAP_HGRIDS < MAP_VGRIDS - 1)
			neighbours->push_back(index + MAP_HGRIDS);

		return (*neighbours);

	} // getAdjacencyGrids

	//--------------------------------------------------------

	int CGridMap::getNumGrids()
	{
		return ( MAP_HGRIDS * MAP_VGRIDS );
	}


} // namespace Logic