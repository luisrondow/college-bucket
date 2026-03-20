public class Point {
    private int x;
    private int y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public Point(int point) {
        this.x = point;
        this.y = point;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public boolean equalsTo(Point p) {
        return p.getX() == this.x && p.getY() == this.y;
    }

    public void checkPossibleLine(Point p1, Point p2) {
        if (p1.equalsTo(p2)) {
            System.out.println("Mesma coordenadas");
            return;
        }

        if (p1.getY() == p2.getY()) {
            System.out.println("Horizontal");
            return;
        }

        if (p1.getX() == p2.getX()) {
            System.out.println("Vertical");
            return;
        }

        System.out.println("Obliqua");
    }

    @Override
    public String toString() {
        return "X: " + this.x + "Y: " + this.y;
    }
}
