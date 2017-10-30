(defun revbr (l) (leftbr (reverse l)))

(defun leftbr (l)
    (cond ((null (cdr l))l)
          ((leftbr (cons (list (car l) (cadr l)) (cddr l))))))


(defun p() '(a b c))

(revbr (p))
