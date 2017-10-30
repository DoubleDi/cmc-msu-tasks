(defun ff(l)
    (cond ((null l)nil)
          (T(cons (car l) (ff (ff (cdr l)))))))

(ff '(1 2 3 4 5))
