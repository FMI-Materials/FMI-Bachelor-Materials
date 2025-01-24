import React from 'react';
import {
    BrowserRouter as Router,
    Switch,
    Route,
    Link
} from "react-router-dom";
import './App.css';
import Auth from './pages/auth'
import Profile from './pages/profile'
import Game from './pages/game'

function App() {
  return (
    <Router>
        <Switch>
            <Route path="/profile">
                <Profile/>
            </Route>
            <Route path="/auth">
                <Auth/>
            </Route>
            <Route path="/">
                <Game/>
            </Route>
        </Switch>
    </Router>
  );
}

export default App;
