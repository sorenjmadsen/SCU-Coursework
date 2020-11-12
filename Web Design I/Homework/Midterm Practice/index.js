// // // const convertSnakeToCamelCase = (toConvert) => {
// //     // let arr = toConvert.split('_')
// //     // let newStr = arr[0];
// //     // for (let i = 1; i < arr.length; i++)
// //         // newStr = newStr + arr[i][0].toUpperCase() + arr[i].substring(1)
// //     // return newStr;
// // // } 

// // const gameOver = () => {
// //     const buttons = document.querySelectorAll('button')
// //     for (let i = 0; i < buttons.length; i++){
// //         let button = buttons[i]
// //         button.disabled = true;
// //     }
// // }

// // const checkWinner = (turn) =>{
// //     const buttons = document.querySelectorAll('button')
// //     let winnerMessage = { message : ""};
// //     // Check Vertical
// //     let first = "";
// //     for (let i = 0; i < 3; i++){
// //         first = buttons[i].innerHTML;
// //         if (first === "")
// //             continue;
// //         if (buttons[i+3].innerHTML === first && buttons[i+6].innerHTML === first){
// //             winnerMessage.message = document.querySelector(".js-" + `${first}` + "-winner")
// //             break;
// //         }
// //     }
    
// //     // Check Horizontal
// //     for (let i = 0; i < 7 && winnerMessage.message === ""; i += 3){
// //         first = buttons[i].innerHTML;
// //         if (first === "")
// //             continue;
// //         if (buttons[i+1].innerHTML === first && buttons[i+2].innerHTML === first){
// //             winnerMessage.message = document.querySelector(".js-" + `${first}` + "-winner")
// //             break;
// //         }
// //     }

// //     // Check Left Diagonal
// //     if (winnerMessage.message === ""){
// //         first = buttons[0].innerHTML;
// //         if (first !== "")
// //             if (buttons[4].innerHTML === first && buttons[8].innerHTML === first)
// //                 winnerMessage.message = document.querySelector(".js-" + `${first}` + "-winner")
// //     }
// //     // Check Right Diagonal
// //     if (winnerMessage.message === ""){
// //         first = buttons[2].innerHTML;
// //         if (first !== "")
// //             if (buttons[4].innerHTML === first && buttons[6].innerHTML === first)
// //                 winnerMessage.message = document.querySelector(".js-" + `${first}` + "-winner")
// //     }
// //     if (winnerMessage.message !== ""){
// //         winnerMessage.message.style.visibility = 'inherit';
// //         if(turn.dataset.value === first)
// //             document.getElementById("current-turn").style.visibility = "hidden"
// //         return true;
// //     }
// // }

// // const changeTurn = (turn) => {
// //     turn.dataset.value = (turn.dataset.value === "🦔") ? "🦄" : "🦔";
// //     turn.innerHTML = "Current player's turn: " + `${turn.dataset.value}`;
// // }

// // const handleButtonClick = (event) => {
// //     let turn =  document.getElementById('current-turn');
// //     if (event.currentTarget.innerHTML === ""){
// //         event.currentTarget.innerHTML = turn.dataset.value;
// //         if(!checkWinner(turn))
// //             changeTurn(turn);
// //         else
// //             gameOver()
// //     }
// // }

// // function main(){
// //     const buttons = document.querySelectorAll('button')
// //     console.log(buttons)
// //     for (let i = 0; i < buttons.length; i++){
// //         const button = buttons[i]
// //         button.addEventListener('click', handleButtonClick)
// //     }
// // }

// // main()

// const combineStanzas = () => {
//     let arr = [];
//     for (let i = 0; i < stanzas.length; i++)
//         arr.push(stanzas[i]);
//     return arr;
// }

// const stanzas = [
//     'A hundred point test', 
//     'with all your skill and wisdom', 
//     'you don\'t need no luck'
// ]


// const haiku = stanzas.reduce(combineStanzas, "")

// console.log(haiku.join('\n'))
const PASSCODE = '1022';
const numberButtons = Array.from(document.querySelectorAll("button"));
let inputElt = document.querySelector("input")
let input = ""

function success(){
    inputElt.classList.add("success")
}

function error(){
    inputElt.classList.add("error")
}

function clear(){
    let classes = inputElt.classList
    if (classes.contains("success"))
        inputElt.classList.remove("success")

    if (classes.contains("error"))
        inputElt.classList.remove("error")
}

function handleNumberPressed(event) {
    let numberPressed = event.currentTarget.textContent;
    input = input + numberPressed;
    if (input.length > 4){
        input = numberPressed;
        clear();
    }
    if (input.length > 3){
        if (PASSCODE === input)
            success();
        else   
            error();
    }
    inputElt.setAttribute("value", input)
}

for(let j = 0; j < numberButtons.length; j++){
    const numberButton = numberButtons[j];
    const currentNumber = numberButton.value;
    
    numberButton.addEventListener('click', handleNumberPressed)
}