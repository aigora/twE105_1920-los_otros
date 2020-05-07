#include<graphics.h>
#include<conio.h>

main()
{
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "C:\\TC\\BGI");
  
  setbkcolor(BLACK);
  
  cleardevice();
  setfillstyle(SOLID_FILL, GREEN);
  setcolor(YELLOW);
  settextstyle(3,HORIZ_DIR,3);
  outtextxy(500,20, "Juego del Dominó");
  bar(160, 60, 1000, 600);
  
  setcolor(RED);
  settextstyle(4,HORIZ_DIR,1);
  outtextxy(1100,425,"Fichas de reserva");
  setcolor(4);
  rectangle(1080, 450, 1350, 600);
  
  setcolor(3);
  setlinestyle(1,DASHED_LINE,3);
  circle(300,530,60);
  
  setcolor(1);
  setlinestyle(1,SOLID_LINE,2);
  circle(300,510,20);
  
  setcolor(1);
  arc(300,555,0,180,25);
  
  setcolor(1);
  line(275,555,325,555);
  
  setcolor(BLUE);
  settextstyle(6,HORIZ_DIR,1);
  outtextxy(235,565,"PLAYER 1");
  
  setcolor(WHITE);
  settextstyle(4,HORIZ_DIR,1);
  outtextxy(1100,125,"PLAYER 2:");
  
  setcolor(LIGHTMAGENTA);
  settextstyle(4,HORIZ_DIR,1);
  outtextxy(1100,225,"PLAYER 3:");
  
  setcolor(LIGHTGREEN);
  settextstyle(4,HORIZ_DIR,1);
  outtextxy(1100,325,"PLAYER 4:");
  
  getch();
  closegraph();
}
