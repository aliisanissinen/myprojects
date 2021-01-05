// Shopping
// TIE-02201 Ohjelmointi 2: Perusteet / TIE-02207 Programming 2: Basics
//
// Program author
// Name: Aliisa Nissinen
//
// Instructions:
// The program reads a file which containing the various shop chains,
// their stores, and their product selections. User can then search for
// different chains, different stores and see the store's product selections.
// User can also search for a place that sells the cheapest product.

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

double OUT_OF_STOCK = 0.00;


// Struct of products and their prices in chains store
struct Product {
    std::string nameProduct;
    double priceProduct;
};


// The function prints all products in the chains.
// Given parameters are the map that contains all chains and
// their stores and products.
// Return nothing.
void products(std::map<std::string, std::map
              <std::string, std::vector<Product>>> listShopsProducts)
{
    // All products are put in a vector.
    std::vector<std::string> allProducts;

    for (auto chain: listShopsProducts) {
        for (auto store : chain.second) {
            for (auto product : store.second) {
                std::vector<std::string>::iterator it =
                        find(allProducts.begin(), allProducts.end(),
                             product.nameProduct);
                if (it != allProducts.end()) {
                  continue;
                }
                else {
                    allProducts.push_back(product.nameProduct);
                }
            }
        }
    }

    sort(allProducts.begin(), allProducts.end());
    for (auto availableProduct : allProducts) {
        std::cout << availableProduct <<std::endl;
    }
}


// The function finds where you can buy the cheapest product.
// Given parameters are the map (contains all chains and their stores
// and products) and the wanted product.
// Return nothing.
void cheapest(std::map<std::string, std::map<std::string,
              std::vector<Product>>> listShopsProducts, std::string product)
{
    // The cheapest product is put in the pair structure, the first is the
    // price and the second is the vector that contains the chain and
    // the store. Initializing the pair with number -1.
    std::pair<double, std::vector<std::pair<std::string, std::string>>>
            cheapestWhere = {-1, {}};
    std::vector<std::pair<std::string, std::string>> vectorInside;
    bool findProduct = false;

    for (auto chain: listShopsProducts) {
        for (auto store : chain.second) {
            for (auto productFind : store.second) {
                if (productFind.nameProduct == product) {
                    findProduct = true;
                    if (productFind.priceProduct == OUT_OF_STOCK) {
                        continue;
                    }
                    else if (cheapestWhere.first == -1) {
                        vectorInside.push_back({chain.first, store.first});
                        cheapestWhere = {productFind.priceProduct,
                                         vectorInside};
                    }
                    else {
                        if (cheapestWhere.first > productFind.priceProduct) {
                            vectorInside.clear();
                            vectorInside.push_back({chain.first, store.first});
                            cheapestWhere = {productFind.priceProduct,
                                             vectorInside};
                        }
                        else if (cheapestWhere.first ==
                                 productFind.priceProduct) {
                            cheapestWhere.second.push_back(
                            {chain.first, store.first});
                        }
                    }
                }
            }
        }
    }

    // Prints price information of the wanted product
    if (not findProduct) {
        std::cout << "The product is not part of product selection"
                  <<std::endl;
    }
    else if (cheapestWhere.first == -1) {
        std::cout << "The product is temporarily out of stock everywhere"
                  <<std::endl;
    }
    else {
            std::cout << std::fixed << std::setprecision(2) <<
                         cheapestWhere.first << " euros" <<std::endl;
            for (auto where : cheapestWhere.second) {
                std::cout << where.first << " " << where.second <<std::endl;
            }
    }
}


