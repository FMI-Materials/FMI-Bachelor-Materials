// SPDX-License-Identifier: MIT
pragma solidity ^0.8.10;

contract Array 
{
    //** moduri de inițializare a vectorilor
    uint[] public vector;
    uint[] public vector2 = [3, 12, 32];
    
    //** vectori cu dimensiune fixă, toate elementele 
    //** sunt inițializate cu 0
    uint[10] public myFixedSizeArr;

    function get(uint index) public view returns (uint) 
    {
        return vector[index];
    }
    
    //** Solidity returnează întregul vector.
    //** Această metodă ar trebui evitată pentru vectori
    //** care pot crește nedeterminat în lungime.
    function getVector() public view returns (uint[] memory) 
    {
        return vector;
    }

    function push(uint index) public 
    {        
        //** adăugarea de elemente în vector
        //** lungimea vectorului va crește în lungime cu 1.
        vector.push(index);
    }

    function pop() public 
    {        
        //** stergerea ultimului element din vector.
        //** această funcție reduce dimensiunea vectorului cu 1
        vector.pop();
    }

    function getLungime() public view returns (uint) 
    {
        return vector.length;
    }

    function sterge(uint index) public 
    {        
        //** ștergerea nu schimbă lungimea vectorului.
        //** resetează valoarea de la indexul menționat la valoarea implicită,
        //** în cazul de față la 0
        delete vector[index];
    }

    function exemplu() external {
        //** declarea unui vector în memorie, cu dimensiune fixă
        uint[] memory a = new uint[](5);
    }
}