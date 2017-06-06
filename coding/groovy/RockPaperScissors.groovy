import groovy.time.TimeCategory
import groovy.time.TimeDuration
import groovyx.gpars.actor.Actor
import groovyx.gpars.actor.DefaultActor

@GrabResolver(name='jboss', root='http://repository.jboss.org/maven2/')
@Grab(group='org.codehaus.gpars', module = 'gpars', version = '1.2.1')

class GameMaster extends DefaultActor {
    int secretNum

    void afterStart() {
        secretNum = new Random().nextInt(10)
    }

    void act() {
        loop {
            react { int num ->
                if (num > secretNum)
                    reply 'too large'
                else if (num < secretNum)
                    reply 'too small'
                else {
                    reply 'you win'
                    terminate()
                }
            }
        }
    }
}

class Player extends DefaultActor {
    String name
    Actor server
    int myNum

    void act() {
        loop {
            myNum = new Random().nextInt(10)
            server.send myNum
            react {
                switch (it) {
                    case 'too large': println "$name: $myNum was too large"; break
                    case 'too small': println "$name: $myNum was too small"; break
                    case 'you win': println "$name: I won $myNum"; terminate(); break
                }
            }
        }
    }
}

def master = new GameMaster().start()
def player = new Player(name: 'Player', server: master).start()
def start = new Date()

//this forces main thread to live until both actors stop
[master, player]*.join()

def end = new Date()
TimeDuration duration = TimeCategory.minus(end, start)
println 'time spent: ' + duration