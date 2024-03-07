/*
    Get references to the input field and button elements.
*/
const todoInput = document.getElementById("todo-input");
const addButton = document.getElementById("add-button");

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
        Add the new list item to the to-do list container.
    */
    const todoList = document.getElementById("todo-container");
    todoList.appendChild(newTodoItem);
    /*
        Clear the input field for the next task.
    */
    todoInput.value = "";
});