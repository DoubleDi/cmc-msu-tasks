(defun eeq(l) (eeeq (cdr l) (car l)))

(defun eeeq(l x)
    (cond ((null x)nil)
          ((null l)T)
          ((eq (car l) x)(eeeq (cdr l) x))))

(eeq '(a a a))
