#include <gtest/gtest.h>
#include <Components/Animator.hpp>
#include <Components/Collider.hpp>
#include <Components/EnemyComp.hpp>
#include <Components/HitBox.hpp>
#include <Components/PlayerComp.hpp>
#include <Components/Renderable.hpp>
#include <Components/RenderLayer.hpp>
#include <Components/Transform.hpp>
#include <entt/entt.hpp>

// Make an entity with animation comp
struct MakeAnimEntt
{
	// Create registry and entity
	entt::registry reg;
	entt::entity entity;

	// Make sizes
	glm::vec2 sizeOfSheet = { 100,100 };
	glm::vec2 sizeOfSprite = { 10,10 };

	// create entity with animation comp
	MakeAnimEntt()
	{
		entity = reg.create();
		reg.emplace<Animator>(entity, sizeOfSheet, sizeOfSprite);
	}
};

// Create test instance -> makes new helper for every test
class AnimTest : public::testing::Test
{
protected:
	MakeAnimEntt helper;
};

// Animator test
TEST_F(AnimTest, canAddComp)
{
	EXPECT_TRUE	(helper.reg.all_of<Animator>(helper.entity));
}

TEST_F(AnimTest, spritesPerRow)
{
	int CorrectSpritesPerRow = 100 / 10;
	auto& animComp = helper.reg.get<Animator>(helper.entity);
	EXPECT_EQ(CorrectSpritesPerRow, animComp.spritesPerRow);
}

TEST_F(AnimTest, defaultState)
{
	auto& animComp = helper.reg.get<Animator>(helper.entity);
	EXPECT_EQ(Animator::animState::Idle, animComp.currentAnimState);
}

TEST_F(AnimTest, uvScaleCorrect)
{
	glm::vec2 uvScale = glm::vec2(helper.sizeOfSprite.x / helper.sizeOfSheet.x, helper.sizeOfSprite.y / helper.sizeOfSheet.y);
	auto& animComp = helper.reg.get<Animator>(helper.entity);
	EXPECT_EQ(uvScale, animComp.uvScale);
}

