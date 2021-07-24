#include "../models/SearchEngine.h"
#include<fstream>
#define gotoxy gotoXY
using namespace std;
void SearchEngine::run() {
    bool stop = true;
    while (stop) {
        system("CLS");

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
        int a1 = 44;
        int b1 = 15;

        drawFrame(a, b);
        draw(x1, y1);
        drawGoogle(x, y);

        readInput(history, rawText, a1, b1, stop);
        if (!stop) break;

        vector<result> results = searchQuery(rawText);

        showRawResult(results);
    }
}
void SearchEngine::drawFrame(int a, int b) {

    gotoXY(a, b);
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    gotoXY(a, b + 8);
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;
    cout << (char)196 << (char)196 << (char)196 << (char)196 << (char)196;

    for (int i = 1; i < 8; i++) {
        gotoXY(a - 1, b + i);
        cout << (char)179;
    }
    for (int i = 1; i < 8; i++) {
        gotoXY(a + 75, b + i);
        cout << (char)179;
    }

}
// search and suggestion frames
void SearchEngine::draw(int x, int y) {
    gotoXY(x, y);
    cout << "SEARCH      :";

    gotoXY(x, y + 2);
    cout << "SUGGESTION  :";
}
void SearchEngine::suggest(int coor, string data) {
    int a = 44;
    int b = 16;

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
void SearchEngine::drawGoogle(int x, int y) {

    //DRAW GOOGLE

    gotoXY(5 + x, 1 + y);
    cout << (char)219 << (char)219;
    cout << (char)219 << (char)219 << (char)219;

    gotoXY(4 + x, 2 + y);
    cout << (char)219 << (char)219;
    gotoXY(3 + x, y + 3);
    cout << (char)219 << (char)219 << char(219);
    gotoXY(4 + x, 2 + y + 2);
    cout << (char)219 << (char)219;
    gotoXY(5 + x, 1 + y + 4);
    cout << (char)219 << (char)219 << (char)219 << (char)219;
    gotoXY(x + 9, y + 4);
    cout << (char)219 << (char)219;
    gotoXY(x + 8, y + 3);
    cout << (char)219 << (char)219;
    //chu G
    gotoXY(x + 16, y + 1);
    cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
    gotoXY(x + 14, y + 2);
    cout << (char)219 << (char)219;
    gotoXY(x + 14, y + 3);
    cout << (char)219 << (char)219;
    gotoXY(x + 14, y + 4);
    cout << (char)219 << (char)219;
    gotoXY(x + 16, y + 5);
    cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
    gotoXY(x + 21, y + 2);
    cout << (char)219 << (char)219;
    gotoXY(x + 21, y + 3);
    cout << (char)219 << (char)219;
    gotoXY(x + 21, y + 4);
    cout << (char)219 << (char)219;
    //chu O
    gotoXY(x + 32 - 3, y + 1);
    cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
    gotoXY(x + 30 - 3, y + 2);
    cout << (char)219 << (char)219;
    gotoXY(x + 30 - 3, y + 3);
    cout << (char)219 << (char)219;
    gotoXY(x + 30 - 3, y + 4);
    cout << (char)219 << (char)219;
    gotoXY(x + 32 - 3, y + 5);
    cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
    gotoXY(x + 37 - 3, y + 2);
    cout << (char)219 << (char)219;
    gotoXY(x + 37 - 3, y + 3);
    cout << (char)219 << (char)219;
    gotoXY(x + 37 - 3, y + 4);
    cout << (char)219 << (char)219;
    //chu O
    gotoXY(44 + x - 2, 1 + y);
    cout << (char)219 << (char)219;
    cout << (char)219 << (char)219 << (char)219;
    gotoXY(43 + x - 2, 2 + y);
    cout << (char)219 << (char)219;
    gotoXY(42 + x - 2, y + 3);
    cout << (char)219 << (char)219 << (char)219;
    gotoXY(43 + x - 2, 2 + y + 2);
    cout << (char)219 << (char)219;
    gotoXY(44 + x - 2, 1 + y + 4);
    cout << (char)219 << (char)219 << (char)219 << (char)219;
    gotoXY(x + 48 - 2, y + 4);
    cout << (char)219 << (char)219;
    gotoXY(x + 47 - 2, y + 3);
    cout << (char)219 << (char)219;
    //chu G
    gotoXY(x + 52, y + 1);
    cout << (char)219 << (char)219;
    gotoXY(x + 52, y + 2);
    cout << (char)219 << (char)219;
    gotoXY(x + 52, y + 3);
    cout << (char)219 << (char)219;
    gotoXY(x + 52, y + 4);
    cout << (char)219 << (char)219;
    gotoXY(x + 52, y + 5);
    cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
    //chu L
    gotoXY(x + 64, y + 1);
    cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
    gotoXY(x + 64, y + 2);
    cout << (char)219 << (char)219;
    gotoXY(x + 64, y + 3);
    cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
    gotoXY(x + 64, y + 4);
    cout << (char)219 << (char)219;
    gotoXY(x + 64, y + 5);
    cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
    //chu E

    gotoXY(x + 10, y + 10);

}
void SearchEngine::readInput(vector<string>& history, string& text, int x, int y, bool& stop) {
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
        gotoXY(44, (i + 1) * 1 + 16);
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
            stop = false;
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
	        gotoXY(44,(i+1)*1+16);
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
        tem2.erase(tem2.begin(), tem2.end());
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

void SearchEngine::showResult(vector<result> results, string text, set<string> words) {

}
vector<string> SearchEngine::getReview(string filename, set<string> words, int maxLength) {
    return vector<string>();
}
vector<string> SearchEngine::getContent(string filename, int maxLength) {
    return vector<string>();
}


