const undoStackContainer = document.getElementById("undo-stack");
const redoStackContainer = document.getElementById("redo-stack");

const undoButton = document.getElementById("undo-button");
const redoButton = document.getElementById("redo-button");

const gridButtons = Array.from(document.querySelectorAll("[data-position]"));

// this line will error until you FIND the undoStackContainer
// and redoStackContainer elements
const undoStack = new Stack(undoStackContainer);
const redoStack = new Stack(redoStackContainer);

// this array is a bunch of hex values for colors so that 
// our random grid will be colored nicely. 
const COLORS = [
    '#1abc9c', '#16a085', '#f1c40f', '#f39c12',
    '#2ecc71', '#27ae60', '#e67e22', '#d35400',
    '#3498db', '#2980b9', '#e74c3c', '#c0392b',
    '#9b59b6', '#8e44ad', '#bdc3c7', '#34495e', 
    '#2c3e50', '#7f8c8d', '#95a5a6',
]

/**
 * @function handleGridButtonClick
 * 
 * @param {MouseEvent} event - the dispatched click event
 * @returns {void}
 * 
 * @description This function is an event handler for the grid buttons. When 
 * a grid button is clicked, it should change to a random color from the COLORS
 * Array. Because each grid button has a data-position property (which can
 * be accessed using event.currentTarget.dataset.position) you'll be able 
 * to figure out which button was clicked as well as what style it currently has.
 * 
 */
function handleGridButtonClick(event) {
    // Change the color
    event.currentTarget.style.backgroundColor = COLORS[Math.trunc(Math.random() * COLORS.length)];

    // Always add to undo stack, include the colors
    undoStack.push([event.currentTarget, event.currentTarget.style.backgroundColor]);

}

/**
 * @function handleStackButtonClicked
 * 
 * @param {Stack} fromStack - the stack to pop from
 * @param {Stack} toStack - the stack to push onto
 * @returns {void}
 * 
 * @description This function can be used to undo or redo a button click. The functionality
 * is roughly the same between undo and redo. The only difference is which stack is an action
 * being moved to and which stack is an action being moved from. Don't worry if you're not 
 * sure how to do this on Lab day. We'll go over some stuff with functions on Week 4 Tuesday
 * 
 */
function handleStackButtonClicked(fromStack, toStack) {
    let action = fromStack.pop()
    if (fromStack === undoStack){
        action[0].style.backgroundColor = '#eee';
    } else {
        action[0].style.backgroundColor = action[1];
    }
    toStack.push(action)
}

/**
 * @method main
 * 
 * @returns {void}
 * 
 * @description We could just run this Javascript as the document is being read. But I like
 * keeping functions separately and then calling them later. Peep the very last line of this
 * file. 
 */
function main() {
    // attach event handlers here

    // Attach the number button handlers
    for (let i = 0; i < gridButtons.length; ++i) {
        gridButtons[i].addEventListener('click', handleGridButtonClick);
    }

    // Attach the stack button handlers
    undoButton.addEventListener('click', (event) => {handleStackButtonClicked(undoStack, redoStack)});
    redoButton.addEventListener('click', (event) => {handleStackButtonClicked(redoStack, undoStack)});
}

// run our main function (even though Javascript doesn't actually need one)
main()