#include <iostream>
#include "raylib.h"

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color DarkGreen = Color{20, 160, 133, 255};
Color LightGreen = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int PlayerScore = 0;
int CpuScore = 0;

class Ball{

   
public:
float x, y;
int spdX, spdY;
int radius;

void Draw(){
DrawCircle(x, y, radius, Yellow);
}

void Update(){

   x += spdX;
   y += spdY;

   if(y + radius >= GetScreenHeight() || y - radius <= 0){

      spdY *= -1;

   }

   if(x + radius >= GetScreenWidth() || x - radius <= 0){

      spdX *= -1;

   }
   if(x + radius >= GetScreenWidth()){

      CpuScore++; 
      ResetBall();
      
   }
   if(x - radius <= 0){

      PlayerScore++;
      ResetBall();
   }

}

   void ResetBall(){

      x = GetScreenWidth()/2;
      y = GetScreenHeight()/2;

      int spdchoices[2] = {-1, 1};
      spdX *= spdchoices[GetRandomValue(0, 1)];
      spdY *= spdchoices[GetRandomValue(0, 1)];

   }

};
 

class Padle{

protected: 

void LimitMovement(){

 if(y <= 0)
         {
      y = 0;
      }


      if(y + height >= GetScreenHeight())
         {
      y = GetScreenHeight() - height;
      }  

}

public:
float x, y;
float widht, height;
int spd;


void Draw(){

DrawRectangleRounded(Rectangle{x, y, widht, height}, 0.8, 0, WHITE);

}


void Update(){

      if(IsKeyDown(KEY_UP)){

      y = y - spd;

      }
      if(IsKeyDown(KEY_DOWN)){

      y = y + spd;

      }
      if(IsKeyDown(KEY_LEFT_SHIFT)){

      spd = 8;

      }else{

      spd = 8;

      }

      LimitMovement();  
   }

};


class CPU : public Padle{
public:

void Update(int bally){

if(y + height/2 > bally){

y = y - spd;

}
if (y + height/2 < bally){

y = y + spd;

}
}
};





Padle Player;
Ball ball;
CPU cpu;


int main(){


const int screen_widht = 1280;
const int screen_height = 800;
InitWindow(screen_widht, screen_height, "Janela Init");
SetTargetFPS(60);

ball.radius = 20;
ball.x = screen_widht/2;
ball.y = screen_height/2;
ball.spdX = 7;
ball.spdY = 7;

Player.widht = 25;
Player.height = 120;
Player.x = screen_widht - Player.widht - 10;
Player.y = screen_height/2 - Player.height/2;
Player.spd = 6;

cpu.height = 120;
cpu.widht = 25;
cpu.x = 10;
cpu.y = screen_height/2 - cpu.height/2;
cpu.spd = 6;

while(!WindowShouldClose()){

BeginDrawing();


Player.Update();
ball.Update();
cpu.Update(ball.y);

if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{Player.x, Player.y, Player.widht, Player.height})){

ball.spdX *= -1;

}
if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.widht, cpu.height})){

ball.spdX *= -1;

}



ClearBackground(DarkGreen);
DrawRectangle(screen_widht/2, 0, screen_widht/2, screen_height, Green);
DrawLine(screen_widht/2, 0, screen_widht/2, screen_height, WHITE);
ball.Draw(); 
cpu.Draw(); 
Player.Draw();
DrawText(TextFormat("%i", CpuScore), screen_widht/4 - 20, 20, 60, WHITE);
DrawText(TextFormat("%i", PlayerScore), 3 *  screen_widht/4 - 20, 20, 80, WHITE);

EndDrawing();
}
   
      CloseWindow();
 
   return 0;
}
