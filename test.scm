(define (fact n)
  (if (< n 2)
      1
      (* n (fact (- n 1)))))

(define i 0)

(define (update dt)
  ;;(randomize_video_mem)
  (let ((colors (list color::red color::green color::blue  
                      color::purple color::yellow color::cyan color::white color::black)))
    (let* ((index (modulo (floor (/ i 60)) (length colors)))
           (color (list-ref colors index)))
      (cls color)
      (rect 0.3 0.3 0.6 0.6 color)
      (display `(dt: ,dt fact10: ,(fact 100) color: ,color i: ,i))
      (newline)
      (set! i (+ i 1)))))
