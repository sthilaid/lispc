(define (fact n)
  (if (< n 2)
      1
      (* n (fact (- n 1)))))

(define i 0)
(define pos (cons 10 10))
(define vel (cons 10 5))
(define accel (cons 10 10))
(define size (cons 10 10))
(define colors (list color::red color::green color::blue  
                     color::purple color::cyan color::white color::black))

(define (sign x) (if (< x 0) -1 1))

(define (update-square dt)
  (define-macro (update-var! cell delta-cell min max)
    `(begin (set! ,cell (+ ,cell (* ,delta-cell dt)))
            (if (< (abs ,cell) ,min)
                (begin
                  (set! ,cell (* (sign ,cell) ,min))
                  (set! ,delta-cell (- ,delta-cell))))
            (if (> (abs ,cell) ,max)
                (begin
                  (set! ,cell (* (sign ,cell) ,max))
                  (set! ,delta-cell (- ,delta-cell))))))
  (update-var! (car pos) (car vel) 1 (- 128 (car size)))
  (update-var! (cdr pos) (cdr vel) 1 (- 128 (cdr size)))
  (update-var! (car vel) (car accel) 10 40)
  (update-var! (cdr vel) (cdr accel) 10 40))

(define (draw-square)
  (let ((x (floor (car pos)))
        (y (floor (cdr pos)))
        (w (car size))
        (h (cdr size)))
    (rect x y w h color::yellow)))

(define (display-vect v)
  (format #f "[~,2F ~,2F]" (car v) (cdr v)))

(define (update dt)
  ;;(randomize_video_mem)
  (let* ((index (modulo (floor (/ i 60)) (length colors)))
         (color (list-ref colors index)))
    (cls color)
    (set! i (+ i 1)))
  
  (update-square dt)
  (draw-square)
    
  (display `(dt: ,(format #f "~,3F" dt) fact10: ,(fact 10)))
  (newline)
  (display `(pos ,(display-vect pos) vel ,(display-vect vel) accel: ,(display-vect accel)))
  (newline))
