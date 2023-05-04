import React, { useState } from 'react';
import './App.css';
import { Routes, Route, Navigate } from 'react-router-dom';
import Login from './components/Login/Login';
import Dashboard from './components/Dashboard/Dashboard';
import Register from './components/Register/Register';
import Forgot from './components/Forgot/Forgot';

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
          <Route path="/dashboard" element={<Dashboard />} />
          <Route path="/register" element={<Register />} />
          <Route path="/forgot" element={<Forgot />} />
        </Routes>
    </div>
  );
}

export default App;