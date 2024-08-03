// SPDX-License-Identifier: MIT
pragma solidity ^0.8.10;

contract Taskuri 
{
    struct Task 
    {
        string text;
        bool realizat;
    }

    // vector de structuri
    Task[] public taskuri;

    function creareTask(string memory numeTask) public 
    {
        // există trei moduri de inițializare a vectorilor
        // - printrun apel al funcției
        taskuri.push(Task(numeTask, false));

        // - mapping prin valoare cheie
        //taskuri.push(Task({text: numeTask, realizat: false}));

        // - inițializarea unei structuri implicite și apoi prin actualizarea acesteia
       // Task memory task;
        //task.text = numeTask;
        
        // adăugăm
        taskuri.push(task);
    }

    function get(uint indexTask) public view returns (string memory text, bool completed) 
    {
        Task storage task = taskuri[indexTask];
        return (task.text, task.realizat);
    }

    // actualizăm taskul
    function actualizare(uint indexTask, string memory text) public 
    {
        Task storage todo = taskuri[indexTask];
        todo.text = text;
    }

    // actualizăm progresul
    function actualizareProgres(uint indexTask) public 
    {
        Task storage task = taskuri[indexTask];
        task.realizat = !task.realizat;
    }
}