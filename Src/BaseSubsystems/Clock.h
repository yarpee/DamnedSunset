//---------------------------------------------------------------------------
// Clock.h
//---------------------------------------------------------------------------

/**
@file Clock.h

Contiene la declaraci�n de un interfaz para un temporizador.

@see BaseSubsystems::IClock

@author David Llans�
@date Julio, 2010
*/

#ifndef __BaseSubsystems_Clock_H
#define __BaseSubsystems_Clock_H

#include "ClockListener.h"

#include <list>
#include <utility>

namespace BaseSubsystems 
{
	/**
	Reloj de la aplicaci�n, que sirve para controlar el tiempo de la
	aplicaci�n.
	
	Los m�todos getTime() y getLastFrameDuration() se utilizan para
	saber "la hora" y el n�mero de milisegundos que ocup� el
	�ltimo frame.

	El m�todo updateTime() es el �nico que hace avanzar la hora,
	y est� pensado para ser llamado desde el bucle principal
	de la aplicaci�n, una vez por vuelta.

	Eso significa que entre dos llamadas a updateTime() los
	valores devueltos por getTime() y getLastFrameDuration()
	son siempre los mismos.

	Hay que hacer notar que antes de la primera invocaci�n
	a updateTime() los m�todos getTime() y getLastFrameDuration()
	devuelven 0, y que tras una �nica invocaci�n a updateTime()
	el getLastFrameDuration() devolver� un valor sin sentido.
	Por lo tanto la aplicaci�n deber�a invocar una primera
	vez a updateTime() antes de comenzar el bucle principal, para
	evitar ese comportamiento an�malo del primer frame.

	La clase es en realidad abstracta, pues no implementa el
	m�todo que tiene que ver con la obtenci�n de la hora "f�sica"
	(ya que es dependiente de la plataforma). Ese m�todo virtual
	puro (que aparece en la parte protegida) es el que
	accede al hardware para obtener el tiempo real.

	Todas las unidades son en milisegundos.

	@author David Llans�, Marco Antonio G�mez Mart�n
	@date Agosto, 2010
	*/
	class IClock
	{
	public:
		/** 
		Constructor de la clase 
		*/
		IClock() : _lastTime(0), _lastFrameDuration(0), _lastRealFrameDuration(0), _factorRalentizar(1) {}

		/** 
		Destructor 
		*/
		virtual ~IClock() {}

		/**
		Hace avanzar la hora del reloj, para que
		getTime() y getLastFrameDuration() devuelvan
		los nuevos valores.
		*/
		void updateTime();

		/**
		Devuelve la hora en el momento de la �ltima invocaci�n
		a updateTime().

		@return Hora (en milisegundos) en la �ltima invocaci�n a
		updateTime(). No se debe asumir que la "hora 0" es la hora
		en la que se inici� el temporizador, ni el tiempo de vida
		de la aplicaci�n, ni siquiera del sistema. La hora debe
		tomarse siempre relativa a otra anterior.
		*/
		unsigned long getTime() const { return _lastTime; }

		/**
		Devuelve la duraci�n del �ltimo frame, o lo que es lo mismo,
		el tiempo transcurrido entre las dos �ltimas invocaciones
		a updateTime().

		@return Duraci�n del �ltimo frame. Si se ha invocado menos
		de dos veces a updateTime() el resultado es indeterminado.
		*/
		unsigned int getLastFrameDuration() const { return _lastFrameDuration; }


		/**
		Devuelve la duraci�n del �ltimo frame, o lo que es lo mismo,
		el tiempo transcurrido entre las dos �ltimas invocaciones
		a updateTime().

		@return Duraci�n del �ltimo frame. Si se ha invocado menos
		de dos veces a updateTime() el resultado es indeterminado.
		*/
		unsigned int getLastRealFrameDuration() const { return _lastRealFrameDuration; }
		/**
		A�ade un nuevo oyente del temporizador con el tiempo tras el cual quiere
		ser avisado.

		@param clock tiempo tras el cual el oyente quiere ser avisado (en milisegundos).
		@param listener oyente del temporizador.
		*/
		void addListener(int clock, IClockListener* listener);

		void clearAllListeners();

		void setFactorRalentizar(float f) { _factorRalentizar = f;}
	protected:

		/**
		 M�todo que devuelve la "hora f�sica" del sistema
		 en milisegundos. Cada invocaci�n al m�todo deber�a
		 devolver una hora distinta (si la precisi�n del
		 reloj hardware lo permite).

		 El "sistema de referencia" del valor devuelto puede
		 ser cualquiera, es decir, no se puede asumir que
		 una hora de 1000 milisegundos signifique que la
		 aplicaci�n llega en ejecuci�n 1 segundo, ni siquiera
		 que el reloj se cre� hace 1 segundo.

		 @return Hora en milisegundos.
		 */
		virtual unsigned long getPhysicalTime() = 0;

		/**
		Comprueba si hay que notificar del fin de temporizador a alg�n listener y lo avisa en caso afirmativo.
		Depu�s de ser avisado lo borra de la lista.
		*/
		void notifyListeners();

		/**
		�ltima hora registrada.
		*/
		unsigned long _lastTime;

		/**
		Duraci�n del �ltimo frame
		*/
		unsigned int _lastFrameDuration;


		/**
		Duracion real del �ltimo frame
		*/
		unsigned int _lastRealFrameDuration;

		/*
			Tiempo que se ralentizara el juego
		*/
		float _factorRalentizar;

		/**
		Tipo Lista de oyentes del temporizador.
		*/
		typedef std::pair<unsigned int, IClockListener*> TListenerRef;
		typedef std::pair<int, TListenerRef> TListenerEntry;
		typedef std::list<TListenerEntry> TListenersList;

		/**
		Lista de todos los oyentes del temporizador.
		*/
		TListenersList _listeners;

		unsigned int _currentTime;

	}; // IClock

} // namespace BaseSubsystems

#endif //  __BaseSubsystems_Clock_H
