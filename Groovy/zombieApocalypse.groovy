import groovyx.gpars.agent.Agent
import groovyx.gpars.GParsExecutorsPool

public class World {
    int alive = 1000
    int undead = 10

    public void eatBrains() {
        alive = alive - undead
        undead = undead * 2
        if (alive <= 0) {
            alive = 0
            println "ZOMBIE APOCALYPSE!"
        }
    }

    public void shotgun() {
        undead = undead * 0.95
    }

    public boolean apocalypse() {
        alive <= 0
    }

    public void report() {
        if (alive > 0) {
            println "alive=" + alive + " undead="+ undead
        }
    }
}

@Grab(group = 'org.codehaus.gpars', module = 'gpars', version = '1.2.1')
def final world = new Agent<World>(new World())

final Thread zombies = Thread.start {
    while (!world.val.apocalypse()) {
        world << { it.eatBrains() }
        sleep 200
    }
}

final Thread survivors = Thread.start {
    while (!world.val.apocalypse()) {
        world << { it.shotgun() }
        sleep 200
    }
}

while (!world.instantVal.apocalypse()) {
    world.val.report()
    sleep 200
}