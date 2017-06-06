import groovy.time.TimeCategory
import groovy.time.TimeDuration
import static groovyx.gpars.GParsPool.runForkJoin
import groovyx.gpars.GParsPool
@Grab(group='org.codehaus.gpars', module = 'gpars', version = '1.2.1')
class Config{
    static DATA_COUNT = 2**14
    static GRANULARITY_THRESHHOLD =128
    static THREADS = 4
}

items = [] as List<Integer>
items.addAll(1..Config.DATA_COUNT)
Collections.shuffle(items)
def start = new Date()
GParsPool.withPool(Config.THREADS) {
    computeMax = runForkJoin(1, Config.DATA_COUNT, items.asImmutable()) {
        begin, end, items ->
            int size = end - begin
            if (size <= Config.GRANULARITY_THRESHHOLD) {
                return items[begin..<end].max()
            } else {
                leftEnd = begin + ((end + 1 - begin) / 2)
                forkOffChild(begin, leftEnd, items)
                forkOffChild(leftEnd + 1, end, items)
                return childrenResults.max()
            }
    }
    println "expectedMax = ${Config.DATA_COUNT}"
    println "computedMax = ${computeMax}"
}
def end = new Date()
TimeDuration duration = TimeCategory.minus(end, start)
println 'time spent: ' + duration