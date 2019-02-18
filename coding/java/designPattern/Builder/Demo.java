class Pizza {
    private String dough;
    private String sauce;
    private String topping;

    public void setDough(String dough) {
        this.dough = dough;
    }

    public void setSauce(String sauce) {
        this.sauce = sauce;
    }

    public void setTopping(String topping) {
        this.topping = topping;
    }

    @java.lang.Override
    public java.lang.String toString() {
        return "Pizza{" +
                "dough='" + dough + '\'' +
                ", sauce='" + sauce + '\'' +
                ", topping='" + topping + '\'' +
                '}';
    }
}

abstract class PizzaBuilder {
    protected Pizza pizza;

    public Pizza getPizza() {
        return pizza;
    }

    public void createNewPizzaProduct() {
        pizza = new Pizza();
    }

    public abstract void buildDough();

    public abstract void buildSauce();

    public abstract void buildTopping();

}

class HawaiianPizzaBuilder extends PizzaBuilder {
    @java.lang.Override
    public void buildDough() {
        pizza.setDough("cross");
    }

    @java.lang.Override
    public void buildSauce() {
        pizza.setSauce("mild");
    }

    @java.lang.Override
    public void buildTopping() {
        pizza.setTopping("ham+pineapple");
    }
}

class SpicyPizzaBuilder extends PizzaBuilder {
    @java.lang.Override
    public void buildDough() {
        pizza.setDough("pan baked");
    }

    @java.lang.Override
    public void buildSauce() {
        pizza.setSauce("hot");
    }

    @java.lang.Override
    public void buildTopping() {
        pizza.setTopping("peperoni+salami");
    }
}

// Director
class Waiter {
    private PizzaBuilder pizzaBuilder;

    public void setPizzaBuilder(PizzaBuilder pizzaBuilder) {
        this.pizzaBuilder = pizzaBuilder;
    }

    public Pizza getPizza() {
        return pizzaBuilder.getPizza();
    }

    public void constructPizza() {
        pizzaBuilder.createNewPizzaProduct();
        pizzaBuilder.buildDough();
        pizzaBuilder.buildSauce();
        pizzaBuilder.buildTopping();
    }
}


public class Demo {
    public static void main(String[] args) {
        Waiter waiter = new Waiter();
        PizzaBuilder hawaiianPizzabuilder = new HawaiianPizzaBuilder();
        PizzaBuilder spicyPizzaBuilder = new SpicyPizzaBuilder();
        waiter.setPizzaBuilder(hawaiianPizzabuilder);
        waiter.constructPizza();
        System.out.println(waiter.getPizza());
    }
}