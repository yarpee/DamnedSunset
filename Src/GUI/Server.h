/**
@file Server.h

Contiene la declaraci�n de la clase CServer, Singleton que se encarga de
la gesti�n de la interfaz con el usuario (entrada de perif�ricos, CEGui...).

@see GUI::CServer

@author David Llans�
@date Agosto, 2010
*/
#ifndef __GUI_Server_H
#define __GUI_Server_H

#include "InputManager.h"
#include "BaseSubsystems/Math.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Logic 
{
	class CAvatarController;
	class CEnemyController;
	class CEnemiesGenerator;
	class CTurretController;
	class CTeletransport;
}

namespace GUI 
{
	class CPlayerController;
	class CCameraController;
	class CInterfazController;
}

namespace CEGUI
{
	class System;
}

// Declaraci�n de la clase
namespace GUI
{
	/**
	Servidor del m�dulo GUI que hace de interfaz con el usuario. Est� 
	implementado como un singlenton de inicializaci�n expl�cita. Sirve 
	para comunicar a CEGUI los eventos producidos ya as� hacer funcionar
	la interfaz gr�fica de usuario y permite que se establezca que entidad 
	es controlada por el GUI::CPlayerController. Este control se hace a 
	trav�s del componente Logic::CAvatarController.

	@ingroup GUIGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CServer : public CKeyboardListener, public CMouseListener
	{
	public:

		/**
		Devuelve la �nica instancia de la clase CServer.
		
		@return �nica instancia de la clase CServer.
		*/
		static CServer* getSingletonPtr() {return _instance;}

		/**
		Inicializa la instancia

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera la instancia de CServer. Debe llamarse al finalizar la 
		aplicaci�n.
		*/
		static void Release();

		/**
		Devuelve la instancia de la clase GUI que se encarga de procesar los
		eventos de entrada para controlar al jugador por si se desea configurar
		externemante.

		@return Instancia de la clase GUI que controla al jugador.
		*/
		CPlayerController *getPlayerController() {return _playerController;}

		/**
		Devuelve la instancia de la clase GUI que se encarga de procesar los
		eventos de entrada para controlar la c�mara si se desea configurar
		externamente.

		@return Instancia de la clase GUI que contra la c�mara.
		*/
		CCameraController *getCameraController() {return _cameraController;}

		/**
		*/
		CInterfazController *getInterfazController() {return _interfazController;}

		/***************************************************************
		M�todos de CKeyboardListener
		***************************************************************/
		
		/**
		M�todo que ser� invocado siempre que se pulse una tecla.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool keyPressed(TKey key);
		
		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de una tecla.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool keyReleased(TKey key);
		
		/***************************************************************
		M�todos de CKeyboardListener
		***************************************************************/
		
		/**
		M�todo que ser� invocado siempre que se mueva el rat�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool mouseMoved(const CMouseState &mouseState);
		
		/**
		M�todo que ser� invocado siempre que se pulse un bot�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool mousePressed(const CMouseState &mouseState);

		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de un bot�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		bool mouseReleased(const CMouseState &mouseState);

		/**
		M�todo que devuelve true en caso de que el rat�n est� encima de la interfaz
		@return true si el rat�n est� encima de la interfaz
		*/
		bool interfaceMouse();

		/**
		M�todo que devuelve la posici�n relativa que tiene el puntero del rat�n
		con respecto del viewPort actual.
		<p>Sirve para hacer raycast desde el viewport y obtener el punto de colisi�n
		al hacer click con el rat�n.
		@return Vector2 que contiene la coordenada X e Y del cursor.
		*/
		Vector2 getMouseRelPos();

		/**
		M�todo para convertir de posici�n relativa en pantalla a absoluta
		
		@param posRel posici�n a convertir
		@return Vector2 contiene la posici�n absoluta
		*/
		Vector2 positionRelToAbs(Vector2 posRel);


	protected:

		/**
		Constructor.
		*/
		CServer ();

		/**
		Destructor.
		*/
		~CServer();

		/**
		Segunda fase de la construcci�n del objeto. Sirve para hacer
		inicializaciones de la propia instancia en vez de inicializaciones 
		est�ticas.

		@return true si todo fue correctamente.
		*/
		bool open();

		/**
		Segunda fase de la destrucci�n del objeto. Sirve para hacer liberar 
		los recursos de la propia instancia, la liberaci�n de los recursos 
		est�ticos se hace en Release().
		*/
		void close();

		/**
		Clase GUI que se encarga de controlar al jugador.
		*/
		CPlayerController *_playerController;

		/**
		Clase GUI que se encarga de controlar la c�mara.
		*/
		CCameraController *_cameraController;

		/**
		Clase GUI que se encarga de controlar la c�mara.
		*/
		CInterfazController *_interfazController;

		/**
		Sistema de la interfaz gr�fica de usuario CEGUI.
		*/
		CEGUI::System *_GUISystem;

	private:
		/**
		�nica instancia de la clase.
		*/
		static CServer* _instance;

		/**
		Posiciones relativas del cursor con respecto del ViewPort actual.
		*/
		float _mouseRelPosX, _mouseRelPosY;

	}; // class CServer

} // namespace GUI

#endif // __GUI_Server_H
