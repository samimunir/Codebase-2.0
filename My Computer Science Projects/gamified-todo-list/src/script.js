/*
    Get references to the input field and button elements.
*/
const todoInput = document.getElementById("todo-input");
const addButton = document.getElementById("add-button");
const clearAllButton = document.getElementById("clear-all-button");

/*
    Add an event listener to the addButton click.
*/
addButton.addEventListener("click", function() {
    /*
        Get the value entered in the input field.
    */
    const newTodoText = todoInput.value;
    /*
        Check if the input field is empty.
    */
    if (newTodoText.trim() === "") {
        alert("Please enter a task!");
        return;
    }
    /*
        Create a new list item element for the new task.
    */
    const newTodoItem = document.createElement("li");
    newTodoItem.textContent = newTodoText;
    /*
        Add the new list item to the to-do list container and update progress bar.
    */
    const todoList = document.getElementById("todo-container");
    todoList.appendChild(newTodoItem);
    updateProgressBar();
    /*
        Clear the input field for the next task.
    */
    todoInput.value = "";
});

/*
    Add an event listener to the clearAllButton click.
*/
clearAllButton.addEventListener("click", function() {
    /*
        Confirm with the user before clearing all tasks.
    */
    if (confirm("Are you sure you want to clear all tasks?")) {
        /*
            Remove all list items from the to-do list container.
        */
        const todoItems = todoList.querySelectorAll("LI");
        /*
            Loop through each list item and remove it.
        */
        for (let i = 0; i < todoItems.length; i++) {
            todoList.removeChild(todoItems[i]);
        }
        /*
            Reset the progres bar with width to 0.
        */
        const progressBar = document.getElementById("progress-bar");
        progressBar.style.width = "0%";
        updateProgressBar();
    }
});

/*
    Get references to the progress bar element and the list container
*/
const progressBar = document.getElementById("progress-bar");
const todoList = document.getElementById("todo-container");

/*
    Function to update the progress bar width based on completion ratio.
*/
function updateProgressBar() {
    const completedTasks = todoList.querySelectorAll(".completed").length;
    const totalTasks = todoList.querySelectorAll("LI").length;
    /*
        Calculate the progress percentage.
    */
    const progress = (completedTasks / totalTasks) * 100;
    /*
        Update the progress bar width
    */
    progressBar.style.width = `${progress}%`;
}

/*
    Update the progress bar initially.
*/
updateProgressBar();

/*
    Add an event listener to the to-do list container.
    - update the progress bar whenever a task is marked as completed.
*/
todoList.addEventListener("click", function(event) {
    /*
        Check if the clicked element is a list item.
    */
    if (event.target.tagName == "LI") {
        /*
            Toggle a class on the clicked list item to visually mark it as completed.
        */
        event.target.classList.toggle("completed");
        updateProgressBar();
    }
});