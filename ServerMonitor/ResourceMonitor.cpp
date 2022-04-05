#include "pch.h"
#include "ResourceMonitor.h"

void ResourceMonitor::Update()
{
	ImGui::Begin("test");
	
	ImGui::Text("Resource USage : 888");

	float values[7] = {
		10, 20, 30, 50, 60, 50, 52 
	};

	const char* overlay = "Resource Usage";

	ImVec2 size = {500, 300};
	ImGui::PlotLines("Resource", values, IM_ARRAYSIZE(values), 0, overlay, 0.f, 100.f, size);

	ImGui::End();
}
