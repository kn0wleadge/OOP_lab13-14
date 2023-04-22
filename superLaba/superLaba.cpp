// #define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <shlobj.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <thread>
#include <chrono>

class FileRead
{
private:
    int* numbers;
    //static float process;
public:
    int QuantityOfElements;
    FileRead()
    {

    }
    void writeBinary(std::ostream& out,const void* ptr, size_t size) {
        out.write((char*)(ptr), size);
    }
    void changeNegativeNum(std::string path, float* process)
    {
        *process = 0;
        std::ifstream file1{ path,std::ios::binary };
        file1.seekg(0, std::ios::end);
        std::string oldPath1 = path;
        path.append("new");
        std::cout << path;
        std::ofstream newFile{ path,std::ios::binary };
        if (!newFile)
        {
            std::cout << "new Samples is not opened";
        }
        std::streampos fileSize = file1.tellg();
        file1.seekg(0, std::ios::beg);
        int numElements = fileSize / sizeof(int);
        QuantityOfElements = numElements;
        numbers = new int[QuantityOfElements + 1];
        const char* empty = new char[2]{"0" };
        if (!file1)
        {
            std::cout << std::endl << "old file is not opened" << std::endl;
        }
        else if (newFile)
        {
            int n;
            for (int i = 0; i < QuantityOfElements; i++)
            {
                file1.read(reinterpret_cast<char*>(&n), sizeof(n));
                numbers[i] = n;
                //std::cout << numbers[i];
                if (numbers[i] > 0)
                {
                    std::string str = std::to_string(numbers[i]);
                    str.append(" ");
                    const char* n1 = str.data();/*new char[4] {0};*/
                    //itoa(numbers[i], n1, 10);
                    writeBinary(newFile, n1, str.size());
                }
                else
                {

                    writeBinary(newFile, empty, sizeof(char));
                }
                *process = ((float)i + 1) / QuantityOfElements;
                //std::this_thread::sleep_for(std::chrono::microseconds(1));
            }
        }
        delete[] empty;

        file1.close();
        newFile.close();
        const char* oldPath = oldPath1.c_str();
        const char* lastPath = path.c_str();
        remove(oldPath);
        rename(lastPath, oldPath);
        std::cout << "OK";
    }
    void checkFile(std::string path)
    {
        std::ifstream file1{ path,std::ios::binary };
        file1.seekg(0, std::ios::end);
        std::streampos fileSize = file1.tellg();
        file1.seekg(0, std::ios::beg);
        int numElements = fileSize / sizeof(int);
        QuantityOfElements = numElements;
        numbers = new int[QuantityOfElements + 1];
        int notZero = 0;
        int zero = 0;
        if (!file1)
        {
            std::cout << "all bad" << std::endl;
        }
        else
        {
            int n;
            float process;
            for (int i = 0; i < QuantityOfElements; i++)
            {
                file1.read(reinterpret_cast<char*>(&n), sizeof(n));
                numbers[i] = n;
                if (numbers[i] > 0)
                    notZero++;
                else
                {
                    zero++;
                }

            }

        }
        std::cout << notZero << "zeros" << zero;
    }
    int getter_q()
    {
        return QuantityOfElements;
    }
    int get_inumber(int i)
    {
        return numbers[i];
    }
    friend class Windo;
};
class Windo
{
    sf::Vector2i mousePosW;
    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;
    sf::RectangleShape pathRec;
    sf::RectangleShape buttonRec;
    sf::RectangleShape loadRec;
    sf::CircleShape chooseTriangle;
    sf::Font font;
    sf::Text randomInt;
    sf::RectangleShape randomIntRec;
    sf::Text textButton;
    sf::Text textPath;
    sf::Text doneProcent;
    sf::RectangleShape thButton;
    sf::Text thText;
    std::string pathToFile;
    std::vector <sf::RectangleShape> loadingRecs;
    sf::RectangleShape loadingRec;
    FileRead file;
    int okeyPressed = 0;
    float process = 0.f;
    void initVariables()
    {
        this->window = nullptr;

        this->font.loadFromFile("consolas.ttf");

        this->textButton.setFont(font);
        this->textButton.setCharacterSize(20);
        this->textButton.setFillColor(sf::Color::Black);
        this->textButton.setString("Ok");
        this->textButton.setPosition(454.5, 50.f);

        this->textPath.setFont(font);
        this->textPath.setCharacterSize(18);
        this->textPath.setFillColor(sf::Color::Black);
        this->textPath.setString("");
        this->textPath.setPosition(25.f, 50.f);

        this->doneProcent.setFont(font);
        this->doneProcent.setCharacterSize(18);
        this->doneProcent.setFillColor(sf::Color::Black);
        this->doneProcent.setString("0%");
        this->doneProcent.setPosition(415.f, 95.f);

        this->thText.setFont(font);
        this->thText.setCharacterSize(12);
        this->thText.setFillColor(sf::Color::Black);
        this->thText.setString("Rand INT");
        this->thText.setPosition(23.f, 9.f);

        this->randomInt.setFont(font);
        this->randomInt.setCharacterSize(18);
        this->randomInt.setFillColor(sf::Color::Black);
        this->randomInt.setString("");
        this->randomInt.setPosition(22.f+65.f, 6.f);


    }
    void initWindow()
    {
        this->videoMode.height = 180;
        this->videoMode.width = 550;
        this->window = new sf::RenderWindow(this->videoMode, "Convert for samples", sf::Style::Titlebar | sf::Style::Close);
        this->window->setFramerateLimit(60);
    }
    void initForms()
    {
        this->pathRec.setPosition(20.f, 50.f);
        this->pathRec.setSize(sf::Vector2f(374.f, 25.f));
        this->pathRec.setFillColor(sf::Color(255, 255, 255, 255));
        this->pathRec.setOutlineColor(sf::Color::Black);
        this->pathRec.setOutlineThickness(1.f);


        this->loadRec.setPosition(20.f, 95.f);
        this->loadRec.setSize(sf::Vector2f(374.f, 25.f));
        this->loadRec.setFillColor(sf::Color(212, 208, 200, 255));
        this->loadRec.setOutlineColor(sf::Color::Black);
        this->loadRec.setOutlineThickness(1.f);


        this->loadingRec.setPosition(22.f, 96.f);
        this->loadingRec.setSize(sf::Vector2f(10.f, 23.f));
        this->loadingRec.setFillColor(sf::Color::Blue);


        this->buttonRec.setPosition(405.f, 50.f);
        this->buttonRec.setSize(sf::Vector2f(122.f, 25.f));
        this->buttonRec.setFillColor(sf::Color(212, 208, 200, 255));
        this->buttonRec.setOutlineColor(sf::Color::Black);
        this->buttonRec.setOutlineThickness(1.f);

        this->chooseTriangle.setRadius(5);
        this->chooseTriangle.setPointCount(3);
        this->chooseTriangle.setPosition(388, 67);
        this->chooseTriangle.setFillColor(sf::Color(0, 0, 0, 255));
        this->chooseTriangle.setRotation(180);

        this->thButton.setSize(sf::Vector2f(60.f,25.f));
        this->thButton.setOutlineColor(sf::Color::Black);
        this->thButton.setOutlineThickness(1.f);
        this->thButton.setPosition(22.f,5.f);
        this->thButton.setFillColor(sf::Color(10, 200, 10, 122));

        this->randomIntRec.setFillColor(sf::Color(255, 255, 255, 255));
        this->randomIntRec.setSize(sf::Vector2f(35.f, 25.f));
        this->randomIntRec.setPosition(22.f + 65.f, 5.f);
        this->randomIntRec.setOutlineColor(sf::Color::Black);
        this->randomIntRec.setOutlineThickness(1.f);
    }
public:
    //Constructor and destructor
    Windo() {
        this->initVariables();
        this->initWindow();
        this->initForms();
    }
    ~Windo()
    {
        delete this->window;
    }


