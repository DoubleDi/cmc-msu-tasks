(defun leftbr (l)
    (cond ((null (cdr l))l)
          ((leftbr (cons (list (car l) (cadr l)) (cddr l))))))


(defun p() '(a b c))

(leftbr (p))
