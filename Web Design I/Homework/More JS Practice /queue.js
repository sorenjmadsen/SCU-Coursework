/**
 * Task 5: Implement a Queue [3 points]
 * 
 * size - which returns the size of the queye
 * enqueue - which takes in a value and puts it into the elements array
 * dequeue - which returns the first element that was put into the array
 * 
 */
function Queue(){
    let elements = [];


    function print() {
        for (let i = 0; i < elements.length - 1; i++ ) {
            const element = elements[i];
            const textMidpoint = Math.floor(element.length / 2)
            const downArrowLine = "↓".padStart(textMidpoint)
            console.log(Queue.border(element))
            console.log(downArrowLine)
        }

        console.log(Queue.border(elements[elements.length - 1]))
    }

    function enqueue(elt){
        // Add to back of array
        elements.push(elt);
    }

    function dequeue(){
        // Grab first element
        elt = elements[0];

        // Instead of shifting, just reassign array
        elements = elements.slice(1, elements.length);
        return elt;
    }

    return {
        // return your functions to use a queue here
        print: print,
        enqueue: enqueue,
        dequeue: dequeue
    } 
}

Queue.border = function(text) {
    const textLength = text.length;
    return [
        '┌ ' + "─".repeat(textLength) + " ┐",
        '│ ' + text + " │",
        "└ " + "─".repeat(textLength) + " ┘"
    ].join('\n')
}

const pockyQueue = Queue()
pockyQueue.enqueue('original')
pockyQueue.enqueue('strawberry')
pockyQueue.enqueue('almond crush')
pockyQueue.enqueue('matcha')
pockyQueue.dequeue()
pockyQueue.print()
