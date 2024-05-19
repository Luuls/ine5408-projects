#include <stdexcept>

#include "../include/xml_tree.h"

XmlTree::XmlTree() {}

XmlTree::XmlTree(const XmlTree& other) : identifier(other.identifier), content(other.content) {
    for (const auto& child : other.children) {
        children.push_back(child);
    }
}

XmlTree& XmlTree::operator=(const XmlTree& other) {
    if (this != &other) {
        this->identifier = other.getIdentifier();
        this->content = other.content;
        this->children = other.children;
    }
    return *this;
}

std::vector<XmlTree> XmlTree::operator[](const std::string& identifier) {
    std::vector<XmlTree> nodes;
    for (auto& child : children) {
        if (child.getIdentifier() == identifier) {
            nodes.push_back(child);
        }
    }

    if (nodes.size() > 0) {
        return nodes;
    }

    std::string msg = "Identifier not found: " + identifier;
    throw std::runtime_error(msg);
}

void XmlTree::addChild(XmlTree& child) { children.push_back(child); }

std::string XmlTree::getContent() const { return this->content; }

void XmlTree::setContent(const std::string& content) { this->content = content; }

std::vector<XmlTree> XmlTree::getChildren() const { return this->children; }

std::string XmlTree::getIdentifier() const { return this->identifier; }

XmlTree::XmlTree(const std::string& identifier) : identifier(identifier) {}

XmlTree::XmlTree(const std::string& identifier, const std::string& content,
        const std::vector<XmlTree>& children)
    : identifier(identifier), content(content), children(children) {}
