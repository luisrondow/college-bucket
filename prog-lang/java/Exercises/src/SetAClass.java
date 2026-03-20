import java.util.Arrays;

public class SetAClass implements Set {
    private static final int CAPACITY = 10;
    private int size;
    private int[] items;

    public SetAClass() {
        this.size = 0;
        this.items = new int[CAPACITY];
    }

    @Override
    public int Size() {
        return size;
    }

    @Override
    public int Get(int i) {
        return items[i];
    }

    @Override
    public void Store(int v) {
        if (Belongs(v)) return;

        this.items[size] = v;
        this.size++;
    }

    @Override
    public boolean Belongs(int v) {
        boolean hasValue = false;
        for (int item: items) {
            if (item == v) {
                hasValue = true;
                break;
            }
        }

        return hasValue;
    }

    @Override
    public Set Union(Set s) {
        Set newSet = new SetAClass();

        for (int i = 0; i < this.size; i++) {
            newSet.Store(this.Get(i));
        }

        for (int i = 0; i < s.Size(); i++) {
            newSet.Store(s.Get(i));
        }

        return newSet;
    }

    @Override
    public void Print() {
        System.out.print("{");

        for (int i = 0; i < size; i++) {
            System.out.print(items[i]);
            if (i < size - 1) System.out.print(", ");
        }

        System.out.println("}");
    }

    public static void main(String[] args) {
        SetAClass a = new SetAClass();

        a.Store(1); a.Store(2); a.Store(3); a.Store(2); // 2 nao duplica

        System.out.print("A = "); a.Print();  // {1, 2, 3}

        SetAClass b = new SetAClass();

        b.Store(3); b.Store(4); b.Store(5);

        System.out.print("B = "); b.Print();  // {3, 4, 5}

        Set c = a.Union(b);

        System.out.print("A U B = "); c.Print();  // {1, 2, 3, 4, 5}

        System.out.println("2 pertence a A? " + a.Belongs(2));  // true

        System.out.println("6 pertence a A? " + a.Belongs(6));  // false

        System.out.println("Tamanho de A: " + a.Size());        // 3

    }
}
