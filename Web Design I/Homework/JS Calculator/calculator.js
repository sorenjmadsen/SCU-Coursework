// function strongPassword(password)
// INPUT:   A password of any length and any combination of characters.
// OUTPUT:  Returns true if password is a strong password, false if not a
//          strong password:
//              - greater than 8 characters in length
//              - contains a number, lowercase letter, and special character
//                  ie. !@#$%^&*()-+
function strongPassword(password){
    if (/[a-z]/.test(password) === false)
        return false;
    if (/[0-9]/.test(password) === false)
        return false;
    if (/[!@#$%^&*()-+]/.test(password) === false)
        return false;
    if (password.length < 8)
        return false;
    if (typeof(password) !== "string")
        return false;
    
    return true;
}


/*
    This is NOT how you should be writing code, but this is what we'll do since
    this is what we've learned so far.
*/
const outputElement = document.getElementById('output')
const numberButtons = Array.from(document.querySelectorAll('[value]'))
const operatorButtons = Array.from(document.querySelectorAll('[data-operation]'));

const operation = {
    operand1: null,
    operand2: null,
    operator: null
}

const OPERATIONS = {
    clear: resetValue,
    equals: commitOperation,
    add: handleAddClicked,
    subtract: handleSubtractClicked,
    multiply: handleMultiplyClicked,
    divide: handleDivideClicked,
    negative: negative,
    percent: percent,
}

// HOMEWORK: Write a function which multiplies the current value by -1 and then 
// commits that operation
function negative() {
    operation.operand1 = getCurrentValue();
    operation.operand2 = -1;
    operation.operator = multiply;
    commitOperation();
}

function percent() {
    operation.operand1 = getCurrentValue()
    operation.operand2 = 100;
    operation.operator = divide;
    commitOperation()
}

// HOMEWORK: write a function to get the current value of the output element
function getCurrentValue() {
    current = outputElement.value;
    return current;
}

// HOMEWORK: write a function to set the value of the output element
function setCurrentValue(value){
    outputElement.value = value
}

function resetValue() {
    outputElement.value = 0;

    if (operation.operator === null) {
        operation.operand1 = null,
        operation.operand2 = null,
        operation.operator = null
    } else {
        operation.operand2 = null;
    }
}

function handleNumberPressed(event) {
    let op1 = operation.operand1;
    let op2 = operation.operand2;

    if (operation.operator === null) {
        op1 = op1 === null 
            ? event.currentTarget.value
            : `${op1}${event.currentTarget.value}`;
        operation.operand1 = op1;
        setCurrentValue(op1);
    } else {
        op2 = op2 === null 
            ? event.currentTarget.value
            : `${op2}${event.currentTarget.value}`;
        operation.operand2 = op2;
        setCurrentValue(op2);
    }
}

function add(a, b) {
    return a + b;
}

function subtract(a, b) {
    return a - b;
}

function multiply(a, b) {
    return a * b;
}

function divide(a, b) {
    return b === 0 ? 0 : a / b;
}

function handleAddClicked() {
    operation.operator = add;

    if (operation.operand1 === null) {
        operation.operand1 = getCurrentValue() 
    }
}

function handleSubtractClicked() {
    operation.operator = subtract;

    if (operation.operand1 === null) {
        operation.operand1 = getCurrentValue() 
    }
}

function handleMultiplyClicked() {
    operation.operator = multiply;

    if (operation.operand1 === null) {
        operation.operand1 = getCurrentValue() 
    }
}

function handleDivideClicked() {
    operation.operator = divide;

    if (operation.operand1 === null) {
        operation.operand1 = getCurrentValue() 
    }
}

function commitOperation() {
    const newValue = operation.operator(
        parseInt(operation.operand1, 10), 
        parseInt(operation.operand2, 10)
    );
    setCurrentValue(newValue);

    operation.operand1 = null,
    operation.operand2 = null,
    operation.operator = null
}

// HOMEWORK: add an event listener for each of the number buttons
for (let i = 0; i < operatorButtons.length; i++) {
    const operatorButton = operatorButtons[i];
    const currentOperation = operatorButton.dataset.operation

    if (typeof(OPERATIONS[currentOperation]) === 'function') {
        operatorButton.addEventListener('click', OPERATIONS[currentOperation])
    }
}

for(let j = 0; j < numberButtons.length; j++){
    const numberButton = numberButtons[j];
    const currentNumber = numberButton.value;
    
    numberButton.addEventListener('click', handleNumberPressed)
}