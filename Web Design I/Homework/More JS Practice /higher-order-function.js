/**
 * Task 1: [1 point]
 * 
 * Write a function countBs that takes a string as its only argument 
 * and returns a number that indicates how many uppercase “B” characters 
 * there are in the string.
 */

function countBs(testStr){
    if(typeof(testStr) !== 'string')
        return 0;
    
    let count = 0;
    for (let i  = 0; i < testStr.length; i++){
        count += (testStr[i] === "B") ? 1 : 0;
    }
    return count;
}

/**
 * Task 2 [1 point]
 * 
 * Write a function called countChar that behaves like countBs, except it 
 * takes a second argument that indicates the character that is to be counted 
 * (rather than counting only uppercase “B” characters).
 */
function countChar(testStr, testChar){
    if(typeof(testStr) !== 'string')
        return 0;

    let count = 0;
    for (let i  = 0; i < testStr.length; i++){
        count += (testStr[i] === testChar) ? 1 : 0;
    }
    return count;
}


/**
 * Task 3 [2 points]
 * 
 *  Write a new countBs function tthat uses countChar
 */

function countBs(testStr){
    return countChar(testStr, "B")
}


console.log(countBs("BBC")); // → 2
console.log(countChar("kakkerlak", "k")); // → 4

/** 
 * Task 4 [3 points]
 * 
 * Arrays in Javascript can be sorted using the .sort method. It takes in a comparison
 * function. Write a function which follows the .sort contract to sort objects. Your sort
 * function should first sort skittles by rating and then sort them by type. Sour skittles
 * are better than tropical. 
 */

const skittles = [
    {
        flavor: 'Sour Green Apple',
        type: 'sour',
        rating: 10 
    },
    {
        flavor: "Mango Tangelo",
        type: 'tropical',
        rating: 5
    },
    {
        flavor: 'Sour Lemon',
        type: 'sour',
        rating: 3
    },
    {
        flavor: 'Sour Strawberry',
        type: 'sour',
        rating: 6
    },
    {
        flavor: "Banana Berry",
        type: 'tropical',
        rating: 2
    },
    {
        flavor: 'Sour Grape',
        type: 'sour',
        rating: 0
    },
    {
        flavor: "Kiwi Lime",
        type: 'tropical',
        rating: 7
    },
    {
        flavor: "Strawberry Starfruit",
        type: 'tropical',
        rating: 9
    },
    {
        flavor: 'Sour Blue Rasberry',
        type: 'sour',
        rating: 8
    },
    {
        flavor: "Pineapple Passionfruit",
        type: 'tropical',
        rating: 4
    },
    {
        flavor: 'Sour Orange',
        type: 'sour',
        rating: 5
    },
     
]

// make sure this function signature follows what sort expecte!
// Code designed so sort() puts the higher rated in earlier spots of array
const skittlesSort = function(skittleOne, skittleTwo) {
    if (skittleOne.rating === skittleTwo.rating) {
        if (skittleOne.type === skittleTwo.type)
            return 0;
        return (skittleOne.type === 'sour') ? -1 : 1;
    }

    return (skittleOne.rating > skittleTwo.rating) ? -1 : 1;
}

console.log(skittles.sort(skittlesSort))