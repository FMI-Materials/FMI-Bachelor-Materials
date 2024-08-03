// SPDX-License-Identifier: MIT
pragma solidity ^0.8.10;

contract Gas {
    uint public contor = 0;

    //** Utilizarea întregii cantități de gaz pe care 
    //** îl trimitem cauzează eșecul procesării tranzacției.
    //** Schimbările de stare nu se mai pot 
    //** face după momentul execuției.
    //** Gazul cheltuit nu este rambursabil
    function runningInfinite() public {
        //** mai jos avem o buclă pe care o rulăm până 
        //** când gaz-ul este cheltuit și tranzacția 
        //** și procesarea acesteia eșuează        
        while (true) {
            contor += 1;
        }
    }
}