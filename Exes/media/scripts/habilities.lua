--Hablididades de los personajes
function habilidadGranada()
	print("habilidad granada")
end

function habilidadGranadaTeletransportadora()
	print("habilidad Granada Teletransportadora")
end

function habilidadRalentizarTiempo()
	print("habilidad Ralentizar Tiempo")
end

function habilidadCurar()
	print("habilidad Curar")
end

function construirTorreta()
	print("construir Torreta")
end

function inicializarBotonesDia()
	print("inicializarBotonesDia")
	cargarBoton(1,"martillo","construirTorreta")
	ocultarBoton(2)
	ocultarBoton(3)
	cargarBoton(4,"bolazul","cambiarANoche")
	print("fin inicializarBotonesDia")
	
	cargarBotonIA(1,"BotonIA1", "funcionIA1")
	cargarBotonIA(2,"BotonIA2", "funcionIA2")
	cargarBotonIA(3,"BotonIA3", "funcionIA3")
end

function funcionIA1()
	print("funcionIA1")
end

function funcionIA2()
	print("funcionIA2")
end

function funcionIA3()
	print("funcionIA3")
end

function cambiarANoche()
	local mensaje = LUA_MCambiarDiaNoche()
	mensaje:setCambiarADia(false)
	mensaje:send()
	
	ocultarBoton(1)
	ocultarBoton(2)
	ocultarBoton(3)
	ocultarBoton(4)
	
	--Ponemos visibles los botones de la IA
	CEGUI.WindowManager:getSingleton():getWindow("InterfazControles/MenuBotonesIA"):setVisible(true)
end