/**
@file SwitchTrigger.h

Contiene la declaraci�n del componente que envia un mensaje MSwitch a una
entidad cuando su entidad es tocada o dejada de ser tocada.

@see Logic::CSwitchTrigger
@see Logic::IComponent

@author David Llans�
@date Octubre, 2010
*/
#ifndef __Logic_SwitchTrigger_H
#define __Logic_SwitchTrigger_H

#include "Logic/Entity/Component.h"

//declaraci�n de la clase
namespace Logic 
{
/**
	Este componente procesa mensajes de tipo MIsTouched (indica que la 
	entidad ha sido tocada o dejada de ser tocada) para enviar un mensaje MSwitch a 
	una entidad objetivo.
	<p>
	La entidad objetivo se especifica en el mapa con el atributo "target". Este 
	atributo <em>debe</em> ser especificado.
	
    @ingroup logicGroup

	@author David Llans� Garc�a
	@date Octubre, 2010
*/
	class CSwitchTrigger : public IComponent
	{
		DEC_FACTORY(CSwitchTrigger);
	public:

		/**
		Constructor por defecto.
		*/
		CSwitchTrigger() : IComponent(), _targetName(""),
			_target(0) {}
		
		/**
		Inicializaci�n del componente usando la descripci�n de la entidad que hay en 
		el fichero de mapa.
		*/
		virtual bool spawn(CEntity* entity, CMap *map, const Map::CEntity *entityInfo);

		/**
		M�todo que se invoca para activar el componente.
		*/
		virtual bool activate();
		
		/**
		M�todo que se invoca al desactivar el componente.
		*/
		virtual void deactivate();

		/**
		Este componente s�lo acepta mensaje de tipo MIsTouched.
		*/
		virtual bool accept(IMessage *message);

		/**
		Al recibir mensaje MIsTouched emite mensajes MSwitch
		a la entidad objetivo para que cambie de posici�n.
		*/
		virtual void process(IMessage *message);

	protected:

		/**
		Nombre de la entidad a la que se desea enviar un MSwitch cuando se 
		recibe un mensaje MIsTouched.
		*/
		std::string _targetName;

		/**
		Entidad a la que se desea enviar un MSwitch cuando se recibe un mensaje 
		MIsTouched.
		*/
		CEntity *_target;

	}; // class CSwitchTrigger

	REG_FACTORY(CSwitchTrigger);

} // namespace Logic

#endif // __Logic_SwitchTrigger_H
