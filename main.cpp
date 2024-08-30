
#include<iostream>
#include<cstdio>
#include<fstream>
#include<sstream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include<windows.h>
#include<mysql_connection.h>
#include<cppconn/driver.h>
#include<cppconn/exception.h>
#include<cppconn/prepared_statement.h>
#include<limits> 

using namespace std;
using namespace sql;

// Global Variable
//int qstate;
//MYSQL* conn;
//MYSQL_ROW row;
//MYSQL_RES* res;
sql::Connection* conn;
// Global Variable End
Driver* driver;
//Connection* conn;
PreparedStatement* pstmt;
ResultSet* res;

class db_response
{
public:
    static void ConnectionFunction()
    {
        try
        {
            sql::Driver* driver = get_driver_instance();
            conn = driver->connect("localhost:3306", "root", "0123456789777"); // Adjust as needed for your database
            conn->setSchema("cpp_musicstore_db");

            cout << "Database Connected To MySQL" << endl;
            cout << "Press any key to continue..." << endl;
            cin.get(); // Replace getch() with cin.get() for portability
            system("cls");
        }
        catch (sql::SQLException& e)
        {
            cout << "Failed To Connect! Error: " << e.what() << endl;
        }
    }
};

void AddNewItemInDatabase();
void ShowAllItems();
void ItemInStock();
void FindMusic();
void EditItem();
void RemoveItem();
void CreateOrder();
void SoldItems();

int main()
{
    // Initial Load
    system("cls");
    system("title Music Store Management Program");
    system("color 0f");
    // Initial Load End

    // Call Methods
    db_response::ConnectionFunction();
    // Call Methods End

    // Variables
    int chooseOneFromMenu = 0;
    char exitSurity;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Music Store Menu" << endl;
    cout << "1. Create Order." << endl;
    cout << "2. Find Music." << endl;
    cout << "3. Sold Items." << endl;
    cout << "4. Item in Stock." << endl;
    cout << "5. All Items." << endl;
    cout << "6. Add New Item." << endl;
    cout << "7. Edit Item." << endl;
    cout << "8. Remove Item." << endl;
    cout << "9. Exit." << endl;
    cout << "Choose One: ";
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        CreateOrder();
        break;
    case 2:
        FindMusic();
        break;
    case 3:
        SoldItems();
        break;
    case 4:
        ItemInStock();
        break;
    case 5:
        ShowAllItems();
        break;
    case 6:
        AddNewItemInDatabase();
        break;
    case 7:
        EditItem();
        break;
    case 8:
        RemoveItem();
        break;
    case 9:
    ExitProgram:
        cout << "Program terminating. Are you sure? (y/N): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y') {
            return 0;
        }
        else if (exitSurity == 'n' || exitSurity == 'N') {
            system("cls");
            main();
        }
        else {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 9. Press Enter To Continue...";
        cin.get();
        system("cls");
        main();
        break;
    }
    return 0;
}

// Music Store Manangement System in C++ Design and Developed by Code With C.com
void ShowAllItems()
{
    system("cls");

    // Variables
    char choose;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Show All Items Menu" << endl << endl;

    try
    {
        // Prepare the SQL statement
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM musicinfo_tb"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        // Fetch and display the results
        while (res->next())
        {
            cout << "ID: " << res->getInt("id")
                << "\nCategory: " << res->getString("category")
                << "\nType: " << res->getString("type")
                << "\nName: " << res->getString("name")
                << "\nArtist: " << res->getString("artist")
                << "\nPrice: " << res->getDouble("price")
                << "\nQuantity: " << res->getInt("quantity") << endl << endl;
        }
    }
    catch (sql::SQLException& e)
    {
        cout << "Query Execution Problem! Error: " << e.what() << endl;
    }

    // Exit Code
    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}

