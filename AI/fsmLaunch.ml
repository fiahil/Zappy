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
      if Broadcast_ic.test_rcp (Broadcast.pp Bridge.take) = !FsmBase.plvl then
        Broadcast_ic.engage ()
      else if (FsmIncant.test_food () = false) then
	FsmSurvival.survival []
      else if (FsmIncant.test_mineral () = false) then
	FsmGather.gather [Inventory.Linemate; Inventory.Sibur; Inventory.Deraumere; Inventory.Phiras; Inventory.Mendiane; Inventory.Thystame]
      else
	FsmIncant.incant ()
      ;
      aux ()
    end
  in
  FsmBase.gather_all ();
  aux ()
