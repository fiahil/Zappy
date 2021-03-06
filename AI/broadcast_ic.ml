(*
 * Fiahil
 * 10.07.2012
 *)

let ic_fp = ref ""
let ic_lvl = ref 0
let ic_mode = ref 0

let rec garbage = function
  | Broadcast.Ica fp    -> Broadcast.Ica fp
  | Broadcast.Err ""    -> Broadcast.pp Bridge.pull
  | _                   -> Broadcast.pp Bridge.take

let rec moving = function
  | Broadcast.Icz id    ->
      Bridge.init ();
    if (FsmIncant.test_crit_food ()) then
      if id = !ic_fp then
        if Utils.move_to (Broadcast.gd ()) then
          Broadcast.bc (Broadcast.Icr (!ic_fp, !PlayerInventory.pid, true))
        else
          moving ((Broadcast.pp Bridge.pull))
      else
        moving ((Broadcast.pp Bridge.pull))
    else
      ()
  | Broadcast.Ica fp    ->
    Bridge.init ();
    if (FsmIncant.test_crit_food ()) then
      if (fp = !ic_fp) then
	()
      else
	moving ((Broadcast.pp Bridge.pull))
    else
      ()
  | _                   -> moving ((Broadcast.pp Bridge.pull))

let rec test_ici = function
  | Broadcast.Ici (fp, l)     ->
    if (FsmIncant.test_crit_food ()) then
      (if fp = !ic_fp && List.exists (fun v -> v = !PlayerInventory.pid) l then
	  true
       else if fp = !ic_fp then
	false
       else
	 test_ici (Broadcast.pp Bridge.pull))
    else
      false
    | Broadcast.Ica fp  ->
      if (FsmIncant.test_crit_food ()) then
	(if (fp = !ic_fp) then
            false
          else
            test_ici (Broadcast.pp Bridge.pull))
      else
	false
    | _                 ->
      if (FsmIncant.test_crit_food ()) then
        test_ici (Broadcast.pp Bridge.pull)
      else
	false

let rec test_rcp = function
    | Broadcast.Icq (fp, lvl)   ->
        begin
          ic_fp := fp;
          ic_lvl := lvl;
          ic_mode := 1
        end
    | Broadcast.Rsn (fp, l)     ->
        begin
          Exchange_ic.ex_fp := fp;
          Exchange_ic.ex_ll := l;
          ic_mode := 2
        end
    | Broadcast.Err ""  -> ic_mode := 0
    | _                 -> test_rcp (Broadcast.pp Bridge.take)

let test_launch v =
  let rec aux n = function
    | Broadcast.Icl id  ->
      if (FsmIncant.test_crit_food ()) then
        (if id = !ic_fp && n = 1 then
            ()
         else if (id = !ic_fp) then
           aux (n + 1) (Broadcast.pp Bridge.pull)
         else
           aux n (Broadcast.pp Bridge.pull))
      else
	()
    | Broadcast.Ica id  ->
      if (FsmIncant.test_crit_food ()) then
	if id = !ic_fp then
          ()
	else
          aux n (Broadcast.pp Bridge.pull)
      else
	()
    | _                 ->
      if (FsmIncant.test_crit_food ()) then
	aux n (Broadcast.pp Bridge.pull)
      else
	()
  in
  aux 0 v

let engage () =
  begin
    Broadcast.bc (Broadcast.Icr (!ic_fp, !PlayerInventory.pid, false));
    if test_ici (Broadcast.pp Bridge.pull) then
      begin
        moving ((Broadcast.pp Bridge.pull));
	if (FsmIncant.test_crit_food ()) then
	  test_launch (Broadcast.pp Bridge.pull)
	else
	  ()
      end
  end
