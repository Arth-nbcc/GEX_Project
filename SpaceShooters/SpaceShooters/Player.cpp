#include "Player.h"

unsigned Player::players = 0;

enum controls { UP = 0, DOWN, LEFT, RIGHT, SHOOT };

enum Weapons { LASER = 0, MISSILE1, MISSILE2 };

Player::Player(std::vector<sf::Texture>& textures,
	int UP, int DOWN,
	int LEFT, int RIGHT,
	int SHOOT)
	:level(1)
	, exp(0) //experience, for future implementation. if kill enemy, experience level ++, level increases
	, expNext(100) /////
	, hp(10)
	, hpMax(10)
	, damage(1)
	, damageMax(3)
	, score(0)

{
	/// update positions
	/// player Center (player central point)
	this->playerCenter.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;


	/// player
	this->sprite.setTexture(textures[0]);
	this->sprite.setScale(0.20f, 0.20f);


	/// bullet & missile
	this->laserTexture = &textures[1];
	this->missile1Texture = &textures[2];
	//this->missile2Texture = &textures[1];

	/// Gun
	this->mainGunSprite.setTexture(textures[3]);

	//Gun position Center (same as player center point)
	this->mainGunSprite.setOrigin(
		this->mainGunSprite.getGlobalBounds().width / 2,
		this->mainGunSprite.getGlobalBounds().height / 2);

	/// timing for shoot
	this->shootTimerMax = 25;
	this->shootTimer = this->shootTimerMax;
	this->damageTimer = 10;
	this->damageTimerMax = this->damageTimerMax;

	//controls
	this->controls[controls::UP] = UP;
	this->controls[controls::DOWN] = DOWN;
	this->controls[controls::LEFT] = LEFT;
	this->controls[controls::RIGHT] = RIGHT;
	this->controls[controls::SHOOT] = SHOOT;

	/// maxspeed, accelaration, force
	this->maxVelocity = 20.f;
	this->acceleration = 1.f;
	this->stabilizerForce = 0.3f;

	//aura


	/// current weapon
	this->currentWeapon = LASER;

	//upgrades
	this->mainGunLevel = 0;
	this->dualMissile1 = true;
	this->dualMissile2 = false;

	//add number of player
	this->playerNr = Player::playerNr;
	Player::players++;
}

Player::~Player()
{
}

int Player::getdamage() const
{
	int damage = 0;

	switch (this->currentWeapon)
	{
	case LASER:
		damage = rand() % this->damageMax + this->damage; //damageMax is 3, so random from 1-3
		break;

	case MISSILE1:
		damage = rand() % this->damageMax + this->damage;
		damage *= 2;	//double damage
		break;

	case MISSILE2:
		damage = rand() % this->damageMax + this->damage;
		damage *= 3;	//3 times damage
		break;

	default:
		damage = rand() % this->damageMax + this->damage;
		break;
	}
	return damage;
}

void Player::Movement()
{
	//UP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::UP])))
	{
		this->direction.x = 0.f;
		this->direction.y = -1.f;

		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}

	//DOWN
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::DOWN])))
	{
		this->direction.x = 0.f;
		this->direction.y = 1.f;

		if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}

	//LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::LEFT])))
	{
		this->direction.x = -1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}

	//RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::RIGHT])))
	{
		this->direction.x = 1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}

	//stabilizier Force
	//for X
	if (this->currentVelocity.x > 0)
	{
		this->currentVelocity.x -= this->stabilizerForce;

		if (this->currentVelocity.x < 0)
			this->currentVelocity.x = 0;
	}
	else if (this->currentVelocity.x < 0)
	{
		this->currentVelocity.x += this->stabilizerForce;

		if (this->currentVelocity.x > 0)
			this->currentVelocity.x = 0;
	}

	//for Y
	if (this->currentVelocity.y > 0)
	{
		this->currentVelocity.y -= this->stabilizerForce;

		if (this->currentVelocity.y < 0)
			this->currentVelocity.y = 0;
	}
	else if (this->currentVelocity.y < 0)
	{
		this->currentVelocity.y += this->stabilizerForce;

		if (this->currentVelocity.y > 0)
			this->currentVelocity.y = 0;
	}

	/// final move
	this->sprite.move(this->currentVelocity.x, this->currentVelocity.y);


	/// player Center, because we need to center it after shoot
	this->playerCenter.x = this->sprite.getPosition().x +
		this->sprite.getGlobalBounds().width / 2;
	this->playerCenter.y = this->sprite.getPosition().y +
		this->sprite.getGlobalBounds().height / 2;
}


/// Accessories for player
void Player::UpdateAccessories()
{

	/// set position of gun to follow player 
	this->mainGunSprite.setPosition(
		this->mainGunSprite.getPosition().x,
		this->playerCenter.y);

	/// animation the main gun and correct after firing (shoot)
	if (this->mainGunSprite.getPosition().x < this->playerCenter.x + 20.f)
	{
		this->mainGunSprite.move(2.f + this->currentVelocity.x, 0.f);
	}
	//correction
	if (this->mainGunSprite.getPosition().x > this->playerCenter.x + 20.f)
	{
		this->mainGunSprite.setPosition(
			this->playerCenter.x + 20.f,
			this->playerCenter.y);
	}
}

void Player::Combact()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->controls[controls::SHOOT]))
		&& this->shootTimer >= shootTimerMax)
	{
		if (this->currentWeapon == LASER)
		{
			/// create bullet
			if (this->mainGunLevel == 0)
			{
				this->bullets.push_back(
					Bullet(laserTexture,
						sf::Vector2f(this->playerCenter.x + 50.f, this->playerCenter.y), //position
						sf::Vector2f(0.2f, 0.2f), //scale
						sf::Vector2f(1.0f, 0.f), //direction
						10.f, 40.f, 2.f));
				//initialVelocity, MaxVelocity, Accelaration
			}
			else if (this->mainGunLevel == 1)
			{

			}
			else if (this->mainGunLevel == 2)
			{

			}

			/// animate gun	(while fire)
			this->mainGunSprite.move(-30.f, 0.f);
		}
		else if (this->currentWeapon == MISSILE1)
		{
			//create missile 1 
			this->bullets.push_back(
				Bullet(missile1Texture,
					sf::Vector2f(this->playerCenter.x, this->playerCenter.y - 40.f),   //position
					sf::Vector2f(0.06f, 0.06f),  //scale
					sf::Vector2f(1.f, 0.f),		//direction
					2.f, 40.f, 1.f));			//initialVelocity, MaxVelocity, Accelaration

			if (this->dualMissile1)
			{
				//create missile 1 
				this->bullets.push_back(
					Bullet(missile1Texture,
						sf::Vector2f(this->playerCenter.x, this->playerCenter.y + 40.f),
						sf::Vector2f(0.06f, 0.06f),
						sf::Vector2f(1.f, 0.f),
						2.f, 40.f, 1.f));
			}
			this->mainGunSprite.move(-30.f, 0.f);
		}
		else if (this->currentWeapon == MISSILE2)
		{
			if (this->dualMissile2)
			{

			}
		}

		this->shootTimer = 0; //RESET TIMER
	}
}

void Player::Update(sf::Vector2u windowBounds)
{
	//update timers
	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer++;

	if (this->damageTimer < this->damageTimerMax)
		this->damageTimer++;

	this->Movement();
	this->UpdateAccessories();
	this->Combact();
}

void Player::Draw(sf::RenderTarget& target)
{
	//target.draw(this->aura);

	//ordering in important, bullets draw beforing the player/sprite
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].Draw(target);
	}

	target.draw(this->mainGunSprite);

	target.draw(this->sprite);

}
