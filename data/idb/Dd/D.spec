product D
    id "A text file"
    image man
        id "Man Pages"
        version 1
        order 9999
        subsys relnotes
            id "Release Notes"
            replaces self
            exp D.man.relnotes
        endsubsys
    endimage
    image books
        id "Books"
        version 2
        order 9999
        subsys userguide
            id "User Guide"
            replaces self
            exp D.books.userguide
        endsubsys
    endimage
endproduct
