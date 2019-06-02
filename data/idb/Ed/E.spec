product E
    id "A text file"
    image man
        id "Man Pages"
        version 2
        order 9999
        subsys manpages
            id "Man Pages"
            replaces self
            exp E.man.manpages
        endsubsys
        subsys relnotes
            id "Release Notes"
            replaces self
            exp E.man.relnotes
        endsubsys
    endimage
    image books
        id "Books"
        version 1
        order 9999
        subsys userguide
            id "User Guide"
            replaces self
            exp E.books.userguide
        endsubsys
    endimage
endproduct
