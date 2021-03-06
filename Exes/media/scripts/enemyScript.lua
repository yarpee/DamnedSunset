--------------------------------------------------
--				M�quina de estados				--
--------------------------------------------------

-- Definici�n de los distintos estados y sus acciones.
idleState = { event = idleStateEvent, action = idleStateAction }
attackState = { event = attackStateEvent, action = attackStateAction }
moveState = { event = moveStateEvent, action = moveStateAction }
runState = { event = runStateEvent, action = runStateAction }
pauseState = { event = pauseStateEvent, action = pauseStateAction }
attackingOtherEnemiesState = { name = "attackingOtherEnemies estado", event = attackingOtherEnemiesStateEvent, action = attackingOtherEnemiesStateAction }
attackingJackState = { event = attackingJackStateEvent, action = attackingJackStateAction }

-- Tabla con todos los estados.
states = {
	{ name = "idle", state = idleState },
	{ name = "attack", state = attackState },
	{ name = "move", state = moveState },
	{ name = "run", state = runState },
	{ name = "pause", state = pauseState},
	{ name = "attackingOtherEnemies", state = attackingOtherEnemiesState},
	{ name = "attackingJack", state = attackingJackState}
}

-- Funci�n que recoger� los eventos a los cuales reaccionar� la m�quina de estados.
function enemyEvent(event, entity)
	local nextState = states[enemies[entity].state].state.event(event, entity)
	enemies[entity].state = nextState
end

-- Funci�n que se llamar� en cada tick para ejecutar las acciones que haga falta en el estado actual.
function AIAction(entity)
	local nextState = states[enemies[entity].state].state.action(entity)
	enemies[entity].state = nextState
end
