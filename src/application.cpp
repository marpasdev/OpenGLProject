/**
 * @file application.cpp
 *
 * @brief A class that manages scenes and their resources.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include <glad/gl.h>

// #include <cstdlib>
#include <cstdio>
#include <iostream>
#include <random>

#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "models/tree.h"
#include "models/sphere.h"
#include "models/bushes.h"
#include "models/plain.h"
#include "models/login.h"
#include "models/space/sun.h"
#include "models/space/earth.h"
#include "models/space/moon.h"

#include "models/clock.h"

#include "transform/transformcomposite.h"
#include "transform/transformleaf.h"

#include "transform/static/translation.h"
#include "transform/static/rotation.h"
#include "transform/static/scale.h"

#include "transform/dynamic/dynamicrotation.h"

#include "application.h"

#include <unordered_map>

void WindowDeleter::operator()(GLFWwindow* window) {
	glfwDestroyWindow(window);
}

Application::~Application() {
	scenes.clear();
	window.reset();
	glfwTerminate();
}

void Application::initializeGLFW(int width, int height) {
	if (!glfwInit())
		exit(EXIT_FAILURE);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);

	window.reset(glfwCreateWindow(width, height, "OpenGL Project", NULL, NULL));
	if (!window.get())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window.get());
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(window.get(), this);
	glfwSetKeyCallback(window.get(), keyCallback);
}

void Application::initialize(int windowWidth, int windowHeight) {
	initializeGLFW(windowWidth, windowHeight);
	
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
        std::cerr << "GLAD initialization failed\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
}

void Application::createScenes() {

	std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
	shaders["basicTransformVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/basictransform.vert");
    shaders["basicFrag"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");
	shaders["green"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/green.frag");
	shaders["lightGreen"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/lightgreen.frag");
	shaders["yellow"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/yellow.frag");
	shaders["blue"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/blue.frag");
	shaders["extendedbasic"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/extendedbasictransform.vert");
	shaders["treeVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/tree.vert");
	shaders["treeFrag"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/tree.frag");
	shaders["bushVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/bush.vert");
	shaders["skyVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/sky.vert");

	shaders["clockVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/clock.vert");
	shaders["clockFrag"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/clock.frag");

	std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> programs;
	programs["basic"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders["basicFrag"]);
	programs["green"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("green"));
	programs["lightGreen"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("lightGreen"));
	programs["yellow"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("yellow"));
	programs["blue"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("blue"));
	programs["extendedBasic"] = std::make_shared<ShaderProgram>(*shaders.at("extendedbasic"), *shaders.at("basicFrag"));
	programs["tree"] = std::make_shared<ShaderProgram>(*shaders.at("treeVert"), *shaders.at("treeFrag"));
	programs["bush"] = std::make_shared<ShaderProgram>(*shaders.at("bushVert"), *shaders.at("treeFrag"));
	programs["clock"] = std::make_shared<ShaderProgram>(*shaders.at("clockVert"), *shaders.at("clockFrag"));
	programs["sky"] = std::make_shared<ShaderProgram>(*shaders.at("skyVert"), *shaders.at("basicFrag"));

	std::vector<VertexAttribute> layout6;
	layout6.push_back({3, GL_FLOAT});
	layout6.push_back({3, GL_FLOAT});

	std::vector<VertexAttribute> layout9;
	layout9.push_back({3, GL_FLOAT});
	layout9.push_back({3, GL_FLOAT});
	layout9.push_back({3, GL_FLOAT});

    float points[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
	
	std::unordered_map<std::string, std::shared_ptr<Model>> models;
    models["triangle"] = std::make_shared<Model>(points, sizeof(points), layout6);

    float square[] = {
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };
	models["square"] = std::make_shared<Model>(square, sizeof(square), layout6);
	models["sphere"] = std::make_shared<Model>(sphere, sizeof(sphere), layout6);
	models["plain"] = std::make_shared<Model>(plain, sizeof(plain), layout6);
    models["login"] = std::make_shared<Model>(login, sizeof(login), layout6);
	models["tree"] = std::make_shared<Model>(tree, sizeof(tree), layout6);
	models["bushes"] = std::make_shared<Model>(bushes, sizeof(bushes), layout6);

	// solar system
	models["sun"] = std::make_shared<Model>(sun, sizeof(sun), layout9);
	models["earth"] = std::make_shared<Model>(earth, sizeof(earth), layout9);
	models["moon"] = std::make_shared<Model>(moon, sizeof(moon), layout9);

	models["clock"] = std::make_shared<Model>(clockModel, sizeof(clockModel), layout9);

    std::vector<std::unique_ptr<DrawableObject>> objects;

	auto signatureTransform = std::make_shared<TransformComposite>();
	signatureTransform->add(std::make_shared<Scale>(0.2f));
	signatureTransform->add(std::make_shared<Translation>(glm::vec3(0.8f, 0.9f, 0.0f)));

	// Scene 0
	auto triangleTransform = std::make_shared<TransformComposite>();
	// triangleTransform->add(std::make_shared<Translation>(glm::vec3(0.5f, 0.0f, 0.0f)));
	// triangleTransform->add(std::make_shared<DynamicRotation>(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 6.0f)));

	// opposite order of transformations:
	triangleTransform->add(std::make_shared<DynamicRotation>(glm::vec3(0.5f, 0.0f, 0.0f), glm::radians(360.0f / 6.0f)));
	triangleTransform->add(std::make_shared<Translation>(glm::vec3(0.0f, 0.5f, 0.0f)));
	objects.push_back(std::make_unique<DrawableObject>(models.at("triangle"),
								programs.at("basic"),
								triangleTransform
								));
	objects.push_back(std::make_unique<DrawableObject>(models.at("login"),
									programs.at("basic"),
									signatureTransform
								));
	scenes.push_back(Scene(std::move(objects)));

	// Scene 1 - little sphere
	objects.clear();

	auto sphereTransform = std::make_shared<TransformComposite>();
	sphereTransform->add(std::make_shared<DynamicRotation>(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 4.0f)));
	sphereTransform->add(std::make_shared<DynamicRotation>(glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(360.0f / 2.0f)));
	sphereTransform->add(std::make_shared<Scale>(0.4f));

	objects.push_back(std::make_unique<DrawableObject>(models.at("sphere"),
								programs.at("basic"),
								sphereTransform
							));
	objects.push_back(std::make_unique<DrawableObject>(models.at("login"),
									programs.at("basic"),
									signatureTransform
								));
	scenes.push_back(Scene(std::move(objects)));
	
	std::mt19937 rng{std::random_device{}()};

	std::uniform_real_distribution<float> dist(-2.0f, 2.0f);
	std::uniform_real_distribution<float> randomAngle(0.0f, 360.0f);
	std::uniform_real_distribution<float> randomShade(0.0f, 0.3f);
	std::uniform_real_distribution<float> randomScale(0.7f, 1.0f);
	
	// Scene 2
	objects.clear();
	auto skyTransform = std::make_shared<TransformComposite>();

	glm::vec3 dayColor{0.4f, 0.7f, 1.0f};
	glm::vec3 nightColor{0.01f, 0.01f, 0.06f};

	float tm = glfwGetTime();
	float cycleDuration = 600.0f;		// duration of day-night cycle in seconds
	float cycle = fmod(tm, cycleDuration) / cycleDuration;
	float cycleAngle = cycle * 360.0f;
	float anglePerSecond = 360.0f / cycleDuration;

	float daylight = (1.0f - cos(glm::radians(cycleAngle))) / 2.0f;

	glm::vec3 skyColor = glm::mix(nightColor, dayColor, daylight);

	skyTransform->add(std::make_shared<Scale>(50.0f));
	auto sky = std::make_unique<DrawableObject>(models.at("sphere"),
										programs.at("sky"),
										skyTransform
									);

	sky->setUniform("shade", skyColor);

	objects.push_back(std::move(sky));

	auto plainTransform = std::make_shared<TransformComposite>();
	plainTransform->add(std::make_shared<Scale>(glm::vec3(10.0f, 0.0f, 10.0f)));
	objects.push_back(std::make_unique<DrawableObject>(models.at("plain"),
									programs.at("lightGreen"),
									plainTransform
									));
	for (size_t i = 0; i < 74; ++i) {
		auto treeTransform = std::make_shared<TransformComposite>();
		treeTransform->add(std::make_shared<Scale>(0.06f * randomScale(rng)));
		treeTransform->add(std::make_shared<Rotation>(glm::vec3(0.0f, glm::radians(randomAngle(rng)), 0.0f)));
		treeTransform->add(std::make_shared<Translation>(glm::vec3(dist(rng), 0.0f, dist(rng))));

		auto tree = std::make_unique<DrawableObject>(models.at("tree"),
										programs.at("tree"),
										treeTransform
										);
		tree->setUniform("shade", randomShade(rng));
		objects.push_back(std::move(tree));									
	}
	for (size_t i = 0; i < 250; ++i) {
		auto bushTransform = std::make_shared<TransformComposite>();
		bushTransform->add(std::make_shared<Scale>(0.2f));
		bushTransform->add(std::make_shared<Rotation>(glm::vec3(0.0f, glm::radians(randomAngle(rng)), 0.0f)));
		bushTransform->add(std::make_shared<Translation>(glm::vec3(dist(rng), 0.0f, dist(rng))));
		objects.push_back(std::make_unique<DrawableObject>(models.at("bushes"),
										programs.at("bush"),
										bushTransform
										));
	}


	
	auto forestSunTransform = std::make_shared<TransformComposite>();
	forestSunTransform->add(std::make_shared<Scale>(1.0f));
	forestSunTransform->add(std::make_shared<Translation>(glm::vec3(0.0f, -12.0f, 12.0f)));
	forestSunTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(anglePerSecond), -1.0f));
	objects.push_back(std::make_unique<DrawableObject>(models.at("sphere"),
									 programs.at("yellow"),
									 forestSunTransform
									 ));
	auto forestMoonTransform = std::make_shared<TransformComposite>();
	forestMoonTransform->add(std::make_shared<Scale>(1.0f));
	forestMoonTransform->add(std::make_shared<Translation>(glm::vec3(0.0f, 12.0f, -12.0f)));
	forestMoonTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(anglePerSecond), 1.0f));
	objects.push_back(std::make_unique<DrawableObject>(models.at("moon"),
									 programs.at("extendedBasic"),
									 forestMoonTransform
									 ));
	objects.push_back(std::make_unique<DrawableObject>(models.at("login"),
									programs.at("basic"),
									signatureTransform
								));
	scenes.push_back(Scene(std::move(objects)));

	// Scene 3 - Login
	objects.clear();
	auto loginTransform = std::make_shared<TransformComposite>();
	loginTransform->add(std::make_shared<Scale>(0.7f));
	loginTransform->add(std::make_shared<DynamicRotation>(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 12.0f)));
	objects.push_back(std::make_unique<DrawableObject>(models.at("login"),
									programs.at("basic"),
									loginTransform
								));
	scenes.push_back(Scene(std::move(objects)));
	
	// Scene 4 - solar system
	objects.clear();
	// Sun
	auto sunTransform = std::make_shared<TransformComposite>();
	sunTransform->add(std::make_shared<Scale>(0.2f));
	auto sunSpin = std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 6.0f), false);
	sunTransform->add(sunSpin);
	objects.push_back(std::make_unique<DrawableObject>(models.at("sun"),
			programs.at("extendedBasic"),
			sunTransform
			));

	// Earth
	auto earthTransform = std::make_shared<TransformComposite>();
	earthTransform->add(std::make_shared<Scale>(0.1f));
	earthTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 4.0f), true));
	earthTransform->add(std::make_shared<Translation>(glm::vec3(0.8f, 0.0f, 0.0f)));
	auto earthOrbit = std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 36.0f), false);
	earthTransform->add(earthOrbit);
	objects.push_back(std::make_unique<DrawableObject>(models.at("earth"),
			programs.at("extendedBasic"),
			earthTransform
			));

	// Moon
	auto moonTransform = std::make_shared<TransformComposite>();
	moonTransform->add(std::make_shared<Scale>(0.05f));
	moonTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 4.0f), false));
	moonTransform->add(std::make_shared<Translation>(glm::vec3(0.2f, 0.0f, 0.0f)));
	moonTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 4.0f), true));
	moonTransform->add(std::make_shared<Translation>(glm::vec3(0.8f, 0.0f, 0.0f)));
	moonTransform->add(earthOrbit);

	objects.push_back(std::make_unique<DrawableObject>(models.at("moon"),
			programs.at("extendedBasic"),
			moonTransform
			));

	objects.push_back(std::make_unique<DrawableObject>(models.at("login"),
									programs.at("basic"),
									signatureTransform
								));
	scenes.push_back(Scene(std::move(objects)));

	objects.clear();

	// Scene 5 - Clock
	auto clockTransform = std::make_shared<TransformComposite>();
	auto clockObject = std::make_unique<DrawableObject>(models.at("clock"),
								programs.at("clock"),
								clockTransform);

	glm::ivec3 t = getTimeHMS();

	float secAngle = glm::radians(-static_cast<float>(t.z % 60 * 6));
	float minAngle = glm::radians(-static_cast<float>(t.y % 60 * 6) + glm::degrees(secAngle) / 60.0f);
	float hourAngle = glm::radians(-static_cast<float>(t.x % 12 * 30) + glm::degrees(minAngle) / 12.0f);

	clockObject->setUniform("hourRot", glm::rotate(glm::mat4(1.0f), hourAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	clockObject->setUniform("minuteRot", glm::rotate(glm::mat4(1.0f), minAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	clockObject->setUniform("secondRot", glm::rotate(glm::mat4(1.0f), secAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	// clockObject->setTransform(std::make_shared<DynamicRotation>(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 6.0f)));

	objects.push_back(std::move(clockObject));						
	objects.push_back(std::make_unique<DrawableObject>(models.at("login"),
									programs.at("basic"),
									signatureTransform
								));

	scenes.push_back(Scene(std::move(objects)));

	glm::vec3 pos(0.0f, 0.1f, 0.0f);

	cam = std::make_shared<Camera>(pos);
	for (auto& s : scenes) {
		s.setCamera(cam);
	}
}

void Application::keyCallback(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->onKey(key, action);
	}
}

void Application::onKey(int key, int action) {
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window.get(), GLFW_TRUE);
	}
	if (action == GLFW_PRESS && key >= GLFW_KEY_0 && key <= GLFW_KEY_9) {
		size_t index = key - GLFW_KEY_0;
		if (currentScene != index && index < scenes.size()) {
			currentScene = index;
		}
	}
	if (action == GLFW_PRESS && key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9) {
		size_t index = key - GLFW_KEY_KP_0;
		if (currentScene != index && index < scenes.size()) {
			currentScene = index;
		}
	}
}

void Application::run() {
	double previousTime = glfwGetTime();

	float speed = 0.5f;
	bool run = false;
	bool runMultiplier = 2.0f;


    while (!glfwWindowShouldClose(window.get())) {
		double now = glfwGetTime();
		float deltaTime = static_cast<float>(now - previousTime);
		previousTime = now;


	glm::ivec3 t = getTimeHMS();

	float secAngle = glm::radians(-static_cast<float>(t.z % 60 * 6));
	float minAngle = glm::radians(-static_cast<float>(t.y % 60 * 6) + glm::degrees(secAngle) / 60.0f);
	float hourAngle = glm::radians(-static_cast<float>(t.x % 12 * 30) + glm::degrees(minAngle) / 12.0f);

	scenes[5].getObject(0)->setUniform("hourRot", glm::rotate(glm::mat4(1.0f), hourAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	scenes[5].getObject(0)->setUniform("minuteRot", glm::rotate(glm::mat4(1.0f), minAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	scenes[5].getObject(0)->setUniform("secondRot", glm::rotate(glm::mat4(1.0f), secAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							

	glm::vec3 dayColor{0.4f, 0.7f, 1.0f};
	glm::vec3 nightColor{0.01f, 0.01f, 0.06f};

	float tm = glfwGetTime();
	float cycleDuration = 600.0f;		// duration of day-night cycle in seconds
	float cycle = fmod(tm, cycleDuration) / cycleDuration;
	float cycleAngle = cycle * 360.0f;

	float daylight = (1.0f - cos(glm::radians(cycleAngle))) / 2.0f;

	glm::vec3 skyColor = glm::mix(nightColor, dayColor, daylight);

	scenes[2].getObject(0)->setUniform("shade", skyColor);

		// handle input
	if (glfwGetKey(window.get(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		bool run = true;
	}
	if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS) {
		for (auto& s : scenes) {
			auto cam = std::make_shared<Camera>(s.getCamera()->getPosition());
			cam->moveForward((run ? runMultiplier : 1.0f) * speed * deltaTime);
			s.setCamera(cam);
		}
	}
	if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS) {
		for (auto& s : scenes) {
			auto cam = std::make_shared<Camera>(s.getCamera()->getPosition());
			cam->moveBackward((run ? runMultiplier : 1.0f) * speed * deltaTime);
			s.setCamera(cam);
		}
	}
	if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS) {
		for (auto& s : scenes) {
			auto cam = std::make_shared<Camera>(s.getCamera()->getPosition());
			cam->moveLeft((run ? runMultiplier : 1.0f) * speed * deltaTime);
			s.setCamera(cam);
		}
	}
	if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS) {
		for (auto& s : scenes) {
			auto cam = std::make_shared<Camera>(s.getCamera()->getPosition());
			cam->moveRight((run ? runMultiplier : 1.0f) * speed * deltaTime);
			s.setCamera(cam);
		}
	}
	if (glfwGetKey(window.get(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		for (auto& s : scenes) {
			auto cam = std::make_shared<Camera>(s.getCamera()->getPosition());
			cam->moveUp((run ? runMultiplier : 1.0f) * speed * deltaTime);
			s.setCamera(cam);
		}
	}
	if (glfwGetKey(window.get(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		for (auto& s : scenes) {
			auto cam = std::make_shared<Camera>(s.getCamera()->getPosition());
			cam->moveDown((run ? runMultiplier : 1.0f) * speed * deltaTime);
			s.setCamera(cam);
		}
	}

	run = false;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scenes[currentScene].update(deltaTime);
		scenes[currentScene].render();

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
}

void Application::getVersionInfo() const {
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}


glm::ivec3 Application::getTimeHMS() const {
	std::time_t t = std::time(nullptr);
	std::tm local{};
#ifdef _WIN32
	localtime_s(&local, &t);
#else
	localtime_r(&t, &local);
#endif
	return glm::ivec3(local.tm_hour, local.tm_min, local.tm_sec);
}