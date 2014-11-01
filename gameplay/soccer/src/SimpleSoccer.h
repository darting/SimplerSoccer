#ifndef SimpleSoccer_H_
#define SimpleSoccer_H_

#include "gameplay.h"
#include "ParamLoader.h"
#include "SoccerPitch.h"
#include "SoccerBall.h"
#include "SoccerTeam.h"
#include "PlayerBase.h"

#include <math.h>

using namespace gameplay;

/**
 * Main game class.
 */
class SimpleSoccer: public Game
{
public:

    /**
     * Constructor.
     */
    SimpleSoccer();

    /**
     * @see Game::keyEvent
     */
	void keyEvent(Keyboard::KeyEvent evt, int key);
	
    /**
     * @see Game::touchEvent
     */
    void touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex);

protected:

    /**
     * @see Game::initialize
     */
    void initialize();

    /**
     * @see Game::finalize
     */
    void finalize();

    /**
     * @see Game::update
     */
    void update(float elapsedTime);

    /**
     * @see Game::render
     */
    void render(float elapsedTime);

private:
    
    bool initializeScene(Node* node);

    /**
     * Draws the scene each frame.
     */
    bool drawScene(Node* node);

	void setupTeamMembers(SoccerTeam* team, Node* player);

	void updateTeamMembers(SoccerTeam* team);

	void simulateToWorld(Node* worldNode, Vector2D simulatePos);

    Scene* _scene;
    bool _wireframe;
};

#endif
