/**
@file Server.h

Contiene la declaraci�n del servidor de f�sica. 

@see Physics::CServer

@author Antonio S�nchez Ruiz-Granados
@date Octubre, 2010
*/

#ifndef __Physics_Server_H
#define __Physics_Server_H

#include <string>

#include "BaseSubsystems/Math.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Physics {
	class CCollisionMng;
};

namespace Logic {
	class CPhysicEntity;
	class CTriggerEntity;
	class CEntity;
};

class CPhysicScene;
class IPhysicModel;
class CPhysicModelSimple;
class CPhysicModelGeneric;
class CPhysicModelCharacter;
class IPhysicObj;
class CPhysicObj;
class CPhysicObjCharacter;

/**
Namespace que contiene las clases nuevas relacionadas con la parte f�sica. 
<p>
En este proyecto tambi�n existe c�digo heredado que est� fuera de este namespace.
El nombre de esas clases comienza por IPhysic o CPhysic.

@author Antonio S�nchez Ruiz-Granados
@date Octubre, 2010
*/
namespace Physics {

    enum TPhysicMode
    {
        PM_STATIC = 0,
        PM_KINEMATIC,
        PM_DYNAMIC
    };

	/**
	Collision groups of physic objects.
	*/
	enum TPhysicGroup
	{
		PG_NONE				= 0x00000000, //Group:
		PG_CHARACTERS		= 1 << 0, //0
		PG_WORLD			= 1 << 1, //1
		PG_BUILDING			= 1 << 2, //2
		PG_TRIGGER			= 1 << 3, //3
		PG_HERO				= 1 << 4, //4
		PG_ENEMY			= 1 << 5, //5
		PG_OTHER			= 1 << 6, //6
		PG_SELECTION		= 1 << 7,
		PG_ALL				= 0xffffffff
	};
	
	/**
	Clase central del subistema f�sico. Se encarga de gestionar las entidades f�sicas
	y simular su comportamiento. Esta clase sirve de wrapper sobre las clases de f�sica
	y cumple varias finalidades:
	
	<ul>
	<li> Proporciona una interfaz com�n con el resto de servidores de la aplicaci�n (gr�ficos, GUI, etc). </li> 
	<li> Simplifica la gesti�n de la escena. PhysX permite trabajar con varias escenas simulat�neamente, 
	pero nuestro juego s�lo va a utilizar una.
	<li> Realiza las conversiones entre los tipos l�gicos y los de PhysX (vectores, matrices, etc).
	</ul>
	
	Esta clase est� implementada como un Singleton de inicializaci�n expl�cita; se debe 
	llamar a su m�todo Init(), para que la instancia est� creada. Al final de 
	la aplicaci�n, habr� que llamar a Release().
	<p>

	@ingroup physicsGroup

	@author Antonio S�nchez Ruiz-Granados
	@date Octubre, 2010
	*/
	class CServer 
	{
	public:

		/**
		Devuelve la �nica instancia de la clase.

		@return Puntero al servidor f�sico.
		*/
		static CServer *getSingletonPtr() { return _instance; }
		
		/**
		Inicializa el servidor f�sico. Esta operaci�n s�lo es necesario realizarla
		una vez durante la inicializaci�n de la aplicaci�n. 

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera el servidor f�sico. Debe llamarse al finalizar la aplicaci�n.
		*/
		static void Release();

		/**
		Funci�n invocada en cada vuelta para actualizaci�n.

		@param secs Segundos desde que se reenderiz� el �ltimo frame.
		@return Valor booleano indicando si todo fue bien.
		*/
		bool tick(float secs);


		//----------------------
		// Gestion de la escena
		//----------------------

		/**
		Crea la escena f�sica. Se asume que s�lo existir� una escena f�sica.
		 */
		void createScene ();

		/**
		Destruye la escena f�sica.
		*/
		void destroyScene ();

		/**
		Devuelve la escena f�sica.

		@return Escena f�sica.
		*/
		CPhysicScene* getScene () const;


		//----------------------
		// Creaci�n de modelos
		//----------------------

		/**
		Crea un modelo f�sico para objetos simples.

		@return modelo con valores por defecto.
		*/
		CPhysicModelSimple* createModelSimple();

		/**
		Crea un modelo f�sico para objetos gen�ricos (objetos compuestos de 
		otros objetos) a partir de un fichero que contiene su descripci�n.

		@param file Ruta del fichero que describe el modelo.
		@param modelo con los valores leidos del fichero.
		*/
		CPhysicModelGeneric* createModelGeneric(const std::string &file);

		/**
		Crea el modelo f�sico de un character controller con forma de c�psula.

		@param radius Radio de la c�psula.
		@param height Altura de la c�psula.
		@return modelo fisico creado.
		*/
		CPhysicModelCharacter* createModelCapsuleCharacter(float radius, float height);

		
		//----------------------------
		// Gesti�n de modelos simples
		//----------------------------

