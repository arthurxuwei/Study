import groovy.xml.MarkupBuilder

/**
 * Created by arthur.xw on 2015/5/15.
 */

/*
<person>
    <name>Tom</name>
    <age>33</age>
    <addr>Shenzhen</addr>
</persion>*/

def out = new StringWriter()
def xml = new MarkupBuilder(out)
xml.person {
    name (type:'givenname','Tom')
    age '33'
    addr 'Shenzhen'
}

println out.toString()
