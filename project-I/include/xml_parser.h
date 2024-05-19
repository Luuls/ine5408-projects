#ifndef XML_PARSER
#define XML_PARSER

#include <fstream>
#include <iterator>
#include "array_stack.h"
#include "xml_tree.h"

class XmlParser {
  public:
    static XmlTree parse(const std::string& xmlPath);

  private:
    static std::string readIdentifier(std::string::iterator& iter);

    // Utilizado para ler o conteúdo dentro de uma tag, a partir de iteradores
    // que apontam para o começo e para o fim do conteúdo.
    static std::string readContent(std::string::iterator contentBegin,
                                   std::string::iterator contentEnd);
};

#endif
