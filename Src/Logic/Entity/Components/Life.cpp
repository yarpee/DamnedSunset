/**
@file Life.cpp

Contiene la implementaci�n del componente que controla la vida de una entidad.
 
@see Logic::CLife
@see Logic::IComponent

@author David Llans�
@date Octubre, 2010
*/

#include "Life.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"
#include "Application/BaseApplication.h"

#include "Graphics/Server.h"
#include "Graphics/Scene.h"
#include "Graphics/Entity.h"
#include "Graphics/Billboard.h"
#include "Graphics.h"

#include "ScriptManager/Server.h"

#include "assert.h"

//Mensajes
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/Healed.h"
#include "Logic/Entity/Messages/AttackEntity.h"
#include "Logic/Entity/Messages/CureEntity.h"
#include "Logic/Entity/Messages/EntityDeathListener.h"
#include "Logic/Entity/Messages/EntityDeath.h"

#include "GUI/Server.h"
#include "GUI/InterfazController.h"

#include "Logic/Entity/Messages/ActivarComponente.h"

namespace Logic 
{
	IMP_FACTORY(CLife);
	
	//---------------------------------------------------------

	CLife::CLife() : IComponent(), _life(100.f), _maxLife(100.0f), _death(false) {
	}

	CLife::~CLife() {
		if (_billboard)
			delete _billboard;
	}

	bool CLife::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		if(entityInfo->hasAttribute("life"))
			_life = entityInfo->getFloatAttribute("life");
		if(entityInfo->hasAttribute("maxLife"))
			_maxLife = entityInfo->getFloatAttribute("maxLife");
		
		//Billboard
		_billboard = new Graphics::CBillboard(_entity);
		if(entityInfo->hasAttribute("billboardLifeMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardLifeMaterial"));
		if(entityInfo->hasAttribute("billboardLifeWith") && entityInfo->hasAttribute("billboardLifeHeight"))
			_billboard->setDimensions(entityInfo->getFloatAttribute("billboardLifeWith"),entityInfo->getFloatAttribute("billboardLifeHeight"));
		if(entityInfo->hasAttribute("billboardLifePosition"))
		{
			Vector3 v = entityInfo->getVector3Attribute("billboardLifePosition");
			_billboard->setPosition(v.x,v.y,v.z);
		}	
		float porcentajeVida = _life/_maxLife;
		float num = 0.5f - porcentajeVida/2.0f;
		_billboard->setPosicionImagen(num/*inicioX*/, 0.0f, num + 0.5f/*finX*/, 1.0f);

