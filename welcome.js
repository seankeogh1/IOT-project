function openDoor(){
    fetch("/DoorOpen")
    .then(response => response.text())
    .then(data =>{
        document.getElementById("status").innerText = data;
        console.log(data);
    })
    .catch(error => console.error("Error:",error));
}