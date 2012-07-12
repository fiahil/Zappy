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

let run () =
  let rec aux () =
    begin
      (* !func !func_param; *)
      Bridge.init ();
      let treat_mineral = function
	| (true, _) -> true
	| (false, ret) ->
	  begin
	    FsmGather.gather ret;
	    false
	  end
      in
      if Broadcast_ic.test_rcp (Broadcast.pp Bridge.take) = !FsmBase.plvl &&
	!PlayerInventory.piv.Inventory.nourriture > 8 then
        Broadcast_ic.engage ()
      else if (FsmIncant.test_food () = false) then
	FsmSurvival.survival []
      else if ((treat_mineral (FsmIncant.test_mineral ())) = false) then
	()
      else
	FsmIncant.incant ()
      ;
      aux ()
    end
  in
  FsmBase.gather_all ();
  aux ()
