#include "game_over_screen.hpp"
#include "ecs_registry.hpp"
#include "game_state_manager.hpp"
#include "splash_screen_state.hpp"

GameOverScreen::~GameOverScreen() {
    cleanup();
}

void GameOverScreen::init()
{
    Sprite splashSprite = renderSystem.loadTexture("game_over.png");

    TransformComponent splashTransform;
    splashTransform.position = glm::vec3(renderSystem.getWindowWidth() / 2.0f, renderSystem.getWindowHeight() / 2.0f, 0.0f);

    splashTransform.scale = glm::vec3(splashSprite.width, splashSprite.height, 1.0f);
    splashTransform.rotation = 0.0f;

    registry.transforms.emplace(gameOverEntity, std::move(splashTransform));

    registry.sprites.emplace(gameOverEntity, std::move(splashSprite));
}

void GameOverScreen::cleanup() {
    registry.remove_all_components_of(gameOverEntity);
}

void GameOverScreen::on_key(int key, int, int action, int) {
    if (action == GLFW_PRESS) {
        renderSystem.getGameStateManager()->changeState<SplashScreenState>();
    }
}

void GameOverScreen::on_mouse_move(const vec2&) {}

void GameOverScreen::on_mouse_click(int button, int action, const vec2&, int) {}

void GameOverScreen::render()
{
    // Clear the screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (registry.sprites.has(gameOverEntity) &&
        registry.transforms.has(gameOverEntity))
    {
        // Retrieve the Sprite and TransformComponent using the registry
        auto& sprite = registry.sprites.get(gameOverEntity);
        auto& transform = registry.transforms.get(gameOverEntity);

        // Use the render system to draw the entity
        renderSystem.drawEntity(sprite, transform);
    }

    renderSystem.renderText("Press any button to continue.", window_width_px * 0.29f, window_height_px * 0.80f, 1.0f, vec3(1), mat4(1));
}

void GameOverScreen::update(float) {

}