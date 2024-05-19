#ifndef XML_TREE_H
#define XML_TREE_H
#include <string>
#include <vector>


class XmlParser;

class XmlTree {
public:

    XmlTree();

    XmlTree(const XmlTree& other);

    XmlTree& operator=(const XmlTree& other);

    std::vector<XmlTree> operator[](const std::string& identifier);

    void addChild(XmlTree& child);

    std::string getContent() const;

    void setContent(const std::string& content);

    std::vector<XmlTree> getChildren() const;

    std::string getIdentifier() const;

private:
    friend class XmlParser;

    XmlTree(const std::string& identifier);

    XmlTree(const std::string& identifier, const std::string& content,
            const std::vector<XmlTree>& children);

    std::string identifier;
    std::string content;
    std::vector<XmlTree> children;
};

#endif
