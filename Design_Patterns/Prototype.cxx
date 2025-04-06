#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <locale>
#include <codecvt>

#ifdef _WIN32
#include <windows.h>
#endif

// Prototype interface
class DocumentPrototype {
public:
    virtual std::unique_ptr<DocumentPrototype> cloneDocument() const = 0;
    virtual void display() const = 0;
    virtual ~DocumentPrototype() {}
};

// Concrete Prototype
class Document : public DocumentPrototype {

    std::string content;
    std::vector<std::string> images;
    std::string formatting;
    std::vector<std::string> annotations;

public:

    Document(const std::string& content
            , const std::vector<std::string>& images
            , const std::string& formatting
            , const std::vector<std::string>& annotations)
        : content{content}, images{images}, formatting{formatting}, annotations{annotations}
        {}
    
    std::unique_ptr<DocumentPrototype> cloneDocument() const override {
        return std::make_unique<Document>(*this);
    }

    // Display doc
    void display() const override {
        std::cout << "Content: " << content <<std::endl;
        std::cout << "Images: ";
        for(const auto& image : images) {
            std::cout << image << " ";
        }
        std::cout << std::endl;
        std::cout << "Formatting: " << formatting <<std::endl;
        std::cout << "Annotations: ";
        for(const auto& annotation : annotations) {
            std::cout << annotation << " ";
        }
        std::cout << std::endl;
    }

    // Doc manipulation methods
    void addImage(const std::string& image) {
        images.push_back(image);
    }

    void addAnnotation(const std::string& annotation) {
        annotations.push_back(annotation);
    }
};

auto main() -> int {
    
#ifdef _WIN32
    // Enable UTF-8 output on Windows
    SetConsoleOutputCP(CP_UTF8);
    // Optional, but can help with some consoles
    SetConsoleCP(CP_UTF8);
#endif

    std::vector<std::string> images{"\xF0\x9F\x91\xBB"};
    std::vector<std::string> annotations{"Annotation1"};

    Document originalDoc("Hello, World!", images, "Basic", annotations);

    std::unique_ptr<DocumentPrototype> copiedDoc{ originalDoc.cloneDocument() };

    originalDoc.addImage("\xF0\x9F\x90\x9B");
    originalDoc.addAnnotation("Annotation2");
    
    std::cout << "Original Document: " << std::endl;
    originalDoc.display();
    std::cout << "\nCopied Document: " << std::endl;
    copiedDoc->display();

    std::cin.get();

    return 0;
}