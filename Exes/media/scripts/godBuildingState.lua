--------------------------------------------------
--				Estado de building				--
--------------------------------------------------

-- Recogida de eventos del estado building de god.
function godBuildingStateEvent(event)
-- El estado de building es el estado 4.
	local nextState

	-- Evento de click de selecci�n.
	if (event == "OnSelectionClick") then
		-- Si recibo un evento de selecci�n (click izquierdo) mando construir el edificio actual.
		emplaceBuild()

		-- Resto los recursos del edificio.
		god.dayTime = god.dayTime - buildingsCost[buildParameters.building].dayTime
		god.solenium = god.solenium - buildingsCost[buildParameters.building].solenium

		-- Aviso a la interfaz que refresque la cantidad de recursos.
		actualizarHorasAmanecer(god.dayTime)
		actualizarSolenium(god.solenium)

		-- Paso al estado idle.
		nextState = 1
	-- Evento de click de acci�n.
	elseif (event == "OnActionClick") then
		-- Si recibo un evento de acci�n (click derecho) cancelo la construcci�n del edificio actual.
		cancelBuild()

		-- Paso al estado de idle.
		nextState = 1
	-- Evento de construcci�n de edificio
	elseif (event == "OnStartBuild") then
		-- Si recibo otro evento de empezar a construir cancelo el edificio actual y empiezo a construir el nuevo.
		cancelBuild()
		startBuild(buildParameters.building)

		-- Me quedo en el estado actual.
		nextState = 4
	-- Evento de que empieza la noche.
	elseif (event == "OnNightStart") then
		-- Cancelo el edificio actual.
		cancelBuild()
		
		-- Busco el ID de Jack.
		local jackID = -1
	
		for playerID, t in pairs(players) do
			if (t.name == "Jack") then
				jackID = playerID
			end
		end
	
		-- Al empezar la noche selecciono a Jack por defecto.
		selectNewTarget(jackID)
		
		-- Paso al estado de seleccionado.
		nextState = 2
	else
		nextState = 4
	end

	return nextState
end

-- Acci�n del estado build de god.
function godBuildingStateAction()
-- El estado de build es el estado 4.
	local nextState = 4

	return nextState
end
