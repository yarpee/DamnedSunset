/**
@file ParticleEffect.h

Contiene la declaraci�n del mensaje enviado para indicar que se quiere mostrar un efecto de part�culas

@see Logic::IMessage

@author Alberto Ortega
@date Marzo, 2012
*/

//Tiene que ir con una M por delante porque si no da problemas con el define del componente Selectable
#ifndef __Logic_ParticleEffect_H
#define __Logic_ParticleEffect_H

#include "Logic/Entity/Message.h"
#include "BaseSubsystems/Math.h"

namespace Logic 
{

	class MParticleEffect : public IMessage
	{
	public:
		/**
		Constructor por defecto.
		*/
		MParticleEffect();


		/**
		M�todo que devuelve el punto donde se muestra el efecto de part�culas

		@return punto donde se muestra el efecto de part�culas
		*/
		Vector3 getPoint();

		/**
		M�todo que establece el punto donde se muestra el efecto de part�culas

		@param point punto donde se muestra el efecto de part�culas
		*/
		void setPoint(Vector3 point);

		/**
		M�todo que estable el efecto de part�culas a mostrar
		
		@param effect effecto de part�culas
		*/
		void setEffect(std::string effect);

		/**
		M�todo que devuelve el efecto de part�culas a mostrar

		@return efecto de part�culas
		*/
		std::string getEffect();

		/**
		*/
		void setOrientation(Vector4 &orientation);
		Vector4 getOrientation();

		void setAltura(float altura);
		float getAltura();

		void setStatic(bool Static);
		bool getStatic();

	protected:

		/**
		Atributo que contiene el punto donde se quiere mostrar el efecto de part�culas
		*/
		Vector3 _point;
		Vector4 _orientation;

		float _altura;
		/**
		Efecto de part�culas a mostrar
		*/
		std::string _effect;

		/**
		No mover el efecto con la entidad
		*/
		bool _static;
	};



} // namespace Logic

#endif // __Logic_ParticleEffect_H