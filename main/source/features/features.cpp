#include "features.hpp"
#include "../utility/rage/invoker/natives/natives.hpp"
#include "../utility/signatures/signatures.hpp"
#include "../utility/config/config.hpp"

static Features* featuresInstance = nullptr;

Features* Features::Instance() {
	if (!featuresInstance)
		featuresInstance = new Features();

	return featuresInstance;
}

void Features::Initialize() {
	pedFactory = *Signatures::Instance()->definitions.pedFactory;
}

void Features::Uninitialize() {
	featuresInstance = nullptr;
    delete this;
}

void Features::Tick() {
    localPlayer = PLAYER::PLAYER_ID();
    localPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(localPlayer);

    if (pedFactory != nullptr) {
        localPedPointer = pedFactory->m_local_ped;
	    localPlayerInfo = localPedPointer->GetPlayerInfo();
    }

    localPedPointer->SetInvincibility(Config::Instance()->self.godmode);
}