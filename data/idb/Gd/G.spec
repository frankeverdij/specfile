product G
    id "A text file"
    image man
        id "Man Pages"
        version 3
        order 9999
        subsys manpages
            id "Man Pages"
            replaces self
            prereq (
                G.books.userguide 2 maxint
            )
            incompat E.man.manpages 0 1
            exp G.man.manpages
        endsubsys
        subsys relnotes
            id "Release Notes"
            replaces self
            exp G.man.relnotes
        endsubsys
    endimage
    image books
        id "Books"
        version 5
        order 9999
        subsys userguide
            id "User Guide"
            replaces self
            exp G.books.userguide
        endsubsys
    endimage
endproduct
