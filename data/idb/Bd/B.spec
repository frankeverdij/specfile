product B
    id "A text file"
    image books
        id "Books"
        version 1
        order 9999
        subsys userguide
            id "User Guide"
            replaces self
            exp B.books.userguide
        endsubsys
    endimage
endproduct
