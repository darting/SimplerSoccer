#include "SimpleSoccer.h"

// Declare our game instance
SimpleSoccer game;
Form* form;
Label* fpsLabel;

SoccerPitch* _soccerPitch;

int pitchSale = 50;
int pitchWidth = 14;
int pitchHeight = 8;
Node* _ball;

SimpleSoccer::SimpleSoccer()
	: _scene(NULL), _wireframe(false) {
}

void SimpleSoccer::initialize() {
	/*Bundle* bundle = Bundle::create("res/soccer.gpb");
	_scene = bundle->loadScene();
	SAFE_RELEASE(bundle);*/

	Properties* properties = Properties::create("res/soccer.config");
	Prm.GoalWidth = properties->getFloat("GoalWidth");
	Prm.NumSupportSpotsX = properties->getInt("NumSupportSpotsX");
	Prm.NumSupportSpotsY = properties->getInt("NumSupportSpotsY");

	Prm.Spot_PassSafeScore = properties->getFloat("Spot_PassSafeScore");
	Prm.Spot_CanScoreFromPositionScore = properties->getFloat("Spot_CanScoreFromPositionScore");
	Prm.Spot_DistFromControllingPlayerScore = properties->getFloat("Spot_DistFromControllingPlayerScore");
	Prm.Spot_ClosenessToSupportingPlayerScore = properties->getFloat("Spot_ClosenessToSupportingPlayerScore");
	Prm.Spot_AheadOfAttackerScore = properties->getFloat("Spot_AheadOfAttackerScore");

	Prm.SupportSpotUpdateFreq = properties->getFloat("SupportSpotUpdateFreq");

	Prm.ChancePlayerAttemptsPotShot = properties->getFloat("ChancePlayerAttemptsPotShot");
	Prm.ChanceOfUsingArriveTypeReceiveBehavior = properties->getFloat("ChanceOfUsingArriveTypeReceiveBehavior");

	Prm.BallSize = properties->getFloat("BallSize");
	Prm.BallMass = properties->getFloat("BallMass");
	Prm.Friction = properties->getFloat("Friction");

	Prm.KeeperInBallRange = properties->getFloat("KeeperInBallRange");
	Prm.PlayerInTargetRange = properties->getFloat("PlayerInTargetRange");
	Prm.PlayerKickingDistance = properties->getFloat("PlayerKickingDistance");
	Prm.PlayerKickFrequency = properties->getFloat("PlayerKickFrequency");

	Prm.PlayerMass = properties->getFloat("PlayerMass");
	Prm.PlayerMaxForce = properties->getFloat("PlayerMaxForce");
	Prm.PlayerMaxSpeedWithBall = properties->getFloat("PlayerMaxSpeedWithBall");
	Prm.PlayerMaxSpeedWithoutBall = properties->getFloat("PlayerMaxSpeedWithoutBall");
	Prm.PlayerMaxTurnRate = properties->getFloat("PlayerMaxTurnRate");
	Prm.PlayerScale = properties->getFloat("PlayerScale");
	Prm.PlayerComfortZone = properties->getFloat("PlayerComfortZone");
	Prm.PlayerKickingAccuracy = properties->getFloat("PlayerKickingAccuracy");

	Prm.NumAttemptsToFindValidStrike = properties->getInt("NumAttemptsToFindValidStrike");

	Prm.MaxDribbleForce = properties->getFloat("MaxDribbleForce");
	Prm.MaxShootingForce = properties->getFloat("MaxShootingForce");
	Prm.MaxPassingForce = properties->getFloat("MaxPassingForce");

	Prm.WithinRangeOfHome = properties->getFloat("WithinRangeOfHome");
	Prm.WithinRangeOfSupportSpot = properties->getFloat("WithinRangeOfSupportSpot");

	Prm.MinPassDist = properties->getFloat("MinPassDist");
	Prm.GoalkeeperMinPassDist = properties->getFloat("GoalkeeperMinPassDist");

	Prm.GoalKeeperTendingDistance = properties->getFloat("GoalKeeperTendingDistance");
	Prm.GoalKeeperInterceptRange = properties->getFloat("GoalKeeperInterceptRange");
	Prm.BallWithinReceivingRange = properties->getFloat("BallWithinReceivingRange");

	Prm.bStates = properties->getBool("ViewStates");
	Prm.bIDs = properties->getBool("ViewIDs");
	Prm.bSupportSpots = properties->getBool("ViewSupportSpots");
	Prm.bRegions = properties->getBool("ViewRegions");
	Prm.bShowControllingTeam = properties->getBool("bShowControllingTeam");
	Prm.bViewTargets = properties->getBool("ViewTargets");
	Prm.bHighlightIfThreatened = properties->getBool("HighlightIfThreatened");

	Prm.FrameRate = properties->getInt("FrameRate");

	Prm.SeparationCoefficient = properties->getFloat("SeparationCoefficient");
	Prm.ViewDistance = properties->getFloat("ViewDistance");
	Prm.bNonPenetrationConstraint = properties->getBool("bNonPenetrationConstraint");

	Prm.BallWithinReceivingRangeSq = Prm.BallWithinReceivingRange * Prm.BallWithinReceivingRange;
	Prm.KeeperInBallRangeSq = Prm.KeeperInBallRange * Prm.KeeperInBallRange;
	Prm.PlayerInTargetRangeSq = Prm.PlayerInTargetRange * Prm.PlayerInTargetRange;
	Prm.PlayerKickingDistance += Prm.BallSize;
	Prm.PlayerKickingDistanceSq = Prm.PlayerKickingDistance * Prm.PlayerKickingDistance;
	Prm.PlayerComfortZoneSq = Prm.PlayerComfortZone * Prm.PlayerComfortZone;
	Prm.GoalKeeperInterceptRangeSq = Prm.GoalKeeperInterceptRange * Prm.GoalKeeperInterceptRange;
	Prm.WithinRangeOfSupportSpotSq = Prm.WithinRangeOfSupportSpot * Prm.WithinRangeOfSupportSpot;



	form = Form::create("res/ui.form");
	fpsLabel = static_cast<Label*>(form->getControl("fpsLabel"));

	_soccerPitch = new SoccerPitch(pitchWidth * pitchSale, pitchHeight * pitchSale);


	// Load game scene from file
	_scene = Scene::load("res/soccer.scene");

	Node* player = _scene->findNode("player");
	setupTeamMembers(_soccerPitch->m_pRedTeam, player);
	player->rotateZ(MATH_DEG_TO_RAD(180.0f));
	setupTeamMembers(_soccerPitch->m_pBlueTeam, player);
	_scene->removeNode(player);

	_ball = _scene->findNode("Platonic");

	Node* cameraNode = _scene->findNode("Camera");
	if (cameraNode) {
		_scene->setActiveCamera(cameraNode->getCamera());
	}
	Camera* camera = _scene->getActiveCamera();
	camera->setAspectRatio(getAspectRatio());

	// Get the box model and initialize its material parameter values and bindings
	/*Node* boxNode = _scene->findNode("box");
	Model* boxModel = boxNode->getModel();
	Material* boxMaterial = boxModel->getMaterial();*/

	// Set the aspect ratio for the scene's camera to match the current resolution
	/*Node* lightNode = Node::create("directionalLight1");
	Light* light = Light::createDirectional(Vector3(1, 0, 0));
	lightNode->setLight(light);
	_scene->addNode(lightNode);*/

	/*Material* material = _modelNode->getModel()->getMaterial();
	MaterialParameter* parameter = material->getParameter("u_lightDirection");
	parameter->bindValue(lightNode, &Node::getForwardVectorView);*/

	cameraNode->setTranslation(Vector3{ 15.0f, 10.0f, 0.0f });

	Matrix matrix;
	Matrix::createLookAt(cameraNode->getTranslation(), Vector3::zero(), Vector3::unitY(), &matrix);
	matrix.transpose();

	Quaternion rotation;
	matrix.getRotation(&rotation);
	cameraNode->setRotation(rotation);
}

