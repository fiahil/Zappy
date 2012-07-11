 (*
  * Busina
  * 08.07.2012
  *)

let test_food () =
  let to_lvl nb =
    if (nb > 1) then (*TODO*)
      false
    else
      if (!PlayerInventory.piv.Inventory.nourriture > (nb * 6)) then
	true
      else
	false
  in
  let aux = function
    | 1 -> to_lvl 1
    | 2 -> to_lvl 2
    | 3 -> to_lvl 2
    | 4 -> to_lvl 4
    | 5 -> to_lvl 4
    | 6 -> to_lvl 6
    | 7 -> to_lvl 6
    | _ -> false
  in
  aux !FsmBase.plvl

let test_mineral () =
  let to_lvl_two () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) then
      true
    else
      false
  in
  let to_lvl_three () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) &&
      (!PlayerInventory.piv.Inventory.deraumere > 0) &&
      (!PlayerInventory.piv.Inventory.sibur > 0)
    then
      true
    else
      false
  in
  let to_lvl_four () =
    if (!PlayerInventory.piv.Inventory.linemate > 1) &&
      (!PlayerInventory.piv.Inventory.sibur > 0) &&
      (!PlayerInventory.piv.Inventory.phiras > 1)
    then
      true
    else
      false
  in
  let to_lvl_five () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) &&
      (!PlayerInventory.piv.Inventory.deraumere > 0) &&
      (!PlayerInventory.piv.Inventory.sibur > 1) &&
      (!PlayerInventory.piv.Inventory.phiras > 0)
    then
      true
    else
      false
  in
  let to_lvl_six () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) &&
      (!PlayerInventory.piv.Inventory.deraumere > 1) &&
      (!PlayerInventory.piv.Inventory.sibur > 0) &&
      (!PlayerInventory.piv.Inventory.mendiane > 2)
    then
      true
    else
      false
  in
  let to_lvl_seven () =
    if (!PlayerInventory.piv.Inventory.linemate > 0) &&
      (!PlayerInventory.piv.Inventory.deraumere > 1) &&
      (!PlayerInventory.piv.Inventory.sibur > 2) &&
      (!PlayerInventory.piv.Inventory.phiras > 0)
    then
      true
    else
      false
  in
  let to_lvl_eight () =
    if  (!PlayerInventory.piv.Inventory.linemate > 1) &&
      (!PlayerInventory.piv.Inventory.deraumere > 1) &&
      (!PlayerInventory.piv.Inventory.sibur > 1) &&
      (!PlayerInventory.piv.Inventory.phiras > 1) &&
      (!PlayerInventory.piv.Inventory.mendiane > 1) &&
      (!PlayerInventory.piv.Inventory.thystame > 0)
    then
      true
    else
      false
  in
  let aux = function
    | 1 -> to_lvl_two ()
    | 2 -> to_lvl_three ()
    | 3 -> to_lvl_four ()
    | 4 -> to_lvl_five ()
    | 5 -> to_lvl_six ()
    | 6 -> to_lvl_seven ()
    | 7 -> to_lvl_eight ()
    | _ -> false
  in
  aux !FsmBase.plvl

let call_player nb =
  IncantManager.init_incant_id ();
  Broadcast.bc (Broadcast.Icq (!IncantManager.id, !FsmBase.plvl));
  let rec loop list =
    Bridge.init ();
    (* get resp *)
    if (test_food ()) then
      loop list
    else
      false
  in
  if (loop [] == false) then
    begin
      Broadcast.bc (Broadcast.Ica !IncantManager.id);
      false
    end
  else
    true

let incant () =
  let to_lvl_two () =
    Bridge.push (Bridge.Pose Inventory.Linemate);
    Bridge.push Bridge.Incantation
  in
  let to_lvl_three () =
    if (call_player 2) then
      begin
	Bridge.push (Bridge.Pose Inventory.Linemate);
	Bridge.push (Bridge.Pose Inventory.Deraumere);
	Bridge.push (Bridge.Pose Inventory.Sibur);
	Bridge.push Bridge.Incantation
      end
    else
      ()
  in
  let aux = function
    | 1 -> to_lvl_two ()
    | 2 -> to_lvl_three ()
    | 3 -> ()
    | 4 -> ()
    | 5 -> ()
    | 6 -> ()
    | 7 -> ()
    | _ -> ()
  in
  aux !FsmBase.plvl
