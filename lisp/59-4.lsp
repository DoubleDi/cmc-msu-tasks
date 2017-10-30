(defun lastatom (l)
    (cond ((atom l)l)
          ((null (cdr l)) (lastatom(car l)))
          ((lastatom (cdr l)))))


(defun p() '(((5)A)()))

(lastatom (p))
