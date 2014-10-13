#include "SoccerGame.h"

// Declare our game instance
SoccerGame game;

SoccerGame::SoccerGame()
    : _scene(NULL), _wireframe(false)
{
}

void SoccerGame::initialize()
{
    // Load game scene from file
    _scene = Scene::load("res/demo.scene");

    // Get the box model and initialize its material parameter values and bindings
    Node* boxNode = _scene->findNode("box");
    Model* boxModel = boxNode->getModel();
    Material* boxMaterial = boxModel->getMaterial();
    

    spriteBatch = SpriteBatch::create("res/soccer_field.png");

    
    _scene->addNode();

    // Set the aspect ratio for the scene's camera to match the current resolution
    _scene->getActiveCamera()->setAspectRatio(getAspectRatio());
}

void SoccerGame::finalize()
{
    SAFE_RELEASE(_scene);
    SAFE_DELETE(spriteBatch);
}

void SoccerGame::update(float elapsedTime)
{
    // Rotate model
    _scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
}

void SoccerGame::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);
    
    
    spriteBatch->start();
    spriteBatch->draw(Rectangle(0, 0, getWidth(), getHeight()),
                 Rectangle(0, 0, getWidth(), getHeight()), Vector4::one());
    spriteBatch->finish();

    // Visit all the nodes in the scene for drawing
    _scene->visit(this, &SoccerGame::drawScene);
}

bool SoccerGame::drawScene(Node* node)
{
    // If the node visited contains a model, draw it
    Model* model = node->getModel(); 
    if (model)
    {
        model->draw(_wireframe);
    }
    return true;
}

void SoccerGame::keyEvent(Keyboard::KeyEvent evt, int key)
{
    if (evt == Keyboard::KEY_PRESS)
    {
        switch (key)
        {
        case Keyboard::KEY_ESCAPE:
            exit();
            break;
        }
    }
}

void SoccerGame::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
{
    switch (evt)
    {
    case Touch::TOUCH_PRESS:
        _wireframe = !_wireframe;
        break;
    case Touch::TOUCH_RELEASE:
        break;
    case Touch::TOUCH_MOVE:
        break;
    };
}
