#include "SimpleSoccer.h"

// Declare our game instance
SimpleSoccer game;
Form* form;
Label* fpsLabel;

SimpleSoccer::SimpleSoccer()
    : _scene(NULL), _wireframe(false)
{
}

void SimpleSoccer::initialize()
{
	/*Bundle* bundle = Bundle::create("res/soccer.gpb");
	_scene = bundle->loadScene();
	SAFE_RELEASE(bundle);*/

	form = Form::create("res/ui.form");
	fpsLabel = static_cast<Label*>(form->getControl("fpsLabel"));

	/*form = Form::create("testForm", NULL);
	form->setSize(600, 600);

	Label* label = Label::create("testLabel");
	label->setPosition(50, 50);
	label->setSize(200, 50);
	label->setText("Label:");
	form->addControl(label);
	label->release();*/

    // Load game scene from file
    _scene = Scene::load("res/soccer.scene");

	Node* cameraNode = _scene->findNode("Camera");
	if (cameraNode) {
		_scene->setActiveCamera(cameraNode->getCamera());
	}
		
    

    // Get the box model and initialize its material parameter values and bindings
    /*Node* boxNode = _scene->findNode("box");
    Model* boxModel = boxNode->getModel();
    Material* boxMaterial = boxModel->getMaterial();*/

    // Set the aspect ratio for the scene's camera to match the current resolution
	Node* lightNode = Node::create("directionalLight1");
	Light* light = Light::createDirectional(Vector3(1, 0, 0));
	lightNode->setLight(light);
	_scene->addNode(lightNode);

	/*Material* material = _modelNode->getModel()->getMaterial();
	MaterialParameter* parameter = material->getParameter("u_lightDirection");
	parameter->bindValue(lightNode, &Node::getForwardVectorView);*/

	Camera* camera = _scene->getActiveCamera();
	camera->setAspectRatio(getAspectRatio());
	
	camera->getNode()->setRotation(0.3, 0.65, 0.29, -0.666);
	camera->getNode()->translateForward(-8.0f);
}

void SimpleSoccer::finalize()
{
    SAFE_RELEASE(_scene);
}

void SimpleSoccer::update(float elapsedTime)
{
    // Rotate model
    //_scene->findNode("box")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));

	std::string fps = "FPS: ";
	fps.append(std::to_string(getFrameRate()));
	fpsLabel->setText(fps.c_str());

	// UI
	form->update(elapsedTime);
}

void SimpleSoccer::render(float elapsedTime)
{
    // Clear the color and depth buffers
    clear(CLEAR_COLOR_DEPTH, Vector4(0.8, 0.8, 0.6, 1.0), 1.0f, 0);

    // Visit all the nodes in the scene for drawing
    _scene->visit(this, &SimpleSoccer::drawScene);

	// UI
	form->draw();
}

bool SimpleSoccer::drawScene(Node* node)
{
	auto pos = node->getTranslation();
	std::cout << node->getId() << " pos: " << pos.x << "," << pos.y << "," << pos.z << std::endl;
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
		case Keyboard::KEY_LEFT_ARROW:{
			auto node = _scene->getActiveCamera()->getNode();

			

			_scene->getActiveCamera()->getNode()->rotateY(node->getRotation().y + 1.0f);
			break;
		}
			
		case Keyboard::KEY_RIGHT_ARROW:{
			auto node = _scene->getActiveCamera()->getNode();
			_scene->getActiveCamera()->getNode()->rotateY(node->getRotation().y - 1.0f);
			break;
		}
			
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
