;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;; https://www.gnu.org/software/emacs/manual/html_node/ccmode/c_002doffsets_002dalist.html

;; c-offsets-alist is a variable defined in ‘cc-vars.el’.
;; Its value is shown below.
;;
;;   Automatically becomes buffer-local when set.
;;   You can customize this variable.
;;   Probably introduced at or before Emacs version 19.23.
;;
;; Documentation:
;; Association list of syntactic element symbols and indentation offsets.
;; As described below, each cons cell in this list has the form:
;;
;;     (SYNTACTIC-SYMBOL . OFFSET)
;;
;; When a line is indented, CC Mode first determines the syntactic
;; context of it by generating a list of symbols called syntactic
;; elements.  The global variable ‘c-syntactic-context’ is bound to that
;; list.  Each element in the list is in turn a list where the first
;; element is a syntactic symbol which tells what kind of construct the
;; indentation point is located within.  More elements in the syntactic
;; element lists are optional.  If there is one more and it isn’t nil,
;; then it’s the anchor position for that construct.
;;
;; After generating the syntactic context for the line, CC Mode
;; calculates the absolute indentation: First the base indentation is
;; found by using the anchor position for the first syntactic element
;; that provides one.  If none does, zero is used as base indentation.
;; Then CC Mode looks at each syntactic element in the context in turn.
;; It compares the car of the syntactic element against the
;; SYNTACTIC-SYMBOL’s in ‘c-offsets-alist’.  When it finds a match, it
;; adds OFFSET to the base indentation.  The sum of this calculation is
;; the absolute offset for line being indented.
;;
;; If the syntactic element does not match any in the ‘c-offsets-alist’,
;; the element is ignored.
;;
;; OFFSET can specify an offset in several different ways:
;;
;;   If OFFSET is nil then it’s ignored.
;;
;;   If OFFSET is an integer then it’s used as relative offset, i.e. it’s
;;   added to the base indentation.
;;
;;   If OFFSET is one of the symbols ‘+’, ‘-’, ‘++’, ‘--’, ‘*’, or ‘/’
;;   then a positive or negative multiple of ‘c-basic-offset’ is added to
;;   the base indentation; 1, -1, 2, -2, 0.5, and -0.5, respectively.
;;
;;   If OFFSET is a symbol with a value binding then that value, which
;;   must be an integer, is used as relative offset.
;;
;;   If OFFSET is a vector then its first element, which must be an
;;   integer, is used as an absolute indentation column.  This overrides
;;   the previous base indentation and the relative offsets applied to
;;   it, and it becomes the new base indentation.
;;
;;   If OFFSET is a function or a lambda expression then it’s called with
;;   a single argument containing the cons of the syntactic symbol and
;;   the anchor position (or nil if there is none).  The return value
;;   from the function is then reinterpreted as an offset specification.
;;
;;   If OFFSET is a list then its elements are evaluated recursively as
;;   offset specifications.  If the first element is any of the symbols
;;   below then it isn’t evaluated but instead specifies how the
;;   remaining offsets in the list should be combined.  If it’s something
;;   else then the list is combined according the method ‘first’.  The
;;   valid combination methods are:
;;
;;   ‘first’ -- Use the first offset (that doesn’t evaluate to nil).
;;   ‘min’   -- Use the minimum of all the offsets.  All must be either
;;              relative or absolute - they can’t be mixed.
;;   ‘max’   -- Use the maximum of all the offsets.  All must be either
;;              relative or absolute - they can’t be mixed.
;;   ‘add’   -- Add all the evaluated offsets together.  Exactly one of
;;              them may be absolute, in which case the result is
;;              absolute.  Any relative offsets that preceded the
;;              absolute one in the list will be ignored in that case.
;;
;; ‘c-offsets-alist’ is a style variable.  This means that the offsets on
;; this variable are normally taken from the style system in CC Mode
;; (see ‘c-default-style’ and ‘c-style-alist’).  However, any offsets
;; put explicitly on this list will override the style system when a CC
;; Mode buffer is initialized (there is a variable
;; ‘c-old-style-variable-behavior’ that changes this, though).
;;
;; Here is the current list of valid syntactic element symbols:
;;
;;  string                 -- Inside multi-line string.
;;  c                      -- Inside a multi-line C style block comment.
;;  defun-open             -- Brace that opens a function definition.
;;  defun-close            -- Brace that closes a function definition.
;;  defun-block-intro      -- The first line in a top-level defun.
;;  class-open             -- Brace that opens a class definition.
;;  class-close            -- Brace that closes a class definition.
;;  inline-open            -- Brace that opens an in-class inline method.
;;  inline-close           -- Brace that closes an in-class inline method.
;;  func-decl-cont         -- The region between a function definition’s
;;                            argument list and the function opening brace
;;                            (excluding K&R argument declarations).  In C, you
;;                            cannot put anything but whitespace and comments
;;                            between them; in C++ and Java, throws declarations
;;                            and other things can appear in this context.
;;  knr-argdecl-intro      -- First line of a K&R C argument declaration.
;;  knr-argdecl		-- Subsequent lines in a K&R C argument declaration.
;;  topmost-intro		-- The first line in a topmost construct definition.
;;  topmost-intro-cont	-- Topmost definition continuation lines.
;;  annotation-top-cont    -- Topmost definition continuation line where only
;;  			   annotations are on previous lines.
;;  annotation-var-cont    -- A continuation of a C (or like) statement where
;;  			   only annotations are on previous lines.
;;  member-init-intro	-- First line in a member initialization list.
;;  member-init-cont	-- Subsequent member initialization list lines.
;;  inher-intro		-- First line of a multiple inheritance list.
;;  inher-cont             -- Subsequent multiple inheritance lines.
;;  block-open             -- Statement block open brace.
;;  block-close            -- Statement block close brace.
;;  brace-list-open        -- Open brace of an enum or static array list.
;;  brace-list-close       -- Close brace of an enum or static array list.
;;  brace-list-intro       -- First line in an enum or static array list.
;;  brace-list-entry       -- Subsequent lines in an enum or static array list.
;;  brace-entry-open       -- Subsequent lines in an enum or static array
;;                            list that start with an open brace.
;;  statement              -- A C (or like) statement.
;;  statement-cont         -- A continuation of a C (or like) statement.
;;  statement-block-intro  -- The first line in a new statement block.
;;  statement-case-intro   -- The first line in a case "block".
;;  statement-case-open    -- The first line in a case block starting with brace.
;;  substatement           -- The first line after an if/while/for/do/else.
;;  substatement-open      -- The brace that opens a substatement block.
;;  substatement-label     -- Labeled line after an if/while/for/do/else.
;;  case-label             -- A "case" or "default" label.
;;  access-label           -- C++ private/protected/public access label.
;;  label                  -- Any ordinary label.
;;  do-while-closure       -- The "while" that ends a do/while construct.
;;  else-clause            -- The "else" of an if/else construct.
;;  catch-clause           -- The "catch" or "finally" of a try/catch construct.
;;  comment-intro          -- A line containing only a comment introduction.
;;  arglist-intro          -- The first line in an argument list.
;;  arglist-cont           -- Subsequent argument list lines when no
;;                            arguments follow on the same line as the
;;                            arglist opening paren.
;;  arglist-cont-nonempty  -- Subsequent argument list lines when at
;;                            least one argument follows on the same
;;                            line as the arglist opening paren.
;;  arglist-close          -- The solo close paren of an argument list.
;;  stream-op              -- Lines continuing a stream operator construct.
;;  inclass                -- The construct is nested inside a class definition.
;;                            Used together with e.g. ‘topmost-intro’.
;;  cpp-macro              -- The start of a C preprocessor macro definition.
;;  cpp-macro-cont         -- Inside a multi-line C preprocessor macro definition.
;;  friend                 -- A C++ friend declaration.
;;  objc-method-intro      -- The first line of an Objective-C method definition.
;;  objc-method-args-cont  -- Lines continuing an Objective-C method definition.
;;  objc-method-call-cont  -- Lines continuing an Objective-C method call.
;;  extern-lang-open       -- Brace that opens an "extern" block.
;;  extern-lang-close      -- Brace that closes an "extern" block.
;;  inextern-lang          -- Analogous to the ‘inclass’ syntactic symbol,
;;                            but used inside "extern" blocks.
;;  namespace-open, namespace-close, innamespace
;;                         -- Similar to the three ‘extern-lang’ symbols, but for
;;                            C++ "namespace" blocks.
;;  module-open, module-close, inmodule
;;                         -- Similar to the three ‘extern-lang’ symbols, but for
;;                            CORBA IDL "module" blocks.
;;  composition-open, composition-close, incomposition
;;                         -- Similar to the three ‘extern-lang’ symbols, but for
;;                            CORBA CIDL "composition" blocks.
;;  template-args-cont     -- C++ template argument list continuations.
;;  inlambda               -- In the header or body of a lambda function.
;;  lambda-intro-cont      -- Continuation of the header of a lambda function.
;;  inexpr-statement       -- The statement is inside an expression.
;;  inexpr-class           -- The class is inside an expression.  Used e.g. for
;;                            Java anonymous classes.

