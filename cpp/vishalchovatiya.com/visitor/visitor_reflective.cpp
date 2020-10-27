#include <iostream>
#include <list>
#include <string>

using namespace std;

struct Document
{
    virtual void addToList(const string &line) = 0;
};

struct Markdown : Document
{
    void addToList(const string &line) {
        mContent.push_back(line);
    }

    string mStart = "* ";
    list<string> mContent;
};

struct HTML : Document
{
    void addToList(const string &line) {
        mContent.push_back(line);
    }

    string mStart = "<li>";
    string mEnd = "</li>";
    list<string> mContent;
};

struct DocumentPrinter {
    static void print(Document *e) {
        if (auto md = dynamic_cast<Markdown *>(e)) {
            for (auto &&item : md->mContent)
                cout << md->mStart << item << endl;
        } else if (auto hd = dynamic_cast<HTML *>(e)) {
            cout << "<ul>" << endl;
            for (auto &&item : hd->mContent)
                cout << "\t" << hd->mStart << item << hd->mEnd << endl;
            cout << "</ul>" << endl;
        }
    }
};

int main()
{
    Document *d = new HTML;
    d->addToList("This is a line");
    DocumentPrinter::print(d);

    delete d;

    d = new Markdown;
    d->addToList("This is a line");
    DocumentPrinter::print(d);

    delete d;

    return EXIT_SUCCESS;
}
