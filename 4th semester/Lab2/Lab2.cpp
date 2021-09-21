#include <stdexcept>
#include "list_class.h"
#include "tree.h"

#include <iostream>
using namespace std;

int main()
{
    List charFrequencyTable;
    char tmp;
    size_t newWeight = 0;
    size_t index = 0;
    unsigned cypheredSize = 0;
    unsigned originalSize = 0;
    cout << "Please enter your message:" << endl;
    cin.unsetf(std::ios::skipws);

    while (!cin.bad())
    {
        cin >> tmp;
        if (tmp == '\n') { break; }
        index = charFrequencyTable.find(tmp);
        
        if (index != 0) // such character has already ocurred
        {
            newWeight = charFrequencyTable.weightAt(index) + 1;
            charFrequencyTable.setWeight(index, newWeight);
            originalSize++;
        }
        else // first occurence of such character
        {
            charFrequencyTable.push_back(tmp, 1);
            originalSize++;
        }
    }

    if (!charFrequencyTable.isEmpty()) 
    {
        List treeConstructionBase;
        treeConstructionBase.copy(charFrequencyTable);

        while (treeConstructionBase.get_size() > 1)
        {
            treeConstructionBase.minPair();
        }

        Tree codeTree(treeConstructionBase.get_head());
        codeTree.setCodes(&charFrequencyTable);
        
        cypheredSize = charFrequencyTable.print_to_console();

        cout << "Cyphered size: " << cypheredSize << endl << "Initial size: " << originalSize << "Compression ratio: " << originalSize/cypheredSize << endl;
    }
    else
    {
        cout << "Error: entered file is empty";
        return 0;
    }
    return 1;
}