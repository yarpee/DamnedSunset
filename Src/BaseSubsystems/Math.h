/**
@file Math.h

Este fichero contiene la definici�n de ciertos tipos de datos
utilizados por la aplicaci�n y relacionados con la base
matem�tica; en particular, define distintos tipos de matriz,
vector, etc.
<p>
En la pr�ctica, los tipos son simplemente tipos sin�nimos
a los de Ogre, para evitar p�rdidas de tiempo en conversiones
superfluas entre la aplicaci�n y Ogre (s� habr� que hacerlas
entre la aplicaci�n y el motor de f�sica, por ejemplo).
<p>
Se ofrecen tambi�n una serie de funciones auxiliares.
 
@author David Llans�
@date Julio, 2010
*/

#ifndef __BaseSubsystems_Math_H
#define __BaseSubsystems_Math_H

// Includes de Ogre donde se definen los tipos
#include <OgreVector2.h>
#include <OgreVector3.h>
#include <OgreVector4.h>
#include <OgreQuaternion.h>
#include <OgreMatrix3.h>
#include <OgreMatrix4.h>
#include <OgreRay.h>

/**
Definicion de matriz de 4x4. La definici�n del tipo de datos
es la misma que la utilizada por el motor gr�fico, por lo tanto
es dependiente del motor usado.
 */
typedef Ogre::Matrix4 Matrix4;

/**
Definici�n de matriz de 3x3 de rotaci�n. La definici�n del tipo 
de datos es la misma que la utilizada por el motor gr�fico, por 
lo tanto es dependiente del motor usado.
 */
typedef Ogre::Matrix3 Matrix3;

/**
Vector (o punto) 2d utilizado. La definici�n del tipo de datos
es la misma que la utilizada por el motor gr�fico, por lo tanto
es dependiente del motor usado.
 */
typedef Ogre::Vector2 Vector2;

/**
Vector (o punto) 3d utilizado. La definici�n del tipo de datos
es la misma que la utilizada por el motor gr�fico, por lo tanto
es dependiente del motor usado.
 */
typedef	Ogre::Vector3 Vector3;

/**
Vector (o punto) 4d utilizado. La definici�n del tipo de datos
es la misma que la utilizada por el motor gr�fico, por lo tanto
es dependiente del motor usado.
 */
typedef	Ogre::Vector4 Vector4;

/**
Quaternion, usado para c�lculos de rotaciones tridimensionales. 
La definici�n del tipo de datos es la misma que la utilizada por 
el motor gr�fico, por lo tanto es dependiente del motor usado.
 */
typedef Ogre::Quaternion Quaternion;

/**
Rayo. La definici�n del tipo de datos es la misma que la utilizada 
por el motor gr�fico, por lo tanto es dependiente del motor usado.
 */
typedef Ogre::Ray Ray;

/**
Namespace en el que ofrecemos alguna definici�n de constante
matam�tica y m�todos para convertir grados en radianes, etc.
*/
namespace Math
{
	/**
	Definici�n de la constante PI.
	*/
	static const float PI = float( 4.0 * atan( 1.0 ) );

	/**
	Constante para pasar de grados a radianes.
	*/
	static const float _deg2Rad = PI / 180.0f;

	/**
	Constante para pasar de radianes a grados.
	*/
	static const float _rad2Deg = 180.0f / PI;

	/**
	Transforma grados en radianes.

	@param degree �ngulo en grados.
	@return �ngulo en radianes.
	*/
	static float fromDegreesToRadians(float degrees) {return degrees*_deg2Rad;}

	/**
	Transforma radianes en grados.

	@param radian �ngulo en radianes.
	@return �ngulo en grados.
	*/
	static float fromRadiansToDegrees(float radians) {return radians*_rad2Deg;}
	
	/**
	Crea un vector unitario de direcci�n a partir de un angulo de
	orientaci�n en radianes.

	@param orientation Orientaci�n en radianes.
	@return Vector unitario en el plano XZ.
	*/
	static Vector3 getDirection(float orientation) 
	{
		return Vector3(-sin(orientation), 0, -cos(orientation));

	} // getDirection
	
	/**
	Aplica un viraje a una matriz de transformaci�n.

	@param turn Giro en radianes que se quiere aplicar.
	@param transform Matriz de transformaci�n a modificar.
	*/
	static void yaw(float turn, Matrix4& transform) 
	{
		Matrix3 rotation;
		transform.extract3x3Matrix(rotation);
		Ogre::Radian yaw, pitch, roll;
		rotation.ToEulerAnglesYXZ(yaw, pitch, roll);
		Ogre::Radian newYaw = yaw + Ogre::Radian(turn);
		rotation.FromEulerAnglesYXZ(newYaw, pitch, roll);
		transform = rotation;

	} // yaw
	
	/**
	Extrae el estado del viraje de una matriz de transformaci�n.

	@param transform Matriz de transformaci�n.
	@return Viraje de la entidad.
	*/
	static float getYaw(const Matrix4& transform) 
	{
		Matrix3 rotation;
		transform.extract3x3Matrix(rotation);
		Ogre::Radian yaw, pitch, roll;
		rotation.ToEulerAnglesYXZ(yaw, pitch, roll);
		return yaw.valueRadians();

	} // getYaw
	
