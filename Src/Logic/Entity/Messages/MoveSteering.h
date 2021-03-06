/**
@file MoveSteering.h

Contiene la declaraci�n del mensaje de un steering movement.

@see Logic::IMessage

@author Luis Mendoza
@date Enero, 2012
*/

#ifndef __Logic_MoveSteering_H
#define __Logic_MoveSteering_H

#include "Logic/Entity/Message.h"

#include "BaseSubsystems/Math.h"

namespace Logic 
{
	/**
	Clase mensaje que se encargar� de avisar a una entidad de que hay que hacer un steering movement.

	@author Luis Mendoza
	@date Enero, 2012
	*/
	class MMoveSteering : public IMessage
	{
	public:

		/**
		Constructor por defecto.
		*/
		MMoveSteering();

		/**
		M�todo que establece el tipo de movimiento.

		@param movementType entero que indica el tipo de movimiento (ver los tipos en IMovement).
		*/
		void setMovementType(int movementType);

		/**
		M�todo que devuelve el tipo de movimiento almacenado en el mensaje.

		@return Tipo de movimiento.
		*/
		int getMovementType();

		/**
		M�todo que establece en el mensaje el destino del movimiento.

		@param target punto de destino.
		*/
		void setTarget(Vector3 target);

		/**
		M�todo que devuelve del mensaje el destino del movimiento.

		@return el punto de destino.
		*/
		Vector3 getTarget();

		/**
		Devuelve true, si este mensaje es el primer movimiento de una
		ruta a seguir.
		*/
		bool isFirstMoveOfRoute();

		/**
		Si firstMove es true, indica que este mensaje contiene
		el primer movimiento de una ruta a seguir.
		*/
		void setFirstMoveOfRoute(bool firstMove);

		/*
		Asignacion de la velocidad extra
		*/
		void setExtraVelocity(float velocity) {_extraVelocity = velocity;}
		
		/*
		Get de la velocidad extra
		*/
		float getExtraVelocity() {return _extraVelocity;}

	protected:

		/**
		Atributo que indica el tipo de movimiento (ver los tipos en IMovement).
		*/
		int _movType;

		/**
		Atributo que indica el destino del movimiento.
		*/
		Vector3 _target;

		/**
		Atributo que indica si el mensaje es el primer movimiento
		de una ruta	a seguir.
		*/
		bool _firstMoveOfRoute;

		/*
		Velocidad extra que tendra en un movimiento concreto
		*/
		float _extraVelocity;
	}; // class MMoveSteering

} // namespace Logic

#endif // __Logic_MoveSteering_H