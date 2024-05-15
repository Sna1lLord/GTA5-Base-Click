#include "../gui.hpp"
#include "../utility/rage/invoker/queue.hpp"
#include "../utility/rage/invoker/natives/natives.hpp"
#include "../utility/signatures/signatures.hpp"
#include "../utility/config/config.hpp"
#include "../utility/rage/joaat.hpp"

void Gui::Self() {
    if (ImGui::BeginTabBar("Tabs")) {
        if (ImGui::BeginTabItem("General")) {
            ImVec2 windowSize = ImGui::GetWindowSize();
            DrawChild(ImVec2(windowSize.x / 2, windowSize.y - 50.f), ImVec2(0.f, 40.f), "General");

            if (ImGui::Button("Clear Wanted")) {
                CPedFactory* pedFactory = *Signatures::Instance()->definitions.pedFactory;
                if (pedFactory != nullptr) {
                    CPed* localPed = pedFactory->m_local_ped;
                    if (localPed != nullptr) {
                        CPlayerInfo* localPlayerInfo = localPed->GetPlayerInfo();
                        if (localPlayerInfo != nullptr) {
                            localPlayerInfo->SetWantedLevel(0);
                        }
                    }
                }
            }

            if (ImGui::Button("Money")) {
                Queue::Instance()->Add([]{
                    if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE())
                        NETSHOPPING::NET_GAMESERVER_BASKET_END();
                    
                    int transaction = -1;
                    __int64 queue = *Signatures::Instance()->definitions.transactionQueue;

                    if (Signatures::Instance()->definitions.constructBasket(queue, &transaction, joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), joaat("NET_SHOP_ACTION_EARN"), 4)) {
                        uint32_t hash = joaat("SERVICE_EARN_JUGGALO_STORY_MISSION");
                        std::vector<std::array<int, 5>> items {
                            {(int)hash, -1, 100000, 0, 1}
                        };

                        for (auto& item : items) {
                            Signatures::Instance()->definitions.addItemToBasket(queue, item.data());
                        }

                        Signatures::Instance()->definitions.processTransaction(queue, transaction, 69420);
                    }
                });
            }

            EndChild();

            DrawChild(ImVec2(windowSize.x / 2 - 5.f, windowSize.y / 2 - 45.f), ImVec2(windowSize.x / 2 + 5.f, 40.f), "Health");

            ImGui::Checkbox("Godmode", &Config::Instance()->self.godmode);

            if (ImGui::Button("Suicide")) {
                Queue::Instance()->Add([=]{
                    ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 1);
                });
            }

            EndChild();

            DrawChild(ImVec2(windowSize.x / 2 - 5.f, 200.f), ImVec2(windowSize.x / 2 + 5.f, windowSize.y / 2 + 5.f), "Invisible");

            

            EndChild();

            DrawChild(ImVec2(windowSize.x / 2 - 5.f, 135.f), ImVec2(windowSize.x / 2 + 5.f, windowSize.y / 2 + 205.f), "Multiplier");

            

            EndChild();

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Cosmetic")) {


            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}