	/**
	Establece un viraje a una matriz de transformaci�n.

	@param turn Giro en radianes que se quiere etablecer.
	@param transform Matriz de transformaci�n a modificar.
	*/
	static void setYaw(float turn, Matrix4& transform) 
	{
		// Reiniciamos la matriz de rotaci�n
		transform = Matrix3::IDENTITY;
		// Sobre esta rotamos.
		Math::yaw(turn,transform);

	} // setYaw
	
	/**
	Crea un vector unitario de direcci�n en el plano XZ a partir 
	de una matriz de transformaci�n.

	@param transform Matriz de transformaci�n.
	@return Vector unitario en el plano XZ.
	*/
	static Vector3 getDirection(const Matrix4& transform) 
	{
		return getDirection(getYaw(transform));

	} // getDirection

	/**
	Devuelve el coseno del �ngulo que se pasa como par�metro.

	@param angle Angulo sobre el que calcular su coseno.
	@return Coseno del �ngulo.
	*/
	static float Cos(const float angle)
	{
		return Ogre::Math::Cos(angle);
	} // Cos

	/**
	Devuelve el seno del �ngulo que se pasa como par�metro.

	@param angle Angulo sobre el que calcular su seno.
	@return Seno del �ngulo.
	*/
	static float Sin(const float angle)
	{
		return Ogre::Math::Sin(angle);
	} // Sin

	/**
	Dado un �ngulo en radianes entre -PI y PI devuelve el �ngulo equivalente entre 0 y 2*PI.

	@param angle Angulo a transformar.
	@return AnglePos �ngulo positivo.
	*/
	static float AnglePos(const float angle)
	{
		if (angle < 0) {return 2 * PI + angle;}
		else {return angle;}
	} // AnglePos

	/**
	Hace una interpolaci�n lineal entre dos vectores.

	@param v1 Vector desde el que se empieza a interpolar.
	@param v2 Vector que indica el final de la interpolaci�n.
	@param amount Cantidad que se debe interpolar. Desde 0.0 hasta 1.0.
	@return Vector resultante de la interpolaci�n lineal.
	*/
	static Vector3 Lerp(const Vector3 v1, const Vector3 v2, const float amount)
	{
		return v1 + ((v2 - v1) * amount);
	} // Lerp

	/**
	Proyecci�n de un vector sobre otro.

	@param v1 Vector que se proyecta.
	@param v2 Vector sobre el que se proyecta.
	@return float proyecci�n.
	*/
	static float Proy(const Vector3 v1, const Vector3 v2)
	{

		return (v1.length()*v1.length() + v2.length()*v2.length() - (v1 - v2).length()*(v1 - v2).length())
				/ (2 * v2.length());
	} // Proy

	/**
	Producto escalar de dos vectores.

	@param v1 Vector 1.
	@param v2 Vector 2.
	@return float producto escalar.
	*/
	static float ProdEscalar(const Vector3 v1, const Vector3 v2)
	{
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	} // ProdEscalar

	/**
	Coordenada z del producto vectorial de dos vectores.

	@param v1 Vector 1.
	@param v2 Vector 2.
	@return float coordenada z del producto vectorial.
	*/
	static float ZProdVect(const Vector3 v1, const Vector3 v2)
	{
		return v1.x*v2.y - v1.y*v2.x;
	} // ZProdVect

	/**
	Potencia de un n�mero.

	@param base Base de la potencia.
	@param exponent Exponente de la potencia.
	*/
	static float Pow(const float base, const float exponent)
	{
		return Ogre::Math::Pow(base, exponent);
	} // Pow

	/**
	Logaritmo en base 2 del exponente dado.
	*/
	static float Log2(const float exponent)
	{
		return Ogre::Math::Log2(exponent);
	}

	/**
	Devuelve el mayor de dos numeros. O el mismo n�mero si son
	iguales.
	*/
	static int Max(const int a, const int b)
	{
		return a > b ? a : b;
	}

	/**
	isInsideRectanle devuelve si un punto est� dentro del �rea de un rectangulo en base a los 4 v�rtices del y 
	el punto a comprobar

	aux, MIN y MAX son funciones necesarias para poder hacer la comprobaci�n
	*/
	#define MIN(x,y) (x < y ? x : y)
	#define MAX(x,y) (x > y ? x : y)

	static int aux(Vector2 p1, Vector2 p2, Vector2 p){
		float xinters;
		if (p.y > MIN(p1.y,p2.y)) {
		  if (p.y <= MAX(p1.y,p2.y)) {
			if (p.x <= MAX(p1.x,p2.x)) {
			  if (p1.y != p2.y) {
				xinters = (p.y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
				if (p1.x == p2.x || p.x <= xinters)
				  return 1;
			  }
			}
		  }
		}
		return 0;
	}

	static bool isInsideRectangle(Vector2 A,Vector2 B,Vector2 C,Vector2 D,Vector2 P) {
		int count = 0;
		count += aux(A,B,P);
		count += aux(B,C,P);
		count += aux(C,D,P);
		count += aux(D,A,P);

		if (count % 2 == 0)
			return(false);
		else
			return(true);
		
	}

	


	


} // namespace Math

#endif // __BaseSubsystems_Math_H
