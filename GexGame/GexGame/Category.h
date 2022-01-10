#pragma once


namespace Category
{
	enum type
	{
		None = 0,
		SceneAirLayer = 1 << 0,
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft = 1 << 3,
		Pickup = 1 << 4,
		AlliedProjectile = 1 << 5,
		EnemyProjectile = 1 << 6,

		// New Categories are needed for pacman
		// you can just add new ones without changing anything else
		Pacman = 1 << 7,
		Cherry = 1 << 8,
		Ghost = 1 << 9,

		Aircraft = PlayerAircraft | AlliedAircraft | EnemyAircraft,
		Projectile = AlliedProjectile | EnemyProjectile,
		SpaceJunk = Projectile | Pickup | EnemyAircraft,
	
	};
}