		// Relleno la tabla con la informaci�n del jugador.
		if (!_entity->getType().compare("Player"))
		{
			//Crear la tabla
			std::stringstream script;
			script << "players[" << _entity->getEntityID() << "].life = " << _life;
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		// Relleno la tabla con la informaci�n del enemigo.
		if (!_entity->getEntityTag().compare("enemy"))
		{
			std::stringstream script;
			script	<< "enemies[" << _entity->getEntityID() << "].life = " << _life;
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		return true;
	} // spawn
	
	//---------------------------------------------------------

	bool CLife::accept(IMessage *message)
	{
		return (message->getType().compare("MDamaged") == 0) || !message->getType().compare("MSendBillboard")
			   || !message->getType().compare("MHealed") || !message->getType().compare("MEntityDeathListener");

	} // accept
	
	//---------------------------------------------------------

	void CLife::process(IMessage *message)
	{
		// Si es un mensaje de da�o, se procesa y se comprueba que la entidad no ha muerto; con todo lo que ello conlleva.
		if (!message->getType().compare("MDamaged"))
		{
				MDamaged *md = static_cast <MDamaged*> (message);
				// Disminuir la vida de la entidad
				_life -= md->getHurt();
				
				if (_life <= 0) {
					_life = 0;
					// Si han matado al jugador salir de la partida
					if (_entity->isPlayer())
						Application::CBaseApplication::getSingletonPtr()->setState("gameOver");
					// Si han matado al enemigo matarlo
					else if (!_entity->getType().compare("Enemy"))
					{
						// @TODO @ENTITYDEATH Habr� que borrar este bloque de c�digo cuando la notificaci�n de la muerte de la entidad funcione bien.
						/*MAttackEntity *m = new MAttackEntity();
						m->setAttack(false);

						if (md->getKiller())
							md->getKiller()->emitMessage(m, this);*/

						// Notifico a todos mis oyentes de que la entidad ha muerto.
						notifyDeathListeners();

						/*
						Map::CEntity * muertoInfo = Map::CMapParser::getSingletonPtr()->getEntityInfo("Entity");

						std::stringstream name;
						name << _entity->getEntityID();
						muertoInfo->setName(name.str());

						std::stringstream pos;
						pos << _entity->getPosition().x << ' ' << _entity->getPosition().y << ' ' << _entity->getPosition().z;
						muertoInfo->setAttribute("position", pos.str());
						muertoInfo->setAttribute("orientation", "90");
						muertoInfo->setAttribute("model", "loco.mesh");

						Logic::CEntity *muerto = Logic::CEntityFactory::getSingletonPtr()->createEntity(muertoInfo, _entity->getMap());
						*/
						if (!_death)
						{
							_death = true;
							MEntityDeath *m_death = new MEntityDeath();
							m_death->setEntityDeath(_entity);
							_entity->emitMessage(m_death);
						}
					}
					else if (!_entity->getName().compare("Jack") || !_entity->getName().compare("Erick")
						      || !_entity->getName().compare("Amor"))
					{
						notifyDeathListeners();

						//Los heroes no pueden morir, se quedan inco
						//Desactivamos sus componentes

						MActivarComponente *m_deactComp = new MActivarComponente();
						m_deactComp->setActivar(false);
						m_deactComp->setNombreComponente("CRouteTo CAttack CLanzadorGranadas CHeal CScript CTiempoBala CSteeringMovement CDistanceAttack");
							//"CDistanceAttack CLanzadorGranadas CAttack CHeal CAnimatedGraphics CLife CBillboardSelected CPhysicCharacter CSteeringMovement CRouteTo CStateMachineExecutor CSelectable CScript CEmpujable CTiempoBala");
						_entity->emitMessage(m_deactComp, this);
					}
				}
				// @todo Poner la animaci�n de herido.
				// @todo Si la vida es menor que 0 poner animaci�n de morir.

				float porcentajeVida = _life/_maxLife;
				float num = 0.5f - porcentajeVida/2.0f;
				//_billboard->setPosicionImagen(num/*inicioX*/, 0.0f, num + 0.5f/*finX*/, 1.0f);

				if (!_entity->getName().compare("Jack"))
				{
					//Actualizamos la vida en la interfaz
					GUI::CServer::getSingletonPtr()->getInterfazController()->actualizarBarraVida('1',_life/_maxLife);
				}
				if (!_entity->getName().compare("Erick"))
				{
					//Actualizamos la vida en la interfaz
					GUI::CServer::getSingletonPtr()->getInterfazController()->actualizarBarraVida('2',_life/_maxLife);
				}
				if (!_entity->getName().compare("Amor"))
				{
					//Actualizamos la vida en la interfaz
					GUI::CServer::getSingletonPtr()->getInterfazController()->actualizarBarraVida('3',_life/_maxLife);
				}
		} else if (!message->getType().compare("MEntityDeathListener")) {
			// Si en un mensaje de listener se mira si hay que a�adirlo o borrarlo y se hace.

			MEntityDeathListener *m = static_cast <MEntityDeathListener*> (message);

			if (m->getAdd())
				addListener(m->getListener());
			else
				removeListener(m->getListener());
			
		} else if (!message->getType().compare("MHealed"))
		{
			MHealed *mh = static_cast <MHealed*> (message);
			// Aumentar la vida de la entidad
			_life += mh->getHeal();
			// Si la entidad se ha curado del todo paramos
			if (_life >= _maxLife)
			{
				_life = _maxLife;
				MCureEntity *m = new MCureEntity();
				m->setCure(false);
				mh->getHealer()->emitMessage(m, this);
			}
		}

		// Relleno la tabla con la informaci�n del jugador.
		if (!_entity->getType().compare("Player"))
		{
			//Crear la tabla
			std::stringstream script;
			script << "players[" << _entity->getEntityID() << "].life = " << _life;
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

		// Relleno la tabla con la informaci�n del enemigo.
		if (!_entity->getEntityTag().compare("enemy"))
		{
			std::stringstream script;
			script	<< "enemies[" << _entity->getEntityID() << "].life = " << _life;
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		}

	} // process

	//---------------------------------------------------------

	void CLife::addListener(IDeathListener* listener)
	{
		_listeners.push_back(listener);
	
	} // addListener

	//---------------------------------------------------------

	void CLife::removeListener(IDeathListener* listener)
	{
		_listeners.remove(listener);

	} // removeListener

	//---------------------------------------------------------

	void CLife::notifyDeathListeners()
	{
		TListenersList::iterator it, end;
		it = _listeners.begin();
		end = _listeners.end();

		for (; it != end; it++)
			(*it)->entityDeath(_entity);

		_listeners.clear();
		
	} // notifyDeathListeners

	//---------------------------------------------------------

} // namespace Logic

