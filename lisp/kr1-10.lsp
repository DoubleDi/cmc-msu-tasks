(defun vstavka(l) (vst l ()))
(defun vst(l x)
    (cond ((null l)x)
          (T(vst (cdr l) (vs (car l) x)))))

(defun vs(a x)
    (cond ((null x)(list a))
          ((> a (car x))(cons (car x) (vs a (cdr x))))
          (T(append (list a (car x)) (cdr x)))))

(vstavka '(9  5 6 1 4 5 2 3 7 ))
