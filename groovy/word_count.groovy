import groovy.time.TimeCategory
import groovy.time.TimeDuration

/**
 * Created by arthur.xw on 2015/5/15.
 */

def processWordsInFile(file, process) {
    file.splitEachLine(/\W+/) {
        matched -> matched.each {
            w -> if (w) process(w)
        }
    }
}

testfile = new File('text')
testfile1 = new File('text1')
testfile2 = new File('text2')

count = 0
processWordsInFile(testfile) { count++ }
println count

words = 0; numbers = 0; separator = 0;
st = new StreamTokenizer(testfile.newReader())
st.slashSlashComments(true)
while (st.nextToken() != StreamTokenizer.TT_EOF) {
    if (st.ttype == StreamTokenizer.TT_WORD) words++
    else if (st.ttype == StreamTokenizer.TT_NUMBER) numbers++
    else if (st.ttype == StreamTokenizer.TT_EOL) println("EOL")
    else separator++//all branch need to be declared, ttype value is ASCII when token just has one char
}
println "Found $words word and $numbers numbers and $separator separator."

def start = new Date()
seen = [:]
[testfile, testfile1, testfile2].each {
    file -> processWordsInFile(file) {
        w = it.toLowerCase()
        if (seen.containsKey(w)) seen[w] += 1
        else seen[w] = 1
    }
}
def end = new Date()
TimeDuration duration = TimeCategory.minus(end, start)
println 'time spent: ' + duration

seen.entrySet().sort {
    a,b -> b.value <=> a.value
}.each {
    e -> printf("%5d %s\n", [e.value, e.key])
}
