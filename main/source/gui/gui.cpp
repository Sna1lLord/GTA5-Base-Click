#include "gui.hpp"
#include "../utility/logger/logger.hpp"
#include "../source/hooks/hooks.hpp"
#include "../utility/rage/invoker/natives/natives.hpp"
#include "../utility/rage/invoker/queue.hpp"
#include "../utility/signatures/signatures.hpp"
#include "../utility/rage/joaat.hpp"

static Gui* guiInstance = nullptr;

Gui* Gui::Instance() {
	if (!guiInstance)
		guiInstance = new Gui();

	return guiInstance;
}

void Gui::Tick() {
    if (GetAsyncKeyState(VK_INSERT) & 1)
        opened ^= true;

	if (opened) {
        ImGui::SetNextWindowSize(ImVec2(740.f, 740.f));
        if (ImGui::Begin("BASE", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar)) {
            ImVec2 windowSize = ImGui::GetWindowSize();
            ImVec2 windowPosition = ImGui::GetWindowPos();
            ImDrawList* drawList = ImGui::GetForegroundDrawList();
            drawList->AddRectFilled(windowPosition, ImVec2(windowPosition.x + windowSize.x, windowPosition.y + 30.f), ImColor(22, 24, 27, 255));

            ImGui::PushFont(titleFont);
            drawList->AddText(ImVec2(windowPosition.x + (windowSize.x - ImGui::CalcTextSize("BASE").x) / 2, windowPosition.y + 7.f), ImColor(1.f, 1.f, 1.f, 1.f), "BASE");
            ImGui::PopFont();

            ImGui::SetNextWindowPos(ImVec2(windowPosition.x + 10.f, windowPosition.y + 35.f));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1059f, 0.1137f, 0.1294f, 1.0000f));
            ImGui::BeginChild("TabChild", ImVec2(50.f, 698.f));
            ImGui::PopStyleColor();
                    
            ImGui::PushFont(iconFont);
            for (int i = 0; i < (int)submenuList.size(); i++) {
                bool current = false;
                if (i == currentSubmenu) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 0.50f));
                    current = true;
                }
                if (ImGui::Button(submenuList[i], ImVec2(50.f, 50.f))) {
                    currentSubmenu = i;
                }
                if (current) {
                    ImGui::PopStyleColor();
                    ImGui::PopStyleColor();
                }
            }
            ImGui::PopFont();
            ImGui::EndChild();
            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical, 2.f);

            ImGui::PushFont(textFont);

            ImGui::SetNextWindowPos(ImVec2(windowPosition.x + 75.f, windowPosition.y + 35.f));
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1059f, 0.1137f, 0.1294f, 1.0000f));
            ImGui::BeginChild("MainChild", ImVec2(657.f, 698.f), true);
            ImGui::PopStyleColor();

			switch (currentSubmenu) {
				case 0: {
					Self();
					break;
				}

				default: break;
			}

            ImGui::PopFont();
            ImGui::EndChild();

            ImGui::End();
        }
    }

	DrawNotifications();
}

void Gui::Initialize() {
	ImGuiIO io = ImGui::GetIO();

    ImFontConfig config;
	config.FontDataOwnedByAtlas = false;
    static const ImWchar iconRanges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
	titleFont = io.Fonts->AddFontFromFileTTF("C:\\Fonts\\nasalization-bold-italic.ttf", 14.f, &config);
    textFont = io.Fonts->AddFontFromFileTTF("C:\\Fonts\\verdana.ttf", 18.f, &config);
    iconFont = io.Fonts->AddFontFromFileTTF("C:\\Fonts\\font-awesome-solid-900.ttf", 22.f, &config, iconRanges);

	ImVec4* colors = ImGui::GetStyle().Colors;
	ImGuiStyle style = ImGui::GetStyle();

	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.17647058823f, 0.20784313725f, 0.25098039215f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.f, 0.f, 0.f, 0.0f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.f, 0.f, 0.f, 0.0f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 1.00f, 0.96f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 1.00f, 0.96f, 0.42f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 1.00f, 0.96f, 0.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.f, 0.f, 0.f, 0.0f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.f, 0.f, 0.f, 0.0f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 0.50f);
	colors[ImGuiCol_TabActive] = ImVec4(0.27058823529f, 0.46274509803f, 0.74901960784f, 0.40f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	style.WindowPadding = ImVec2(10, 10);
	style.FramePadding = ImVec2(15, 4);
	style.ItemSpacing = ImVec2(15, 5);
	style.ItemInnerSpacing = ImVec2(10, 4);
	style.ScrollbarSize = 5;
	style.GrabMinSize = 20;

	style.WindowBorderSize = 0;
	style.ChildBorderSize = 0;
	style.FrameBorderSize = 0;
	style.TabBorderSize = 0;

	style.WindowRounding = 5;
	style.ChildRounding = 12;
	style.FrameRounding = 10;
	style.ScrollbarRounding = 2;
	style.GrabRounding = 2;
	style.TabRounding = 2;

	style.WindowMenuButtonPosition = 0;
}

