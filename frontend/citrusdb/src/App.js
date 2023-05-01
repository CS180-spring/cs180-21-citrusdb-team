import React, { useState } from 'react';
import './App.css';
import { BrowserRouter, Routes, Route } from 'react-router-dom';
import Login from './components/Login/Login';
import Dashboard from './components/Dashboard/Dashboard';
import Preferences from './components/Preferences/Preferences';

/*
  Credit 
  https://www.digitalocean.com/community/tutorials/how-to-add-login-authentication-to-react-applications
*/



function App() {
  const [token, setToken] = useState();

  if(!token) {
    return <Login setToken={setToken} />
  }
  return (
    <div className="App">
      <h1>CitrusDB</h1>
      <BrowserRouter>
        <Routes>  
          <Route path="/dashboard" element={<Dashboard />} />
        </Routes>
      </BrowserRouter>
    </div>
  );
}

export default App;
