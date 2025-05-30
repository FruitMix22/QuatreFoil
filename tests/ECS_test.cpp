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

TEST_F(AnimTest, AnimStateUpdate)
{
	auto& animComp = helper.reg.get<Animator>(helper.entity);
	animComp.setAnimState(Animator::animState::Running);
	EXPECT_EQ(Animator::animState::Running, animComp.currentAnimState);
}

TEST_F(AnimTest, currentSpriteResets)
{
	auto& animComp = helper.reg.get<Animator>(helper.entity);
	animComp.setAnimState(Animator::animState::Running);
	EXPECT_TRUE(animComp.startRun == animComp.currentSprite);
}

TEST_F(AnimTest, doesNotResetFrameOnSameState)
{
	auto& anim = helper.reg.get<Animator>(helper.entity);

	anim.setAnimState(Animator::animState::Running);
	anim.currentSprite = 8; // midway in the running anim

	anim.setAnimState(Animator::animState::Running);

	// Test the branching
	EXPECT_EQ(anim.currentSprite, 8); 
}

TEST_F(AnimTest, doesNotAdvanceBeforeAnimUpdate)
{
	auto& anim = helper.reg.get<Animator>(helper.entity);
	anim.setAnimState(Animator::animState::Idle);
	anim.currentSprite = 2;

	float dt = anim.animUpdate / 2.0f;  // Not enough time
	anim.Update(dt);

	EXPECT_EQ(anim.currentSprite, 2);
}

TEST_F(AnimTest, doesAdvanceAfterAnimUpdate)
{
	auto& anim = helper.reg.get<Animator>(helper.entity);
	anim.setAnimState(Animator::animState::Idle);
	anim.currentSprite = 2;

	float dt = anim.animUpdate;  // enough time
	anim.Update(dt);

	EXPECT_EQ(anim.currentSprite, 3);
}

// Make an entity with animation comp
struct MakeTransformColliderEntt
{
	// Create registry and entity
	entt::registry reg;
	entt::entity entity;

	// create entity with animation comp
	MakeTransformColliderEntt()
	{
		entity = reg.create();
		reg.emplace<Collider>(entity);
		reg.emplace<Transform>(entity);
	}
};

// Create test instance -> makes new helper for every test
class ColliderTransformTest : public::testing::Test
{
protected:
	MakeTransformColliderEntt helper;
};

TEST_F(ColliderTransformTest, DoesTransformHaveCorrectValues)
{
	auto& transform = helper.reg.get<Transform>(helper.entity);

	EXPECT_EQ(transform.position, glm::vec2(0.f, 0.f));
	EXPECT_EQ(transform.scale, glm::vec2(1.f, 1.f));
	EXPECT_FLOAT_EQ(transform.rotation, 0.f);
}

TEST_F(ColliderTransformTest, defaultTransform)
{
	auto& transform = helper.reg.get<Transform>(helper.entity);

	glm::mat4 expected = glm::mat4(1.f);

	EXPECT_EQ(transform.GetModelMatrix(), expected);
}

TEST_F(ColliderTransformTest, transformModelMatrrixTest)
{
	auto& transform = helper.reg.get<Transform>(helper.entity);
	transform.position = { 5.f, 10.f };

	glm::mat4 modelMatrix = transform.GetModelMatrix();

	EXPECT_FLOAT_EQ(modelMatrix[3][0], 5.f);
	EXPECT_FLOAT_EQ(modelMatrix[3][1], -10.f); // y is flipped for screen space
}

TEST_F(ColliderTransformTest, ScaleAffectsMatrix)
{
	auto& transform = helper.reg.get<Transform>(helper.entity);
	transform.scale = { 2.f, 3.f };
	glm::mat4 model = transform.GetModelMatrix();

	EXPECT_FLOAT_EQ(model[0][0], 2.f);
	EXPECT_FLOAT_EQ(model[1][1], 3.f);
}





