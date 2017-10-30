(defun allsumm(S)
    (cond ((numberp S)S)
          ((atom S)0)
          (T(+ (allsumm (car S)) (allsumm (cdr S))))))

(allsumm '((1 . ( 1 . ( 1 . a ))) . (1 . ( 1 . ( 1 . a )))) )
