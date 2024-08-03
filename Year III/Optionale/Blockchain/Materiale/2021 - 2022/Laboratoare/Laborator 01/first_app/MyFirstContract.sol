pragma solidity ^0.8.0;

contract ContractulMeu {
    uint valoare = 1;

    function get() public view returns (uint) 
    {
        return valoare;
    }

    function double() public {
        valoare *= 2;
    }
}


/// panic garbage harsh cereal sniff local flush mushroom apology dose lounge say