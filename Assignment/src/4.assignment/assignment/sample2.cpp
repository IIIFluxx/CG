/* Author: Bharath Sukesh - 19982634
 * References: Sample2 code was used as a foundation/base for this program's code. 
 * Texture References are included in /Assignment/resources/References.txt
 * Also mentioned at the end of my Report (located in the main folder directory)
 * All header files, some functions were sourced from 
 * LearnOpenGL: https://learnopengl.com/ by Joey de Vries.
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>

#include <iostream>
#include <string>
// For randomised coords
#include <stdlib.h>
#include <time.h>

#include <learnopengl/camera.h> // From LearnOpenGL.

#define PI 3.14159265
 
// Box coordinate with 36 vertices.
// Every 3 coordinates will form 1 triangle.
// The last 2 columns represent texture coordinate for mapping.
float box[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);
unsigned int loadTexture(char const * path);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void restart();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera
glm::vec3 camera_pos   = glm::vec3(0.0f, 0.9f,  3.0f);
// We would change this ^^ to change the Spawn. 

Camera camera(camera_pos);

// lighting
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool ORTHO = false;
int ORTHO_DELAY = 0;
bool DAYTIME = false;
int DAYTIME_DELAY = 0;
int RESTART_DELAY = 0;

// timing
float delta_time = 0.0f;	// time between current frame and last frame
float last_frame = 0.0f;

// Object settings/variables
glm::vec3 wolf_global_pos(-13.0f, 0.4f, -15.0f);
glm::vec3 wolf_curpos(0.0f, 0.0f, 0.0f);
float angle;

float angleLeg = 0.0f;
float transLeg = 1.5f;

glm::vec3 portal_curpos(0.0f, 0.0f, 0.0f);
glm::vec3 portal_global_pos(6.0f, 0.0f, -10.0f);

glm::vec3 tree_curpos(0.0f, 0.0f, 0.0f);
glm::vec3 tree_global_positions[50];

glm::vec3 totem_curpos(0.0f, 0.0f, 0.0f);
glm::vec3 spec_totem_temppos(0.0f, 0.0f, 0.0f);

glm::vec3 barrier_curpos(0.0f, 0.0f, 0.0f);
glm::vec3 barrier_global_pos(6.0f, 0.0f, -10.0f);

// Light
glm::vec3 torch_global_pos(5.0f, 0.0f, 6.0f);
glm::vec3 light_pos(5.0f, 0.0f, 6.0f);

glm::vec3 torch_curpos(0.0f, 0.0f, 0.0f);
glm::vec3 lamp_pos(5.0f, 0.15f, 6.0f);



//=======

int atnI = 6; 
// From LearnOpenGL.com -- Lighting Casters // Section: Attenuation.
const float lin[12] = {
	0.0014f,
	0.007f,
	0.014f,
	0.022f,
	0.027f,
	0.045f,
	0.07f,
	0.09f,
	0.14f,
	0.22f,
	0.35f,
	0.7f
	};
const float quad[12] = {
	0.000007f,
	0.0002f,
	0.0007f,
	0.0019f,
	0.0028f,
	0.0075f,
	0.017f,
	0.032f,
	0.07f,
	0.20f,
	0.44f,
	1.8f
	};


//=======
// Torch variables
bool TORCH_PRESSED = true; // Torch is on. Change this to change light intensity.
int TORCH_DELAY = 0; 
bool TORCH_CLOSE_ENOUGH = false; // Torch is close enough
bool TORCH_PICKED_UP = false; // Torch picked up

// Proximity variables
bool PORTAL_CLOSE_ENOUGH = false; // Portal is close enough
bool TOTEM_CLOSE_ENOUGH = false; // Totem is close enough
bool TOTEM_FOUND = false;
int TOTEM_DELAY = 0;
bool LAUNCH_BARRIER = false;


bool DEAD = false;
bool WON = false;
bool DEAD_CAM = false;


bool SHOW_COORDINATE = false;
int SHOW_DELAY = 0;


// Countdown until the button trigger can be pressed again.
// This prevents accidental burst repeat clicking of the key.
void update_delay()
{
	if(SHOW_DELAY > 0) SHOW_DELAY -= 1;
	if(TORCH_DELAY > 0) TORCH_DELAY -= 1;
	if(DAYTIME_DELAY > 0) DAYTIME_DELAY -= 1;	
	if(ORTHO_DELAY > 0) ORTHO_DELAY -= 1;	
	if(TOTEM_DELAY > 0) TOTEM_DELAY -= 1;	
	if(RESTART_DELAY > 0) RESTART_DELAY -= 1;
}

// Toggle torch pick up only if the camera is close enough.
void toggle_torch_distance(glm::vec3 torch_pos)
{
	if(glm::length(camera.Position - torch_pos) <= 1.6f)
		TORCH_CLOSE_ENOUGH = true;
	else
		TORCH_CLOSE_ENOUGH = false;
}

// Toggle portal interaction (allows game finish) only if the camera is close enough.
void toggle_portal_distance(glm::vec3 portal_pos)
{
	if(glm::length(camera.Position - portal_pos) <= 4.5f)
		PORTAL_CLOSE_ENOUGH = true;
	else
		PORTAL_CLOSE_ENOUGH = false;
}

// Toggle totem pick up only if the camera is close enough.
void toggle_totem_distance(glm::vec3 totem_pos)
{
	if(glm::length(camera.Position - totem_pos) <= 1.6f)
		TOTEM_CLOSE_ENOUGH = true;
	else
		TOTEM_CLOSE_ENOUGH = false;
}

void toggle_impact(glm::vec3 camera_pos)
{
	//If too close to Wolf, game over - you die
	if(glm::length(camera_pos - wolf_global_pos) <= 1.6f && !WON)
	{
		DEAD = true;
	}
	else
	{
		DEAD = false;
	}
}

void toggle_game_won(glm::vec3 portal_pos)
{
	//&& TOTEM_FOUND == true
	if((glm::length(camera.Position - portal_pos) <= 1.6f) && TOTEM_FOUND)
		WON = true;
	//else
		//WON = false;
}



int main()
{
	// Set random seed
	srand(time(NULL));
	// X & Z -- make random
	float randX = 0, randZ = 0;
	randX = rand() % 20;
	randZ = rand() % 20;
	
	// New addition for trees
	float treeX = 0, treeZ = 0;
	
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement for OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Jumpscare inc?", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader lighting_shader("./sample2.vs", "./sample2.fs");
	Shader lamp_shader("./lamp.vs", "./lamp.fs");
	
	// tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------

	unsigned int VBO_box, VAO_box;

	glGenVertexArrays(1, &VAO_box);
	glGenBuffers(1, &VBO_box);

	glBindVertexArray(VAO_box);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);

	//vertex coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//normal vectors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int VAO_light;
	glGenVertexArrays(1, &VAO_light);
	glBindVertexArray(VAO_light);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_box);
	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);





	// load and create a texture 
	// -------------------------
	unsigned int tex_wood_diffuse, tex_street_diffuse, tex_grass_diffuse, tex_marble_diffuse, tex_curtin_diffuse;
	unsigned int tex_wood_specular, tex_street_specular, tex_grass_specular, tex_marble_specular, tex_curtin_specular;

	unsigned int tex_red_dark_diffuse, tex_red_bright_diffuse, tex_red_diffuse, tex_green_diffuse, tex_blue_diffuse;
	unsigned int tex_red_dark_specular, tex_red_bright_specular, tex_red_specular, tex_green_specular, tex_blue_specular;
	unsigned int tex_night_sky_diffuse, tex_night_sky_specular;
	
	tex_wood_diffuse = loadTexture(FileSystem::getPath("resources/textures/wood2.jpg").c_str());
	tex_wood_specular = loadTexture(FileSystem::getPath("resources/textures/wood2_specular.jpg").c_str());
	tex_street_diffuse = loadTexture(FileSystem::getPath("resources/textures/street.png").c_str());
	tex_street_specular = loadTexture(FileSystem::getPath("resources/textures/street_specular.png").c_str());
	tex_grass_diffuse = loadTexture(FileSystem::getPath("resources/textures/grass.jpg").c_str());
	tex_grass_specular = loadTexture(FileSystem::getPath("resources/textures/grass_specular.jpg").c_str());
	tex_marble_diffuse = loadTexture(FileSystem::getPath("resources/textures/marble.jpg").c_str());
	tex_marble_specular = loadTexture(FileSystem::getPath("resources/textures/marble_specular.jpg").c_str());
	tex_curtin_diffuse = loadTexture(FileSystem::getPath("resources/textures/curtin.jpg").c_str());
	tex_curtin_specular = loadTexture(FileSystem::getPath("resources/textures/curtin_specular.jpg").c_str());

	tex_red_dark_diffuse = loadTexture(FileSystem::getPath("resources/textures/red_dark.jpg").c_str());
	tex_red_dark_specular = loadTexture(FileSystem::getPath("resources/textures/red_dark_specular.jpg").c_str());
	tex_red_bright_diffuse = loadTexture(FileSystem::getPath("resources/textures/red_bright.jpg").c_str());
	tex_red_bright_specular = loadTexture(FileSystem::getPath("resources/textures/red_bright_specular.jpg").c_str());
	tex_red_diffuse = loadTexture(FileSystem::getPath("resources/textures/red.jpg").c_str());
	tex_red_specular = loadTexture(FileSystem::getPath("resources/textures/red_specular.jpg").c_str());
	tex_green_diffuse = loadTexture(FileSystem::getPath("resources/textures/green.jpg").c_str());
	tex_green_specular = loadTexture(FileSystem::getPath("resources/textures/green_specular.jpg").c_str());
	tex_blue_diffuse = loadTexture(FileSystem::getPath("resources/textures/blue.jpg").c_str());
	tex_blue_specular = loadTexture(FileSystem::getPath("resources/textures/blue_specular.jpg").c_str());
	tex_night_sky_diffuse = loadTexture(FileSystem::getPath("resources/textures/night_sky.jpg").c_str());
	tex_night_sky_specular = loadTexture(FileSystem::getPath("resources/textures/night_sky_specular.jpg").c_str());

	unsigned int tex_wolf_diffuse, tex_darkgrass_diffuse, tex_fur_diffuse, tex_wood3_diffuse, tex_leaf_diffuse, tex_tree_diffuse;
	unsigned int tex_portal_diffuse, tex_obsidian_diffuse, tex_totem_diffuse, tex_plastic_diffuse, tex_restart, tex_win;
	
	tex_wolf_diffuse = loadTexture(FileSystem::getPath("resources/textures/wolf.png").c_str());
	tex_darkgrass_diffuse = loadTexture(FileSystem::getPath("resources/textures/darkgrass.png").c_str());
	tex_fur_diffuse = loadTexture(FileSystem::getPath("resources/textures/fur.png").c_str());
	tex_wood3_diffuse = loadTexture(FileSystem::getPath("resources/textures/wood3.png").c_str());
	
	tex_tree_diffuse = loadTexture(FileSystem::getPath("resources/textures/tree.jpg").c_str());
	tex_leaf_diffuse = loadTexture(FileSystem::getPath("resources/textures/leaf.png").c_str());	
	tex_portal_diffuse = loadTexture(FileSystem::getPath("resources/textures/portal.png").c_str());
	tex_obsidian_diffuse = loadTexture(FileSystem::getPath("resources/textures/obsidian.png").c_str());
	
	tex_totem_diffuse = loadTexture(FileSystem::getPath("resources/textures/totem.png").c_str());
	tex_plastic_diffuse = loadTexture(FileSystem::getPath("resources/textures/plastic.jpg").c_str());
	tex_restart =  loadTexture(FileSystem::getPath("resources/textures/restart.png").c_str());
	tex_win =  loadTexture(FileSystem::getPath("resources/textures/win.png").c_str());
	
	
	//shader configuration -------------------------------------------------------------------------------------------
	lighting_shader.use();
	lighting_shader.setInt("material.diffuse", 0);
	lighting_shader.setInt("material.specular", 1);

	// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	// -----------------------------------------------------------------------------------------------------------




	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;

		//update delay countdown
		update_delay();

		// input
		// -----
		process_input(window);

		// render
		// ------
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		
		
		glm::mat4 projection;
		
		if(ORTHO)
		{
			projection = glm::ortho(-10.0f, 10.0f, 0.0f, 10.0f, -30.0f, 300.0f); // Values obtained from Lecture Slides
		}
		else
		{
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f); // Default - from Sample 2 Code
		}		
		
		// activate shader
		lighting_shader.use();
		lighting_shader.setMat4("projection", projection);
		// light properties
		if(DAYTIME || WON || DEAD) // TODO or escaped/won.
		{
			lighting_shader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
			lighting_shader.setFloat("light.linear", lin[12]);
	        lighting_shader.setFloat("light.quadratic", quad[12]);
		}
		else
		{
			lighting_shader.setVec3("light.ambient", 0.4f, 0.4f, 0.4f);
			lighting_shader.setFloat("light.linear", lin[atnI]); //Chosen linear value 
			lighting_shader.setFloat("light.quadratic", quad[atnI]); //Chosen quadratic value 
		}
		
		lighting_shader.setVec3("light.diffuse", 2.5f, 2.5f, 2.5f);
		lighting_shader.setVec3("light.specular", 0.5f, 0.5f, 0.5f);
		lamp_shader.setFloat("intensity", 1.5f); // Changed from 1 -- testing.
		
		if(TORCH_PICKED_UP)
		{
			lighting_shader.setVec3("light.position", torch_global_pos + glm::vec3(0.0f, 0.4f, 0.0f));
		}
		else
		{
			lighting_shader.setVec3("light.position", light_pos);
		}
		
		// Spotlight
		lighting_shader.setVec3("light.direction", camera.Front);
        lighting_shader.setFloat("light.cutOff", glm::cos(glm::radians(6.5f)));
        lighting_shader.setFloat("light.outerCutOff", glm::cos(glm::radians(9.5f)));
		
		lighting_shader.setVec3("viewPos", camera.Position);
		

		// material properties
		lighting_shader.setFloat("material.shininess", 65.0f);
		// for now just set the same for every object. But, you can make it dynamic for various objects.

		lighting_shader.setFloat("light.constant", 1.0f); //Lighting constant 
		
		

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();		
		lighting_shader.setMat4("view", view);
		
		//declare transformation matrix
		glm::mat4 model = glm::mat4();

		


		//Draw objects
		//------------------------------------------------------------------------------------------
						
		if(DEAD == true)
		{
			if(!DEAD_CAM)
			{
				camera.Pitch = 89.0f;
				camera.Yaw = 89.0f;
				camera.Position.y = 0.5;
			}
			
			// Game over - you lose. 
			
			glBindVertexArray(VAO_box);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_restart);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_restart);


			model = glm::mat4();
			// + glm::vec3( 0.0f, 0.2f, 0.0f)
			model = glm::translate(model, camera.Position + camera.Front + glm::vec3(0,1,0)); // Put above Death Cam
			model = glm::rotate(model, glm::radians(-270.0f), glm::vec3(0,0,1));
			//model = glm::translate(model, glm::vec3( 0.0f, 0.0f, 0.05f)); // Position
			
			model = glm::scale(model, glm::vec3( 0.25f, 0.30f, 0.15f)); // Scale			

			//model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f)); // World Space


			lighting_shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		
		//Sky
		glBindVertexArray(VAO_box);//This does not have to binded every time after first call, but just for consistency.
	
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_night_sky_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_night_sky_specular);

		model = glm::mat4();
		model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));

		lighting_shader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// Walls
		glm::vec3 wall_scales[] = {
            glm::vec3(100.0f, 1.50f, 0.10f),
			glm::vec3(100.0f, 1.50f, 0.10f),
			glm::vec3(0.10f, 1.50f, 100.0f),
			glm::vec3(0.10f, 1.50f, 100.0f),
        };
		
		glm::vec3 wall_positions[] = {
            glm::vec3(0.0f, 0.0f, 50.0f), // Front
			glm::vec3(0.0f, 0.0f, -50.0f), // Back
			glm::vec3(-50.0f, 0.0f, 0.0f), // Left
			glm::vec3(50.0f, 0.0f, 0.0f), // Right
        };
		
		for(int tab = 0; tab < 4; tab++)
		{
			glBindVertexArray(VAO_box);
		
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_wood3_diffuse);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_night_sky_specular);


			model = glm::mat4();
			model = glm::translate(model, glm::vec3(0,0,0));
			model = glm::translate(model, wall_positions[tab]);
			model = glm::scale(model, wall_scales[tab]);

			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));


			lighting_shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		

		//Coordinate System
		if(SHOW_COORDINATE == true)
		{
			
			glm::vec3 coord_scales[] = {
				glm::vec3( 100.0f,  0.02f,  0.02f),	//X
				glm::vec3( 0.02f,  100.0f,  0.02f),	//Y
				glm::vec3( 0.02f,  0.02f,  100.0f),	//Z
			};

			glBindVertexArray(VAO_box);

			
			
			for(int tab = 0; tab < 3; tab++)
			{	
				if(tab == 0) // X
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_red_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_red_specular);
				}
				if(tab == 1) // Y
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_green_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_green_specular);
				}
				if(tab == 2) // Z
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_blue_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_blue_specular);
				}

				model = glm::mat4();
				model = glm::scale(model, coord_scales[tab]);

				lighting_shader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}


		//Grass
		glBindVertexArray(VAO_box);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_darkgrass_diffuse);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex_grass_specular);

		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 0.00f, 0.0f)); 
		model = glm::scale(model, glm::vec3(100.0f, 0.0f, 100.0f)); // Floor is 50 x 50, made of grass texture.tex_darkgrass

		lighting_shader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// =================
		// =================
		
		// Object #1: Torch
		
		
        glm::vec3 torch_scales[] = {
            glm::vec3( 0.05f, 0.15f, 0.05f ), // handle
            glm::vec3( 0.05f, 0.05f, 0.05f), // top
			glm::vec3( 0.07f, 0.025f, 0.07f), // bevel below light
			glm::vec3( 0.07f, 0.025f, 0.07f), // bevel at bottom
			glm::vec3( 0.01f, 0.075f, 0.01f), // Side bevel #1
			glm::vec3( 0.01f, 0.075f, 0.01f), // Side bevel #2
			glm::vec3( 0.01f, 0.075f, 0.01f), // Side bevel #3
			glm::vec3( 0.01f, 0.075f, 0.01f), // Side bevel #4
        };
		
		glm::vec3 torch_positions[] = {
            glm::vec3(torch_curpos.x, torch_curpos.y, torch_curpos.z), // handle
            glm::vec3(torch_curpos.x, torch_curpos.y + 0.15f, torch_curpos.z ), // top
			glm::vec3(torch_curpos.x, torch_curpos.y + 0.10f, torch_curpos.z ), // bevel below light
			glm::vec3(torch_curpos.x, torch_curpos.y, torch_curpos.z ), // bevel at bottom
			glm::vec3(torch_curpos.x, torch_curpos.y + 0.025f, torch_curpos.z + 0.025f),
			glm::vec3(torch_curpos.x, torch_curpos.y + 0.025f, torch_curpos.z - 0.025f),
			glm::vec3(torch_curpos.x + 0.025f, torch_curpos.y + 0.025f, torch_curpos.z),
			glm::vec3(torch_curpos.x - 0.025f, torch_curpos.y + 0.025f, torch_curpos.z),
        };
		
		toggle_torch_distance(torch_global_pos);
		
		for(int tab = 0; tab < 8; tab++)
		{
			glBindVertexArray(VAO_box);
			
			// If top
			if(tab == 1)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_red_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_red_bright_specular);
			}
			else if(tab == 4 || tab == 5 || tab == 6 || tab == 7 || tab == 8)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_marble_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_marble_specular);
			}
			else // If handle
			{
				glActiveTexture(GL_TEXTURE0);
		        glBindTexture(GL_TEXTURE_2D, tex_wood3_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_red_bright_specular);
			}
			
			model = glm::mat4();

			
			if(TORCH_PICKED_UP == true && !DEAD) // If torch has been picked up
			{
				torch_global_pos = camera.Position + camera.Front;
				
				//std::cout << "Position X: " << torch_global_pos.x << "\t";
				//std::cout << "Position Z: " << torch_global_pos.z << "\n";		
			}
			
			/*if(TORCH_PICKED_UP && DEAD)
			{
				torch_global_pos.y -= 0.5f;
			}*/
			
			model = glm::translate(model, torch_global_pos);
			model = glm::translate(model, torch_positions[tab]);
			model = glm::scale(model, torch_scales[tab]);

			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));


			lighting_shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
				
		// =================
		// =================

		// Object #2: Tree
		
		glm::vec3 tree_positions[] = {
            glm::vec3(tree_curpos.x, tree_curpos.y, tree_curpos.z), // Trunk
            glm::vec3(tree_curpos.x, tree_curpos.y+2.75, tree_curpos.z), // Leaves
        };
		
		glm::vec3 tree_scales[] = {
            glm::vec3( 0.65f, 2.75f, 0.65f ), // Trunk
            glm::vec3( 2.95f, 2.5f, 2.95f), // Leaves
        };
		
		// World Space positions of our Trees
		/*glm::vec3 tree_global_positions[] = {
			glm::vec3(-4.0f, 0.0f, 8.0f), // X:-2  || Z: 4
			glm::vec3(4.0f, 0.0f, 8.0f), // X:2    || Z: 4
			glm::vec3(-8.0f, 0.0f, 14.0f), // X:-4  || Z: 7
			glm::vec3(-10.0f, 0.0f, 8.0f), // X:-8  || Z: 4
			glm::vec3(8.0f, 0.0f, 12.0f), // X: 4 || Z: 6 			
			glm::vec3(20.0f, 0.0f, 20.0f),
			glm::vec3(10.0f, 0.0f, 4.0f),
			glm::vec3(3.0f, 0.0f, -6.0f),
			glm::vec3(6.5f, 0.0f, 5.0f),
			glm::vec3(12.0f, 0.0f, -5.0f),
			glm::vec3(19.0f, 0.0f, 15.0f),
			glm::vec3(2.0f, 0.0f, -2.0f),
			glm::vec3(-8.0f, 0.0f, 4.0f),
			glm::vec3(-12.0f, 0.0f, 12.0f),
		};*/
			srand(1);
		
			for(int ii=0;ii<50;ii++)
			{
				treeX = rand() % 30;
				treeZ = rand() % 30;
				tree_global_positions[ii] = glm::vec3(treeX, 0.0f, treeZ); // X:-2  || Z: 4		
			}
		
		
		// =======
		glBindVertexArray(VAO_box);
		
        for(int ii=0; ii< 50; ii++) // Positions loop
        { 
				
			for(int tab = 0; tab < 2; tab++)
			{
				//glBindVertexArray(VAO_box);
			
				// If leaves
				if(tab == 1)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_leaf_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_red_dark_specular);
				}
				else // If trunk
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_tree_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_red_dark_specular);
				}
				model = glm::mat4();			
				model = glm::translate(model, tree_global_positions[ii]);
				model = glm::translate(model, tree_positions[tab]);
				model = glm::scale(model, tree_scales[tab]);
				model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

				lighting_shader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}		
		// =================
		// =================
		
		// Object #3: Portal
		
			
		// When X, Y = Global position aka no changes --> Bottom of the Portal = Middle of the Portal.
		// We also need: Top, Right, Left, Bottom
		
		// Perspective: Camera facing the Portal. Left side of Portal coord = on our Right side.
		
		glm::vec3 portal_positions[] = {
			glm::vec3(portal_curpos.x, portal_curpos.y + 0.2, portal_curpos.z), // Portal
			glm::vec3(portal_curpos.x, portal_curpos.y, portal_curpos.z), // Bottom
            glm::vec3(portal_curpos.x, portal_curpos.y + 1.5f, portal_curpos.z), // Top
			glm::vec3(portal_curpos.x - 0.5f, portal_curpos.y + 0.2, portal_curpos.z), // Right - change in X
			glm::vec3(portal_curpos.x + 0.5f, portal_curpos.y + 0.2, portal_curpos.z), // Left - change in X
        };
		
		glm::vec3 portal_scales[] = {
            glm::vec3(0.7f, 1.3f, 0.5f), // Portal
            glm::vec3(0.7f, 0.2f, 0.5f), // Bottom - same scales as Top
			glm::vec3(0.7f, 0.35f, 0.5f), // Top - same scales as Bottom
            glm::vec3(0.3f, 1.3f, 0.5f), // Right - same scales as Left
			glm::vec3(0.3f, 1.3f, 0.5f), // Left - same scales as Right
        };
		
		toggle_portal_distance(portal_global_pos);
		toggle_game_won(portal_global_pos);
		
		glBindVertexArray(VAO_box);
		
		for(int tab = 0; tab < 5; tab++)
		{
			// If Portal (middle)
			//TODO: Task check here
			if(tab == 0)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_portal_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
			}
			else // if portal parts
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_obsidian_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
			}
			model = glm::mat4();			
			model = glm::translate(model, portal_global_pos);
			model = glm::translate(model, portal_positions[tab]);
			model = glm::scale(model, portal_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lighting_shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);					
		}
		
		// =================
		// =================
		// Object #4: Barrier
			glm::vec3 barrier_positions[] = {
				glm::vec3(barrier_curpos.x, barrier_curpos.y, barrier_curpos.z + 0.4f), // Front
				glm::vec3(barrier_curpos.x, barrier_curpos.y, barrier_curpos.z - 0.4f), // Back
				glm::vec3(barrier_curpos.x - 0.7f, barrier_curpos.y, barrier_curpos.z), // Left
				glm::vec3(barrier_curpos.x + 0.7f, barrier_curpos.y, barrier_curpos.z), // Right
				glm::vec3(barrier_curpos.x, barrier_curpos.y + 3.0f, barrier_curpos.z), // Top Layer I
				glm::vec3(barrier_curpos.x, barrier_curpos.y + 3.2f, barrier_curpos.z), // Top Layer II
				glm::vec3(barrier_curpos.x, barrier_curpos.y + 3.5f, barrier_curpos.z), // Top Layer II
			 };  
		
			glm::vec3 barrier_scales[] = {
				glm::vec3(1.3f, 3.0f, 0.2f), // Front
				glm::vec3(1.3f, 3.0f, 0.2f), // Back
				glm::vec3(0.1f, 3.0f, 1.0f), // Left
				glm::vec3(0.1f, 3.0f, 1.0f), // Right
				glm::vec3(2.0f, 0.2f, 2.0f), // Top Layer I
				glm::vec3(1.5f, 0.3f, 1.5f), // Top Layer II
				glm::vec3(0.75f, 0.4f, 0.75f), // Top Layer II
			};
				//std::cout << "Position X: " << camera.Position.x << "\t";
				//std::cout << "Position Z: " << camera.Position.z << "\n";
		
			glBindVertexArray(VAO_box);
		
			for(int tab = 0; tab < 7; tab++)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_obsidian_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
				model = glm::mat4();			
				
				if(LAUNCH_BARRIER == true)
				{
					barrier_global_pos.y += delta_time * 0.25f;
				}
								
				model = glm::translate(model, barrier_global_pos);
				model = glm::translate(model, barrier_positions[tab]);
				model = glm::scale(model, barrier_scales[tab]);
				model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

				lighting_shader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);					
			}
		
		
		// =================
		// =================
		
		// Object #5: Totem - Decoration
		// totem_curpos
		glm::vec3 totem_positions[] = {
            glm::vec3(totem_curpos.x, totem_curpos.y, totem_curpos.z), // Bottom/Body
            glm::vec3(totem_curpos.x, totem_curpos.y + 0.3f, totem_curpos.z), // Head
			glm::vec3(totem_curpos.x, totem_curpos.y + 0.2f, totem_curpos.z - 0.1f), // Wings
			glm::vec3(totem_curpos.x, totem_curpos.y + 0.3f, totem_curpos.z + 0.01f), // Face
        };
		
		// Leave y alone
		glm::vec3 totem_scales[] = {
            glm::vec3(0.15f, 0.3f, 0.15f), // Bottom/Body
            glm::vec3(0.15f, 0.15, 0.2f), // Head
			glm::vec3(0.35f, 0.1f, 0.1f), // Wings
			glm::vec3(0.14f, 0.13, 0.2f), // Face
        };
		
		
		// World Space positions of our Totems
		glm::vec3 totem_global_positions[] = {
			glm::vec3(-2.0f, 0.0f, 6.0f), // X:-2  || Z: 4
			glm::vec3(-4.0f, 0.0f, 9.0f), // X:-4  || Z: 7
			glm::vec3(-8.0f, 0.0f, 6.0f), // X:-8  || Z: 4
		};
		

		
		for(int ii=0; ii<3; ii++) 
		{
			for(int tab = 0; tab < 4; tab++)
			{
				glBindVertexArray(VAO_box);

				// If Face
				if(tab == 3)
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_totem_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
				}
				else if(tab == 2) // Wings
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_plastic_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
				}
				else // Bottom/Body
				{
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, tex_plastic_diffuse);
					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
				}

				model = glm::mat4();
				
				model = glm::translate(model, totem_global_positions[ii]);
				model = glm::translate(model, totem_positions[tab]);
				model = glm::scale(model, totem_scales[tab]);
				model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

				lighting_shader.setMat4("model", model);

				glDrawArrays(GL_TRIANGLES, 0, 36);

			}
		}
		
		
		// Object #6: Special Totem - Collectable 
		
			glm::vec3 spec_totem_positions[] = {
            glm::vec3(totem_curpos.x, totem_curpos.y, totem_curpos.z), // Bottom/Body
            glm::vec3(totem_curpos.x, totem_curpos.y + 0.3f, totem_curpos.z), // Head
			glm::vec3(totem_curpos.x, totem_curpos.y + 0.2f, totem_curpos.z - 0.1f), // Wings
			glm::vec3(totem_curpos.x, totem_curpos.y + 0.3f, totem_curpos.z + 0.01f), // Face
        };
		
		// Leave y alone
		glm::vec3 spec_totem_scales[] = {
            glm::vec3(0.15f, 0.3f, 0.15f), // Bottom/Body
            glm::vec3(0.15f, 0.15, 0.2f), // Head
			glm::vec3(0.35f, 0.1f, 0.1f), // Wings
			glm::vec3(0.14f, 0.13, 0.2f), // Face
        };
		
		
		
		
		glm::vec3 spec_totem_global_position = {
			glm::vec3(randX, 0.0f, randZ), // X:-2  || Z: 4		
		};
		
		spec_totem_temppos = spec_totem_global_position;
		
		toggle_totem_distance(spec_totem_global_position);
		
		for(int tab = 0; tab < 4; tab++)
		{
			glBindVertexArray(VAO_box);

			// If Face
			if(tab == 3)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_totem_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
			}
			else if(tab == 2) // Wings
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_red_dark_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
			}
			else // Bottom/Body
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_red_dark_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_grass_specular);
			}

			model = glm::mat4();
			
			
						
			if(TOTEM_FOUND == true && !DEAD) // If torch has been picked up
			{
				spec_totem_global_position = camera.Position + camera.Front + glm::vec3(0.0f, -0.7f, 0.0f);
			}
			
			
			model = glm::translate(model, spec_totem_global_position);
			model = glm::translate(model, spec_totem_positions[tab]);
			model = glm::scale(model, spec_totem_scales[tab]);
			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));

			lighting_shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		
		
		
		
		
		if(TOTEM_FOUND == true)
		{
			LAUNCH_BARRIER = true;
		}
		else
		{
			LAUNCH_BARRIER = false;
		}
		
		// =================
		// =================	
		// Object #7: Wolf
		
		// Perspective: Camera facing the Wolf. Left ear = on our Right side.
		
		glm::vec3 wolf_positions[] = {
            glm::vec3(wolf_curpos.x, wolf_curpos.y, wolf_curpos.z), // Centre of mass / Center of Body @ 0, 0, 0
            glm::vec3(wolf_curpos.x, wolf_curpos.y + 0.01f, wolf_curpos.z + 0.25f), // Head - Elongate FROM the body
            glm::vec3(wolf_curpos.x - 0.08f, wolf_curpos.y + 0.15f, wolf_curpos.z + 0.3f), // Right Ear - same Y, Z, different X
            glm::vec3(wolf_curpos.x + 0.08f, wolf_curpos.y + 0.15f, wolf_curpos.z + 0.3f),  // Left Ear - same Y, Z, different X

            glm::vec3(wolf_curpos.x - 0.08f, wolf_curpos.y - 0.25f, wolf_curpos.z + 0.2f), // Front right leg
			glm::vec3(wolf_curpos.x + 0.08f, wolf_curpos.y - 0.25f, wolf_curpos.z + 0.2f), // Front left leg
			glm::vec3(wolf_curpos.x - 0.08f, wolf_curpos.y - 0.25f, wolf_curpos.z - 0.2f), // Rear right leg
			glm::vec3(wolf_curpos.x + 0.08f, wolf_curpos.y - 0.25f, wolf_curpos.z - 0.2f), // Rear left leg

			glm::vec3(wolf_curpos.x, wolf_curpos.y - 0.05f, wolf_curpos.z - 0.25f), // Tail
			glm::vec3(wolf_curpos.x, wolf_curpos.y + 0.01f, wolf_curpos.z + 0.25f), // Face
        };
		
		glm::vec3 wolf_scales[] = {
            glm::vec3(0.3f, 0.27f, 0.5f), // Centre of mass / Center of Body
            glm::vec3(0.2f, 0.2f, 0.23f), // Head
            glm::vec3(0.05f, 0.1f, 0.05f), // Right Ear
            glm::vec3(0.05f, 0.1f, 0.05f),  // Left Ear
            glm::vec3(0.08f, 0.2f, 0.08f), // Front right leg
			glm::vec3(0.08f, 0.2f, 0.08f), // Front left leg
			glm::vec3(0.08f, 0.2f, 0.08f), // Rear right leg
			glm::vec3(0.08f, 0.2f, 0.08f), // Rear left leg
			glm::vec3(0.05f, 0.05f, 0.25f), // Tail
			glm::vec3(0.19f, 0.18f, 0.25f), // Face
        };
				
		
		for(int tab = 0; tab < 10; tab++) // 10 because 10 vectors
		{	
			
			glBindVertexArray(VAO_box);
			
			if(tab != 9) // If not face -- all other parts
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tex_fur_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_red_bright_specular);
			}
			else // If Head.
			{
				glActiveTexture(GL_TEXTURE0);
		        glBindTexture(GL_TEXTURE_2D, tex_wolf_diffuse);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tex_red_bright_specular);
			}			
			
			model = glm::mat4();
			// === Make wolf follow Camera
			
			//if(TOTEM_FOUND == true && !WON)
			if(!WON)
			{
				if (camera.Position.x < wolf_global_pos.x) 
				{
					wolf_global_pos.x -= 0.004f;
				}
				else
				{
					wolf_global_pos.x += 0.004f;
				}

				if (camera.Position.z < wolf_global_pos.z)
				{
					wolf_global_pos.z -= 0.004f;
				}
				else
				{
					wolf_global_pos.z += 0.004f;
				}				
			}
			
			
			// ====
			model = glm::translate(model, wolf_global_pos); // Put it in our World Space specific to a coord.
			// Make wolfy face camera using Trig.
			float xDistance = camera.Position.x - wolf_global_pos.x;
			float zDistance = camera.Position.z - wolf_global_pos.z;
			angle = atan2(xDistance,zDistance);
			
			model = glm::rotate(model, angle, glm::vec3(0,1,0));
			// ===
			model = glm::translate(model, wolf_positions[tab]); // Place his parts in the right place
			// ===
			// Make legs rotate
			if(tab == 4 || tab == 5)
			{
				// 	angleLeg = 0.0f; transLeg = 1.5f;			
				if(angleLeg >= 40.0f)
				{
			        transLeg = -1.5f;
				}
		        else if(angleLeg <= -40.0f)
				{
			        transLeg = 1.5f;
				}

		        angleLeg += transLeg;
			    
                model = glm::rotate(model, glm::radians(angleLeg), glm::vec3(1.0f,0.0f,0.0f));	
			}
			
			// ===
			model = glm::scale(model, wolf_scales[tab]); // Scale his parts appropriately.
			toggle_impact(camera.Position);
			lighting_shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		// =================
		// =================
		
		
		if(WON == true)
		{
			// Game over - you win. 
			
			glBindVertexArray(VAO_box);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tex_win);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tex_win);


			model = glm::mat4();
			
			model = glm::translate(model, portal_global_pos + glm::vec3( 0.0f, 0.9f, -3.0f)); // Put at Camera Front
			
			model = glm::translate(model, glm::vec3( 0.0f, 0.0f, 0.05f)); // Position
			
			model = glm::scale(model, glm::vec3( 0.50f, 0.30f, 0.15f)); // Scale		

			model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f)); // World Space


			lighting_shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		
		
		// =================
		
		// Draw cube
		
		lamp_shader.use();
		lamp_shader.setMat4("projection", projection);
		lamp_shader.setMat4("view", view);
		model = glm::mat4();
		model = glm::translate(model, light_pos);
		
		if(TORCH_PICKED_UP == true && !DEAD)
		{
			light_pos = camera.Position + camera.Front;
			model = glm::mat4();
			model = glm::translate(model, light_pos);
		}
		
		model = glm::scale(model, glm::vec3(0.02f, 0.0f, 0.02f));
		lamp_shader.setMat4("model", model);
		
		glBindVertexArray(VAO_light);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		
		// =================


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_box);
	glDeleteBuffers(1, &VBO_box);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void process_input(GLFWwindow *window)
{
    	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, true);

	// WASD
	if(!DEAD)
	{		
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, delta_time);
		
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, delta_time);
		
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, delta_time);
		
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, delta_time);
	}
	
	// Limit player area
	if(camera.Position.z < -50.0f)
	{
		camera.Position -= glm::vec3(0.0f, 0.0f, -1.0f);
	}
	
	if(camera.Position.z > 50.0f)
	{
		camera.Position -= glm::vec3(0.0f, 0.0f, 1.0f);
	}
	
	if(camera.Position.x < -50.0f)
	{
		camera.Position -= glm::vec3(-1.0f, 0.0f, 0.0f);
	}
	
	if(camera.Position.x > 50.0f)
	{
		camera.Position -= glm::vec3(1.0f, 0.0f, 0.0f);
	}
	
	
	//Pick up torch, but only if close enough (F)
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && TORCH_CLOSE_ENOUGH == true)
	{
		TORCH_DELAY = 20;
		glm::vec3 torchPos = glm::vec3(torch_global_pos.x, torch_global_pos.y, torch_global_pos.z);
		
		if (glm::length(camera.Position - torchPos) < 1.5f && !TORCH_PICKED_UP)
		{
			TORCH_PICKED_UP = true;
		}
		// If you want to drop the Torch:
		/*else
		{
			TORCH_PICKED_UP = false;
		}*/
    	}
		
	//Increase Torch Attenuation Index (Dimmer) (K)
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) 
	{		
		if(atnI < 11)
		{
			atnI += 1; 
		}		
		//std::cout << "atnI: " << atnI << "\n";
	}

	// Lower Torch Attenuation Index (Brighter) (K)
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) 
	{
		if(atnI > 0)
		{
			atnI -= 1; 
		}
		//std::cout << "atnI: " << atnI << "\n";
	}
	
	//======
	
	// DAYTIME
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && DAYTIME_DELAY == 0) 
	{
		DAYTIME_DELAY = 30;

		if (DAYTIME)
		{
			DAYTIME = false;
		}
		else
		{
			DAYTIME = true;
		}
	}
	
	// ORTHO
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && ORTHO_DELAY == 0) 
	{
		ORTHO_DELAY = 30;

		if (ORTHO)
		{
			ORTHO = false;
		}
		else
		{
			ORTHO = true;
		}
	}
	
	// =======
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && RESTART_DELAY == 0)
	{
		RESTART_DELAY = 20;
		restart();
	}
	
	// =======
	
	//Picking up totem only if it is close
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && TOTEM_CLOSE_ENOUGH == true)
    {
        TOTEM_DELAY = 20;
		glm::vec3 totemPos = glm::vec3(spec_totem_temppos.x, spec_totem_temppos.y, spec_totem_temppos.z);
		
		if (glm::length(camera.Position - totemPos) < 1.5f && !TOTEM_FOUND)
		{
			TOTEM_FOUND = true;
		}
    }

	//toggle coordinate visibility
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && SHOW_DELAY == 0)
	{
		SHOW_DELAY = 20;
		if(SHOW_COORDINATE == false) 		
			SHOW_COORDINATE = true;
		else
			SHOW_COORDINATE = false;
	}
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

