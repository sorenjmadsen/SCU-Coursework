/**
 * @class Stack - represents a stack from which actions can be pushed and popped
 * 
 * @member {Array<any>} actions - the array which holds all the actions that a user did
 * @member {HTMLElement} containerElement - the element which will show all the children of a stack
 * 
 * @note Because we add this at the global scope (not inside any function) this class will be 
 * available to any script defined below script.js in the HTML document that adds this script.
 */
class Stack {
    /**
     * @constructor
     * 
     * @param {HTMLElement} containerElement - the element which contains all children of this stack
     * @note You don't need to modify this function at all. Instead, it'll get called
     */
    constructor(containerElement) {
        this.actions = []
        this.containerElement = containerElement;
    }

    /**
     * @function push
     * @this {Stack}
     * 
     * @param {any} action - the action that's pushed and popped from the stack
     * @returns {void}
     * 
     * @note You should write out the two things that happen when you click on a button. 
     * Ask the TA's to demo to you, but try to break it down on your own. 
     * 
     * // TASK 1D: Write a description of what happens in this function
     * @description The push function adds an action to the stack at the very first place,
     * pushing all other elements further back. The addition to the HTML will take place in index.js.
     */
    push(action) {
        // Add it to the stack
        this.actions.push(action)

        // Add the HTML element
        let newAction = document.createElement("p");
        newAction.innerHTML = action[0].textContent;
        newAction.setAttribute("class", "stack-action");
        newAction.setAttribute("style", "background-color:" + action[1])
        this.containerElement.appendChild(newAction)
    }

    /**
     * @function pop
     * @this {Stack}
     * 
     * @returns {Action | undefined} - undefined if the size is 0
     * 
     * // TASK 1E: Write a description of what happens in this function
     * @description The pop function returns the element in the very first position, moving 
     * all other elements forward after removal.
     */
    pop() {
        if(this.actions.length < 1)
            return undefined;

        // Remove the HTML element
        let elements = Array.from(this.containerElement.querySelectorAll(".stack-action"))
        this.containerElement.removeChild(elements[elements.length - 1])

        // Return the action
        return this.actions.pop();
    }

    /**
     * @function size
     * @this {Stack}
     * 
     * @returns {Number} - number of actions in the stack
     */
    size() {
        return this.actions.length;
    }
}