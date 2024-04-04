public class ArrayDS {

    private int[] main_array;
    private int capacity = 0;
    private int pointer = -1;
    public ArrayDS() {
        capacity = 5;
        main_array = new int[capacity];
        Console.WriteLine("\nSuccessfully initialized main_array[] to capacity [" + capacity + "].\n\tpointer: " + pointer);
    }

    public ArrayDS(int capacity) {
        this.capacity = capacity;
        main_array = new int[capacity];
        Console.WriteLine("\nSuccessfully initialized main_array[] to capacity [" + capacity + "].\n\tpointer: " + pointer);
    }
}