// Music Store Manangement System in C++ Design and Developed by CodeWithC.com
void AddNewItemInDatabase()
{
    // Initial Load
    system("cls");
    // Initial Load End

    // Variables
    string category;
    string type;
    string name;
    string artist;
    float price = 0.0;
    int quantity = 0;
    char choose;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Add New Item Menu" << endl << endl;

    cin.ignore(1, '\n');
    cout << "Enter Category: ";
    getline(cin, category);
    cout << "Enter Type: ";
    getline(cin, type);
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Artist: ";
    getline(cin, artist);
    cout << "Enter Price: ";
    cin >> price;
    cout << "Enter Quantity: ";
    cin >> quantity;

    try
    {
        // Prepare the SQL insert statement
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "INSERT INTO musicinfo_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) VALUES (?, ?, ?, ?, ?, ?)"));

        // Bind parameters to the statement
        pstmt->setString(1, category);
        pstmt->setString(2, type);
        pstmt->setString(3, name);
        pstmt->setString(4, artist);
        pstmt->setDouble(5, price);
        pstmt->setInt(6, quantity);

        // Execute the statement
        pstmt->executeUpdate();

        cout << endl << "Successfully added to the database." << endl;
    }
    catch (sql::SQLException& e)
    {
        cout << "Query Execution Problem! Error: " << e.what() << endl;
    }

    // Exit Code
    cout << "Press 'm' to Menu and 'a' to Insert Again Or Any Other key to exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'a' || choose == 'A')
    {
        AddNewItemInDatabase();
    }
    else
    {
        exit(0);
    }
}

// Music Store Manangement System in C++ Design and Developed by CodeWithC.com
void ItemInStock()
{
    system("cls");

    // Variables
    char choose;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Items In Stock Menu" << endl << endl;

    try
    {
        // Prepare the SQL select statement
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
            "SELECT m_name, m_artist, m_price, m_quantity FROM musicinfo_tb"));

        // Execute the query
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        // Iterate through the result set
        while (res->next())
        {
            int quantity = res->getInt("m_quantity");
            if (quantity > 0)
            {
                cout << "Name: " << res->getString("m_name") << "\nArtist: " << res->getString("m_artist") << "\nPrice: " << res->getDouble("m_price") << "\nQuantity: " << quantity << endl << endl;
            }
        }
    }
    catch (sql::SQLException& e)
    {
        cout << "Query Execution Problem! Error: " << e.what() << endl;
    }

    // Exit Code
    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}


void FindMusic()
{
    system("cls");

    // Variables
    char choose;
    string input;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Find Music Menu" << endl << endl;

    cout << "Find by \n1. Name\n2. Category\n3. Type\n4. Artist\nAny other number to Menu" << endl;
    cout << "Choose One: "; cin >> choose;
    system("cls");

    cin.ignore(1, '\n');

    string query;
    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt;

        if (choose == '1')
        {
            cout << "Enter Name: "; getline(cin, input);
            query = "SELECT * FROM musicinfo_tb WHERE m_name LIKE ?";
        }
        else if (choose == '2')
        {
            cout << "Enter Category: "; getline(cin, input);
            query = "SELECT * FROM musicinfo_tb WHERE m_category LIKE ?";
        }
        else if (choose == '3')
        {
            cout << "Enter Type: "; getline(cin, input);
            query = "SELECT * FROM musicinfo_tb WHERE m_type LIKE ?";
        }
        else if (choose == '4')
        {
            cout << "Enter Artist: "; getline(cin, input);
            query = "SELECT * FROM musicinfo_tb WHERE m_artist LIKE ?";
        }
        else
        {
            goto ExitMenu;
        }

        // Prepare the query and bind the input parameter
        pstmt.reset(conn->prepareStatement(query));
        pstmt->setString(1, input + "%");

        // Execute the query
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        // Display results
        while (res->next())
        {
            cout << "ID: " << res->getInt("id") << "\nCategory: " << res->getString("m_category")
                << "\nType: " << res->getString("m_type") << "\nName: " << res->getString("m_name")
                << "\nArtist: " << res->getString("m_artist") << "\nPrice: " << res->getDouble("m_price")
                << "\nQuantity: " << res->getInt("m_quantity") << endl << endl;
        }
    }
    catch (sql::SQLException& e)
    {
        cout << "Query Execution Problem! Error: " << e.what() << endl;
    }

ExitMenu:
    cout << "Press 'm' to Menu, 'a' to Search again and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'a' || choose == 'A')
    {
        FindMusic();
    }
    else
    {
        exit(0);
    }
}


