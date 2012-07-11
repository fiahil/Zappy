 (*
  * Busina
  * 08.07.2012
  *)

let test_food () =
  let to_lvl nb =
    if (nb > 2) then (*TODO*)
      false
    else
      if (!PlayerInventory.piv.Inventory.nourriture > (nb * 3)) then
	true
      else
	false
  in
  let aux = function
    | 1 -> to_lvl 2
    | 2 -> to_lvl 3
    | 3 -> to_lvl 4
    | 4 -> to_lvl 5
    | 5 -> to_lvl 6
    | 6 -> to_lvl 7
    | 7 -> to_lvl 8
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

let incant () =
  let to_lvl_two () =
    Bridge.push (Bridge.Pose Inventory.Linemate);
    Bridge.push Bridge.Incantation
  in
  let aux = function
    | 1 -> to_lvl_two ()
    | 2 -> ()
    | 3 -> ()
    | 4 -> ()
    | 5 -> ()
    | 6 -> ()
    | 7 -> ()
    | _ -> ()
  in
  aux !FsmBase.plvl
