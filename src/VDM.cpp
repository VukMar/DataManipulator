#include "../include/VDM.hpp"

int main()
{
    //Create an SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "FDM - Data Manipulator", sf::Style::Close);

    //Set the window's vertical sync enabled
    window.setVerticalSyncEnabled(true);

    //Set up the OPENFILENAME structure
    char cwd[MAX_PATH];
    if(_getcwd(cwd, sizeof(cwd)) == NULL)
    {
        std::cout << "Directory load ERROR - Program FAILED!\n";
        return 1;
    }
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = new TCHAR[MAX_PATH];
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = TEXT("All Files (*.*)\0*.*\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = cwd;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    //Cyber font file created by this data manipulator, that contains font data.
    CyberFont cf;
    std::vector<unsigned char> fontdata = cf.read();
    
    //Open file button
    vui::Button openfile;
    if(openfile.loadFontFromMemory(fontdata))
        openfile.create("OPEN FILE", 30, sf::Vector2f(300,40), sf::Vector2f(50,200), sf::Color::Red, sf::Color::Blue);

    //Create header button
    vui::Button createHeader;
    if(createHeader.loadFontFromMemory(fontdata))
        createHeader.create("CREATE HEADER", 30, sf::Vector2f(300,40), sf::Vector2f(50,510), sf::Color::Red, sf::Color::Blue);

    //Crate BIN button
    vui::Button createBIN;
    if(createBIN.loadFontFromMemory(fontdata))
        createBIN.create("CREATE BIN", 30, sf::Vector2f(300,40), sf::Vector2f(460,510), sf::Color::Red, sf::Color::Blue);
    
    //Setting up text box that displays file pathh
    vui::TextBox FilePathDisplay;
    if(FilePathDisplay.setFontFromMemory(fontdata))
    {
        FilePathDisplay.create(sf::Vector2f(700,60), sf::Vector2f(50,260), 15);
        FilePathDisplay.MultiLine = true;
        FilePathDisplay.Scrollable = false;
        FilePathDisplay.changeTextFillColor(sf::Color::Black);
    }
    else
    {
        std::cout << "Font for textbox failed!\n";
    }
    
    //Seting up file input box
    vui::TextBox FileNameInput;
    if(FileNameInput.setFontFromMemory(fontdata))
    {
        FileNameInput.create(sf::Vector2f(700,30), sf::Vector2f(50,430), 20);
        FileNameInput.MultiLine = true;
        FileNameInput.Scrollable = false;
        FileNameInput.changeTextFillColor(sf::Color::Black);
    }
    else
    {
        std::cout << "Font for textbox failed!\n";
    }
    
    //Font loaded from memory to be used for text display
    sf::Font font;
    font.loadFromMemory(fontdata.data(), fontdata.size());

    //Text  that idicated if file is loaded
    sf::Text LoadIndicatior;
    LoadIndicatior.setCharacterSize(30);
    LoadIndicatior.setFont(font);
    LoadIndicatior.setPosition(360.f,200.f);

    //Text to title
    sf::Text Title;
    Title.setCharacterSize(60);
    Title.setFont(font);
    Title.setString("DATA MANIPULATOR");
    sf::FloatRect fr = Title.getGlobalBounds();
    Title.setOrigin(fr.width/2+fr.left, 0);
    Title.setPosition(400.f,50.f);


    bool fileLoaded = false;
    std::string OpenedFile;
    std::string filePathToDisplay;
    std::vector<unsigned char> data;
    std::string fileName;
    // Run the main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(FileNameInput.isActive(window))
                FileNameInput.typeOn(event);
        }
        if(openfile.isButtonPressed(window))
        {
            // Show the open file dialog
            if(GetOpenFileName(&ofn) == TRUE)
            {
                // Get the selected file path
                OpenedFile = ofn.lpstrFile;
                data = vui::FDM.readData(OpenedFile);
                ofn.lpstrInitialDir = cwd;
                fileLoaded = true;
                delete[] ofn.lpstrFile;
            }
            else //If file loding is canceled any previously loaded file will be cleared
            {
                if(!OpenedFile.empty())
                {
                    OpenedFile.clear();
                }
                fileLoaded = false;
                ofn.lpstrInitialDir = cwd;
                
            }
        }
        
        //Bool values that tell the program which option is chosen
        //Values will be reset on next loop iteration
        bool toCreateBIN = createBIN.isButtonPressed(window);
        bool toCreateHeader = createHeader.isButtonPressed(window);
        
        //Update text that indicated file opened
        if(fileLoaded)
        {
            LoadIndicatior.setFillColor(sf::Color::Green);
            LoadIndicatior.setString("File LOADED!");
        } 
        else
        {
            LoadIndicatior.setFillColor(sf::Color::Red);
            LoadIndicatior.setString("File NOT LOADED!");
        }

        if(filePathToDisplay != OpenedFile)
        {
            filePathToDisplay = OpenedFile;
            FilePathDisplay.displayText(filePathToDisplay);
        }
        
        //Create a file based on option
        if(toCreateHeader || toCreateBIN)
        {
            fileName = FileNameInput.getText();
            if(!fileName.empty())
            {
                //Make youre the file is being created in the directory of the program
                _chdir(cwd);
                if(toCreateBIN)
                {
                    CreateDirectory("BIN/", NULL); //BIN file creation
                    vui::FDM.createBIN(fileName, data);
                }
                else
                {
                    CreateDirectory("Headers/", NULL); //Header file creation
                    vui::FDM.createHexDataHeader(fileName, data);
                }
                fileLoaded = false;
                data.clear();
                OpenedFile.clear();
                fileName.clear();
                FileNameInput.clear();
            }
        }

        //Clear the window
        window.clear();

        //Draw the window content...
        window.draw(Title);
        openfile.displayTo(window);
        FilePathDisplay.displayTo(window);
        window.draw(LoadIndicatior);
        FileNameInput.displayTo(window);
        createHeader.displayTo(window);
        createBIN.displayTo(window);
        
        //Display the window
        window.display();
    }

    return 0;
}