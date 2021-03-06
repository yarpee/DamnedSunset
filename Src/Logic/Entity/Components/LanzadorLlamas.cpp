/**
@file LanzadorLlamas.cpp

Contiene la implementaci�n del componente que controla el lanzallamas.

@see Logic::CLanzadorLlamas
@see Logic::IComponent

@author Luis Mendoza
@date Agosto, 2012
*/

#include "LanzadorLlamas.h"

#include "Logic/Server.h"
#include "BaseSubsystems/Server.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"

#include "Graphics/Billboard.h"

#include "Logic/Entity/Messages/LanzarLlamas.h"
#include "Logic/Entity/Messages/Damaged.h"
#include "Logic/Entity/Messages/ParticleEffect.h"
#include "Logic/Entity/Messages/SoundEffect.h"

#include "Physics/Server.h"

namespace Logic 
{
	IMP_FACTORY(CLanzadorLlamas);
	
	//---------------------------------------------------------

	CLanzadorLlamas::CLanzadorLlamas() : IComponent() {

	}

	CLanzadorLlamas::~CLanzadorLlamas() {
		if (_billboard)
			delete _billboard;
		if (_flamesDirection)
			delete _flamesDirection;
	}

	bool CLanzadorLlamas::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		// Billboard que se�ala el alcance del lanzallamas
		_billboard = new Graphics::CBillboard(entity);
		if(entityInfo->hasAttribute("billboardLlamasMaterial"))
			_billboard->setMaterial(entityInfo->getStringAttribute("billboardLlamasMaterial"));
		if(entityInfo->hasAttribute("billboardLlamasWith") && entityInfo->hasAttribute("billboardLlamasHeight"))
			_billboard->setDimensions(entityInfo->getFloatAttribute("billboardLlamasWith"),entityInfo->getFloatAttribute("billboardLlamasHeight"));
		_billboard->setPerpendicular();
		_billboard->setVisible(false);

		if(entityInfo->hasAttribute("angleLanzallamas"))
			_angleAction = entityInfo->getFloatAttribute("angleLanzallamas");
		if(entityInfo->hasAttribute("radioLanzallamas"))
			_radioAction = entityInfo->getFloatAttribute("radioLanzallamas");
		if(entityInfo->hasAttribute("damageLanzallamas"))
			_damageSecs = entityInfo->getFloatAttribute("damageLanzallamas");
		if(entityInfo->hasAttribute("timeLanzallamas"))
			_timeAction = entityInfo->getFloatAttribute("timeLanzallamas");
		if(entityInfo->hasAttribute("frecDamageLlamas"))
			_frecDamage = entityInfo->getFloatAttribute("frecDamageLlamas");
		
		if(entityInfo->hasAttribute("lanzadorLlamasEffect"))
			_lanzadorLlamasEffect = entityInfo->getStringAttribute("lanzadorLlamasEffect");
		if(entityInfo->hasAttribute("lanzadorLlamasSound"))
			_lanzadorLlamasSound = entityInfo->getStringAttribute("lanzadorLlamasSound");


		_timeAcc = 0;
		_secsAcc = 0;
		_flamesOn = false;

		_flamesDirection = new Vector3(Vector3::ZERO);

