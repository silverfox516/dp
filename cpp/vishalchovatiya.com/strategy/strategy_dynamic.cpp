#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Format{
    Markdown,
    Html,
};

struct ListStrategy
{
    virtual ~ListStrategy() = default;
    virtual void addListItem(ostringstream &oss, string &item) {};
    virtual void start(ostringstream &oss) {};
    virtual void end(ostringstream &oss) {};
};

struct MarkdownListStrategy : ListStrategy
{
    void addListItem(ostringstream &oss, string &item) override {
        oss << " - " << item << endl;
    }
};

struct HtmlListStrategy : ListStrategy
{
    void start(ostringstream &oss) override {
        oss << "<ul>" << endl;
    }
    void end(ostringstream &oss) override {
        oss << "</ul>" << endl;
    }
    void addListItem(ostringstream &oss, string &item) override {
        oss << "\t<li>" << item << "</li>" << endl;
    }
};

struct TextProcessor
{
    void clear() {
        mOss.str("");
        mOss.clear();
    }

    void appendList(vector<string> &items) {
        mListStrategy->start(mOss);
        for (auto &item : items)
            mListStrategy->addListItem(mOss, item);
        mListStrategy->end(mOss);
    }

    void setOutputFormat(Format &format) {
        switch (format) {
        case Format::Markdown:
            mListStrategy = make_unique<MarkdownListStrategy>();
            break;
        case Format::Html:
            mListStrategy = make_unique<HtmlListStrategy>();
            break;
        }
    }

    string str() {
        return mOss.str();
    }
private:
    ostringstream mOss;
    unique_ptr<ListStrategy> mListStrategy;
};

int main()
{
    TextProcessor tp;
    tp.setOutputFormat(Format::Markdown);
    tp.appendList({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    tp.clear();
    tp.setOutputFormat(Format::Html);
    tp.appendList({"foo", "bar", "baz"});
    cout << tp.str() << endl;

    return EXIT_SUCCESS;
}