		/**
		A�ade un volumen de colisi�n (shape) con forma de c�psula a un modelo simple.

		@param model Modelo simple al que vamos a a�adir la shape.
		@param radius Radio de la c�psula.
		@param height Altura de la capsula.
		@param group Grupo de colisi�n al que pertenecer� la shape.
		*/
		void createCapsuleShape(CPhysicModelSimple *model, float radius, float height, int group);

		/**
		A�ade un volumen de colisi�n (shape) con forma de esfera a un modelo simple.

		@param model Modelo simple al que vamos a a�adir la shape.
		@param radius Radio de la esfera.
		@param group Grupo de colisi�n al que pertenecer� la shape.
		*/
		void createSphereShape(CPhysicModelSimple *model, float radius, int group);

		/**
		A�ade un volumen de colisi�n (shape) con forma de caja a un modelo simple.

		@param model Modelo simple al que vamos a a�adir la shape.
		@param dimensions Dimensiones de la caja divididas entre 2. Es decir, los lados de la caja
				resultante medir�n dimensions*2.
		@param group Grupo de colisi�n al que pertenecer� la shape.
		*/
		void createBoxShape(CPhysicModelSimple *model, const Vector3 &dimensions, int group);

		/**
		A�ade un volumen de colisi�n (shape) con forma de plano a un modelo simple. El plano
		pasa por el origen de coordenadas.

		@param model Modelo simple al que vamos a a�adir la shape.
		@param normal Vector normal al plano.
		@param group Grupo de colisi�n al que pertenecer� la shape.
		*/
		void createPlaneShape(CPhysicModelSimple *model, const Vector3 &normal, int group);

		/**
		Marca / desmarca un volumen de colisi�n (shape) como trigger.

		@param model Modelo de colisi�n simple al que pertenece la shape.
		@param idxShape �ndice de la shape que queremos marcar / desmarcar como trigger.
		@param isTrigger Indica si la shape es o no un trigger.
		*/
		void setTrigger(CPhysicModelSimple *model, int idxShape, bool isTrigger);

		/**
		Establece la masa de un modelo.

		@param model Modelo f�sico.
		@param mass Masa asociada al modelo f�sico.
		*/
		void setMass(CPhysicModelSimple *model, float mass);

		
		//----------------------------
		// Gesti�n de objetos f�sicos
		//----------------------------

		/**
		Crea un nuevo objeto f�sico y lo activa.

		@param component Componente l�gico asociado a la nueva entidad f�sica.
		@param mode Indica si el objeto es est�tico, din�mico o kinem�tico.
		@param position Posicion inicial del objeto.
		@param orientation Orientaci�n inicial del objeto.
		@param model Modelo que describe el tipo de objeto f�sico a crear.
		@return Nuevo objeto f�sico creado o NULL si hubo alg�n problema.
		*/
		IPhysicObj* createObject(Logic::CPhysicEntity *component, TPhysicMode mode, 
			                     const Vector3 &position, const Matrix3 &orientation, 
								 const IPhysicModel *model); 

		/**
		Crea un nuevo objeto f�sico y lo activa.

		@param component Componente l�gico asociado a la nueva entidad f�sica.
		@param mode Indica si el objeto es est�tico, din�mico o kinem�tico.
		@param position Posicion inicial del objeto.
		@param orientation Orientaci�n inicial del objeto.
		@param model Modelo que describe el tipo de objeto f�sico a crear.
		@return Nuevo objeto f�sico creado o NULL si hubo alg�n problema.
		*/
		IPhysicObj* createTrigger(Logic::CTriggerEntity *component, TPhysicMode mode, 
			                     const Vector3 &position, const Matrix3 &orientation, 
								 const IPhysicModel *model);

		/**
		Destruye un objeto f�sico.

		@param obj Objeto f�sico a eliminar.
		*/
		void destroyObject(IPhysicObj *obj);

		/**
		Devuelve la posici�n de un objeto f�sico.

		@return Posici�n en coordenadas del mundo.
		*/
		Vector3 getPosition(const IPhysicObj *obj);

		/**
		Establece la posici�n de un objeto f�sico.

		@warning No es recomendable utilizar este m�todo. Unicamente se utiliza
		para reposicionar objetos f�sicos al principio del juego.
		Puede afectar al rendimiento de la simulaci�n.
		*/
		void setStaticObjectPosition(IPhysicObj *obj, const Vector3 &position);

		/**
		Devuelve la orientaci�n de un objeto f�sico. Puesto que los objetos f�sicos gen�ricos
		pueden estar compuesto spor varias partes es necesario indicar la parte de la que 
		queremos obtener la orientaci�n. N�tese que los objetos simples s�lo tienen una parte 
		por lo que idxPart siempre deber� ser 0 cuando trabajemos con ellos.

		@param obj Objeto f�sico del que se desea conocer la orientaci�n.
		@param idxPart Parte del objeto f�sico que se usa para recuperar su orientaci�n.
		*/
		Matrix3 getOrientation(const IPhysicObj *obj, int idxPart);
		
		
		