		return true;
	} // spawn


	bool CLanzadorLlamas::activate()
	{	
		return true;
	} // activate
	//---------------------------------------------------------

	void CLanzadorLlamas::deactivate()
	{	

	} // deactivate
	//---------------------------------------------------------

	bool CLanzadorLlamas::accept(IMessage *message)
	{
		return !message->getType().compare("MLanzarLlamas");
	} // accept
	
	//---------------------------------------------------------

	void CLanzadorLlamas::process(IMessage *message)
	{
		if (!message->getType().compare("MLanzarLlamas"))
		{
			MLanzarLlamas *m_flames = static_cast <MLanzarLlamas*> (message);

			if (m_flames->getOrdenLlamas() == mostrarBLlamas)
			{
				_billboard->setVisible(true);
			} 
			else if (m_flames->getOrdenLlamas() == ocultarBLamas)
			{
				_billboard->setVisible(false);
			}
			else if (m_flames->getOrdenLlamas() == lanzarLlamas)
			{
				// PULSAMOS EL LANZALLAMAS
				std::cout << "Lanzando llamas\n";

				// Ocultamos el billboard
				_billboard->setVisible(false);
				_flamesOn = true;
				_timeAcc = 0;
				_secsAcc = 0;

				// Posicion destino solo con X, Y.
				Vector2 posDestino = *m_flames->getPosition();
				// Posicion destino con X, Y, Z.  
				Vector3 posDestino3 = Vector3(posDestino.x, 4, posDestino.y);
				
				// Calculamos el vector de direccion al que apunta el rat�n
				_flamesDirection = new Vector3(posDestino3.x - _entity->getPosition().x, 0, posDestino3.z - _entity->getPosition().z);
				_flamesDirection->normalise();

				Logic::CEntity* * entidadesColision;
				int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions(_entity->getPosition(),
					_radioAction, entidadesColision);

				//Orientar la entidad
				float yaw = atan((posDestino3.x - _entity->getPosition().x) / (posDestino3.z - _entity->getPosition().z));
						if ((posDestino3.z - _entity->getPosition().z) >= 0)
							yaw += Math::PI;

				_entity->setYaw(yaw);

				// Env�o del mensaje al componente que se encarga de mostrar los efectos de part�culas
				MParticleEffect *rc_message = new MParticleEffect();
				Vector3 aux = _entity->getPosition();
				rc_message->setAltura(10);
				rc_message->setPoint(aux);
				rc_message->setEffect(_lanzadorLlamasEffect);
				//rc_message->setOrientation(Vector4(1, _posDestino.x,_posDestino.y + 10,_posDestino.z));
				rc_message->setOrientation(Vector4( 0,1,0,yaw+Math::PI/2));//(Math::PI) * 180 / Math::PI));
				_entity->emitInstantMessage(rc_message,this);

				// Env�o del mensaje al componente que se encarga de reproducir los sonidos
				MSoundEffect *rc2_message = new MSoundEffect();
				rc2_message->setSoundEffect(_lanzadorLlamasSound);
				_entity->emitInstantMessage(rc2_message,this);

				for(int i = 0; i < numColisiones; ++i)
				{
					// Entidad que se encuentra dentro del c�rculo de acci�n
					CEntity * entidad = entidadesColision[i];

					if (!(entidad->getTag() == "Player"))
					{
						Vector3 targ = entidad->getPosition() - _entity->getPosition();

						// Si est� en el sector circular seleccionado se da�a a la entidad
						if ((_flamesDirection->angleBetween(targ)).valueDegrees() < _angleAction/2.0f
							 && _entity->getEntityID() != entidad->getEntityID())
						{
							// Enviamos mensaje de da�o a la entidad
							MDamaged *mDamaged = new MDamaged();
							mDamaged->setHurt(_damageSecs);
							mDamaged->setKiller(0);
							entidad->emitMessage(mDamaged, this);
						}
					}
				}
			}
		}

	} // process
	
	//---------------------------------------------------------

	void CLanzadorLlamas::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);

		if (_flamesOn)
		{
			_timeAcc += msecs;
			_secsAcc += msecs;
			_flamesOn = _timeAcc <= _timeAction;

			if (_secsAcc >= _frecDamage)
			{
				_secsAcc = 0;
				Logic::CEntity* * entidadesColision;
				int numColisiones = Physics::CServer::getSingletonPtr()->detectCollisions(_entity->getPosition(),
						_radioAction, entidadesColision);

				for(int i = 0; i < numColisiones; ++i)
				{
					// Entidad que se encuentra dentro del c�rculo de acci�n
					CEntity * entidad = entidadesColision[i];

					if (!(entidad->getTag() == "Player"))
					{
						Vector3 targ = entidad->getPosition() - _entity->getPosition();
				
						// Si est� en el sector circular seleccionado se da�a a la entidad
						if ((_flamesDirection->angleBetween(targ)).valueDegrees() < _angleAction/2.0f
							 && _entity->getEntityID() != entidad->getEntityID())
						{
							// Enviamos mensaje de da�o a la entidad
							MDamaged *mDamaged = new MDamaged();
							mDamaged->setHurt(_damageSecs);
							mDamaged->setKiller(0);
							entidad->emitMessage(mDamaged, this);
						}
					}
				}
			}
		}

	} // tick

} // namespace Logic