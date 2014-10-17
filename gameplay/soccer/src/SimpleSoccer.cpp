#include "SimpleSoccer.h"

// Declare our game instance
SimpleSoccer game;

SimpleSoccer::SimpleSoccer()
    : _scene(NULL), _wireframe(false)
{
}

void SimpleSoccer::initialize()
{
    // Load game scene from file
    _scene = Scene::load("res/demo.scene");

	Bundle* bundle = Bundle::create("res/test.gpb");
	Node* monkey = bundle->loadNode("abc");
	SAFE_RELEASE(bundle);

	_scene->addNode(monkey);

    // Get the box model and initialize its material parameter values and bindings
    Node* boxNode = _scene->findNode("box");
    Model* boxModel = boxNode->getModel();
    Material* boxMaterial = boxModel->getMaterial();

	Material* m = Material::create("res/test.material");


	monkey->getModel()->setMaterial(m);

    // Set the aspect ratio for the scene's camera to match the current resolution
    _scene->getActiveCamera()->setAspectRatio(getAspectRatio());
}

void SimpleSoccer::finalize()
{
    SAFE_RELEASE(_scene);
}

void SimpleSoccer::update(float elapsedTime)
{
    // Rotate model
    _scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
}

void SimpleSoccer::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4::zero(), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    _scene->visit(this, &SimpleSoccer::drawScene);
}

bool SimpleSoccer::drawScene(Node* node)
{
    // If the node visited contains a model, draw it
    Model* model = node->getModel(); 
    if (model)
    {
        model->draw(_wireframe);
    }
    return true;
}

void SimpleSoccer::keyEvent(Keyboard::KeyEvent evt, int key)
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

void SimpleSoccer::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex)
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
