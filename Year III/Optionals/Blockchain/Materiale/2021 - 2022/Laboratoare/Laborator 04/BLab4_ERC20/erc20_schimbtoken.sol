//Sursa: https://solidity-by-example.org/app/erc20/
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.10;

import "https://github.com/OpenZeppelin/openzeppelin-contracts/blob/v4.0.0/contracts/token/ERC20/IERC20.sol";

/*
Cum se realizeaza schimbul de token-uri

1. Alice has 100 tokens from AliceCoin, which is a ERC20 token.
2. Bob has 100 tokens from BobCoin, which is also a ERC20 token.
3. Alice and Bob wants to trade 10 AliceCoin for 20 BobCoin.
4. Alice or Bob deploys TokenSwap
5. Alice approves TokenSwap to withdraw 10 tokens from AliceCoin
6. Bob approves TokenSwap to withdraw 20 tokens from BobCoin
7. Alice or Bob calls TokenSwap.swap()
8. Alice and Bob traded tokens successfully.
*/

contract SchimbToken {
    IERC20 public token1;
    address public proprietar1;
    uint public amount1;

    IERC20 public token2;
    address public proprietar2;
    uint public amount2;

    constructor(
        address _token1,
        address _proprietar1,
        uint _amount1,
        address _token2,
        address _proprietar2,
        uint _amount2
    ) {
        token1 = IERC20(_token1);
        proprietar1 = _proprietar1;
        amount1 = _amount1;
        token2 = IERC20(_token2);
        proprietar2 = _proprietar2;
        amount2 = _amount2;
    }

    function swap() public {
        require(msg.sender == proprietar1 || msg.sender == proprietar2, "Fara autorizatie");
        require(
            token1.allowance(proprietar1, address(this)) >= amount1,
            "Token 1 allowance too low"
        );
        require(
            token2.allowance(proprietar2, address(this)) >= amount2,
            "Token 2 allowance too low"
        );

        _safeTransferFrom(token1, proprietar1, proprietar2, amount1);
        _safeTransferFrom(token2, proprietar2, proprietar1, amount2);
    }

    function _safeTransferFrom(
        IERC20 token,
        address sender,
        address recipient,
        uint amount
    ) private {
        bool sent = token.transferFrom(sender, recipient, amount);
        require(sent, "transferul token-ului a esuat");
    }
}