		//------------------------------------
		// Movimiento de entidades kinem�ticas
		//------------------------------------

		/**
		Mueve un objeto f�sico kinem�tico.

		@param obj Objeto f�sico kinem�tico.
		@param pos Nueva posici�n del objeto f�sico.
		*/
		void move(IPhysicObj *obj, const Vector3 &pos);

		/**
		Mueve un objeto f�sico kinem�tico.

		@param obj Objeto f�sico kinem�tico.
		@param rot Nueva rotaci�n del objeto f�sico.
		*/
		void move(IPhysicObj *obj, const Matrix3 &rot);
		
		/**
		Mueve un objeto f�sico kinem�tico.

		@param obj Objeto f�sico kinem�tico.
		@param transf Nueva posici�n y rotaci�n del objeto f�sico.
		*/
		void move(IPhysicObj *obj, const Matrix4 &transf);

		

		//---------------------------------
		// Gesti�n de character controllers
		//---------------------------------

		/**
		Mueve un character controller. El controller puede no terminar en la posici�n
		deseada si colisiona con otras entidades durante el movimiento.

		@param obj Objeto f�sico que representa al character controller.
		@param displ Vector de desplazamiento que representa el movimiento a realizar.
		@return Posible combinaci�n de los flags NxControllerFlag de PhysX indicando
				colisiones.
		*/
		unsigned moveCharacter(CPhysicObjCharacter *obj, const Vector3 &displ);

		/**
		Teletransporta un character controller a una posici�n. Este m�todo no comprueba
		si el controller "cabe" en la posici�n de destino o si terminar� atravesando
		otra entidad ya existente, por lo que debe usarse con cuidado.
		
		@param obj Objeto f�sico que representa al character controller.
		@param position Nueva posici�n del character controller en coordenadas del mundo.
		*/
		void setPosition(CPhysicObjCharacter *obj, const Vector3 &position);


		//--------------------------
		// Lanzamiento de rayos
		//--------------------------

		/**
		 Lanza un rayo y devuelve la primera entidad l�gica contra la que interseca. Si el rayo
		 no choca contra ninguna entidad devuelve NULL.
		 
		 @param ray Rayo lanzado.
		 @param maxDist distancia m�xima de la primera intersecci�n
		 @return Primera entidad l�gica alcanzada o NULL.
		 */
		Logic::CEntity* raycastClosest (const Ray& ray, float maxDist) const; 


		/**
		Devuelve las entidades que tengan una capsula, que hay a una distancia "maxDist" de "point"
		@param point
		@param maxdist
		@param entidades - guarda en esta variable un array con las entidades que colisiona
		@return numero de entidades con las que colisiona
		*/
		int detectCollisions(Vector3 point, float maxDist, Logic::CEntity* * & entidades) const;

		/**
		 Lanza un rayo y devuelve la primera entidad l�gica contra la que interseca. Si el rayo
		 no choca contra ninguna entidad devuelve NULL.
		 
		 @param ray Rayo lanzado.
		 @param point Vector3 que devuelve la posici�n donde ha intersecado el rayo.
		 @param maxDist distancia m�xima a la que se debe encontrar intersecci�n
		 @param groups Mascara de grupos con los que se busca intersecar.
		 @return Primera entidad l�gica alcanzada o NULL.
		 */
		Logic::CEntity* raycastGroup (const Ray& ray, Vector3* point, TPhysicGroup groups = PG_ALL, float maxDist = FLT_MAX ) const; 

		/**
		Lanza un rayo y devuelve la primera entidad l�gica contra la que interseca y el punto que en que ha intersecado.
		Si el rayo
		no choca contra ninguna entidad devuelve NULL.

		@param ray Rayo lanzado.
		@param entity par�metro donde se alamcenar� el punto de la entidada en el que ha chocado
		@return Primera entidad l�gica alcanzada o NULL.
		*/
		Logic::CEntity* raycastAdvanced (const Ray& ray, Vector3* point) const;


	private:

		/**
		Constructor de la clase.
		*/
		CServer();

		/**
		Destructor de la clase.
		*/
		virtual ~CServer();

		/**
		Instancia �nica de la clase.
		*/
		static CServer *_instance;

		/**
		Gestor de colisiones.
		*/
		CCollisionMng *_collisionMng;

		/**
		Modelos f�sicos. En realidad deber�a haber un gestor de recursos en el que registrar
		los distintos modelos y poder reutilizarlos. Cada "tipo" de entidad tendr�a un modelo 
		f�sico asociado, y para crear entidades concretas de ese tipo s�lo habr�a que instanciar 
		su tipo f�sico.	Como no tenemos fichero de tipos de entidades (o arquetipos), por ahora 
		no tiene mucho sentido tener un gestor de modelos f�sicos. Simplemente vamos a almacenar 
		los modelos en una lista para liberarlos al final.
		*/
		std::list<IPhysicModel*> models;

	}; // class CServer

}; // namespace Physics

#endif // __Physics_Server_H
