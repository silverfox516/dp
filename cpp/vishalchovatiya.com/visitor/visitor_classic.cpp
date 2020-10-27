#include <iostream>
#include <list>
#include <string>

using namespace std;

struct DocumentVisitor
{
    virtual void visit(class Markdown*) = 0;
    virtual void visit(class HTML*) = 0;
};

struct DocumentPrinter : DocumentVisitor
{
    void visit(class Markdown *md);
    void visit(class HTML *hd);
};

struct Document
{
    virtual void addToList(const string &line) = 0;
    virtual void accept(DocumentVisitor*) = 0;
};

struct Markdown : Document
{
    void addToList(const string &line) {
        mContent.push_back(line);
    }
    void accept(DocumentVisitor *dv) {
        dv->visit(this);
    };

    string mStart = "* ";
    list<string> mContent;
};

struct HTML : Document
{
    void addToList(const string &line) {
        mContent.push_back(line);
    }
    void accept(DocumentVisitor *dv) {
        dv->visit(this);
    }

    string mStart = "<li>";
    string mEnd = "</li>";
    list<string> mContent;
};

void DocumentPrinter::visit(Markdown *md) {
    for (auto &&item : md->mContent)
        cout << md->mStart << item << endl;
}

void DocumentPrinter::visit(HTML *hd) {
    cout << "<ul>" << endl;
    for (auto &&item : hd->mContent)
        cout << "\t" << hd->mStart << item << hd->mEnd << endl;
    cout << "</ul>" << endl;
}

int main()
{
    Document *d = new HTML;
    d->addToList("This is a line");
    d->accept(new DocumentPrinter);

    Markdown *m = new Markdown;
    m->addToList("This is a line");
    m->accept(new DocumentPrinter);

    delete d, m;

    return EXIT_SUCCESS;
}
