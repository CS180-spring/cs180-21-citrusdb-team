import React, { useState } from 'react';
import UCRLOGO from '../../images/cutiehack.png'
import { useNavigate } from 'react-router-dom';
import { registerUser } from '../API/API.js';
import './Register.css';

function Register() {
    const [username, setUserName] = useState('');
    const [password, setPassword] = useState('');
    const [userEmail, setUserEmail] = useState('');
    const [confirmPass, setConfirmPass] = useState('');
    const navigate = useNavigate();

    const handleRegister = async (event) => {
        event.preventDefault();
        if (password !== confirmPass) {
            alert("Passwords do not match!");
        }
        else {
            var result = await registerUser(username, password, userEmail);
            if (result === 200) {
                alert("User successfully registered!");
                navigate("/login");
            }
            else {
                alert("Failed! Please try again.");
                console.log(result);
            }
        }
    }

    var disableButton = (username.length === 0) || (password.length === 0) || (confirmPass.length === 0);

    return(
        <div className="register-wrapper">
                <h1>CitrusDB</h1>
                <h2>Register</h2>
                <img src={UCRLOGO} alt="UCRLOGO.png"/>
                <form onSubmit={handleRegister}>
                    <label>
                        <p>Username</p>
                        <input type="text" onChange={e => setUserName(e.target.value)} />
                    </label>
                    <label>
                        <p>Email</p>
                        <input type="text" onChange={e => setUserEmail(e.target.value)} />
                    </label>
                    <label>
                        <p>Password</p>
                        <input type="password" onChange={e => setPassword(e.target.value)} />
                    </label>
                    <label>
                        <p>Confirm Password</p>
                        <input type="password" onChange={e => setConfirmPass(e.target.value)} />
                    </label>
                    <br />
                    <button type="submit" id="regPageButton" disabled={disableButton}>Sign Up!</button>
                </form>
        </div>
    );
};

export default Register;