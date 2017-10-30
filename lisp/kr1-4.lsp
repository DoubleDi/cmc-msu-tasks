(defun ch(l) (chet (length l)))

(defun chet(x)
    (cond ((= x 0)T)
          ((= x 1)nil)
          (T(chet (- x 2)))))

(ch '(a a a a) )
