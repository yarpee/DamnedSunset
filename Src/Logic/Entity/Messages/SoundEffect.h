/**
@file SoundEffect.h

Contiene la declaración del mensaje enviado para indicar que se quiere reporducir un efecto de sonido

@see Logic::IMessage

@author Alberto Ortega
@date Marzo, 2012
*/

//Tiene que ir con una M por delante porque si no da problemas con el define del componente Selectable
#ifndef __Logic_SoundEffect_H
#define __Logic_SoundEffect_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

#include "Sound/Sound.h"

namespace Logic 
{

	class MSoundEffect : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MSoundEffect();

		void setSoundEffect(std::string sound){_sound = sound;}
		std::string getSoundEffect(){return _sound;}

	protected:

		std::string _sound;
		
	};



} // namespace Logic

#endif // __Logic_SoundEffect_H