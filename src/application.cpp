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
#include "models/space/mercury.h"
#include "models/space/venus.h"
#include "models/space/satellite.h"

#include "models/clock.h"

#include "transform/transformcomposite.h"
#include "transform/transformleaf.h"

#include "transform/static/translation.h"
#include "transform/static/rotation.h"
#include "transform/static/scale.h"

#include "transform/dynamic/dynamicrotation.h"
#include "transform/dynamic/backandforthtranslation.h"

#include "skybox.h"

#include "application.h"

#include <unordered_map>

void WindowDeleter::operator()(GLFWwindow* window) {
	glfwDestroyWindow(window);
}

Application::Application() : camera(Camera(glm::vec3(0.0f, 0.1f, -0.5f))) {
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
	glfwSetFramebufferSizeCallback(window.get(), framebufferSizeCallback);
	glfwSetCursorPosCallback(window.get(), cursorPosCallback);
	glfwSetMouseButtonCallback(window.get(), mouseButtonCallback);
}

void Application::initialize(int windowWidth, int windowHeight) {
	initializeGLFW(windowWidth, windowHeight);
	
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
        std::cerr << "GLAD initialization failed\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
}

std::unordered_map<std::string, std::unique_ptr<Shader>> Application::createShaders() const {
	std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
	shaders["v_pvm"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/pvm.vert");
    shaders["f_basic"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");
	shaders["f_green"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/green.frag");
	shaders["f_lightgreen"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/lightgreen.frag");
	shaders["f_yellow"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/yellow.frag");
	shaders["f_blue"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/blue.frag");
	shaders["v_pvm9"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/pvm9.vert");
	shaders["v_tree"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/tree.vert");
	shaders["f_tree"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/tree.frag");
	shaders["v_bush"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/bushpvm.vert");
	shaders["v_sky"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/sky.vert");

	shaders["v_lambert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/lambert.vert");
	shaders["f_lambert"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/lambert.frag");

	shaders["v_phong"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/phong.vert");
	shaders["f_phong"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/phong.frag");

	shaders["v_phong9"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/phong9.vert");
	shaders["f_phong9"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/phong9.frag");

	shaders["v_clock"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/clock.vert");
	shaders["f_clock"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/clock.frag");

	shaders["f_blinn"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/blinn.frag");

	shaders["v_constant"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/constant.vert");
	shaders["f_constant"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/constant.frag");

	shaders["v_treephong"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/tree_phong.vert");
	shaders["f_treephong"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/tree_phong.frag");
	
	shaders["v_texture"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/texture.vert");
	shaders["f_texture"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/texture.frag");

	shaders["v_texturephong"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/texture_phong.vert");
	shaders["f_texturephong"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/texture_phong.frag");

	shaders["v_skybox"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/skybox.vert");
	shaders["f_skybox"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/skybox.frag");

	return std::move(shaders);
}

std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> Application::createPrograms(const std::unordered_map<std::string, std::unique_ptr<Shader>>& shaders) {
	std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> programs;
	programs["basic"] = std::make_unique<ShaderProgram>(*shaders.at("v_pvm"), *shaders.at("f_basic"), &camera);
	programs["green"] = std::make_unique<ShaderProgram>(*shaders.at("v_pvm"), *shaders.at("f_green"), &camera);
	programs["lightgreen"] = std::make_unique<ShaderProgram>(*shaders.at("v_pvm"), *shaders.at("f_lightgreen"), &camera);
	programs["yellow"] = std::make_unique<ShaderProgram>(*shaders.at("v_pvm"), *shaders.at("f_yellow"), &camera);
	programs["blue"] = std::make_unique<ShaderProgram>(*shaders.at("v_pvm"), *shaders.at("f_blue"), &camera);
	programs["pvm9"] = std::make_unique<ShaderProgram>(*shaders.at("v_pvm9"), *shaders.at("f_basic"), &camera);
	programs["tree"] = std::make_unique<ShaderProgram>(*shaders.at("v_tree"), *shaders.at("f_tree"), &camera);
	programs["bush"] = std::make_unique<ShaderProgram>(*shaders.at("v_bush"), *shaders.at("f_tree"), &camera);
	programs["clock"] = std::make_unique<ShaderProgram>(*shaders.at("v_clock"), *shaders.at("f_clock"), &camera);
	programs["sky"] = std::make_unique<ShaderProgram>(*shaders.at("v_sky"), *shaders.at("f_basic"), &camera);
	programs["lambert"] = std::make_unique<ShaderProgram>(*shaders.at("v_lambert"), *shaders.at("f_lambert"), &camera);
	programs["phong"] = std::make_unique<ShaderProgram>(*shaders.at("v_phong"), *shaders.at("f_phong"), &camera);
	programs["phong9"] = std::make_unique<ShaderProgram>(*shaders.at("v_phong9"), *shaders.at("f_phong9"), &camera);
	programs["blinnphong"] = std::make_unique<ShaderProgram>(*shaders.at("v_phong"), *shaders.at("f_blinn"), &camera);
	programs["constant"] = std::make_unique<ShaderProgram>(*shaders.at("v_constant"), *shaders.at("f_constant"), &camera);

	programs["treephong"] = std::make_unique<ShaderProgram>(*shaders.at("v_treephong"), *shaders.at("f_treephong"), &camera);

	programs["texture"] = std::make_unique<ShaderProgram>(*shaders.at("v_texture"), *shaders.at("f_texture"), &camera);

	programs["texturephong"] = std::make_unique<ShaderProgram>(*shaders.at("v_texturephong"), *shaders.at("f_texturephong"), &camera);
	programs["skybox"] = std::make_unique<ShaderProgram>(*shaders.at("v_skybox"), *shaders.at("f_skybox"), &camera);
	return programs;
}

void Application::createModels() {
    float points[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    models.add("triangle", points, sizeof(points));

    float square[] = {
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };
	models.add("square", square, sizeof(square));

	models.add("sphere", sphere, sizeof(sphere));
	models.add("plain", plain, sizeof(plain));
	models.add("login", login, sizeof(login));
	models.add("tree", tree, sizeof(tree));
	models.add("bush", bushes, sizeof(bushes));
	models.add("terrain", "teren.obj");

	// solar system
	models.add("sun", sun, sizeof(sun), VertexLayoutPreset::PosNorCol);
	models.add("mercury", mercury, sizeof(mercury), VertexLayoutPreset::PosNorCol);
	models.add("venus", venus, sizeof(venus), VertexLayoutPreset::PosNorCol);
	// models.add("earth", earth, sizeof(earth), VertexLayoutPreset::PosNorCol);
	models.add("moon", moon, sizeof(moon), VertexLayoutPreset::PosNorCol);
	models.add("satellite", satellite, sizeof(satellite), VertexLayoutPreset::PosNorCol);

	models.add("planet", "planet.obj");

	models.add("clock", clockModel, sizeof(clockModel), VertexLayoutPreset::PosNorCol);

	const float uvplain[] = {
    //position, normal, uv coordinate
    1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
    1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
 
   -1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
    1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
   -1.0f, 0.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f
	};
	models.add("uvplain", uvplain, sizeof(uvplain), VertexLayoutPreset::PosNorUV);

	models.add("eb408", "EB408.obj");
	models.add("eb408_door", "Door.obj");
	models.add("orange_chair", "OrangeChair.obj");
	models.add("eb408_table", "table.obj");
	models.add("whiteboard", "Whiteboard.obj");
	models.add("monitor", "monitor.obj");
	
	models.add("skybox", "skybox.obj", VertexLayoutPreset::PosNorUVW);
}

void Application::createTextures() {
	textures.add("wood", "wooden_fence.png");
	textures.add("grass", "grass.png");

	// Classroom
	textures.add("eb408", "T_EB408.png");
	textures.add("eb408_door", "T_door_basecolor.png");
	textures.add("orange_chair", "T_OrangeChair_BaseColor.png");
	textures.add("eb408_table", "T_Table_BaseColor.png");
	textures.add("whiteboard", "T_Whiteboard_Drawn_BaseColor.png");
	textures.add("monitor", "T_Monitor_BaseColor.png");

	// Space
	textures.add("sun", "sun2k.jpg");
	textures.add("mercury", "mercury8k.jpg");
	textures.add("venus", "venus2k.jpg");
	textures.add("earth", "earth8k.jpg");
	textures.add("moon", "moon2k.jpg");
	textures.add("mars", "mars2k.jpg");
	textures.add("jupiter", "jupiter2k.jpg");
	textures.add("saturn", "saturn2k.jpg");
}

std::shared_ptr<TransformComposite> createPlanetTransform(float scale, float axialTilt, float spinLengthInDays, float yearLength, float distance) {
	auto planetTransform = std::make_shared<TransformComposite>();
	planetTransform->add(std::make_shared<Scale>(glm::vec3{-scale, scale, scale}));
	planetTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3{0.0f, 1.0f, 0.0f}, glm::radians(360.0f / spinLengthInDays), true));
	planetTransform->add(std::make_shared<Rotation>(glm::vec3{glm::radians(axialTilt), 0.0f, 0.0f}));
	planetTransform->add(std::make_shared<Translation>(glm::vec3{distance, 0.0f, 0.0f}));
	planetTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3{0.0f, 1.0f, 0.0f}, glm::radians(360.0f / yearLength), false));
	return planetTransform;
}

void Application::createScenes() {
	auto shaders = createShaders();

	auto programs = createPrograms(std::move(shaders));

	objectInventory.push_back({"Tree", std::make_shared<DrawableObject>(
		models.get("tree"), programs.at("tree"), std::make_shared<Scale>(0.1f)
	)});
	objectInventory.push_back({"Chair", std::make_shared<DrawableObject>(
		models.get("orange_chair"), programs.at("texturephong"), std::make_shared<Scale>(0.2f), textures.get("orange_chair")
	)});

	skybox = std::make_optional(std::move(Skybox(programs.at("skybox"), { "cubemap/posx.jpg", "cubemap/negx.jpg",
		"cubemap/posy.jpg", "cubemap/negy.jpg", "cubemap/posz.jpg", "cubemap/negz.jpg"},
		models.get("skybox"))));

	// create scenes
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
	objects.push_back(std::make_unique<DrawableObject>(models.get("triangle"),
								programs.at("basic"),
								triangleTransform
								));
	objects.push_back(std::make_unique<DrawableObject>(models.get("login"),
									programs.at("basic"),
									signatureTransform
								));
	scenes.push_back(Scene(std::move(objects)));

	// Scene 1 - sphere 
	objects.clear();

	auto littleSphereTransform = std::make_shared<TransformComposite>();
	littleSphereTransform->add(std::make_shared<Scale>(0.2f));
	littleSphereTransform->add(std::make_shared<BackAndForthTranslation>(glm::vec3{1.0f}, glm::vec3{5.0f}, 2.0f));
	objects.push_back(std::make_unique<DrawableObject>(models.get("sphere"),
			programs.at("basic"), littleSphereTransform));

	objects.push_back(std::make_unique<DrawableObject>(models.get("login"),
									programs.at("basic"),
									signatureTransform
								));

	scenes.push_back(Scene(std::move(objects)));

	
	// Scene 2 - Forest
	objects.clear();

	std::mt19937 rng{std::random_device{}()};

	std::uniform_real_distribution<float> dist(-4.0f, 4.0f);
	std::uniform_real_distribution<float> randomAngle(0.0f, 360.0f);
	std::uniform_real_distribution<float> randomShade(0.0f, 0.3f);
	std::uniform_real_distribution<float> randomScale(0.7f, 1.0f);
	
	// auto skyTransform = std::make_shared<TransformComposite>();

	// glm::vec3 dayColor{0.4f, 0.7f, 1.0f};
	// glm::vec3 nightColor{0.01f, 0.01f, 0.06f};

	float tm = glfwGetTime();
	float cycleDuration = 600.0f;		// duration of day-night cycle in seconds
	float cycle = fmod(tm, cycleDuration) / cycleDuration;
	float cycleAngle = cycle * 360.0f;
	float anglePerSecond = 360.0f / cycleDuration;

	float daylight = (1.0f - cos(glm::radians(cycleAngle))) / 2.0f;

	// glm::vec3 skyColor = glm::mix(nightColor, dayColor, daylight);

	// skyTransform->add(std::make_shared<Scale>(50.0f));
	// auto sky = std::make_unique<DrawableObject>(models.get("sphere"),
	// 									programs.at("sky"),
	// 									skyTransform
	// 								);

	// sky->setUniform("shade", skyColor);

	// objects.push_back(std::move(sky));

	auto clockTransform1 = std::make_shared<TransformComposite>();
	clockTransform1->add(std::make_shared<Scale>(0.05f));
	clockTransform1->add(std::make_shared<Rotation>(glm::vec3(glm::radians(90.0f), 0.0f, 0.0f)));
	clockTransform1->add(std::make_shared<DynamicRotation>(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 24.0f)));
	clockTransform1->add(std::make_shared<Translation>(glm::vec3(0.4f, 0.0f, 0.29f)));
	auto clockObject1 = std::make_unique<DrawableObject>(models.get("clock"),
								programs.at("clock"),
								clockTransform1);

	glm::ivec3 t = getTimeHMS();

	float secAngle = glm::radians(-static_cast<float>(t.z % 60 * 6));
	float minAngle = glm::radians(-static_cast<float>(t.y % 60 * 6) + glm::degrees(secAngle) / 60.0f);
	float hourAngle = glm::radians(-static_cast<float>(t.x % 12 * 30) + glm::degrees(minAngle) / 12.0f);

	clockObject1->setUniform("hourRot", glm::rotate(glm::mat4(1.0f), hourAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	clockObject1->setUniform("minuteRot", glm::rotate(glm::mat4(1.0f), minAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	clockObject1->setUniform("secondRot", glm::rotate(glm::mat4(1.0f), secAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							

	objects.push_back(std::move(clockObject1));						

	auto clockTransform2 = std::make_shared<TransformComposite>();
	clockTransform2->add(std::make_shared<Translation>(glm::vec3(0.5f, 1.0f, 0.3f)));
	clockTransform2->add(std::make_shared<Rotation>(glm::vec3(0.0f, glm::radians(30.0f), 0.0f)));
	clockTransform2->add(std::make_shared<Scale>(0.05f));
	auto clockObject2 = std::make_unique<DrawableObject>(models.get("clock"),
								programs.at("clock"),
								clockTransform2);

	clockObject2->setUniform("hourRot", glm::rotate(glm::mat4(1.0f), hourAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	clockObject2->setUniform("minuteRot", glm::rotate(glm::mat4(1.0f), minAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	clockObject2->setUniform("secondRot", glm::rotate(glm::mat4(1.0f), secAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							

	objects.push_back(std::move(clockObject2));						

	// auto plainTransform = std::make_shared<TransformComposite>();
	// plainTransform->add(std::make_shared<Scale>(glm::vec3(10.0f, 0.0f, 10.0f)));
	// objects.push_back(std::make_unique<DrawableObject>(models.get("plain"),
	// 								programs.at("lightgreen"),
	// 								plainTransform
	// 								));
	auto terrainTransform = std::make_shared<TransformComposite>();
	terrainTransform->add(std::make_shared<Scale>(glm::vec3(0.1f, 0.1f, 0.1f)));
	objects.push_back(std::make_unique<DrawableObject>(models.get("terrain"),
									programs.at("texture"),
									terrainTransform,
									textures.get("grass")
									));
	for (size_t i = 0; i < 74; ++i) {
		auto treeTransform = std::make_shared<TransformComposite>();
		treeTransform->add(std::make_shared<Scale>(0.1f * randomScale(rng)));
		treeTransform->add(std::make_shared<Rotation>(glm::vec3(0.0f, glm::radians(randomAngle(rng)), 0.0f)));
		treeTransform->add(std::make_shared<Translation>(glm::vec3(dist(rng), 0.0f, dist(rng))));

		auto tree = std::make_unique<DrawableObject>(models.get("tree"),
										programs.at("tree"),
										treeTransform
										);
		tree->setUniform("shade", randomShade(rng));
		objects.push_back(std::move(tree));									
	}
	for (size_t i = 0; i < 50; ++i) {
		auto bushTransform = std::make_shared<TransformComposite>();
		bushTransform->add(std::make_shared<Scale>(0.2f));
		bushTransform->add(std::make_shared<Rotation>(glm::vec3(0.0f, glm::radians(randomAngle(rng)), 0.0f)));
		bushTransform->add(std::make_shared<Translation>(glm::vec3(dist(rng), 0.0f, dist(rng))));
		objects.push_back(std::make_unique<DrawableObject>(models.get("bush"),
										programs.at("bush"),
										bushTransform
										));
	}
	
	// auto forestSunTransform = std::make_shared<TransformComposite>();
	// forestSunTransform->add(std::make_shared<Scale>(1.0f));
	// forestSunTransform->add(std::make_shared<Translation>(glm::vec3(0.0f, -12.0f, 12.0f)));
	// forestSunTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(anglePerSecond), -1.0f));
	// objects.push_back(std::make_unique<DrawableObject>(models.get("sphere"),
	// 								 programs.at("yellow"),
	// 								 forestSunTransform
	// 								 ));
	// auto forestMoonTransform = std::make_shared<TransformComposite>();
	// forestMoonTransform->add(std::make_shared<Scale>(1.0f));
	// forestMoonTransform->add(std::make_shared<Translation>(glm::vec3(0.0f, 12.0f, -12.0f)));
	// forestMoonTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(anglePerSecond), 1.0f));
	// objects.push_back(std::make_unique<DrawableObject>(models.get("moon"),
	// 								 programs.at("pvm9"),
	// 								 forestMoonTransform
	// 								 ));
	objects.push_back(std::make_unique<DrawableObject>(models.get("login"),
									programs.at("basic"),
									signatureTransform
								));
	scenes.push_back(Scene(std::move(objects)));

	// Scene 3 - Login
	objects.clear();
	auto loginTransform = std::make_shared<TransformComposite>();
	loginTransform->add(std::make_shared<Scale>(0.7f));
	loginTransform->add(std::make_shared<DynamicRotation>(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 12.0f)));
	objects.push_back(std::make_unique<DrawableObject>(models.get("login"),
									programs.at("basic"),
									loginTransform
								));
	scenes.push_back(Scene(std::move(objects)));
	
	// Scene 4 - Solar system
	objects.clear();
	// Sun
	auto sunTransform = std::make_shared<TransformComposite>();
	sunTransform->add(std::make_shared<Scale>(0.2f));
	auto sunSpin = std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 6.0f), false);
	sunTransform->add(sunSpin);
	objects.push_back(std::make_unique<DrawableObject>(models.get("planet"),
			programs.at("texture"),
			sunTransform,
			textures.get("sun")
			));

	float baseScale = 0.1f;
	// Mercury
	auto mercuryTransform = std::make_shared<TransformComposite>();
	mercuryTransform->add(std::make_shared<Scale>(baseScale * 0.389f));
	mercuryTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3{0.0f, 1.0f, 0.0f}, glm::radians(360.0f / 4.0f), true));
	// mercuryTransform->add(std::make_shared<Rotation>(glm::vec3{glm::radians(0.0f), 0.0f, 0.0f}));	// unnecessary - axis tilt angle is near 0
	mercuryTransform->add(std::make_shared<Translation>(glm::vec3{0.7f, 0.0f, 0.0f}));
	mercuryTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3{0.0f, 1.0f, 0.0f}, glm::radians(360.0f / 115.88f), false));
	objects.push_back(std::make_unique<DrawableObject>(models.get("planet"),
			programs.at("texturephong"), mercuryTransform,
			textures.get("mercury")));
			
	// Venus
	auto venusTransform = std::make_shared<TransformComposite>();
	venusTransform->add(std::make_shared<Scale>(baseScale * 0.949f));
	venusTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3{0.0f, 1.0f, 0.0f}, glm::radians(360.0f / 4.0f), true));
	venusTransform->add(std::make_shared<Rotation>(glm::vec3{glm::radians(177.4f), 0.0f, 0.0f}));
	venusTransform->add(std::make_shared<Translation>(glm::vec3{1.3f, 0.0f, 0.0f}));
	venusTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3{0.0f, 1.0f, 0.0f}, glm::radians(360.0f / 224.7f), false));
	objects.push_back(std::make_unique<DrawableObject>(models.get("planet"),
			programs.at("texturephong"), venusTransform, textures.get("venus")));

	// Earth
	auto earthTransform = std::make_shared<TransformComposite>();
	earthTransform->add(std::make_shared<Scale>(glm::vec3{-baseScale, baseScale, baseScale}));
	earthTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 1.0f), true));
	earthTransform->add(std::make_shared<Rotation>(glm::vec3{glm::radians(23.44f), 0.0f, 0.0f}));
	earthTransform->add(std::make_shared<Translation>(glm::vec3(1.8f, 0.0f, 0.0f)));
	auto earthOrbit = std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 365.0f), false);
	earthTransform->add(earthOrbit);
	objects.push_back(std::make_unique<DrawableObject>(models.get("planet"),
			programs.at("texturephong"),
			earthTransform,
			textures.get("earth")
			));

	// Moon
	auto moonTransform = std::make_shared<TransformComposite>();
	moonTransform->add(std::make_shared<Scale>(baseScale * 0.273f));
	moonTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 4.0f), false));
	moonTransform->add(std::make_shared<Translation>(glm::vec3(0.2f, 0.0f, 0.0f)));
	moonTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 28.0f), true));
	moonTransform->add(std::make_shared<Translation>(glm::vec3(1.8f, 0.0f, 0.0f)));
	moonTransform->add(earthOrbit);

	objects.push_back(std::make_unique<DrawableObject>(models.get("planet"),
			programs.at("texturephong"),
			moonTransform,
			textures.get("moon")
			));

	auto satelliteTransform = std::make_shared<TransformComposite>();
	satelliteTransform->add(std::make_shared<Scale>(0.07f));
	satelliteTransform->add(std::make_shared<Rotation>(glm::vec3{glm::radians(0.0f), 0.0f, glm::radians(90.0f)}));
	satelliteTransform->add(std::make_shared<Translation>(glm::vec3{2.1f, 0.0f, 0.0f}));
	satelliteTransform->add(std::make_shared<DynamicRotation>(glm::vec3{0.0f, 1.0f, 0.0f}, glm::radians(360.0f / 72.0f)));

	objects.push_back(std::make_unique<DrawableObject>(models.get("satellite"),
			programs.at("phong9"),
			satelliteTransform
			));

	auto marsTransform = std::make_shared<TransformComposite>();
	marsTransform->add(std::make_shared<Scale>(glm::vec3{-baseScale, baseScale, baseScale} * 0.532f));
	marsTransform->add(std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 1.0f), true));
	marsTransform->add(std::make_shared<Rotation>(glm::vec3{glm::radians(25.19f), 0.0f, 0.0f}));
	marsTransform->add(std::make_shared<Translation>(glm::vec3(2.74f, 0.0f, 0.0f)));
	auto marsOrbit = std::make_shared<DynamicRotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 687.0f), false);
	marsTransform->add(marsOrbit);
	objects.push_back(std::make_unique<DrawableObject>(models.get("planet"),
			programs.at("texturephong"),
			marsTransform,
			textures.get("mars")
			));

	objects.push_back(std::make_unique<DrawableObject>(models.get("planet"),
			programs.at("texturephong"),
			createPlanetTransform(baseScale * 11.21f, glm::radians(3.13f), 10.0f / 24.0f, 11.86 * 365.0f, 9.37f),
			textures.get("jupiter")
			));

	objects.push_back(std::make_unique<DrawableObject>(models.get("planet"),
			programs.at("texturephong"),
			createPlanetTransform(baseScale * 9.45, glm::radians(26.73f), 10.5f / 24.0f, 29.46 * 365.0f, 17.17f),
			textures.get("saturn")
			));

	objects.push_back(std::make_unique<DrawableObject>(models.get("login"),
									programs.at("basic"),
									signatureTransform
								));

	auto spaceSkybox = std::make_optional(std::make_shared<Skybox>(programs.at("skybox"), 
	std::array<std::string, 6>{"milkyway2k.jpg", "milkyway2k.jpg", "stars2k.jpg",
		"stars2k.jpg", "milkyway2k.jpg", "milkyway2k.jpg"}, models.get("skybox")));

	scenes.push_back(Scene(std::move(objects), spaceSkybox));

	objects.clear();

	// Scene 5 - Clock
	auto clockTransform = std::make_shared<TransformComposite>();
	auto clockObject = std::make_unique<DrawableObject>(models.get("clock"),
								programs.at("clock"),
								clockTransform);

	clockObject->setUniform("hourRot", glm::rotate(glm::mat4(1.0f), hourAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	clockObject->setUniform("minuteRot", glm::rotate(glm::mat4(1.0f), minAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	clockObject->setUniform("secondRot", glm::rotate(glm::mat4(1.0f), secAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	// clockObject->setTransform(std::make_shared<DynamicRotation>(glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(360.0f / 6.0f)));

	objects.push_back(std::move(clockObject));						
	objects.push_back(std::make_unique<DrawableObject>(models.get("login"),
									programs.at("basic"),
									signatureTransform
								));

	scenes.push_back(Scene(std::move(objects)));

	// Scene 6 - spheres with lighting
	objects.clear();

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			std::string program = "";
			if (i == 0) {
				if (j == 0) {
					program = "phong";
				} else {
					program = "constant";
				}
			} else if (i == 1) {
				if (j == 0) {
					program = "blinnphong";
				} else {
					program = "lambert";
				}
			}
			auto sphereTransform = std::make_shared<TransformComposite>();
			sphereTransform->add(std::make_shared<Scale>(0.3f));
			sphereTransform->add(std::make_shared<Translation>(glm::vec3(-0.5f + i * 1.0f, - 0.5f + j * 1.0f, 0.0f)));
			objects.push_back(std::make_unique<DrawableObject>(models.get("sphere"),
										programs.at(program),
										sphereTransform
									));
		}
	}

	objects.push_back(std::make_unique<DrawableObject>(models.get("login"),
									programs.at("basic"),
									signatureTransform
								));
	scenes.push_back(Scene(std::move(objects)));

	// Scene 7 - Classroom
	objects.clear();

	auto ebtransform = std::make_shared<TransformComposite>();
	ebtransform->add(std::make_shared<Scale>(glm::vec3{-0.2f, 0.2f, 0.2f}));

	objects.push_back(std::make_unique<DrawableObject>(models.get("eb408"),
				programs.at("texturephong"),
				ebtransform, std::make_optional(textures.get("eb408"))));

	auto doortransform = std::make_shared<TransformComposite>();
	doortransform->add(std::make_shared<Scale>(glm::vec3{0.2f, 0.2f, 0.2f}));
	// doortransform->add(std::make_shared<Rotation>(glm::vec3{0.0f, glm::radians(5.0f), 0.0f}));
	doortransform->add(std::make_shared<Translation>(glm::vec3{0.7f, 0.0f, 1.55f}));

	objects.push_back(std::make_unique<DrawableObject>(models.get("eb408_door"),
				programs.at("texturephong"),
				doortransform, std::make_optional(textures.get("eb408_door"))));

	auto whiteboardTransform = std::make_shared<TransformComposite>();
	whiteboardTransform->add(std::make_shared<Scale>(glm::vec3{0.2f, 0.2f, -0.2f}));
	whiteboardTransform->add(std::make_shared<Rotation>(glm::vec3{0.0f, glm::radians(180.0f), 0.0f}));
	whiteboardTransform->add(std::make_shared<Translation>(glm::vec3{0.76f, 0.0f, 0.7f}));

	for (int tableX = -1; tableX < 2; ++tableX) {
		for (int tableZ = 0; tableZ < 3; ++tableZ) {
			auto tableTransform = std::make_shared<TransformComposite>();
			tableTransform->add(std::make_shared<Scale>(glm::vec3{0.2f, 0.2f, 0.2f}));
			tableTransform->add(std::make_shared<Rotation>(glm::vec3{0.0f, glm::radians(-90.0f), 0.0f}));
			tableTransform->add(std::make_shared<Translation>(glm::vec3{tableX * 0.37f - 0.1f, 0.0f, tableZ * 0.37f + 0.3f}));

			objects.push_back(std::make_unique<DrawableObject>(models.get("eb408_table"),
				programs.at("texturephong"),
				tableTransform, std::make_optional(textures.get("eb408_table"))));
		}
	}
	auto tableTransform = std::make_shared<TransformComposite>();
	tableTransform->add(std::make_shared<Scale>(glm::vec3{0.2f, 0.2f, 0.2f}));
	tableTransform->add(std::make_shared<Rotation>(glm::vec3{0.0f, glm::radians(90.0f), 0.0f}));
	tableTransform->add(std::make_shared<Translation>(glm::vec3{1 * 0.37f + 0.09f, 0.0f, 0 * 0.37f + 0.3f}));
	objects.push_back(std::make_unique<DrawableObject>(models.get("eb408_table"),
		programs.at("texturephong"),
		tableTransform, std::make_optional(textures.get("eb408_table"))));

	for (int chairX = -1; chairX < 2; ++chairX) {
		for (int chairZ = 0; chairZ < 6; ++chairZ) {
			auto chairTransform = std::make_shared<TransformComposite>();
			chairTransform->add(std::make_shared<Scale>(glm::vec3{0.2f, 0.2f, 0.2f}));
			chairTransform->add(std::make_shared<Rotation>(glm::vec3{0.0f, glm::radians(90.0f), 0.0f}));
			chairTransform->add(std::make_shared<Translation>(glm::vec3{chairX * 0.37f - 0.20f, 0.0f, chairZ * 0.185f + 0.205f}));

			objects.push_back(std::make_unique<DrawableObject>(models.get("orange_chair"),
				programs.at("texturephong"),
				chairTransform, std::make_optional(textures.get("orange_chair"))));

		}
	}
	auto chairTransform = std::make_shared<TransformComposite>();
	chairTransform->add(std::make_shared<Scale>(glm::vec3{0.2f, 0.2f, 0.2f}));
	chairTransform->add(std::make_shared<Rotation>(glm::vec3{0.0f, glm::radians(-90.0f), 0.0f}));
	chairTransform->add(std::make_shared<Translation>(glm::vec3{1 * 0.37f + 0.20f, 0.0f, 0 * 0.185f + 0.205f}));

	objects.push_back(std::make_unique<DrawableObject>(models.get("orange_chair"),
		programs.at("texturephong"),
		chairTransform, std::make_optional(textures.get("orange_chair"))));

	for (int monX = -1; monX < 2; ++monX) {
		for (int monZ = 0; monZ < 6; ++monZ) {
			auto monTransform = std::make_shared<TransformComposite>();
			monTransform->add(std::make_shared<Scale>(glm::vec3{-0.1f, 0.1f, 0.1f}));
			monTransform->add(std::make_shared<Rotation>(glm::vec3{0.0f, glm::radians(0.0f), 0.0f}));
			monTransform->add(std::make_shared<Translation>(glm::vec3{monX * 0.37f - 0.05f, 0.13f, monZ * 0.185f + 0.205f}));

			objects.push_back(std::make_unique<DrawableObject>(models.get("monitor"),
				programs.at("texturephong"),
				monTransform, std::make_optional(textures.get("monitor"))));

		}
	}
	auto monTransform = std::make_shared<TransformComposite>();
	monTransform->add(std::make_shared<Scale>(glm::vec3{-0.1f, 0.1f, 0.1f}));
	monTransform->add(std::make_shared<Rotation>(glm::vec3{0.0f, glm::radians(180.0f), 0.0f}));
	monTransform->add(std::make_shared<Translation>(glm::vec3{1 * 0.37f + 0.05f, 0.13f, 0 * 0.185f + 0.205f}));

	objects.push_back(std::make_unique<DrawableObject>(models.get("monitor"),
		programs.at("texturephong"),
		monTransform, std::make_optional(textures.get("monitor"))));

	objects.push_back(std::make_unique<DrawableObject>(models.get("whiteboard"),
				programs.at("texturephong"),
				whiteboardTransform, std::make_optional(textures.get("whiteboard"))));

	objects.push_back(std::make_unique<DrawableObject>(models.get("login"),
									programs.at("basic"),
									signatureTransform
								));

	scenes.push_back(Scene(std::move(objects)));

}

void Application::keyCallback(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->onKey(key, action);
	}
}

std::string modeToString(InteractionMode mode) {
	if (mode == InteractionMode::PlaceMode) {
		return "Place mode";
	}
	if (mode == InteractionMode::InteractMode) {
		return "Interaction mode";
	}
	if (mode == InteractionMode::DeleteMode) {
		return "Delete mode";
	}
	return "";
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
	if (action == GLFW_RELEASE && key == GLFW_KEY_UP) {
		int newMode = static_cast<int>(intmode) + 1;
		if (newMode >= 3) { newMode = 0; }
		this->intmode = static_cast<InteractionMode>(newMode);
		std::cout << "Current mode: " << modeToString(intmode) << "\n";
	}
	if (action == GLFW_RELEASE && key == GLFW_KEY_DOWN) {
		int newMode = static_cast<int>(intmode) - 1;
		if (newMode < 0) { newMode = 2; }
		this->intmode = static_cast<InteractionMode>(newMode);
		std::cout << "Current mode: " << modeToString(intmode) << "\n";
	}
	if (action == GLFW_RELEASE && key == GLFW_KEY_RIGHT) {
		++selectedObject;
		if (selectedObject >= objectInventory.size()) { selectedObject = 0; }
		std::cout << "Current object: " << objectInventory.at(selectedObject).first << "\n";
	}
	if (action == GLFW_RELEASE && key == GLFW_KEY_LEFT) {
		--selectedObject;
		if (selectedObject < 0) { selectedObject = objectInventory.size() - 1; }
		std::cout << "Current object: " << objectInventory.at(selectedObject).first << "\n";
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
	for (size_t i = 0; i <= 1; ++i) {
		scenes[2].getObject(i)->setUniform("hourRot", glm::rotate(glm::mat4(1.0f), hourAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
		scenes[2].getObject(i)->setUniform("minuteRot", glm::rotate(glm::mat4(1.0f), minAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
		scenes[2].getObject(i)->setUniform("secondRot", glm::rotate(glm::mat4(1.0f), secAngle, glm::vec3(0.0f, 0.0f, 1.0f)));							
	}

	// glm::vec3 dayColor{0.4f, 0.7f, 1.0f};
	// glm::vec3 nightColor{0.01f, 0.01f, 0.06f};

	// float tm = glfwGetTime();
	// float cycleDuration = 600.0f;		// duration of day-night cycle in seconds
	// float cycle = fmod(tm, cycleDuration) / cycleDuration;
	// float cycleAngle = cycle * 360.0f;

	// float daylight = (1.0f - cos(glm::radians(cycleAngle))) / 2.0f;

	// glm::vec3 skyColor = glm::mix(nightColor, dayColor, daylight);

	// scenes[2].getObject(0)->setUniform("shade", skyColor);

		// handle input
	if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS) {
		camera.moveForward((run ? runMultiplier : 1.0f) * speed * deltaTime);
	}
	if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS) {
		camera.moveBackward((run ? runMultiplier : 1.0f) * speed * deltaTime);
	}
	if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS) {
		camera.moveLeft((run ? runMultiplier : 1.0f) * speed * deltaTime);
	}
	if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS) {
		camera.moveRight((run ? runMultiplier : 1.0f) * speed * deltaTime);
	}
	if (glfwGetKey(window.get(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.moveUp((run ? runMultiplier : 1.0f) * speed * deltaTime);
	}
	if (glfwGetKey(window.get(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		camera.moveDown((run ? runMultiplier : 1.0f) * speed * deltaTime);
	}

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (currentScene == 7 
			|| currentScene == 2
		) {
			if (skybox.has_value()) {
				skybox->draw();
			}
		}

		scenes[currentScene].drawSkybox();

		scenes[currentScene].update(deltaTime);
		scenes[currentScene].render();

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
}

void Application::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->onResize(width, height);
	}
}

void Application::onResize(int width, int height) {
	if (width == 0 || height == 0) { return; }

	camera.setResolution(glm::vec2{static_cast<float>(width), static_cast<float>(height)});

	glViewport(0, 0, width, height);
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	camera.setProjection(glm::perspective(glm::radians(60.0f), aspectRatio, 0.1f, 100.0f));
}

void Application::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->onMouseButton(button, action);
	}
}

void Application::onMouseButton(int button, int action) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			rotating = true;
			glfwGetCursorPos(window.get(), &lastX, &lastY);
		} else if (action == GLFW_RELEASE) {
			rotating = false;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			glfwGetCursorPos(window.get(), &lastX, &lastY);
			GLbyte color[4];
			GLfloat depth;
			GLuint index;

			float xscale, yscale;
			int wwidth, wheight;

			glfwGetWindowSize(window.get(), &wwidth, &wheight);

			glfwGetWindowContentScale(window.get(), &xscale, &yscale);

			GLint x = (GLint)lastX;
			GLint y = (GLint)lastY;

			int newy = camera.getResolution().y - 1 - y;

			glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
			glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
			glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
			
			if (intmode == InteractionMode::InteractMode) {
				printf("Clicked on pixel %d, %d, color %02hhx%02hhx%02hhx%02hhx, depth %f, stencil index %u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
			}

			glm::vec3 screenX = glm::vec3(x, newy, depth);
			glm::mat4 view = camera.getView();
			glm::mat4 projection = camera.getProjection();
			glm::vec4 viewPort = glm::vec4(0, 0, camera.getResolution().x, camera.getResolution().y);
			glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);
			
			if (intmode == InteractionMode::InteractMode) {
				printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);
			}

			if (placeStart == std::nullopt) {
				placeStart = std::make_optional(glm::vec3{pos.x, pos.y, pos.z});
			}

			if (intmode == InteractionMode::DeleteMode) {
				scenes[currentScene].removeObject(index);
				std::cout << "Deleted \'" << objectInventory.at(selectedObject).first << "\' on coordinates [" << pos.x << ", " << pos.y << 
					", " << pos.z << "]\n";
			}

		} else if (action == GLFW_RELEASE) {
			glfwGetCursorPos(window.get(), &lastX, &lastY);
			GLfloat depth;

			float xscale, yscale;
			int wwidth, wheight;

			glfwGetWindowSize(window.get(), &wwidth, &wheight);

			glfwGetWindowContentScale(window.get(), &xscale, &yscale);

			GLint x = (GLint)lastX;
			GLint y = (GLint)lastY;

			int newy = camera.getResolution().y - 1 - y;

			glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

			glm::vec3 screenX = glm::vec3(x, newy, depth);
			glm::mat4 view = camera.getView();
			glm::mat4 projection = camera.getProjection();
			glm::vec4 viewPort = glm::vec4(0, 0, camera.getResolution().x, camera.getResolution().y);
			glm::vec3 pos = glm::unProject(screenX, view, projection, viewPort);
			
			// printf("unProject [%f,%f,%f]\n", pos.x, pos.y, pos.z);

			if (intmode == InteractionMode::PlaceMode) {
				auto placeEnd = glm::vec3{pos.x, pos.y, pos.z};

				auto obj = std::make_shared<DrawableObject>(*(objectInventory.at(selectedObject).second));

				auto placedTransform = std::make_shared<TransformComposite>();
				placedTransform->add(obj->getTransform());
				
				if (placeStart.has_value()) {
					if (glm::length(placeEnd - placeStart.value()) > 0.10f) {
						placedTransform->add(std::make_shared<BackAndForthTranslation>(placeStart.value(), placeEnd, 1.0f));
					} else {
						placedTransform->add(std::make_shared<Translation>(placeEnd));
					}
				} else {
					placedTransform->add(std::make_shared<Translation>(placeEnd));
				}
					
					obj->setTransform(placedTransform);
					scenes[currentScene].addObject(*obj);

				placeStart = std::nullopt;

				auto placePos = placeStart.has_value() ? placeStart.value() : placeEnd;
				std::cout << "Placed \'" << objectInventory.at(selectedObject).first << "\' on coordinates [" << placePos.x << ", " << placePos.y << 
					", " << placePos.z << "]\n";
			}
		}
	}
}

void Application::cursorPosCallback(GLFWwindow* window, double x, double y) {
	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->onMouseMove(x, y);
	}
}

void Application::onMouseMove(double x, double y) {
	if (rotating) {
		float dx = static_cast<float>(x - lastX);
		float dy = static_cast<float>(y - lastY);
		lastX = x;
		lastY = y;

		camera.rotate(dx * mouseSensitivity, -dy * mouseSensitivity);
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