/**
@file ParticleEffect.h


@author Alberto
@date septiembre, 2012
*/


#ifndef __Graphics_ParticleEffect_H
#define __Graphics_ParticleEffect_H

#include "BaseSubsystems/Math.h"

#include <string>

namespace Logic
{
	class CEntity;
}
namespace Ogre 
{
	class Entity;
	class SceneNode;
	class Vector3;
	class ParticleSystem;
}

namespace Graphics 
{
	class CScene;
}

namespace Graphics 
{
	/**

	@ingroup graphicsGroup

	@author Alberto
	@date Septiembre, 2012
	*/
	class CParticleEffect 
	{
	public:

		/**
		Constructor de la clase.
		*/
		CParticleEffect(std::string &name,std::string &effect, Vector3 &point);
		CParticleEffect(std::string &name,std::string &effect, Vector3 &point, float altura);
		
		/**
		Destructor de la clase.
		*/
		virtual ~CParticleEffect();

		void setPosition(Vector3 &point);

		void setOrientation(Vector4 &orientation);

		void setStatic(bool statc);

		bool getStatic();

	protected:
		friend class CScene;
		
	
		Ogre::ParticleSystem* _particleSystem;


		Ogre::SceneNode* _sceneNode;

		Vector4 _orientation;
		/**
		Poder mantener una altura inicial constante
		*/
		float _altura;

		bool _static;
	};

}

#endif