unsigned int loadTexture(char const * path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	//TODO:  if Alive (outside if first mouse)
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
	
	// Everything below in the original code without Camera Class
	// is implemented within the camera class itself with the ProcessMouseMovement method
    camera.ProcessMouseMovement(xoffset, yoffset);
}


void restart()
{
	//glm::vec3 camera_pos  			= glm::vec3(0.0f, 0.9f,  3.0f);
	camera = Camera(glm::vec3(0.0f, 0.9f,  3.0f));
	ORTHO 							= false;
	ORTHO_DELAY 					= 0;
	DAYTIME 						= false;
	DAYTIME_DELAY 					= 0;

	// Object settings/variables
	wolf_global_pos = glm::vec3(-13.0f, 0.4f, -15.0f);
	wolf_curpos = glm::vec3 (0.0f, 0.0f, 0.0f);
	angle = 0.0f;
	angleLeg = 0.0f;
	transLeg = 1.5f;
	portal_curpos = glm::vec3 (0.0f, 0.0f, 0.0f);
	portal_global_pos = glm::vec3(6.0f, 0.0f, -10.0f);
	tree_curpos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 tree_global_positions[50];
	totem_curpos = glm::vec3(0.0f, 0.0f, 0.0f);
	spec_totem_temppos = glm::vec3(0.0f, 0.0f, 0.0f);
	barrier_curpos = glm::vec3(0.0f, 0.0f, 0.0f);
	barrier_global_pos = glm::vec3(6.0f, 0.0f, -10.0f);

	// Light
	torch_global_pos = glm::vec3(5.0f, 0.0f, 6.0f); 
	light_pos = glm::vec3 (5.0f, 0.0f, 6.0f);
	torch_curpos = glm::vec3 (0.0f, 0.0f, 0.0f); 
	lamp_pos = glm::vec3 (5.0f, 0.15f, 6.0f);
	//=======
	atnI = 6;

	//=======
	// Torch variables
	TORCH_PRESSED = true; // Torch is on. Change this to change light intensity.
	TORCH_DELAY = 0; 
	TORCH_CLOSE_ENOUGH = false; // Torch is close enough
	TORCH_PICKED_UP = false; // Torch picked up

	// Proximity variables
	PORTAL_CLOSE_ENOUGH = false; // Portal is close enough
	TOTEM_CLOSE_ENOUGH = false; // Totem is close enough
	TOTEM_FOUND = false;
	TOTEM_DELAY = 0;
	LAUNCH_BARRIER = false;

	DEAD = false;
	WON = false;
	DEAD_CAM = false;

	SHOW_COORDINATE = false;
	SHOW_DELAY = 0;

}
