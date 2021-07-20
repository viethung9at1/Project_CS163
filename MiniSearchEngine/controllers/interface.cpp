#include "../models/SearchEngine.h"

void SearchEngine::run() {

}
vector<string> SearchEngine::getSuggestion() { // Online History
	return vector<string>();
}
set<string> SearchEngine::getWords(string text) {
	return set<string>();
}

void SearchEngine::showResult(vector<result> results, string text, set<string> words) {

}
vector<string> SearchEngine::getReview(string filename, set<string> words, int maxLength) {

}
vector<string> SearchEngine::getContent(string filename, int maxLength) {

}


/*
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
using namespace std;
void gotoxy(int x, int y)
{
    static HANDLE  h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x,y};
    SetConsoleCursorPosition(h,c);
}
void drawGoogle(int x,int y);

void TextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void readInput(vector<string>&history,string&text,int x,int y){
    char character;
    gotoxy(x,y);
    vector<string> t;
    while (character=_getch(),character!=13){

        if(character== '\b'){
            if (text.size() == 0) continue;
            text.pop_back();
            gotoxy(x + (int)text.size(), y); cout << ' ';
            gotoxy(x + (int)text.size(), y);

    }
        // keyUp keyDown on suggestion
        /*while(true){
        char c = getch();
        if(c == -32){
            c = getch();
            if(c == 72){
                printf("Ban vua an phim mui ten len!\n");
            }
            if(c == 80){
                printf("Ban vua an phim mui ten xuong!\n");
            }
            if(c == 75){
                printf("Ban vua an phim mui ten sang trai!\n");
            }
            if(c == 77){
                printf("Ban vua an phim mui ten sang phai!\n");
            }
            if(c == 27) break;
       }
   }*/
        else {

        text += character;
        cout << character;
    }
        }
        t.erase(t.begin(), t.end());
        t = getSuggestion(history, text);
        // suggestion (toi da 3 cai)
        for (int i = 0; i < 10; i++) {
            if (t.size() > i) {
                suggest(i + 1, t[i]);
            }
        }
        //add to history
        bool check = true;
        for (auto x : history) {
            if (text.compare(x)) {
                check = false;
            }
        }
        if (!check) history.push_back(text);
    }
    }
    vector<string> getSuggestion(vector<string>history, string text) {
        vector<string> tem;
        for (auto x : history) {
            int t = x.find(text);
            if (t == 0) tem.push_back(x);
        }
        return tem;
    }
    void suggest(int coor, string data) {
        int a = 30;
        int b = 15;
        //gotoxy(a,b+coor*4);
        for (int i = 0; i < 30; i++) {
            gotoxy(a + i, coor * 1 + b);
            cout << ' ';
        }
        gotoxy(a, b + coor * 1);
        cout << data;
    }
    int main() {

        string rawText;

        vector<string> history;
        //
        drawGoogle(20, 0);
        //TextColor(1);
        // (char) 10 is \n
        // 50,12 : search
        int a = 50;
        int b = 12;
        //gotoxy(50,12);
        //readInput(text,a,b);
        gotoxy(50, 30);
        cout << (char)196 << (char)196;
        cout << (char)179;

        //
        //readInput()
        char character;
        character = getch();
        int key = character;


        //lay du lieu 

    }


    void drawGoogle(int x, int y) {

        //DRAW GOOGLE

        gotoxy(5 + x, 1 + y);
        cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        gotoxy(4 + x, 2 + y);
        cout << (char)219 << (char)219;
        gotoxy(3 + x, y + 3);
        cout << (char)219 << (char)219 << char(219);
        gotoxy(4 + x, 2 + y + 2);
        cout << (char)219 << (char)219;
        gotoxy(5 + x, 1 + y + 4);
        cout << (char)219 << (char)219 << (char)219 << (char)219;
        gotoxy(x + 9, y + 4);
        cout << (char)219 << (char)219;
        gotoxy(x + 8, y + 3);
        cout << (char)219 << (char)219;
        //chu G
        gotoxy(x + 16, y + 1);
        cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        gotoxy(x + 14, y + 2);
        cout << (char)219 << (char)219;
        gotoxy(x + 14, y + 3);
        cout << (char)219 << (char)219;
        gotoxy(x + 14, y + 4);
        cout << (char)219 << (char)219;
        gotoxy(x + 16, y + 5);
        cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        gotoxy(x + 21, y + 2);
        cout << (char)219 << (char)219;
        gotoxy(x + 21, y + 3);
        cout << (char)219 << (char)219;
        gotoxy(x + 21, y + 4);
        cout << (char)219 << (char)219;
        //chu O
        gotoxy(x + 32 - 3, y + 1);
        cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        gotoxy(x + 30 - 3, y + 2);
        cout << (char)219 << (char)219;
        gotoxy(x + 30 - 3, y + 3);
        cout << (char)219 << (char)219;
        gotoxy(x + 30 - 3, y + 4);
        cout << (char)219 << (char)219;
        gotoxy(x + 32 - 3, y + 5);
        cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        gotoxy(x + 37 - 3, y + 2);
        cout << (char)219 << (char)219;
        gotoxy(x + 37 - 3, y + 3);
        cout << (char)219 << (char)219;
        gotoxy(x + 37 - 3, y + 4);
        cout << (char)219 << (char)219;
        //chu O
        gotoxy(44 + x - 2, 1 + y);
        cout << (char)219 << (char)219;
        cout << (char)219 << (char)219 << (char)219;
        gotoxy(43 + x - 2, 2 + y);
        cout << (char)219 << (char)219;
        gotoxy(42 + x - 2, y + 3);
        cout << (char)219 << (char)219 << (char)219;
        gotoxy(43 + x - 2, 2 + y + 2);
        cout << (char)219 << (char)219;
        gotoxy(44 + x - 2, 1 + y + 4);
        cout << (char)219 << (char)219 << (char)219 << (char)219;
        gotoxy(x + 48 - 2, y + 4);
        cout << (char)219 << (char)219;
        gotoxy(x + 47 - 2, y + 3);
        cout << (char)219 << (char)219;
        //chu G
        gotoxy(x + 52, y + 1);
        cout << (char)219 << (char)219;
        gotoxy(x + 52, y + 2);
        cout << (char)219 << (char)219;
        gotoxy(x + 52, y + 3);
        cout << (char)219 << (char)219;
        gotoxy(x + 52, y + 4);
        cout << (char)219 << (char)219;
        gotoxy(x + 52, y + 5);
        cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        //chu L
        gotoxy(x + 64, y + 1);
        cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        gotoxy(x + 64, y + 2);
        cout << (char)219 << (char)219;
        gotoxy(x + 64, y + 3);
        cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        gotoxy(x + 64, y + 4);
        cout << (char)219 << (char)219;
        gotoxy(x + 64, y + 5);
        cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
        //chu E

        gotoxy(x + 10, y + 10);

    }
    */