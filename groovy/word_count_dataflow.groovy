import groovy.time.TimeCategory
import groovy.time.TimeDuration
import groovyx.gpars.GParsExecutorsPool
import groovyx.gpars.dataflow.DataflowQueue

/**
 * Created by arthur.xw on 2015/5/15.
 */

def processWordsInFile(file, stream, process) {
    file.splitEachLine(/\W+/) {
        matched -> matched.each {
            w -> if (w) process(w)
        }
    }
    stream << "DONE"
}

testfile = new File('text')
testfile1 = new File('text1')
testfile2 = new File('text2')

@Grab(group='org.codehaus.gpars', module = 'gpars', version = '1.2.1')
def start = new Date()
def result = new DataflowQueue()
def files = [testfile, testfile1, testfile2]
GParsExecutorsPool.withPool {
    files.each {
        { query ->
            processWordsInFile(query, result) {
                w = it.toLowerCase()
                result << w.toString()
            }
        }.callAsync(it)
    }
}

int doneMessages = 0
while (doneMessages < files.size()) {
    msg = result.val
    if (msg == "DONE") {
        doneMessages++
    } else {
        println "${msg}"
    }
}

def end = new Date()
TimeDuration duration = TimeCategory.minus(end, start)
println 'time spent: ' + duration

