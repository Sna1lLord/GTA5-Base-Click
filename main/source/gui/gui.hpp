#ifndef _GUI_HPP
#define _GUI_HPP

#include <common.hpp>
#include "fonts.hpp"

class Gui {
public:
    ID3D11Device* device;
	ID3D11DeviceContext* context;
    HWND hwnd;
    bool initialized;
    bool opened;
    int currentSubmenu;

    ImFont* titleFont;
    ImFont* textFont;
    ImFont* childHeaderFont;
    ImFont* iconFont;

    std::vector<const char*> submenuList = {ICON_FA_USER, ICON_FA_USERS, ICON_FA_NETWORK_WIRED, ICON_FA_PERSON_CIRCLE_PLUS, ICON_FA_CAR, ICON_FA_GUN, ICON_FA_SACK_DOLLAR, ICON_FA_CIRCLE_QUESTION, ICON_FA_SHIELD_HALVED, ICON_FA_GLOBE, ICON_FA_GEAR, ICON_FA_TERMINAL, ICON_FA_PUZZLE_PIECE};

    std::vector<std::pair<std::string, uint64_t>> notifications;
public:
    static Gui* Instance();
    void Initialize();
    void Uninitialize();
    void Tick();
    void DrawChild(ImVec2 size, ImVec2 position, const char* text);
    void EndChild();

    void AddNotification(const char* format, ...);
	void DrawNotifications();
public:
    void Self();
};

#endif