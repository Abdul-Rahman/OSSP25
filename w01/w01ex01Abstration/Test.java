package w01ex01Abstration;

public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Animal b = new Bird();
		Animal f = new Fish();
		
		b.label();
		b.move();
		b.eat();
		
		f.label();
		f.move();
		f.eat();
	}
}