void SimpleSoccer::setupTeamMembers(SoccerTeam* team, Node* player) {
	auto members = team->Members();
	for (auto &member : members) {
		auto id = member->ID();
		auto memberNode = player->clone();
		memberNode->setId(("MEMBER" + std::to_string(id)).c_str());
		_scene->addNode(memberNode);
	}
}

void SimpleSoccer::updateTeamMembers(SoccerTeam* team) {
	auto members = team->Members();
	for (auto &member : members) {
		auto id = member->ID();
		auto node = _scene->findNode(("MEMBER" + std::to_string(id)).c_str());
		simulateToWorld(node, member->Pos());
	}
}

void SimpleSoccer::simulateToWorld(Node* worldNode, Vector2D simulatePos) {
	worldNode->setTranslation(simulatePos.y / pitchSale - pitchHeight / 2, 0, simulatePos.x / pitchSale - pitchWidth / 2);
}

void SimpleSoccer::finalize() {
	SAFE_RELEASE(_scene);
}

void SimpleSoccer::update(float elapsedTime) {
	// Rotate model
	//_scene->findNode("Camera")->rotateY(MATH_DEG_TO_RAD((float)elapsedTime / 1000.0f * 180.0f));
	//_scene->findNode("Camera")->translateForward(-1.0f);

	_soccerPitch->Update();

	auto ball = _soccerPitch->Ball();
	simulateToWorld(_ball, ball->Pos());

	updateTeamMembers(_soccerPitch->m_pRedTeam);
	updateTeamMembers(_soccerPitch->m_pBlueTeam);

	std::string fps = "FPS: ";
	fps.append(std::to_string(getFrameRate()));
	fpsLabel->setText(fps.c_str());

	// UI
	form->update(elapsedTime);
}

void SimpleSoccer::render(float elapsedTime) {
	// Clear the color and depth buffers
	clear(CLEAR_COLOR_DEPTH, Vector4(0.8, 0.8, 0.6, 1.0), 1.0f, 0);

	// Visit all the nodes in the scene for drawing
	_scene->visit(this, &SimpleSoccer::drawScene);

	// UI
	form->draw();
}

bool SimpleSoccer::drawScene(Node* node) {
	//auto pos = node->getTranslation();
	//std::cout << node->getId() << " pos: " << pos.x << "," << pos.y << "," << pos.z << std::endl;
	// If the node visited contains a model, draw it
	Model* model = node->getModel();
	if (model) {
		model->draw(_wireframe);
	}
	return true;
}

void SimpleSoccer::keyEvent(Keyboard::KeyEvent evt, int key) {
	if (evt == Keyboard::KEY_PRESS) {
		switch (key) {
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

void SimpleSoccer::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex) {
	switch (evt) {
	case Touch::TOUCH_PRESS:
		_wireframe = !_wireframe;
		break;
	case Touch::TOUCH_RELEASE:
		break;
	case Touch::TOUCH_MOVE:
		break;
	};
}
