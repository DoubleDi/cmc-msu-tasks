
(defun check(x) (
    cond((atom x) nil)
        ((and (atom (cdr x)) (atom (car x))) (null (cdr x)))
        ((atom (car x)) (check (cdr x)))
        ((atom (cdr x)) (and (null (cdr x)) (check (car x))))
        (T (and (check (car x)) (check (cdr x))))))

(defun t() 'a)

(check (t))
