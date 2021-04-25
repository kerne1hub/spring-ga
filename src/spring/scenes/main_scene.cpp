//
// Created by kernel on 25.04.2021.
//

#include <spring/configuration.h>
#include <spring/scenes/main_scene.h>
#include <spring/systems/analysis_system.h>
#include <spring/systems/crossover_system.h>
#include <spring/systems/generation_system.h>
#include <spring/systems/mutation_system.h>
#include <spring/systems/rendering_system.h>
#include <spring/systems/selection_system.h>

MainScene::MainScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}

void MainScene::OnCreate() {
  config_ = std::make_unique<Configuration>(ctx_->Get<Configuration>("config"));

  pages_.emplace_back(56, 1, 40, 22, " Результаты ");

  auto sys = engine.GetSystemManager();

  sys->AddSystem<GenerationSystem>(state, *config_, 100);
  sys->AddSystem<AnalysisSystem>(state, *config_);
  sys->AddSystem<SelectionSystem>(state, *config_);
  sys->AddSystem<CrossoverSystem>(state, *config_);
  sys->AddSystem<MutationSystem>(state, *config_);
  sys->AddSystem<RenderingSystem>(state, &pages_);
}

void MainScene::OnRender() {
  engine.OnUpdate();
}

void MainScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();

  keyFuncMap_.clear();
  terminal_composition(TK_OFF);
}