void EditItem()
{
    system("cls");

    // Variables
    string category = "";
    string type = "";
    string name = "";
    string artist = "";
    string items[5000];
    string price = "";
    string quantity = "";
    char choose;
    int itemId;
    bool HaveException = false;
    bool NotInDatabase = true;
    int indexForId = 0;

    // Store Variables
    string storeid = "";
    string storecategory = "";
    string storetype = "";
    string storename = "";
    string storeartist = "";
    string storeprice = "";
    string storequantity = "";
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Edit Item Menu" << endl << endl;

    // Fetch all items
    try
    {
        std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT m_id, m_name FROM musicinfo_tb"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        cout << "ID\tName\n" << endl;
        while (res->next())
        {
            cout << res->getInt("m_id") << "\t" << res->getString("m_name") << endl;
            items[indexForId] = to_string(res->getInt("m_id"));
            indexForId++;
        }
    }
    catch (sql::SQLException& e)
    {
        cout << "Query Execution Problem! Error: " << e.what() << endl;
        return;
    }

    // Input Item ID
    try
    {
        cout << endl;
        cout << "Enter Item ID: ";
        cin >> itemId;
        cout << endl;
    }
    catch (exception& e)
    {
        cout << "Please Enter a valid NUMBER." << endl;
        cout << "Exception: " << e.what() << endl;
        HaveException = true;
        goto ExitMenu;
    }

    if (!HaveException)
    {
        stringstream streamid;
        streamid << itemId;
        string strid = streamid.str();

        for (int i = 0; i < indexForId; i++)
        {
            if (strid == items[i])
            {
                NotInDatabase = false;
                break;
            }
        }

        if (!NotInDatabase)
        {
            // Fetch item details by ID
            try
            {
                std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement("SELECT * FROM musicinfo_tb WHERE m_id = ?"));
                pstmt->setInt(1, itemId);
                std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

                if (res->next())
                {
                    cout << "ID: " << res->getInt("m_id")
                        << "\nCategory: " << res->getString("m_category")
                        << "\nType: " << res->getString("m_type")
                        << "\nName: " << res->getString("m_name")
                        << "\nArtist: " << res->getString("m_artist")
                        << "\nPrice: " << res->getString("m_price")
                        << "\nQuantity: " << res->getInt("m_quantity") << endl << endl;

                    storeid = to_string(res->getInt("m_id"));
                    storecategory = res->getString("m_category");
                    storetype = res->getString("m_type");
                    storename = res->getString("m_name");
                    storeartist = res->getString("m_artist");
                    storeprice = res->getString("m_price");
                    storequantity = to_string(res->getInt("m_quantity"));
                }
            }
            catch (sql::SQLException& e)
            {
                cout << "Query Execution Problem! Error: " << e.what() << endl;
                return;
            }

            // Input new details or keep the old ones
            cin.ignore(1, '\n');
            cout << "Enter Category (xN to not change): ";
            getline(cin, category);
            if (category == "xN") category = storecategory;

            cout << "Enter Type (xN to not change): ";
            getline(cin, type);
            if (type == "xN") type = storetype;

            cout << "Enter Name (xN to not change): ";
            getline(cin, name);
            if (name == "xN") name = storename;

            cout << "Enter Artist (xN to not change): ";
            getline(cin, artist);
            if (artist == "xN") artist = storeartist;

            cout << "Enter Price (xN to not change): ";
            cin >> price;
            if (price == "xN") price = storeprice;

            cout << "Enter Quantity (xN to not change): ";
            cin >> quantity;
            if (quantity == "xN") quantity = storequantity;

            // Update the item in the database
            try
            {
                std::unique_ptr<sql::PreparedStatement> pstmt(conn->prepareStatement(
                    "UPDATE musicinfo_tb SET m_category = ?, m_type = ?, m_name = ?, m_artist = ?, m_price = ?, m_quantity = ? WHERE m_id = ?"));
                pstmt->setString(1, category);
                pstmt->setString(2, type);
                pstmt->setString(3, name);
                pstmt->setString(4, artist);
                pstmt->setString(5, price);
                pstmt->setInt(6, stoi(quantity));
                pstmt->setInt(7, itemId);

                pstmt->executeUpdate();

                cout << endl << "Successfully Updated In Database." << endl;
            }
            catch (sql::SQLException& e)
            {
                cout << "Failed To Update! Error: " << e.what() << endl;
            }
        }
        else
        {
            cout << "Item Not Found in database." << endl;
        }
    }

ExitMenu:
    cout << "Press 'm' to Menu, 'e' to edit another item and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else if (choose == 'e' || choose == 'E')
    {
        EditItem();
    }
    else
    {
        exit(0);
    }
}

// Music Store Manangement System in C++ Design and Developed by CodeWithC.com

