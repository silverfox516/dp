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

struct DocumentPrinter
{
    void operator()(Markdown &md) {
        for (auto &&item : md.mContent)
            cout << md.mStart << item << endl;
    }
    void operator()(HTML &hd) {
        cout << "<ul>" << endl;
        for (auto &&item : hd.mContent)
            cout << "\t" << hd.mStart << item << hd.mEnd << endl;
        cout << "</ul>" << endl;
    }
};

using document = std::variant<Markdown, HTML>;

int main()
{
    HTML hd;
    hd.addToList("This is a line");
    document d = hd;
    DocumentPrinter dp;
    std::visit(dp, d);
    return EXIT_SUCCESS;
}
