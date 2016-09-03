//The player that will move around on the screen
class Player	
{
    public:
		//The dimensions of the player
		static const int PLAYER_WIDTH = 20;
		static const int PLAYER_HEIGHT = 20;

		//Maximum axis velocity of the player
		static const int PLAYER_VEL = 10;

		//Initializes the variables
		Player();

		//Takes key presses and adjusts the player's velocity
		void handleEvent( SDL_Event& e );

		//Moves the player
		void move();

		//Shows the player on the screen
		void render();

    private:
		//The X and Y offsets of the player
		int mPosX, mPosY;

		//The velocity of the player
		int mVelX, mVelY;
}


