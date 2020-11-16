#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

template<typename LS>
struct TextProcessor
{
    void appendList(const vector<string> &items) {
        mListStrategy.start(mOss);
        for (auto &item : items)
            mListStrategy.addListItem(mOss, item);
        mListStrategy.end(mOss);
    }

    string str() const {
        return mOss.str();
    }
private:
    ostringstream mOss;
    LS mListStrategy;
};

int main()
{
    TextProcessor<MarkdownListStrategy> tp1;
    tp1.appendList({"foo", "bar", "baz"});
    cout << tp1.str() << endl;

    TextProcessor<HtmlListStrategy> tp2;
    tp2.appendList({"foo", "bar", "baz"});
    cout << tp2.str() << endl;
}
