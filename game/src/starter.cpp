#include <game/sceneRender.hpp>
#include <game/scene.hpp>
#include <game/starter.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/sound.hpp>

using namespace stemaj;

std::optional<std::unique_ptr<State>> Starter::SwitchState(const ButtonAction& action)
{
	switch (action) {
		case START_GAME:
			SO.StopMusic();
			return std::make_unique<Scene>(Scene::Scenery::EASY);
		case BACK:
			SO.StopMusic();
			return std::make_unique<MainMenuState>();
		default:
			return std::nullopt;
	}
}