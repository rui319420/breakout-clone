#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "Breakout Clone - Paddle");
    SetTargetFPS(60);

    // ボールの初期値
    Vector2 ballPosition = { 400, 225 };
    Vector2 ballSpeed = { 5.0f, 4.0f };
    float ballRadius = 10;

    // パドルの初期値（追加！）
    Rectangle paddle = { 400 - 50, 400, 100, 20 };

    while (!WindowShouldClose()) {
        // --- 更新処理 ---
        // 左右キーでパドルを動かす
        if (IsKeyDown(KEY_RIGHT) && (paddle.x < GetScreenWidth() - paddle.width)) paddle.x += 7.0f;
        if (IsKeyDown(KEY_LEFT) && (paddle.x > 0)) paddle.x -= 7.0f;

        // ボールの移動
        ballPosition.x += ballSpeed.x;
        ballPosition.y += ballSpeed.y;

        // 壁での反射
        if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) ballSpeed.x *= -1.0f;
        if (ballPosition.y <= ballRadius) ballSpeed.y *= -1.0f;

        // パドルとの衝突判定（追加！）
        if (CheckCollisionCircleRec(ballPosition, ballRadius, paddle)) {
            if (ballSpeed.y > 0) ballSpeed.y *= -1.0f;
        }

        // --- 描画処理 ---
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircleV(ballPosition, ballRadius, MAROON); // ボール
            DrawRectangleRec(paddle, DARKBLUE);           // パドル
            DrawText("Use Arrow Keys to Move", 10, 10, 20, GRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}