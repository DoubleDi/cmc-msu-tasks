(defun removelast (l)
    (cond ((null l)l)
          ((null (cdr l)) ())
          ((cons (car l) (removelast (cdr l))))))


(defun p() '(((5)A)()))
(RemoveLast '(()))
