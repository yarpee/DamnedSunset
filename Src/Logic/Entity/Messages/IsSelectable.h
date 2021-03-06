/**
@file IsSelectable.h

Contiene la declaraci�n del mensaje enviado para preguntar a una entidad si es seleccionable

@see Logic::IMessage

@author Alberto Ortega
@date Enero, 2012
*/

//Tiene que ir con una M por delante porque si no da problemas con el define del componente Selectable
#ifndef __Logic_IsSelectable_H
#define __Logic_IsSelectable_H

#include "Logic/Entity/Message.h"

namespace Logic
{
	class CEntity;
}

namespace Logic 
{
	enum SelectablePetition
	{
		SELECTION_REQUEST,
		SELECTION_RESPONSE
	};

	class MIsSelectable : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MIsSelectable();

		/**
		M�todo que devuelve el tipo del mensaje,
		si es de peticion o respuesta de seleccion.

		@return enumerado que contiene el tipo del mensaje.
		*/
		SelectablePetition getMessageType();

		/**
		M�todo que establece el tipo del mensaje,
		si es de peticion o respuesta de seleccion.
		*/
		void setMessageType(SelectablePetition petitionType);

		/**
		Establece la entidad que emite este mensaje.
		Debe ser cambiado cuando se manda una respuesta.
		*/
		void setSenderEntity(CEntity* sender);

		/**
		Devuelve la entidad que envia el mensaje.
		*/
		CEntity* getSenderEntity();

	private:

		/**
		Atributo que contiene el tipo de mensaje que es
		*/
		SelectablePetition _petition;

		unsigned int _senderID;
	};

} // namespace Logic

#endif // __Logic_IsSelectable_H