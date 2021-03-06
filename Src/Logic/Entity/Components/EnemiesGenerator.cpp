/**
@file EnemiesGenerator.cpp

Contiene la implementaci�n del componente que controla la generaci�n 
de enemigos en el mapa.
 
@see Logic::CEnemiesGenerator
@see Logic::IComponent

@author Luis Mendoza
@date Febrero, 2012
*/

#include "EnemiesGenerator.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"

#include "ScriptManager/Server.h"

#include "Logic/Entity/Messages/SpawnEnemy.h"
#include "Logic/Entity/Messages/EnemyCreated.h"

#include <stdlib.h>
#include <sstream>

namespace Logic
{
	IMP_FACTORY(CEnemiesGenerator);
	
	//---------------------------------------------------------

	bool CEnemiesGenerator::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("grid_position"))
			_origen = entityInfo->getVector2Attribute("grid_position");

		if(entityInfo->hasAttribute("periodo"))
			_periodo = entityInfo->getIntAttribute("periodo");

		if(entityInfo->hasAttribute("automaticSpawn"))
			_automaticSpawn = entityInfo->getBoolAttribute("automaticSpawn");
		else
			_automaticSpawn = false;

		if(entityInfo->hasAttribute("ID"))
		{
			_ID = entityInfo->getIntAttribute("ID");

			// Si es un spawner de estado de misi�n creo la tabla normal.
			if(entityInfo->hasAttribute("stagesSpawner") && entityInfo->getBoolAttribute("stagesSpawner")) 
			{
				_specialSpawner = false;

				// Crear la tabla del spawner actual.
				std::stringstream scriptCreate;
				scriptCreate << "spawners[" << _ID << "] = {}";
				ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreate.str().c_str());

				// Relleno la tabla con el ID de la entidad.
				std::stringstream script;
				script << "spawners[" << _ID << "].entityID = " << _entity->getEntityID();
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

				// Creo la tabla de enemigos.
				std::stringstream scriptCreateEnemies;
				scriptCreateEnemies << "spawners[" << _ID << "].enemies = {}";
				ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreateEnemies.str().c_str());

				// Inicializo el tiempo de cada spawner.
				std::stringstream scriptTime;
				scriptTime << "spawners[" << _ID << "].spawnTime = 0";
				ScriptManager::CServer::getSingletonPtr()->executeScript(scriptTime.str().c_str());

				// Inicializo el conteo de enemigos que hay que mandar a atacar de cada spawner.
				std::stringstream scriptAttack;
				scriptAttack << "spawners[" << _ID << "].attackEnemies = 0";
				ScriptManager::CServer::getSingletonPtr()->executeScript(scriptAttack.str().c_str());
			}
			// Si es un spawner especial lo a�ado a la tabla de spawners especiales.
			else
			{
				_specialSpawner = true;

				// Crear la tabla del spawner actual.
				std::stringstream scriptCreate;
				scriptCreate << "specialSpawners[" << _ID << "] = {}";
				ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreate.str().c_str());

				// Relleno la tabla con el ID de la entidad.
				std::stringstream script;
				script << "specialSpawners[" << _ID << "].entityID = " << _entity->getEntityID();
				ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

				// Creo la tabla de enemigos.
				std::stringstream scriptCreateEnemies;
				scriptCreateEnemies << "specialSpawners[" << _ID << "].enemies = {}";
				ScriptManager::CServer::getSingletonPtr()->executeScript(scriptCreateEnemies.str().c_str());

				// Inicializo el tiempo de cada spawner.
				std::stringstream scriptTime;
				scriptTime << "specialSpawners[" << _ID << "].spawnTime = 0";
				ScriptManager::CServer::getSingletonPtr()->executeScript(scriptTime.str().c_str());

				// Inicializo el conteo de enemigos que hay que mandar a atacar de cada spawner.
				std::stringstream scriptAttack;
				scriptAttack << "specialSpawners[" << _ID << "].attackEnemies = 0";
				ScriptManager::CServer::getSingletonPtr()->executeScript(scriptAttack.str().c_str());
			}
		}

		std::srand(time(NULL));

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CEnemiesGenerator::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CEnemiesGenerator::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CEnemiesGenerator::accept(IMessage *message)
	{
		return !message->getType().compare("MSpawnEnemy");

	} // accept
	
	//---------------------------------------------------------

	void CEnemiesGenerator::process(IMessage *message)
	{
		if (!message->getType().compare("MSpawnEnemy"))
		{
			MSpawnEnemy *m = static_cast <MSpawnEnemy*> (message);
			_spawn += m->getNumEnemies();

			if (_spawn > _maxSpawn)
				_spawn = _maxSpawn;
		}

	} // process
	
	//---------------------------------------------------------

	Logic::CEntity* CEnemiesGenerator::spawnEnemy()
	{
		Map::CEntity *enemyInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Enemy");
		std::stringstream name;
		name << "Enemy" << _enemy << "_" << _entity->getEntityID();
		enemyInfo->setName(name.str());

		TOffset offset = calculateOffset();
				
		std::stringstream pos;
		pos << _origen.x + offset.offsetX << ' ' << _origen.y + offset.offsetY << ' ';
		enemyInfo->setAttribute("grid_position", pos.str());

		Logic::CEntity *ent = Logic::CEntityFactory::getSingletonPtr()->createEntity(enemyInfo, _entity->getMap());
		ent->activate();

		if (_specialSpawner)
		{
			// A�ado un nuevo enemigo a la tabla de enemigos creados por el spawner.
			std::stringstream script;
			script << "specialSpawners[" << _ID << "].enemies[" << _enemy << "] = { ID = " << ent->getEntityID() << ", }";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}
		else
		{
			// A�ado un nuevo enemigo a la tabla de enemigos creados por el spawner.
			std::stringstream script;
			script << "spawners[" << _ID << "].enemies[" << _enemy << "] = { ID = " << ent->getEntityID() << ", }";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		//Avisar a los player de la creaci�n del enemigo para que actualicen el componente de percepci�n y el controlador de la IA
		MEnemyCreated *m = new MEnemyCreated();
		
		Logic::CEntity *player = _entity->getMap()->getEntityByTag("Player");
		m->setCreatedEnemy(ent);
		m->addPtr();
		while (player != NULL)
		{
			//player->emitMessage(m);
			player = _entity->getMap()->getEntityByTag("Player", player);
		}
		m->removePtr();

		_enemy++;

		return ent;

	} // spawnEnemy

	//---------------------------------------------------------

	void CEnemiesGenerator::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		if (_automaticSpawn)
		{
			// Si est� activado el spawn autom�tico, se spawnea un enemigo cada per�odo de tiempo.
			_time += msecs;
			if (_time >= _periodo)
			{
				_time = 0;
				
				spawnEnemy();
			}
		}

		// Para no saturar la l�gica del juego spawneo un enemigo a la vez en cada tick.
		if (_spawn > 0)
		{
			_spawn--;

			spawnEnemy();
		}

	} // tick

	//---------------------------------------------------------

	CEnemiesGenerator::TOffset CEnemiesGenerator::calculateOffset()
	{
		TOffset offset;

		int posOffset = _enemy % _maxSpawn;
		switch (posOffset)
		{
		case 0:
			offset.offsetX = 0;
			offset.offsetY = 0;
			break;
		case 1:
			offset.offsetX = -1;
			offset.offsetY = -1;
			break;
		case 2:
			offset.offsetX = 0;
			offset.offsetY = -1;
			break;
		case 3:
			offset.offsetX = 1;
			offset.offsetY = -1;
			break;
		case 4:
			offset.offsetX = -1;
			offset.offsetY = 0;
			break;
		case 5:
			offset.offsetX = 1;
			offset.offsetY = 0;
			break;
		case 6:
			offset.offsetX = -1;
			offset.offsetY = 1;
			break;
		case 7:
			offset.offsetX = 0;
			offset.offsetY = 1;
			break;
		case 8:
			offset.offsetX = 1;
			offset.offsetY = 1;
			break;
		}

		return offset;

	} // calculateOffset

	//---------------------------------------------------------

} // namespace Logic

