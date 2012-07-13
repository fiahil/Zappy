(*
 * Fiahil
 * 12.07.2012
 *)

let ex_fp = ref ""
let ex_ll = ref []

let rec moving = function
  | Broadcast.Rsz id    ->
      Bridge.init ();
      if id = !ex_fp then
        if FsmIncant.test_crit_food () && Utils.move_to (Broadcast.gd ()) then
          Broadcast.bc (Broadcast.Rsr (!ex_fp, true))
        else if FsmIncant.test_crit_food () then
          moving (Broadcast.pp Bridge.pull)
        else if FsmIncant.test_crit_food () then
          moving (Broadcast.pp Bridge.pull)
  | Broadcast.Rsa fp    ->
      Bridge.init ();
      if (fp = !ex_fp) then
        ()
      else if FsmIncant.test_crit_food () then
        moving (Broadcast.pp Bridge.pull)
  | _                   ->
      if FsmIncant.test_crit_food () then
        moving (Broadcast.pp Bridge.pull)

let drop_all l =
  let rec aux v n =
    if n > 0 then
      begin
        Bridge.push (Bridge.Pose v);
        aux v (n - 1)
      end
  in
  let rec auxx = function
    | []                -> ()
    | (v, n)::tail      -> aux v n
  in
  auxx l

let rec test_rsc = function
  | Broadcast.Rsc (fp, id)      ->
      if fp = !ex_fp && !PlayerInventory.pid = id then
        true
      else if fp = !ex_fp then
        false
      else
        test_rsc (Broadcast.pp Bridge.pull)
  | Broadcast.Rsa fp            ->
      if fp = !ex_fp then
        false
      else
        test_rsc (Broadcast.pp Bridge.pull)
  | _                           -> test_rsc (Broadcast.pp Bridge.pull)

let engage () =
  let rec aux = function
    | []                                -> true
    | (Inventory.Nourriture, v)::tail   ->
        if !PlayerInventory.piv.Inventory.nourriture >= v then
          aux tail
      else
        false
    | (Inventory.Linemate, v)::tail     ->
        if !PlayerInventory.piv.Inventory.linemate >= v then
          aux tail
        else
          false
    | (Inventory.Deraumere, v)::tail    ->
        if !PlayerInventory.piv.Inventory.deraumere >= v then
          aux tail
        else
          false
    | (Inventory.Sibur, v)::tail        ->
        if !PlayerInventory.piv.Inventory.sibur >= v then
          aux tail
        else
          false
    | (Inventory.Mendiane, v)::tail     ->
        if !PlayerInventory.piv.Inventory.mendiane >= v then
          aux tail
        else
          false
    | (Inventory.Phiras, v)::tail       ->
        if !PlayerInventory.piv.Inventory.phiras >= v then
          aux tail
        else
          false
    | (Inventory.Thystame, v)::tail     ->
        if !PlayerInventory.piv.Inventory.thystame >= v then
          aux tail
        else
          false
    | (Inventory.Joueur, v)::tail       ->
        if !PlayerInventory.piv.Inventory.joueur >= v then
          aux tail
        else
          false
  in
  if aux !ex_ll then
    begin
      Broadcast.bc (Broadcast.Rsh (!ex_fp, !PlayerInventory.pid));
      if test_rsc (Broadcast.pp Bridge.pull) then
        begin
          moving (Broadcast.pp Bridge.pull);
          drop_all !ex_ll;
          Broadcast.bc (Broadcast.Rse !ex_fp)
        end
    end
