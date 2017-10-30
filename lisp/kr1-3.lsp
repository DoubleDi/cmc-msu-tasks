(defun copyatom(a x)
    (cond ((<= x 0)())
          (T(cons a (copyatom a (- x 1))))))

(copyatom '() 4)
