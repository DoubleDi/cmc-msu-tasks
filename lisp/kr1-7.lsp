(defun insatom(a l)
    (cond ((null l)())
          (T(cons (cons a (car l))(insatom a (cdr l))))))

(insAtom '7 '(()()()))
