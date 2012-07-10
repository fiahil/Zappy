(*
 * Fiahil
 * 10.07.2012
 *)

let func = ref (fun _ -> ())
let func_last = ref (fun _ -> ())
let func_param = ref []

let set f =
  begin
    func_last := !func;
    func := f
  end

let set_param l =
  func_param := l

let reset () =
  let swap a b =
    begin
      func := a;
      func_last := b
    end
  in
  swap !func_last !func

let rec run () =
  begin
    !func !func_param;
    run ()
  end
