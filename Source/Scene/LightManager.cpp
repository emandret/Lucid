#include "LightManager.h"
#include "../Application/GameApplication.h"

#include <iostream>

LightManager::LightManager()
{

}

void LightManager::AddLight(std::shared_ptr<LightNode> lightNode)
{
	// make sure it wasn't already added
	for(auto it = m_Lights.begin(); it != m_Lights.end(); it++)
		if((*it) == lightNode)
			return;
	m_Lights.push_back(lightNode);
}

void LightManager::RemoveLight(std::shared_ptr<LightNode> lightNode)
{
	m_Lights.erase(std::remove(m_Lights.begin(), m_Lights.end(), lightNode));
}

void LightManager::UpdateShader(Scene *scene, std::shared_ptr<Shader> shader)
{
	float time = GameApplication::GetInstance()->GetTime();
    // Update all lights that are currently visible to the shader (up to a maximum)
	shader->Use();
	int nr_active = 0;
	for(int i = 0; i < m_Lights.size(); ++i)
	{
		if (m_Lights[i]->IsVisible(scene))
		{
			float value = std::sin(GameApplication::GetInstance()->GetTime() * 4.0f + (i * m_Lights.size()) + (rand() % 100) / 200.0f) * (0.03 + (rand() % 100) / 1500.0f) + 1.0;
			//std::cout << value << std::endl;
			std::shared_ptr<LightNode> light = m_Lights[i];
			shader->SetVector3f("Lights[" + std::to_string(i) + "].Position", glm::vec3(light->GetPosition() + light->GetScale() * 0.5f, light->GetDepth())); // no need to inverse depth due to LHC system
			shader->SetVector3f("Lights[" + std::to_string(i) + "].Diffuse", light->GetDiffuse());
			shader->SetVector3f("Lights[" + std::to_string(i) + "].Specular", light->GetSpecular());
			shader->SetFloat("Lights[" + std::to_string(i) + "].Linear", light->GetAttenuation() * value);
			//shader->SetFloat("Lights[" + std::to_string(i) + "].Linear", value);
			++nr_active;
		}
	}
	shader->SetInteger("NrActiveLights", nr_active);
}