#ifndef __TUT_HPP
#define __TUT_HPP

#include <olcTemplate/game/src/state/levelState.hpp>

namespace stemaj {

class TutorialRender;

class Tutorial : public LevelState
{
public:

  explicit Tutorial();
  virtual ~Tutorial();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  std::unique_ptr<TutorialRender> _render;
};

} // namespace stemaj

#endif // __TUT_HPP

