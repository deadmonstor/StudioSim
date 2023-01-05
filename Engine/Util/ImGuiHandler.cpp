#include "ImGuiHandler.h"


#include <iterator>
#include <sstream>

#include "../Library/imgui/imgui_impl_glfw.h"
#include "../Library/imgui/imgui_impl_opengl3.h"
#include "../WindowManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Util/stb_image.h"

void ImGuiHandler::init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL(WindowManager::Instance()->GetWindow(), true);


	//Create Image
	Image diceImage;
	diceImage.filename = "PNG_transparency_demonstration_1.png";
	m_Images.push_back(diceImage);

	// Load Textures
	for (int i = 0; i < m_Images.size(); i++)
	{
		loadTexture(m_Images.at(i).filename, &m_Images.at(i).texture, &m_Images.at(i).width, &m_Images.at(i).height);
	}
}

void ImGuiHandler::update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	
;
	// Make m_vLog into a string with newlines
	std::string sLog;
	for (auto& s : m_vLog)
	{
		sLog += s + "\n";
	}

	ImGui::Begin("Logging Window");
	ImGui::Text("%s", sLog.c_str());
	ImGui::End();
	
	//New Window For Image Testing
	ImGui::Begin("Image Window");
	//Render Textures
	for (int i = 0; i < m_Images.size(); i++) 
	{
		ImGui::Image((void *)(intptr_t)m_Images.at(i).texture, ImVec2(m_Images.at(i).width, m_Images.at(i).height));
	}
	ImGui::End();

	//Image Control Window
	ImGui::Begin("Image Control Window");
	for (int i = 0; i < m_Images.size(); i++)
	{
		ImGui::SliderInt("width", &m_Images.at(i).width, 100, 1000);
		ImGui::SliderInt("height", &m_Images.at(i).height, 100, 1000);
	}
	ImGui::End();
}

void ImGuiHandler::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiHandler::addLog(const std::string &log)
{
	m_vLog.push_back(log);
}

void ImGuiHandler::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
}

bool ImGuiHandler::loadTexture(const char *filename, GLuint *outputTexture, int *width, int *height)
{ 
	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char *image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL) {
		return false;
	}

	GLuint image;
	glGenTextures(1, &image);
	glBindTexture(GL_TEXTURE_2D, image);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*outputTexture = image;
	*width = image_width;
	*height = image_height;

	return true; 
}
