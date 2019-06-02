product F
    id "A text file"
    image man
        id "Man Pages"
        version 3
        order 9999
        subsys manpages
            id "Man Pages"
            replaces self
            prereq (
                F.books.userguide 2 maxint
            )
            incompat E.man.manpages 0 1
            exp F.man.manpages
        endsubsys
        subsys relnotes
            id "Release Notes"
            replaces self
            exp F.man.relnotes
        endsubsys
    endimage
    image books
        id "Books"
        version 5
        order 9999
        subsys userguide default
            id "User Guide"
            replaces self
            exp F.books.userguide
        endsubsys
    endimage
endproduct
