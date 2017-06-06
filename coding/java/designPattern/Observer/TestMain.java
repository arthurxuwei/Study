package designPattern.Observer;

public class TestMain {
	public WeatherData weatherData;
	public CurrentConditionsDisplay currentConditionsDisplay;
	public ForcastDisplay forcastDisplay;
	public StatisticDisplay statisticDisplay;
	
	public void Init() {
		weatherData = new WeatherData();
		currentConditionsDisplay = new CurrentConditionsDisplay(weatherData);
		forcastDisplay = new ForcastDisplay(weatherData);
		statisticDisplay = new StatisticDisplay(weatherData);
	}
	
	public void Dispose() {
		weatherData = null;
		currentConditionsDisplay = null;
		forcastDisplay = null;
		statisticDisplay = null;
	}
	public static void main(String argc[]) {
		TestMain t= new TestMain();
		t.Init();
		t.weatherData.SetMeasurements(80, 65, 30.4f);
		System.out.println(t.currentConditionsDisplay.Display());
		
		t.weatherData.SetMeasurements(81,63,31.2f);
		System.out.println(t.forcastDisplay.Display());
		t.weatherData.SetMeasurements(81,63,29.92f);
		System.out.println(t.forcastDisplay.Display());
		t.weatherData.SetMeasurements(81,63,29.92f);
		System.out.println(t.forcastDisplay.Display());
		
		t.weatherData.SetMeasurements(80, 63, 31.2f);
		t.weatherData.SetMeasurements(81,63,29.92f);
		t.weatherData.SetMeasurements(81,63,29.92f);
		if (t.statisticDisplay.getNumberOfReadings() == 7) {
			System.out.println(t.statisticDisplay.Display());
		}
	
		t.Dispose();
	}
}