void Gui::Uninitialize() {
    opened = false;

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (context) { context->Release(); context = NULL; }
	if (device) { device->Release(); device = NULL; }
	SetWindowLongPtr(Gui::Instance()->hwnd, GWLP_WNDPROC, (LONG_PTR)(Hooks::Instance()->originalWndProc));
}

void Gui::DrawChild(ImVec2 size, ImVec2 position, const char* text) {
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15.f, 50.f));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 15.f);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0627f, 0.0706f, 0.0745f, 1.0000f));
	ImVec2 windowPosition = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();
	ImGui::SetNextWindowPos(ImVec2(windowPosition.x + position.x, windowPosition.y + position.y));
	ImGui::BeginChild(text, size, ImGuiChildFlags_Border);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

	ImVec2 childPosition = ImGui::GetWindowPos();
	ImVec2 childSize = ImGui::GetWindowSize();
	ImDrawList* drawList = ImGui::GetForegroundDrawList();
	drawList->AddRectFilled(childPosition, ImVec2(childPosition.x + childSize.x, childPosition.y + 40.f), ImColor(27, 29, 33, 255));
	drawList->AddText(ImVec2(childPosition.x + (childSize.x - ImGui::CalcTextSize(text).x) / 2, childPosition.y + 10.f), ImColor(255, 255, 255, 255), text); 
}

void Gui::EndChild() {
	ImGui::EndChild();
}

void Gui::AddNotification(const char* format, ...) {
	char notificationText[256];

	va_list args;
	va_start(args, format);
	vsnprintf(notificationText, sizeof(notificationText), format, args);

	for (auto pair : notifications) {
		if (pair.first == std::string(notificationText)) {
			pair.second = GetTickCount64();
			return;
		}
	}

	notifications.push_back(std::make_pair(std::string(notificationText), GetTickCount64()));

	va_end(args);
}

void Gui::DrawNotifications() {
	for (int i = 0; i < (int)notifications.size(); i++) {
		if (GetTickCount64() - notifications[i].second >= 3000) {
			notifications.erase(notifications.begin() + i);
			continue;
		}

		ImVec2 screenSize = ImGui::GetIO().DisplaySize;

		float width = ImGui::CalcTextSize(notifications[i].first.c_str()).x + 40.f;
		float positionY = 30.f + (i * 43.f);
		float barWidth = width - (float)(((double)(GetTickCount64() - notifications[i].second) / 3000) * width);

		ImDrawList* drawList = ImGui::GetForegroundDrawList();
		drawList->AddRectFilled(
			ImVec2(screenSize.x - width, positionY),
			ImVec2(screenSize.x, positionY + 30.f),
			ImColor(27,29,33,255)
		);
		drawList->AddRectFilled(
			ImVec2(screenSize.x - width, positionY),
			ImVec2(screenSize.x - width + 5.f, positionY + 30.f),
			ImColor(74,13,159,255)
		);
		drawList->AddRectFilled(
			ImVec2(screenSize.x - width, positionY + 30.f),
			ImVec2(screenSize.x - width + barWidth, positionY + 35.f),
			ImColor(74,13,159,255)
		);

		ImGui::PushFont(textFont);
		drawList->AddText(
			ImVec2(screenSize.x - width + 25.f, positionY + 4.f),
			ImColor(255, 255, 255, 255),
			notifications[i].first.c_str()
		);
		ImGui::PopFont();
	}
}