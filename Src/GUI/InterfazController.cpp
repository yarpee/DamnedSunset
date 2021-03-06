
#include "InterfazController.h"
#include "InputManager.h"

#include "Logic/Server.h"
#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Message.h"

#include "Logic/Maps/Map.h"

#include <cassert>

#include <CEGUISystem.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>
#include <elements/CEGUIPushButton.h>

#include <CEGUIUDim.h>

//Mensajes
#include "Logic/Entity/Messages/UbicarCamara.h"
#include "Logic/Entity/Messages/ActivarComponente.h"

//Includes para crear entidades dinamicamente
#include "Map/MapEntity.h"
#include "Logic/Maps/EntityFactory.h"
#include "Logic/Maps/Map.h"


#include "Logic\Entity\Message.h"
#include "Logic\Entity\Messages\EmplaceBuilding.h"
#include "Logic\Entity\Messages\Damaged.h"
#include "Logic\Entity\Messages\EntitySelected.h"
#include "Logic\Entity\Messages\ActivateSkill.h"
#include "Logic\Entity\Messages\ActivarTiempoBala.h"

#include "Logic\Entity\Messages\CrearBillboardMovimiento.h"
#include "Logic\Entity\Messages\LanzarGranada.h"
#include "BaseSubsystems/Server.h"

// ScriptManager
#include "ScriptManager\Server.h"

namespace GUI {

	CInterfazController::CInterfazController()
	{

	} 

	//--------------------------------------------------------

	CInterfazController::~CInterfazController()
	{
		deactivate();
	}

	bool CInterfazController::init()
	{
		_vida1 = 100000;

		// Cargamos la interfaz
		//CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Interfaz.layout");

		//_interfazWindow = CEGUI::WindowManager::getSingleton().getWindow("Interfaz");
		//_interfazWindow =  (CEGUI::Window*)(ScriptManager::CServer::getSingletonPtr()->getGlobal("interfazW", error));
		//this->ocultarBotones();

		// Cargamos la ventana que muestra los FPS
		//CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Time.layout");
		//_fpsWindow = CEGUI::WindowManager::getSingleton().getWindow("Time");

		// Asociamos los botones del men� con las funciones que se deben ejecutar.
		//CEGUI::WindowManager::getSingleton().getWindow("Interfaz/bPersonaje1")->
		//	subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickPersonaje1, this));

		//CEGUI::WindowManager::getSingleton().getWindow("Interfaz/bPersonaje2")->
		//	subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickPersonaje2, this));

		//CEGUI::WindowManager::getSingleton().getWindow("Interfaz/bPersonaje3")->
		//	subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::SubscriberSlot(&GUI::CInterfazController::clickPersonaje3, this));

		_time = 0;
		_nFrames = 0;
		return true;
	}
	//--------------------------------------------------------

	void CInterfazController::activate()
	{
		CInputManager::getSingletonPtr()->addKeyListener(this);

		ScriptManager::CServer::getSingletonPtr()->executeProcedure("activate");

		// Activamos la ventana de interfaz
		//CEGUI::System::getSingletonPtr()->setGUISheet(_interfazWindow);
		//_interfazWindow->setVisible(true);
		//_interfazWindow->activate();
		
		// Activamos la ventana que muestra los FPS
		//_interfazWindow->addChildWindow(_fpsWindow);
		//_fpsWindow->setVisible(true);
		//_fpsWindow->activate();
	}

	//--------------------------------------------------------

