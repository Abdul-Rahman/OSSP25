package w01ex01Abstration;

public class TestBird {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Animal myBird =  new Bird();
		myBird.label();
		myBird.move();
		myBird.eat();
	}
}
