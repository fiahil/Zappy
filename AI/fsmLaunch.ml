(*
 * Fiahil
 * 10.07.2012
 *)

let func = ref (fun _ -> ())
let func_last = ref (fun _ -> ())
let func_param = ref []
let count = ref 0

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

let run () =

  let rec aux () =

    let treat_mineral = function
      | (true, _) -> true
      | (false, ret) ->
          begin
	    FsmGather.gather ret;
	    false
	  end
      in
    begin
      Bridge.init ();
      Broadcast_ic.test_rcp (Broadcast.pp Bridge.take);
      count := (!count - 1);
      if !Broadcast_ic.ic_mode = 1 &&
	!PlayerInventory.piv.Inventory.nourriture > (8 + !MapSize.size_coef) then
        (if !Broadcast_ic.ic_lvl = !FsmBase.plvl then
            Broadcast_ic.engage ())
      else if !Broadcast_ic.ic_mode = 2 &&
	     !PlayerInventory.piv.Inventory.nourriture > (8 + !MapSize.size_coef) then
        Exchange_ic.engage ()
      else if (FsmIncant.test_food () = false) then
	FsmSurvival.survival []
      else if ((treat_mineral (FsmIncant.test_mineral ())) = false) then
	()
      else if (!count <= 0) then
	(if ((FsmIncant.incant ()) = false) then
	    count := (Random.int 5))
      else
	()
      ;
      aux ()
    end
  in
  FsmBase.gather_all ();
  aux ()
