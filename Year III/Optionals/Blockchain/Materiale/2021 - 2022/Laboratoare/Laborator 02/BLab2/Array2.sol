// SPDX-License-Identifier: MIT
pragma solidity ^0.8.10;

contract StergeElementVectorPrinShiftare
{
    // [1, 2, 3] -- remove(1) --> [1, 3, 3] --> [1, 3]
    // [1, 2, 3, 4, 5, 6] -- remove(2) --> [1, 2, 4, 5, 6, 6] --> [1, 2, 4, 5, 6]
    // [1, 2, 3, 4, 5, 6] -- remove(0) --> [2, 3, 4, 5, 6, 6] --> [2, 3, 4, 5, 6]
    // [1] -- remove(0) --> [1] --> []

    uint[] public vector;

    function sterge(uint indexV) public 
    {
        require(indexV < vector.length, "indexul se afla in afara limitelor");

        for (uint poz = indexV; poz < vector.length - 1; poz++) 
        {
            vector[poz] = vector[poz + 1];
        }
        //** stergem
        vector.pop();
    }

    function testare() external 
    {
        vector = [1, 2, 3, 4, 5];
        
       
        assert(vector[0] == 1);
        assert(vector[1] == 2);
        assert(vector[2] == 4);
        assert(vector[3] == 5);
        assert(vector.length == 4);

        vector = [1];        
        
        assert(vector.length == 0);
    }
}