;; https://www.gnu.org/software/emacs/manual/html_node/ccmode/Adding-Styles.html
(c-add-style "alpine-toolkit"
	     ;; ([base-style] [(variable . value) …])
             '("gnu"
               (c-basic-offset . 2)
               (c-offsets-alist
                (access-label . -)
                (annotation-top-cont . 0)
                (annotation-var-cont . +)
                (arglist-close . c-lineup-arglist)
                (arglist-cont c-lineup-gcc-asm-reg 0)
                (arglist-cont-nonempty c-lineup-gcc-asm-reg c-lineup-arglist)
                (arglist-intro . c-lineup-arglist-intro-after-paren)
                (block-close . 0)
                (block-open . 0)
                (brace-entry-open . 0)
                (brace-list-close . 0)
                (brace-list-entry . 0)
                (brace-list-intro first c-lineup-2nd-brace-entry-in-arglist c-lineup-class-decl-init-+ +)
                (brace-list-open . +)
                (c . c-lineup-C-comments)
                (case-label . 0)
                (catch-clause . 0)
                (class-close . 0)
                (class-open . 0)
                (comment-intro c-lineup-knr-region-comment c-lineup-comment)
                (composition-close . 0)
                (composition-open . 0)
                (cpp-define-intro c-lineup-cpp-define +)
                (cpp-macro . [0])
                (cpp-macro-cont . +)
                (defun-block-intro . +)
                (defun-close . 0)
                (defun-open . 0)
                (do-while-closure . 0)
                (else-clause . 0)
                (extern-lang-close . 0)
                (extern-lang-open . 0)
                (friend . 0)
                (func-decl-cont . +)
                (inclass . +)
                (incomposition . +)
                (inexpr-class . +)
                (inexpr-statement . +)
                (inextern-lang . +)
                (inher-cont . c-lineup-multi-inher)
                (inher-intro . +)
                (inlambda . 0)
                (inline-close . 0)
                (inline-open . 0)
                (inmodule . +)
                (innamespace . 0)
                (knr-argdecl . 0)
                (knr-argdecl-intro . 5)
                (label . 0)
                (lambda-intro-cont . +)
                (member-init-cont . c-lineup-multi-inher)
                (member-init-intro . +)
                (module-close . 0)
                (module-open . 0)
                (namespace-close . 0)
                (namespace-open . 0)
                (objc-method-args-cont . c-lineup-ObjC-method-args)
                (objc-method-call-cont c-lineup-ObjC-method-call-colons c-lineup-ObjC-method-call +)
                (objc-method-intro . [0])
                (statement . 0)
                (statement-block-intro . +)
                (statement-case-intro . +)
                (statement-case-open . +)
                (statement-cont . +)
                (stream-op . c-lineup-streamop)
                (string . c-lineup-dont-change)
                (substatement . +)
                (substatement-label . 0)
                (substatement-open . +)
                (template-args-cont c-lineup-template-args +)
                (topmost-intro . 0)
                (topmost-intro-cont first c-lineup-topmost-intro-cont c-lineup-gnu-DEFUN-intro-cont)
	        )
               (c-access-key . "\\<\\(signals\\|public\\|protected\\|private\\|public slots\\|protected slots\\|private slots\\):")
	       ))

(defun set-alpine-toolkit-style ()
  (interactive)
  (c-set-style "alpine-toolkit")
  (message "Set Alpine Toolkit C Style.")
  )

;; (defun my-c-setup ())
;; (add-hook 'c++-mode-hook 'my-c-setup)
