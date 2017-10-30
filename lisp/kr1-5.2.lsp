(defun newlist(l)
    (cond ((null l)())
          ((null (cadr l))l)
          (T(cons (max (car l)(cadr l)) (newlist (cddr l))))))

(newlist '(1 2 3 4 5 6 7 8 9) )