void RemoveItem() {
    system("cls");

    // Variables
    char choose;
    int itemId;
    vector<string> items;
    bool NotInDatabase = true; // Initialize NotInDatabase to true

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Remove Item Menu" << endl << endl;

    try {
        sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT m_id, m_name FROM musicinfo_tb");
        sql::ResultSet* res = pstmt->executeQuery();

        cout << "ID\tName\n" << endl;
        while (res->next()) {
            cout << res->getString("m_id") << "\t" << res->getString("m_name") << endl;
            items.push_back(res->getString("m_id"));
        }
        delete pstmt;
        delete res;
    }
    catch (sql::SQLException& e) {
        cout << "Query Execution Problem! Error: " << e.what() << endl;
        return;
    }

    cout << endl;
    cout << "Enter Item ID: ";
    try {
        cin >> itemId;
        if (cin.fail()) {
            throw invalid_argument("Invalid input");
        }
    }
    catch (const exception& e) {
        cout << "Please enter a valid NUMBER." << endl;
        cin.clear(); // Clear the error flag
        //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        return;
    }

    stringstream streamid;
    string strid;
    streamid << itemId;
    streamid >> strid;

    NotInDatabase = find(items.begin(), items.end(), strid) == items.end();

    if (!NotInDatabase) {
        try {
            sql::PreparedStatement* pstmt = conn->prepareStatement("DELETE FROM musicinfo_tb WHERE m_id = ?");
            pstmt->setString(1, strid);
            pstmt->executeUpdate();

            cout << "Successfully Deleted From Database." << endl;
            delete pstmt;
        }
        catch (sql::SQLException& e) {
            cout << "Failed To Delete! Error: " << e.what() << endl;
        }
    }
    else {
        cout << "Item Not Found in database." << endl;
    }

    // Exit Code
    cout << "Press 'm' to Menu, 'd' to delete another item, or any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        // Call the main menu function (assuming it exists)
        main();
    }
    else if (choose == 'd' || choose == 'D') {
        RemoveItem();
    }
    else {
        exit(0);
    }
}


