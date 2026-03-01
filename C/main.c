#include "raylib.h"

#define ROWS 5
#define COLS 10

typedef struct
{
	Rectangle rect;
	bool active;
} Brick;

int main(void)
{
	InitWindow(800, 450, "Simple Breakout");
	SetTargetFPS(60);

	// ボールの設定
	Vector2 ballPosition = {400, 225};
	Vector2 ballSpeed = {4.0f, 4.0f};
	float ballRadius = 8;

	// パドルの設定
	Rectangle paddle = {400 - 50, 400, 100, 20};

	// ブロックの初期化
	Brick bricks[ROWS][COLS];
	float brickWidth = 60;
	float brickHeight = 20;
	float padding = 10;
	float offsetTop = 50;
	float offsetLeft = (800 - (COLS * (brickWidth + padding))) / 2;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			bricks[i][j].rect = (Rectangle){offsetLeft + j * (brickWidth + padding), offsetTop + i * (brickHeight + padding), brickWidth, brickHeight};
			bricks[i][j].active = true;
		}
	}

	while (!WindowShouldClose())
	{
		// --- 更新処理 ---
		// パドルの移動
		if (IsKeyDown(KEY_RIGHT) && (paddle.x < GetScreenWidth() - paddle.width))
			paddle.x += 7.0f;
		if (IsKeyDown(KEY_LEFT) && (paddle.x > 0))
			paddle.x -= 7.0f;

		// ボールの移動
		ballPosition.x += ballSpeed.x;
		ballPosition.y += ballSpeed.y;

		// 壁での反射
		if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius))
			ballSpeed.x *= -1.0f;
		if (ballPosition.y <= ballRadius)
			ballSpeed.y *= -1.0f;

		// パドルとの衝突判定
		if (CheckCollisionCircleRec(ballPosition, ballRadius, paddle))
		{
			if (ballSpeed.y > 0)
				ballSpeed.y *= -1.0f;
		}

		// ブロックとの衝突判定
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if (bricks[i][j].active)
				{
					if (CheckCollisionCircleRec(ballPosition, ballRadius, bricks[i][j].rect))
					{
						bricks[i][j].active = false;
						ballSpeed.y *= -1.0f; // 跳ね返り
						break;
					}
				}
			}
		}

		// 画面外（下）に落ちたらリセット
		if (ballPosition.y > GetScreenHeight())
		{
			ballPosition = (Vector2){400, 225};
			ballSpeed = (Vector2){4.0f, -4.0f};
		}

		// --- 描画処理 ---
		BeginDrawing();
		ClearBackground(RAYWHITE);

		// ボールとパドルの描画
		DrawCircleV(ballPosition, ballRadius, MAROON);
		DrawRectangleRec(paddle, DARKBLUE);

		// ブロックの描画
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if (bricks[i][j].active)
				{
					DrawRectangleRec(bricks[i][j].rect, GRAY);
				}
			}
		}

		DrawText("Break all bricks!", 10, 10, 20, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}