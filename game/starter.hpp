#ifndef __STARTER_HPP
#define __STARTER_HPP

#include <olcTemplate/game/input.hpp>
#include <optional>
#include <memory>

namespace stemaj {

class State;

class Starter
{
public:
	static std::optional<std::unique_ptr<State>> SwitchState(const ButtonAction& action);
};

} // namespace stemaj

#endif // __STARTER_HPP