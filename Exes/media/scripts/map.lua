Map = {

	Sand = {
		model = "sand.mesh",
		coste = 2,
	},

	Road = {
		model = "road.mesh",
	},

	Grid = {
		grid_size = 16,
		type = "Grid",
		width = 20,
		height = 20,
		grid_map = {
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
			{ "Sand", "Road", "Road", "Road", "Road", "Road", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand", "Sand" },
		},
	},

	World = {
		position = {0, 0, 0},
		orientation = 0,
		physic_entity = "simple",
		model = "plane.mesh",
		static = true,
		physic_height = 1,
		physic_normal = {0, 1, 0},
		type = "World",
		physic_type = "static",
		physic_shape = "box",
		physic_radius = 1,
		physic_dimensions = {160.0, 0.5, 160.0},
	},

	Camera = {
		distance = 60,
		height = 100,
		grid_position = { 18, 19 },
		targetHeight = 7,
		targetName = "PlayerGod",
		type = "Camera",
		targetDistance = 10,
	},

	PlayerGod = {
		isPlayer = true,
		orientation = 225,
		isTargetCamera = true,
		southVision = 40,
		northVision = 20,
		eastVision = 25,
		grid_position = { 17, 19 },
		westVision = 30,
		type = "PlayerGod",
		eastEntity = 17,
		northEntity = 22,
		westEntity = 17,
		southEntity = 10,
	},

	Sun = {
		position = {0, 10, -100},
		scale = 30.0,
		orientation = 0,
		model = "esfera.mesh",
		grid_position = { 16, 19 },
		speed = 5.0,
		inclination = 120.0,
		type = "Sun",
	},

	EnemiesGenerator = {
		model = "torreta_pie.mesh",
		grid_position = { 19, 2 },
		type = "Enemies",
	},

	Jack = {
		life = 100.0,
		grid_position = { 15, 14 },
		type = "Player",
	},

	Erick = {
		life = 80.0,
		grid_position = { 17, 11 },
		type = "Player",
	},

	Amor = {
		life = 10.0,
		grid_position = { 14, 8 },
		script = "amorScript",
		type = "Player",
	},

	Turret1 = {
		grid_position = { 11, 11 },
		type = "Turret",
	},

	Turret2 = {
		grid_position = { 8, 11 },
		type = "Turret",
	},

	Turret4 = {
		grid_position = { 8, 9 },
		type = "Turret",
	},

	Turret3 = {
		grid_position = { 11, 9 },
		type = "Turret",
	},

}