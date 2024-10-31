#include <iostream>
#include <vector>

int main()
{
	std::vector<std::vector<char>> test;
	for(int y = 0; y < 10; y++)
	{
		test.push_back(std::vector<char>());
		for(int x = 0; x < 5; x++)
		{
			test[y].push_back('X');
		}
	}
/*
#include <iostream>
#include <vector>

int main(){
    std::vector<std::vector<int>>MyVector;
    std::vector<int>temp;

    temp.push_back(1);
    temp.push_back(2);
    temp.push_back(3);
    MyVector.push_back(temp);

    std::cout << "Rows in the 2d vector: " << MyVector.size() <<
    std::endl << "Collumns in the 1st row: " << MyVector[0].size() <<
    std::endl;

    system("pause");
    return 0;
}
*/

	std::cout << test.size() << std::endl;
	std::cout << test[0].size() << std::endl;
	for(int y = 0; y < 10; y++)
	{
		for(int x = 0; x < 5; x++)
		{
			std::cout << test[y][x];
		}
		std::cout << std::endl;
	}
}
