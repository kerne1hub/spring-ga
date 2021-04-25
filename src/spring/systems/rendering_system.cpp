//
// Created by kernel on 25.04.2021.
//

#include <BearLibTerminal.h>
#include <lib/ecs/entity_manager.h>
#include <spring/components/characteristics_component.h>
#include <spring/components/fitness_component.h>
#include <spring/state.h>
#include <spring/systems/rendering_system.h>

#include <vector>

RenderingSystem::RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager, const State& state,
                                 std::vector<Page>* pages)
    : ISystem(entity_manager, system_manager), state_(const_cast<State&>(state)), pages_(pages) {}

void RenderingSystem::OnUpdate() {
  terminal_clear();

  for (auto& page : *pages_) {
    page.Draw();
  }

  for (int x = 57; x < 95; x++) {
    terminal_put(x, 2, L'─');
    terminal_put(x, 4, L'─');
    terminal_put(x, 6, L'─');
    terminal_put(x, 8, L'─');
    terminal_put(x, 10, L'─');
    terminal_put(x, 12, L'─');
    terminal_put(x, 14, L'─');
    terminal_put(x, 16, L'─');
  }

  for (int y = 3; y < 17; y += 2) {
    terminal_put(66, y, L'│');
  }

  for (int y = 4; y < 16; y += 2) {
    terminal_put(66, y, 0x253C);
  }

  terminal_put(66, 2, 0x252C);
  terminal_put(66, 16, 0x2534);

  terminal_printf(59, 3, "D, мм");
  terminal_printf(59, 5, "d, мм");
  terminal_printf(59, 7, "N");
  terminal_printf(59, 9, "V, мм");
  terminal_printf(59, 11, "[U+03B4], МПа");
  terminal_printf(59, 13, "[U+03B4], мм");
  terminal_printf(59, 15, "[U+03B4], N");

  if (static_cast<int>(state_.GetSolutionId()) != -1) {
    auto result = GetEntityManager().Get(state_.GetSolutionId());
    auto chars = result->Get<CharacteristicsComponent>();
    auto fitness = result->Get<FitnessComponent>();

    terminal_printf(68, 3, "%.3f", chars->D_);
    terminal_printf(68, 5, "%.1f", chars->d_);
    terminal_printf(68, 7, "%.0f", chars->n_);
    terminal_printf(68, 11, "%.3f", fitness->fi1_);
    terminal_printf(68, 13, "%.3f", fitness->fi2_);
    terminal_printf(68, 15, "%.0f", fitness->fi4_);
  }

  terminal_refresh();
}