// Music Store Manangement System in C++ Design and Developed by CodeWithC.com
void CreateOrder()
{
    system("cls");

    // Variables
    char choose;
    vector<string> itemId;
    char chooseEditOrBuy;
    float totalPrice = 0.0;
    bool purchase = false;

    vector<string> storeId;
    vector<string> storeCategory;
    vector<string> storeType;
    vector<string> storeName;
    vector<string> storeArtist;
    vector<string> storePrice;
    vector<string> storeQuantity;

    // Database connection
    sql::Driver* driver;
    //sql::Connection* conn;

    try
    {
        //driver = get_driver_instance();
        //conn = driver->connect("tcp://127.0.0.1:3306", "user", "password"); // Adjust as needed
        //conn->setSchema("your_database");

        // Retrieve items from the database
        sql::PreparedStatement* pstmt = conn->prepareStatement("SELECT * FROM musicinfo_tb WHERE m_quantity > 0");
        sql::ResultSet* res = pstmt->executeQuery();
        while (res->next())
        {
            cout << "ID: " << res->getString("m_id") << "\nCategory: " << res->getString("m_category")
                << "\nType: " << res->getString("m_type") << "\nName: " << res->getString("m_name")
                << "\nArtist: " << res->getString("m_artist") << "\nPrice: " << res->getString("m_price")
                << "\nQuantity: " << res->getString("m_quantity") << endl << endl;

            storeId.push_back(res->getString("m_id"));
            storeCategory.push_back(res->getString("m_category"));
            storeType.push_back(res->getString("m_type"));
            storeName.push_back(res->getString("m_name"));
            storeArtist.push_back(res->getString("m_artist"));
            storePrice.push_back(res->getString("m_price"));
            storeQuantity.push_back(res->getString("m_quantity"));
        }
        delete pstmt;
        delete res;

        // User selection of items
        while (true)
        {
            cout << "Enter a Music ID (q to exit): ";
            string getId;
            cin >> getId;
            if (getId == "q")
                break;

            if (find(storeId.begin(), storeId.end(), getId) != storeId.end())
            {
                itemId.push_back(getId);
            }
            else
            {
                cout << "Enter a valid ID." << endl;
            }
        }

        // Display selected items
        cout << "You chose these song IDs: ";
        for (const auto& id : itemId)
        {
            cout << id << " ";
        }
        cout << endl;

    CHOOSEEDITORBUY:
        cout << "Do you want to edit items (e) or buy these items (b): ";
        cin >> chooseEditOrBuy;

        if (chooseEditOrBuy == 'e')
        {
            while (true)
            {
                cout << "Remove item ID (q to exit): ";
                string getId;
                cin >> getId;
                if (getId == "q")
                    break;

                auto it = std::remove(itemId.begin(), itemId.end(), getId);
                if (it != itemId.end())
                {
                    itemId.erase(it, itemId.end());
                }
                else
                {
                    cout << "ID not found in your selection." << endl;
                }
            }

            // Display selected items
            cout << "You chose these song IDs: ";
            for (const auto& id : itemId)
            {
                cout << id << " ";
            }
            cout << endl;

            goto CHOOSEEDITORBUY;
        }
        else if (chooseEditOrBuy == 'b')
        {
            sql::PreparedStatement* pstmt;
            for (const auto& id : itemId)
            {
                auto it = std::find(storeId.begin(), storeId.end(), id);
                if (it != storeId.end())
                {
                    size_t j = std::distance(storeId.begin(), it);
                    int quantity = std::stoi(storeQuantity[j]);

                    if (quantity > 0)
                    {
                        // Insert into solditem_tb
                        pstmt = conn->prepareStatement("INSERT INTO solditem_tb (m_category, m_type, m_name, m_artist, m_price, m_quantity) VALUES (?, ?, ?, ?, ?, ?)");
                        pstmt->setString(1, storeCategory[j]);
                        pstmt->setString(2, storeType[j]);
                        pstmt->setString(3, storeName[j]);
                        pstmt->setString(4, storeArtist[j]);
                        pstmt->setString(5, storePrice[j]);
                        pstmt->setInt(6, 1); // Quantity bought is 1
                        if (pstmt->executeUpdate())
                        {
                            purchase = true;
                        }
                        else
                        {
                            cout << "Failed to execute INSERT query." << endl;
                            delete pstmt;
                            throw sql::SQLException(); // Optional: You can throw an exception to exit gracefully
                        }
                        delete pstmt;

                        // Update musicinfo_tb
                        quantity--;
                        pstmt = conn->prepareStatement("UPDATE musicinfo_tb SET m_quantity = ? WHERE m_id = ?");
                        pstmt->setInt(1, quantity);
                        pstmt->setString(2, storeId[j]);
                        if (pstmt->executeUpdate())
                        {
                            totalPrice += std::stof(storePrice[j]);
                        }
                        else
                        {
                            cout << "Failed to execute UPDATE query." << endl;
                            delete pstmt;
                            throw sql::SQLException(); // Optional: You can throw an exception to exit gracefully
                        }
                        delete pstmt;
                    }
                }
            }

            if (purchase)
            {
                cout << endl << "Purchase Successfully Done." << endl;
                cout << "Total Price: " << totalPrice << endl;
            }
        }

        // Cleanup
        delete conn;

    }
    catch (sql::SQLException& e)
    {
        cout << "SQLException: " << e.what() << endl;
    }
    catch (std::exception& e)
    {
        cout << "Exception: " << e.what() << endl;
    }

    // Exit Code
    cout << endl << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M')
    {
        main();
    }
    else
    {
        exit(0);
    }
}


// Music Store Manangement System in C++ Design and Developed by CodeWithC.com
void SoldItems() {
    system("cls");

    // Variables
    char choose;
    // Variables End

    cout << "Welcome To Music Store" << endl << endl;
    cout << "Sold Items Menu" << endl << endl;

    try {
        pstmt = conn->prepareStatement("SELECT m_name, m_artist, m_category, m_type, m_price, SUM(m_quantity) FROM solditem_tb GROUP BY m_name");
        res = pstmt->executeQuery();

        while (res->next()) {
            cout << "Name: " << res->getString("m_name") << "\nArtist: " << res->getString("m_artist") << "\nCategory: " << res->getString("m_category") << "\nType: " << res->getString("m_type") << "\nPrice: " << res->getString("m_price") << "\nQuantity: " << res->getString("SUM(m_quantity)") << endl << endl;
        }
    }
    catch (SQLException& e) {
        cout << "Query Execution Problem! Error: " << e.what() << endl;
    }

    // Exit Code
    cout << "Press 'm' to Menu and any other key to Exit: ";
    cin >> choose;
    if (choose == 'm' || choose == 'M') {
        // Call the main menu function (assuming it exists)
        // mainMenu();
    }
    else {
        exit(0);
    }
}

