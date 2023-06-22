export async function registerUser(username, password, email) {
    const url = "http://18.118.196.59:80/create";

    const userBody = {
        username: username,
        password: password,
        email: email
    };

    try {
        const response = await fetch(url, {
            method: "POST",
            headers: {
              "Content-Type": "application/json"
            },
            body: JSON.stringify(userBody)
        });
        
        console.log(response.status);
        
        if (response.status === 200) {
            const data = await response.text();
            console.log(data);
            return 200;
        } 
    }
    catch (error) {
        console.log(error);
        return 400;
    }
}

registerUser("testuser", "testpass", "testemail");