	void CInterfazController::deactivate()
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);


		ScriptManager::CServer::getSingletonPtr()->executeProcedure("desactivarInterfazNoche");

	} // deactivate

	void CInterfazController::tick(unsigned int msecs)
	{
		// Actualizamos el conteo de FPS
		_time += msecs;
		++_nFrames;
		if (_time > 500)
		{
			std::stringstream text;
			text << "\"FPS: " << (_nFrames*1000)/_time << "\"";
			//_fpsWindow->setText(text.str());
			std::stringstream script;
			script << "interfazDeltaTime = " << _time << " ";
			script << "interfazTick" << "(" << text.str() << ")";
			ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());

			_time = 0;
			_nFrames = 0;
		}
	
		
	}


	bool CInterfazController::keyPressed(TKey key)
	{
		return false;
	}

	//--------------------------------------------------------

	bool CInterfazController::keyReleased(TKey key)
	{
		return false;

	}

	/**
		VISUALIZAR LOS DISTINTOS BOTONES Y MENUS
	**/
	//void CInterfazController::ocultarBotones() {
		//_interfazWindow->getChild("Interfaz/Menu")->getChild("Interfaz/Menu/b1")->setVisible(false);
		//_interfazWindow->getChild("Interfaz/Menu")->getChild("Interfaz/Menu/b2")->setVisible(false);
		//_interfazWindow->getChild("Interfaz/Menu")->getChild("Interfaz/Menu/b3")->setVisible(false);
		//_interfazWindow->getChild("Interfaz/Menu")->getChild("Interfaz/Menu/b4")->setVisible(false);
	//}
	//void CInterfazController::cargarBoton(char numBoton, std::string nombreBoton) {
		//std::string nombreHijo = "Interfaz/Menu/b";
		//nombreHijo+=numBoton;
		//std::string imagen1 = "set:InterfazUtils image:";
		//std::string imagen2 = "set:InterfazUtils image:";
		//std::string imagen3 = "set:InterfazUtils image:";
		//imagen1.append(nombreBoton);
		//imagen2.append(nombreBoton)+='2';
		//imagen3.append(nombreBoton)+='3';

		//_interfazWindow->getChild("Interfaz/Menu")->getChild(nombreHijo)->setProperty("NormalImage",imagen1);
		//_interfazWindow->getChild("Interfaz/Menu")->getChild(nombreHijo)->setProperty("HoverImage",imagen2);
		//_interfazWindow->getChild("Interfaz/Menu")->getChild(nombreHijo)->setProperty("PushedImage",imagen3);
		//_interfazWindow->getChild("Interfaz/Menu")->getChild(nombreHijo)->setVisible(true);
	//}

	//void CInterfazController::menuJugador1() {
		//_estado = normal;
		//_jugadorSel = 1;
		////this->ocultarBotones();
		//ScriptManager::CServer::getSingletonPtr()->executeProcedure("ocultarBotones");
		////this->cargarBoton('1', "martillo");
		////this->cargarBoton('2',"granada");
		////this->cargarBoton('3',"granada");
		////this->cargarBoton('4',"granada");
		//std::stringstream script;
		//script << "cargarBoton" << "(1," << "\"martillo\"" << ")";
		//ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		//script.str("");
		//script << "cargarBoton" << "(4," << "\"granada\"" << ")";
		//ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
	//}
	//void CInterfazController::menuJugador2() {
		//_estado = normal;
		//_jugadorSel = 2;
		////this->ocultarBotones();
		//ScriptManager::CServer::getSingletonPtr()->executeProcedure("ocultarBotones");
		////this->cargarBoton('1',"martillo");
		////this->cargarBoton('4',"bolazul");
		//std::stringstream script;
		//script << "cargarBoton" << "(1," << "\"martillo\"" << ")";
		//ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		//script.str("");
		//script << "cargarBoton" << "(4," << "\"bolazul\"" << ")";
		//ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
	//}

	//void CInterfazController::menuJugador3() {
		//_estado = normal;
		//_jugadorSel = 3;
		////this->ocultarBotones();
		//ScriptManager::CServer::getSingletonPtr()->executeProcedure("ocultarBotones");
		////this->cargarBoton('1',"martillo");
		////this->cargarBoton('3',"bolazul");
		////this->cargarBoton('4',"jeringa");
		//std::stringstream script;
		//script << "cargarBoton" << "(1," << "\"martillo\"" << ")";
		//ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		//script.str("");
		//script << "cargarBoton" << "(3," << "\"bolazul\"" << ")";
		//ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
		//script.str("");
		//script << "cargarBoton" << "(4," << "\"jeringa\"" << ")";
		//ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
	//}
	

	/**
		GESTIONA LA NAVEGACION ENTRE LOS BOTONES
	**/
	//bool CInterfazController::clickPersonaje1(const CEGUI::EventArgs& e)
	//{
	//	this->sendClickMessage("Jack");
	//	return true;
	//}
	//bool CInterfazController::clickPersonaje2(const CEGUI::EventArgs& e)
	//{
	//	this->sendClickMessage("Erick");
	//	return true;
	//}
	//bool CInterfazController::clickPersonaje3(const CEGUI::EventArgs& e)
	//{
	//	this->sendClickMessage("Norah");
	//	return true;
	//}
	//bool CInterfazController::clickB1(const CEGUI::EventArgs& e)
	//{
	//	std::stringstream script;
	//	switch (_estado) {
	//	case normal:
	//		//BOTON CONSTRUIR
	//		_estado = construir;
	//		//this->ocultarBotones();
	//		ScriptManager::CServer::getSingletonPtr()->executeProcedure("ocultarBotones");
	//		//this->cargarBoton('1',"volver");
	//		//this->cargarBoton('2',"torreta");
	//		script << "cargarBoton" << "(1," << "\"volver\"" << ")";
	//		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
	//		script.str("");
	//		script << "cargarBoton" << "(2," << "\"torreta\"" << ")";
	//		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
	//		break;
	//	case construir:
	//		//BOTON VOLVER
	//		_estado = normal;
	//		switch (_jugadorSel) {
	//			case 1: this->menuJugador1(); break;
	//			case 2: this->menuJugador2(); break;
	//			case 3: this->menuJugador3(); break;
	//		}
	//		break;
	//	}
	//	return true;
	//}
	//bool CInterfazController::clickB2(const CEGUI::EventArgs& e)
	//{
	//	Logic::CEntity *player = Logic::CServer::getSingletonPtr()->getPlayer();

	//	Logic::MEmplaceBuilding *buildMessage = new Logic::MEmplaceBuilding();
	//	buildMessage->setAction(Logic::BuildingMessage::START_BUILDING);
	//	buildMessage->setBuildingType("Turret");

	//	return player->emitMessage(buildMessage);
	//}
	//bool CInterfazController::clickB3(const CEGUI::EventArgs& e)
	//{
	//	if (_jugadorSel == 3)	
	//	{
	//		//Ralentizar tiempo
	//		Logic::MActivarTiempoBala * m = new Logic::MActivarTiempoBala();
	//		m->setTime(5.0f);

	//		unsigned int id1 = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Amor")->getEntityID();
	//		unsigned int id2 = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Jack")->getEntityID();
	//		unsigned int id3 = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Erick")->getEntityID();

	//		m->addEntity(id1);
	//		m->addEntity(id2);
	//		//m->addEntity(id3);
	//		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Amor")->emitMessage(m);

	//	}
	//	return true;
	//}
	//bool CInterfazController::clickB4(const CEGUI::EventArgs& e)
	//{

	//	if (_jugadorSel == 1)
	//	{
	//		//Granada
	//		Logic::MLanzarGranada *mLanzarGranada = new Logic::MLanzarGranada();
	//		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Jack")->emitMessage(mLanzarGranada);
	//		mLanzarGranada = new Logic::MLanzarGranada();
	//		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("PlayerGod")->emitMessage(mLanzarGranada);
	//	}
	//	if (_jugadorSel == 2)
	//	{
	//		//Granada
	//		Logic::MLanzarGranada *mLanzarGranada = new Logic::MLanzarGranada();
	//		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("Erick")->emitMessage(mLanzarGranada);
	//		mLanzarGranada = new Logic::MLanzarGranada();
	//		Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("PlayerGod")->emitMessage(mLanzarGranada);
	//	}
	//	if (_jugadorSel == 3)
	//	{
	//		//Jeringuilla
	//		Logic::MActivateSkill *m_skill = new Logic::MActivateSkill();
	//		m_skill->setSkill(Logic::TSkill::CURE);
	//		Logic::CServer::getSingletonPtr()->getPlayer()->emitMessage(m_skill);
	//	}
	//	return true;
	//}

	void CInterfazController::sendClickMessage(std::string name)
	{
		//Obtener la entidad encargadad de controllar el gameplay
		//Logic::CEntity *diosEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName("PlayerGod");
			
		//Crear y enviar el mensaje de entity selected
		//Logic::MEntitySelected* m_selected = new Logic::MEntitySelected();

		//Logic::CEntity * playerEntity = Logic::CServer::getSingletonPtr()->getMap()->getEntityByName(name);
		//m_selected->setSelectedEntity(playerEntity);
		//m_selected->setInterface(true);
		//diosEntity->emitMessage(m_selected);

		std::stringstream script;
		script << "sendClickMessage(" << "\"" << name << "\"" << ")";
		ScriptManager::CServer::getSingletonPtr()->executeScript(script.str().c_str());
	}

	bool CInterfazController::isMouseOnInterface(){
		CEGUI::Window* guiW1 = CEGUI::WindowManager::getSingleton().getWindow("Interfaz");
		CEGUI::Window* guiW2 = CEGUI::WindowManager::getSingleton().getWindow("InterfazControles");
		CEGUI::Window* guiW3 = CEGUI::WindowManager::getSingleton().getWindow("InterfazDia");
		CEGUI::Window* guiW4 = CEGUI::WindowManager::getSingleton().getWindow("InterfazPrincipal");

		CEGUI::Window* guiMouse = CEGUI::System::getSingletonPtr()->getWindowContainingMouse();

		/*
		Si el raton esta sobre una de estas ventanas (ventanas las cuales son transparentes), es que no esta sobre ninguna ventana secundaria.
		*/
		if (guiMouse == guiW1 || guiMouse == guiW2 || guiMouse == guiW3 || guiMouse == guiW4)
		{
			//printf("FALSE");
			return false;
		} else {
			//printf("TRUE");
			return true;
		}
	}
} // namespace GUI
