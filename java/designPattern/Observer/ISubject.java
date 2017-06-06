package designPattern.Observer;

public interface ISubject {
	void RegisterObserver(IObserver o);
	void RemoveOvserver(IObserver o);
	void NotifyObserver();
}
