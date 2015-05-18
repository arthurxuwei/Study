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

count = 0
processWordsInFile(testfile) { count++ }
println count

words = 0; numbers = 0
st = new StreamTokenizer(testfile.newReader())
st.slashSlashComments(true)
while (st.nextToken() != StreamTokenizer.TT_EOF) {
    if (st.ttype == StreamTokenizer.TT_WORD) words++
    else (st.ttype == StreamTokenizer.TT_NUMBER) numbers++
}
println "Found $words word and $numbers numbers."

seen = [:]
processWordsInFile(testfile) {
    w = it.toLowerCase()
    if (seen.containsKey(w)) seen[w] += 1
    else seen[w] = 1
}

seen.entrySet().sort {
    a,b -> b.value <=> a.value
}.each {
    e -> printf("%5d %s\n", [e.value, e.key])
}