import React, { useState } from 'react';
import './App.css';
import { Routes, Route, Navigate } from 'react-router-dom';
import Login from './components/Login/Login.js';
import Dashboard from './components/Dashboard/Dashboard.js';
import Register from './components/Register/Register.js';
import Forgot from './components/Forgot/Forgot.js';
import Collection from './components/Collection/Collection.js';

/*
  Credit 
  https://www.digitalocean.com/community/tutorials/how-to-add-login-authentication-to-react-applications
*/



function App() {
  const [token, setToken] = useState();

  return (
    <div className="App">
        <Routes>
          <Route
            path="/"
            element={token ? <Navigate to="/dashboard" /> : <Navigate to="/login" />}/>
          <Route path="/login" element={<Login setToken={setToken}/>} />
          <Route path="/dashboard" element={<Dashboard setToken={setToken}/>} />
          <Route path="/register" element={<Register />} />
          <Route path="/forgot" element={<Forgot />} />
          <Route path="/collection" element={<Collection />} />
        </Routes>
    </div>
  );
}

export default App;