// The function prints all products in the chain store.
// Given parameters are the map (contains all chains and their stores and products)
// and the wanted chain and the store.
// Return nothing.
void selection(std::map<std::string, std::map<std::string,
               std::vector<Product>>> listShopsProducts, std::string chain,
               std::string store)
{
    // All products are put in the map, the key is the name of product and
    // the value is the price. It helps with alphabetical order.
    std::map<std::string, double> allProductsInStore;
    bool findChain = false;
    bool findStore = false;

    for (auto chainFind : listShopsProducts) {
        if (chainFind.first == chain) {
            findChain = true;
            for (auto storeFind : chainFind.second) {
                if (storeFind.first == store) {
                    findStore =true;;
                    for (auto product : storeFind.second) {
                        allProductsInStore.insert(
                        {product.nameProduct, product.priceProduct});
                    }
                }
            }
        }
    }

    // If chain or store is not found
    if (not findChain) {
        std::cout << "Error: unknown chain name" <<std::endl;
    }
    else if (not findStore) {
        std::cout << "Error: unknown store" <<std::endl;
    }
    else {
        for (auto product : allProductsInStore) {
            std::cout << product.first;
            if (product.second == OUT_OF_STOCK) {
                std::cout << " out of stock"<<std::endl;
            }
            else {
                std::cout << " " << std::fixed << std::setprecision(2) <<
                         product.second <<std::endl;
            }
        }
    }
}


// The function prints all stores in alphabetical order.
// Given parameters are the map (contains all chains and their
// stores and products) and the wanted chain.
// Return nothing.
void storesInorder(std::map<std::string, std::map<std::string,
                   std::vector<Product>>> listShopsProducts, std::string chain)
{
    bool findChain = false;

    for (auto chainFind : listShopsProducts) {
        if (chainFind.first == chain) {
            findChain = true;
            for (auto store : chainFind.second) {
                std::cout << store.first <<std::endl;
            }
        }
    }

    // If chain is not found
    if (not findChain) {
        std::cout << "Error: unknown chain name" <<std::endl;
    }
}


// The function prints all chains in alphabetical order.
// Given parameter is the map that contains all chains and their stores and products.
// Return nothing.
void chainsInorder(std::map<std::string, std::map
                   <std::string, std::vector<Product>>> listShopsProducts)
{
    for (auto chain : listShopsProducts) {
        std::cout << chain.first <<std::endl;
    }
}


// The function splits the row, that is given from the other function.
// Given parameters are the row to split and the delimiter.
// Returns all factors inside the vector.
std::vector<std::string> split(std::string fileline, std::string delimiter)
{
    std::vector<std::string> fileComponents;

    while(fileline.find(delimiter) != std::string::npos) {
        std::string new_part = fileline.substr(0, fileline.find(delimiter));
        fileline = fileline.substr(fileline.find(delimiter)+1,fileline.size());
        if(not new_part.empty()) {
            fileComponents.push_back(new_part);
        }
    }
    if(not fileline.empty()) {
        fileComponents.push_back(fileline);
    }
    return fileComponents;
}


// The function reads the user's command and works according to it.
// Given parameter is the map that contains all chains and their stores
// and products.
// Returns false if the command is quit, otherwise true.
bool readCommand(std::map<std::string, std::map
                 <std::string, std::vector<Product>>> listShopsProducts)
{
    std::cout << "> ";
    std::string command;
    getline(std::cin, command);

    std::string delimiter = " ";
    std::vector<std::string> commandVector = split(command, delimiter);

    // All possible commands
    std::vector<std::string> Commands =
    {"quit", "chains", "stores", "selection", "cheapest", "products"};

    if (commandVector.at(0) == Commands.at(0) or
            commandVector.at(0) == Commands.at(1) or
            commandVector.at(0) == Commands.at(2) or
            commandVector.at(0) == Commands.at(3) or
            commandVector.at(0) == Commands.at(4) or
            commandVector.at(0) == Commands.at(5)) {

        if (commandVector.at(0) == Commands.at(0) and
                commandVector.size() == 1) {
            return false;
        }
        else if (commandVector.at(0) == Commands.at(1) and
                 commandVector.size() == 1) {
            chainsInorder(listShopsProducts);
            return true;
        }
        else if (commandVector.at(0) == Commands.at(2) and
                 commandVector.size() == 2) {
            storesInorder(listShopsProducts, commandVector.at(1));
            return true;
        }
        else if (commandVector.at(0) == Commands.at(3) and
                 commandVector.size() == 3) {
            selection(listShopsProducts, commandVector.at(1),
                      commandVector.at(2));
            return true;
        }
        else if (commandVector.at(0) == Commands.at(4) and
                 commandVector.size() == 2) {
            cheapest(listShopsProducts, commandVector.at(1));
            return true;
        }
        else if (commandVector.at(0) == Commands.at(5) and
                 commandVector.size() == 1) {
            products(listShopsProducts);
            return true;
        }
        else {
            std::cout << "Error: error in command " << commandVector.at(0)
                      <<std::endl;
        }
    }
    else {
        std::cout << "Error: unknown command: " << command <<std::endl;
    }
    return true;
}


