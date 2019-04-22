//
//  main.cpp
//
//  Test file for the database class
//
//  Created by Behnam Dezfouli
//

#include "database.h"

using namespace coen79_lab7;

int main(int argc, const char * argv[]) {
    
    std::cout << "\nTesting constructor...!\n";
    database myDB1;
    std::cout << "\nInserting company names...!\n";
    myDB1.insert_company("Intel");
    myDB1.insert_company("NVIDIA");
    myDB1.insert_company("Cypress");

    std::cout << "\nPrinting myDB1...\n";
    myDB1.print_companies();


    std::cout << "\nInserting company names to invoke reserve...!\n";
    myDB1.insert_item("Intel", "Core i7", 300.0);
    myDB1.insert_item("Intel", "Core i5", 200.0);
    std::cout << "\nPrinting myDB1...\n";
    myDB1.print_items_by_company("Intel");


    std::cout << "\nInserting company names to invoke reserve...!\n";

    myDB1.insert_company("Qualcomm");
    myDB1.insert_company("Apple");
    
    std::cout << "\nInserting product names...!\n";
    myDB1.insert_item("Apple", "iPhone 6", 400.0);
    myDB1.insert_item("Apple", "iPhone X", 900.0);
    std::cout << "\nPrinting products of Apple and Intel...\n";
    myDB1.print_items_by_company("Apple");
    myDB1.print_items_by_company("Intel");

    
    std::cout << "\nCreating myDB2 on heap...\n";
    database *myDB2 = new database();
    myDB2->insert_company("Google");
    myDB2->insert_item("Google", "glass", 1000.0);
    myDB2->insert_item("Google", "phone", 1000.0);
    myDB2->insert_item("Google", "Android", 0.0);
    myDB2->insert_item("Google", "TensorFlow", 0.0);
    myDB2->erase_item("Google", "phone");
    std::cout << "\nPrinting myDB2...\n";
    myDB2->print_items_by_company("Google");

    
    std::cout << "\nCreating myDB3 on heap...\n";
    database *myDB3 = new database();
    std::cout << "\nAssigning myDB2 to myDB3...\n";
    *myDB3 = *myDB2;
    std::cout << "\nPrinting myDB3...\n";
    myDB3->print_items_by_company("Google");

    
    myDB2->erase_company("Google");
    std::cout << "\nPrinting myDB2...\n";
    myDB2->print_items_by_company("Google");
    std::cout << "\nPrinting myDB3...\n";
    myDB3->print_items_by_company("Google");

    
    std::cout << "\nDeleting myDB2 and myDB3...\n";
    delete myDB2;
    delete myDB3;

    
    return 0;
}
