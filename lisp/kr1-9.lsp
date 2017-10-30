(defun repdep(l) (repd l 0))
(defun repd(l x)
    (cond ((null l)())
          ((atom l)x)
          (T(cons (repd (car l)(+ x 1)) (repd (cdr l)x)))))

(repDep '(((A (5) 8) B (K)) H (G (C))))