// The function place all data from the input file (from readFile function)
// to the map structure, that contains another map inside.
// Given parameters are map structure and vector with data from the
// input file (from readFile function).
// Returns nothing, the map structure is editing directly to the readFile
// function.
void addMap(std::map<std::string, std::map<std::string, std::vector<Product>>>&
            shoppingList, std::vector<std::string> fileComponents)
{
    std::string chain = fileComponents.at(0);
    std::string store = fileComponents.at(1);
    std::string product = fileComponents.at(2);
    double price;
    if (fileComponents.at(3) == "out-of-stock" or
            fileComponents.at(3) == "OUT-OF-STOCK") {
        price = OUT_OF_STOCK;
    }
    else {
        price = stod(fileComponents.at(3));
    }

    // Helps with the map structure (inside map)
    std::vector<Product> vectorInside;
    vectorInside.push_back({product, price});
    bool ready = false;

    // Checks if the chain is in the map already
    if (shoppingList.find(chain) != shoppingList.end()) {
        // Checks if the store is in the map already
        if (shoppingList.at(chain).find(store) !=
                shoppingList.at(chain).end()) {
            // Checks if the product is on the map already, if so,
            // the price will be corrected.
            for (auto& allProducts : shoppingList.at(chain).at(store)) {
                if (allProducts.nameProduct == product) {
                    allProducts.priceProduct = price;
                    ready = true;
                    break;
                    }
            }
            if (not ready) {
                shoppingList.at(chain).at(store).push_back({product, price});
            }
        }
        else {
            shoppingList.at(chain).insert({store, vectorInside});
        }
    }

    // If the chain is new in the map
    else {
        std::map<std::string, std::vector<Product>> mapInside;
        mapInside.insert({store, vectorInside});
        shoppingList.insert({chain, mapInside});
    }
    }


// The function reads the input file, then uses another function to split
// the rows in the file and another function to place all the data
// in the map container.
// Returns the map, that contains the map inside (chains, stores and products).
std::map<std::string, std::map<std::string, std::vector<Product>>> readFile()
{
    std::map<std::string, std::map<std::string, std::vector<Product>>>
            shoppingList;

    std::cout << "Input file: ";
    std::string filename;
    getline(std::cin, filename);

    std::ifstream file(filename);

    if (not file) {
        std::cout << "Error: the input file cannot be opened" <<std::endl;
    }
    else {
        std::string row;
        while (getline(file, row)) {
            std::string delimiter = ";";
            std::vector<std::string> fileComponents = split(row, delimiter);

            // All rows must contain 4 factors, else program stops
            // in the main function
            if (fileComponents.size() != 4) {
                std::cout << "Error: the input file has an erroneous line"
                          <<std::endl;
                shoppingList.clear();
                return shoppingList;
            }

            addMap(shoppingList, fileComponents);
            fileComponents.clear();
        }
        file.close();
    }
    return shoppingList;
}


int main()
{
    std::map<std::string, std::map<std::string, std::vector<Product>>>
            listShopsProducts = readFile();

    // If something goes wrong, readFile returns an empty map. Program stops.
    if (listShopsProducts.empty()) {
        return EXIT_FAILURE;
    }

    // The while loop works until the user writes "quit" command.
    while (readCommand(listShopsProducts)) {
    }

    return EXIT_SUCCESS;
}