    //Functions
    void pollEvents()//+
    {
        while (this->window->pollEvent(this->ev))
        {
            switch (this->ev.type)
            {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code = sf::Keyboard::Escape)
                    this->window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (this->ev.mouseButton.button == sf::Mouse::Left && mousePosW.x > 404 && mousePosW.x < 528 && mousePosW.y > 49 && mousePosW.y < 76)
                {
                    this->buttonRec.setFillColor(sf::Color(182, 178, 170, 255));
                    this->doneProcent.setString("0%");
                    okeyPressed = 1;



                }
                else if (this->ev.mouseButton.button == sf::Mouse::Left && (mousePosW.x > 380 && mousePosW.x < 395 && mousePosW.y > 59 && mousePosW.y < 71))
                {
                    pathToFile = OpenFileDialog();
                }
                else if (this->ev.mouseButton.button == sf::Mouse::Left && (mousePosW.x > 20 && mousePosW.x < 84 && mousePosW.y > 4 && mousePosW.y < 32))
                {
                    createRandomInt();
                }
                break; 
            case sf::Event::MouseButtonReleased:
                if (this->ev.mouseButton.button == sf::Mouse::Left)
                {
                    this->buttonRec.setFillColor(sf::Color(212, 208, 200, 255));
                    if (okeyPressed) {
                        this->loadingRecs.clear();
                        std::thread th(&FileRead::changeNegativeNum, &file, pathToFile, &process);
                        th.detach();

                    };
                }

                okeyPressed = 0;
                break;

            }

        }

    }
    void createRandomInt (){
        this->randomInt.setString(std::to_string(rand() % 1000));
    }
    const bool isOpen() const
    {
        return this->window->isOpen();
    }
    void updateMousePos()
    {
        this->mousePosW = sf::Mouse::getPosition(*this->window);
    }
    void updateLoadingProcess(int totalElements, int i)
    {
        this->process = (int)(((float)i / totalElements) * 100);
    }
    void updatePathToFile()
    {
        this->textPath.setString(pathToFile);
    }
    void updateLoadingRecs(float process)
    {
        std::string persent = std::to_string((int)(process * 100));
        persent.append("%");
        this->doneProcent.setString(persent);
        if (this->loadingRecs.size() < 31 && (float)(this->loadingRecs.size()) * (100.f / 31.f) < process * 100.f)
            this->createLoadingRec();
    }
    void createLoadingRec()
    {
        float xPos = 22.f + loadingRecs.size() * 12.f;
        float yPos = 96.f;
        this->loadingRec.setPosition(xPos, yPos);
        this->loadingRec.setFillColor(sf::Color::Blue);

        this->loadingRecs.push_back(this->loadingRec);
    }
    void update()
    {
        pollEvents();

        updateMousePos();

        updatePathToFile();

        updateLoadingRecs(process);

    }
    void renderBlocks()
    {
        this->window->draw(pathRec);
        this->window->draw(buttonRec);
        this->window->draw(loadRec);
        this->window->draw(textButton);
        this->window->draw(doneProcent);
        this->window->draw(textPath);
        this->window->draw(chooseTriangle);
        this->window->draw(thButton);
        this->window->draw(thText);
        this->window->draw(randomIntRec);
        this->window->draw(randomInt);
        for (auto e : this->loadingRecs)
            this->window->draw(e);
    }
    void render()
    {
        window->clear(sf::Color(212, 208, 200, 255));
        renderBlocks();
        window->display();
        // std::cout << "x: " << mousePosW.x << " " << "y: " << mousePosW.y << "\n";

    }
    std::string OpenFileDialog()
    {
        std::string filePath;

        OPENFILENAME ofn = { 0 };
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrTitle = TEXT("Select a file");
        ofn.lpstrFilter = TEXT("All files (*.*)\0*.*\0");
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

        TCHAR fileName[MAX_PATH] = { 0 };
        ofn.lpstrFile = fileName;
        ofn.nMaxFile = MAX_PATH;

        if (GetOpenFileName(&ofn))
        {
            filePath = (std::string)fileName;
        }
        std::string::difference_type ab = std::count(filePath.begin(), filePath.end(), '\\');
        int pos = 0;
        pos = filePath.find('\\');
        while (ab != 0)
        {
            filePath.insert(pos, "\\");
            ab--;
            pos = filePath.find('\\', pos + 2);

        }
        return filePath;
    }
};



int main()
{
    srand(time(NULL));
    Windo window;
    sf::Event ev;
    while (window.isOpen())
    {
        window.update();


        window.render();
    }
    /*  std::string path = OpenFileDialog();
      std::cout << path;
      FileRead file(path);*/


}