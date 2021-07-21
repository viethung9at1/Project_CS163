#include "../models/SearchEngine.h"

void SearchEngine::run() {
    string rawText;

    vector<string> history;
    int x = 20;
    int y = 2;
    int a = 20;
    int b = 1;

    //coordinate for search and suggestion
    int x1 = 30;
    int y1 = 15;

    // coordinate for read input
    int a1 = 50;
    int b1 = 15;

    drawFrame(a, b);
    draw(x1, y1);
    drawGoogle(x, y);
    bool stop = true;
    while (stop) {
        readInput(history, rawText, a1, b1, stop);

    }
    
    gotoxy(50, 50);
}
void SearchEngine::drawFrame(int a, int b) {

    gotoxy(a, b);
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    gotoxy(a, b + 8);
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;

    for (int i = 1; i < 8; i++) {
        gotoxy(a - 1, b + i);
        cout << (char)179;
    }
    for (int i = 1; i < 8; i++) {
        gotoxy(a + 75, b + i);
        cout << (char)179;
    }

}
// search and suggestion frames
void SearchEngine::draw(int x, int y) {
    gotoxy(x, y);
    cout << "SEARCH      :";

    gotoxy(x, y + 2);
    cout << "SUGGESTION  :";
}
void SearchEngine::TextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void SearchEngine::suggest(int coor, string data) {
    int a = 50;
    int b = 16;

    gotoxy(a, b + coor * 1);
    cout << data;
}
vector<string> SearchEngine::getSuggestion(vector<string>history, string text) {
    vector<string> tem;
    for (auto x : history) {
        int t = x.find(text);
        if (t == 0) tem.push_back(x);
    }
    return tem;
}
void SearchEngine::drawGoogle(int x, int y) {

    //DRAW GOOGLE

    gotoxy(5 + x, 1 + y);
    cout << (char)219 << (char)219;
    cout << (char)219 << (char)219 << (char)219;

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
void SearchEngine::readInput(vector<string>& history, string& text, int x, int y, bool& stop) {
    char character;

    for (int i = 0; i < 30; i++) {
        gotoxy(x + i, y);
        cout << ' ';
    }
    while (!text.empty()) text.pop_back();
    gotoxy(x, y);
    vector<string> t;
    while (character = _getch(), (int)character != 13) {
        if ((int)character == 27) {
            stop = false;
            return;
        }
        if (character == '\b') {
            if (text.size() == 0) continue;
            text.pop_back();
            gotoxy(x + (int)text.size(), y); cout << ' ';
            gotoxy(x + (int)text.size(), y);

        }
        // keyUp keyDown on suggestion
  /*    while (true) {
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
   }
   */
        else {

            text += character;
            cout << character;
        }
        t.erase(t.begin(), t.end());

        for (auto x : getSuggestion(history, text)) {
            t.push_back(x);
        }
        //clear all suggestion
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 30; j++) {
                gotoxy(50 + j, (i + 1) * 1 + 16);
                cout << ' ';
            }
        }
        // suggestion (toi da 10 cai)
        for (int i = 0; i < 10; i++) {
            if (t.size() > i) {
                suggest(i + 1, t[i]);
            }
        }
        //gotoxy(x, y);

        gotoxy(x + (int)text.size(), y);
    }



    //add to history
    bool check = true;
    for (auto x : history) {
        if (!text.compare(x)) {
            check = false;
        }
    }
    if (check) history.push_back(text);

}




/*
set<string> SearchEngine::getWords(string text) {
	return set<string>();
}
*/
void SearchEngine::showResult(vector<result> results, string text, set<string> words) {

}
vector<string> SearchEngine::getReview(string filename, set<string> words, int maxLength) {

}
vector<string> SearchEngine::getContent(string filename, int maxLength) {

}


