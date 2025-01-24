// SPDX-License-Identifier: MIT
pragma solidity ^0.8.10;

contract InstructiuniMapping 
{
    //** mapping de la adresa la uint
    mapping(address => uint) public mappingCurent;

    function getAddress(address adresa) public view returns (uint) 
    {
        //** Un mapping întotdeauna returnează o valoare.
        //** Dacă valoarea nu a fost folosită, 
        //** o valoare implicăt este returnată
        return mappingCurent[adresa];
    }

    function setAddress(address adresa, uint valoare) public 
    {
        //** actualizează valoarea la adresa menționată
        mappingCurent[adresa] = valoare;
    }

    function removeAddress(address adresa) public 
    {
        //** inițializăm valoarea la valoarea implicită
        delete mappingCurent[adresa];
    }
}

contract InstructiuniMappingNested 
{
    //** mapping-uri imbricate (sau nested) - 
    //** mapping de la o adresă la alt mapping
    mapping(address => mapping(uint => bool)) public nImbricat;

    function get(address adresaImbricat, uint val) public view returns (bool) 
    {        
        //** Există posibilitatea de a obține 
        //** valori de la un mapping imbricat
        //** chiar dacă nu este inițializată
        return nImbricat[adresaImbricat][val];
    }

    function set(
        address adresaImbricat,
        uint val,
        bool booleanValue
    ) public 
    {
        nImbricat[adresaImbricat][val] = booleanValue;
    }

    function remove(address adresaImbricat, uint val) public 
    {
        delete nImbricat[adresaImbricat][val];
    }
}