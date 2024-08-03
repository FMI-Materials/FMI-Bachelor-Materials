//Sursa: https://solidity-by-example.org/app/erc20/

// SPDX-License-Identifier: MIT
pragma solidity ^0.8.10;

import "https://github.com/OpenZeppelin/openzeppelin-contracts/blob/v4.0.0/contracts/token/ERC20/ERC20.sol";

contract UBExempluToken is ERC20 {
    constructor(string memory name, string memory symbol) ERC20(name, symbol) {
        // mint 100 tokeni pentru msg.sender - in mod unic token-ul din blockchain va fi cumparabil.         
        // Similar to how
        // 1 dolar = 100 centi
        // 1 token = 1 * (10 ** decimals)
        _mint(msg.sender, 100 * 10**uint(decimals()));
    }
}