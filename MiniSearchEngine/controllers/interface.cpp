#include "../models/SearchEngine.h"
#include<fstream>
#define gotoxy gotoXY

using namespace std;
void SearchEngine::run() {
    int stop = 1;
    while (stop) {
        system("CLS");

        string rawText;

        vector<string> history;
        int x = 35;
        int y = 2;
        int a = 33;
        int b = 1;
        int w1 = 51;
        //coordinate for search and suggestion
        int x1 = 29;
        int y1 = 12;

        // coordinate for read input
        int a1 = 44;
        int b1 = 12;

        drawFrame(a, b,w1);
        draw(x1, y1);
        drawGoogle(x, y);

        readInput(history, rawText, a1, b1, stop);
        if (!stop) break;
        if (stop == 2) {
            stop = 1;
            reload();
            continue;
        }

        vector<result> results = searchQuery(rawText);

        showResult(rawText, results);
    }
}
void SearchEngine::drawGoogle(int x, int y) {

    ifstream fin;
    vector<string> v;
    fin.open("google.txt");
    string tem;
    for (int i = 0; i < 6; i++) {
        getline(fin, tem);
        v.push_back(tem);
    }
    for (int i = 0; i < 6; i++) {
        gotoxy(x, y + i * 1);
        cout << v[i];
    }
}
void SearchEngine::drawFrame(int a, int b, int w) {

    gotoxy(a, b);
    int width = w;
    int tem = w;
    cout << (char)TOP_LEFT;
    while (width > 0) {
        cout << (char)HORIZONTAL;
        width--;
    }
    cout << (char)TOP_RIGHT;

    for (int i = 1; i < 8; i++) {
        gotoxy(a, b + i);
        cout << (char)VERTICAL;
    }
    gotoxy(a, b + 7);
    cout << (char)BOT_LEFT;
    while (tem > 0) {
        cout << (char)HORIZONTAL;
        tem--;
    }
    for (int i = 1; i < 8; i++) {
        gotoxy(a + w + 1, b + i);
        cout << (char)VERTICAL;
    }
    gotoxy(a + w + 1, b + 7);
    cout << (char)BOT_RIGHT;

}

// search and suggestion frames
void SearchEngine::draw(int x, int y) {
    int w = 12, t = 12;
    gotoxy(x - 1, y); cout << (char)VERTICAL_lite;
    gotoxy(x + w, y); cout <<(char) VERTICAL_lite;
    gotoxy(x - 1, y - 1);
    cout <<(char)TOP_LEFT_lite;
    
    while (w > 0) {
        cout << (char)HORIZONTAL_lite;
        w--;
    }
    cout << (char)TOP_RIGHT_lite;
    gotoxy(x - 1, y + 1);
    cout << (char)BOT_LEFT_lite;
    while (t > 0) {
        cout << (char)HORIZONTAL_lite;
        t--;
    }
    cout << (char)BOT_RIGHT_lite;
    gotoXY(x, y);
    cout << "   SEARCH";
    w = 12;
    t = 12;
    gotoxy(x - 1, y+4); cout << (char)VERTICAL_lite;
    gotoxy(x + w, y+4); cout << (char)VERTICAL_lite;
    gotoxy(x - 1, y +3);
    cout << (char)TOP_LEFT_lite;
    while (w > 0) {
        cout << (char)HORIZONTAL_lite;
        w--;
    }
    cout << (char)TOP_RIGHT_lite;
    gotoxy(x - 1, y + 5);
    cout << (char)BOT_LEFT_lite;
    while (t > 0) {
        cout << (char)HORIZONTAL_lite;
        t--;
    }
    cout << (char)BOT_RIGHT_lite;
    gotoXY(x, y + 4);
    cout << " SUGGESTION";
}
void SearchEngine::suggest(int coor, string data) {
    int a = 44;
    int b =15;

    gotoXY(a, b + coor * 1);
    cout << data;
}
vector<string> SearchEngine::getSuggestion(vector<string>history, string text) {
    vector<string> tem;
    for (auto &x : history) {
        int t = x.find(text);
        if (t == 0) tem.push_back(x);
    }
    return tem;
}

void SearchEngine::readInput(vector<string>& history, string& text, int x, int y, int& stop) {
    string blank(40,' ');
	char character;
    ifstream fin;
    ofstream fout;
    for (int i = 0; i < 50; i++) {
        gotoXY(x + i, y);
        cout << ' ';
    }
    while (!text.empty()) text.pop_back();
    string tem1;
    if (history.size() == 0) {
        //history.erase(history.begin(), history.end());
        fin.open("history.txt");
        if (fin) {
            while (!fin.eof()) {
                getline(fin, tem1);
                if (!tem1.empty()) history.push_back(tem1);
            }
        }
        else history.push_back("");
        fin.close();
    }
    vector<string> t;
    for (auto &x : getSuggestion(history, text)) {
        t.push_back(x);
    }
    reverse(t.begin(), t.end());

    //clear all suggestion
    for (int i = 0;i < 10;i++) {
        gotoXY(44, (i + 1) * 1 + 15);
        cout << blank;
    }

    // suggestion (toi da 10 cai)
    for (int i = 0; i < 10; i++) {
        if (t.size() > i) {
            suggest(i + 1, t[i]);
        }
    }

    gotoxy(x, y);
    while (character = _getch(), (int)character != 13) {
        if ((int)character == 27) {
            stop = 0;
            return;
        }
        if ((int)character == 0) {
            character = _getch();
            stop = 2;
            return;
        }
        if (character == '\b') {
            if (text.size() == 0) continue;
            text.pop_back();
            gotoXY(x + (int)text.size(), y); cout << ' ';
            gotoXY(x + (int)text.size(), y);

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
        for (auto &x : getSuggestion(history, text)) {
            t.push_back(x);
        }
        reverse(t.begin(), t.end());

        //clear all suggestion
        for(int i=0;i<10;i++){
	        gotoXY(44,(i+1)*1+15);
	        cout<<blank;
	    }

        // suggestion (toi da 10 cai)
        for (int i = 0; i < 10; i++) {
            if (t.size() > i) {
                suggest(i + 1, t[i]);
            }
        }

        //gotoxy(x, y);
        gotoXY(x + (int)text.size(), y);
    }

    //add to history
    if (text.empty()) return;
    bool check = true;
    for (auto &x : history) {
        if (!text.compare(x)) {
            check = false;
        }
    }
    if (check) {
        fout.open("history.txt", ios::app);
        fout << text << endl;
        fout.close();
        history.push_back(text);
    }
    else {
        fout.open("history.txt");
        //fout << text << endl;
        vector<string> tem2;
        for (auto& x : history) tem2.push_back(x);
        vector<string> ::iterator it = tem2.begin();

        for (int i = 0; i < tem2.size(); i++) {
            if (!tem2[i].compare(text)) {
                advance(it, i);
                tem2.erase(it, it + 1);
                break;
            }
        }
        for (auto& x : tem2) fout << x << endl;
        fout << text << endl;
        history.erase(history.begin(), history.end());

        for (auto& x : tem2) history.push_back(x);
        history.push_back(text);
        fout.close();
    }
}
