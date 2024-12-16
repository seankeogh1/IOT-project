// To create literal strings stored in flash memory enclose your HTML code between 
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Login</title>
    <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' 
    rel='stylesheet'>
    <style>
        
    *{
        margin: 0;
        padding: 0;
        box-sizing: border-box;
        font-family:"Poppins" sans-serif;
    }
    
    
    
    
    body{
        background : url(https://www.dueruote.it/content/dueruote/it/pubbliredazionale/bacheca/2021/03/01/Hoermann/jcr:content/social-image.img.png/1612878357306.png);
        background-size: cover;
        background-position: center;
        min-height: 98vh;
        justify-content: center;
        display: flex;
        align-items: center;
        min-height: 100vh;
    }
    
    .wrapper{
        width: 420px;
        background: transparent;
        border: 2px solid rgba(255, 255, 255, .2);
        color: antiquewhite;
        backdrop-filter: blur(20px);
        border-radius: 10px;
        padding: 30px 40px;
    }
    
    .wrapper h1 {
    font-size: 36px;
    text-align: center;
    }
    .wrapper .input-box {
        position: relative;
        width: 100%;
        height: 50px;
        margin: 30px 0;
    }
    
    .input-box input {
        width: 100%;
        height: 100%;
        background: transparent;
        border: none;
        outline:  none;
        border: 2px solid rgba(255, 255, 255, 0.2);
        border-radius: 40px;
        font-size: 16px;
        color: #fff;
        padding: 20px 45px 20px 20px;
    
    }
    
    .input-box input::placeholder {
        color:aliceblue;
    } 
    
    .input-box i {
        position: absolute;
        right: 20px;
        top: 50%;
        transform: translateY(-50%);
    }
    
    .wrapper .btn {
        width: 100%;
        height: 45px;
        background: #fff;
        border: none;
        outline: none;
        border-radius: 40px;
        box-shadow: 0 0 10px rgba(0, 0, 0, .1);
        cursor: pointer;
        font-size: 16px;
        color: #333;
        font: weight 600;
    }
</style>

</head>
<body>
    <div class="wrapper">
        <form action="">
            <h1>Login</h1>
            <div class="input-box">
                <input type="Code"
                 placeholder="Code" required>
                 <i class='bx bx-dialpad'></i>
            </div>


        <button type="submit" class="btn"> Login </button>
        </form>
    </div>
</body>
</html>)=====");
//String homePagePart2 = F(R"=====(CSS/HTML code here)=====");
