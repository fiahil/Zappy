(*
 * Fiahil
 * 12.07.2012
 *)

let ex_fp = ref ""
let ex_ll = ref []

let engage () =
  let rec aux = function
    | []                                -> true
    | (Inventory.Nourriture, v)::tail   ->
        if !PlayerInventory.piv.Inventory.nourriture = v then
          aux tail
        else
          false
    | (Inventory.Linemate, v)::tail     ->
        if !PlayerInventory.piv.Inventory.linemate = v then
          aux tail
        else
          false
    | (Inventory.Deraumere, v)::tail    ->
        if !PlayerInventory.piv.Inventory.deraumere = v then
          aux tail
        else
          false
    | (Inventory.Sibur, v)::tail        ->
        if !PlayerInventory.piv.Inventory.sibur = v then
          aux tail
        else
          false
    | (Inventory.Mendiane, v)::tail     ->
        if !PlayerInventory.piv.Inventory.mendiane = v then
          aux tail
        else
          false
    | (Inventory.Phiras, v)::tail       ->
        if !PlayerInventory.piv.Inventory.phiras = v then
          aux tail
        else
          false
    | (Inventory.Thystame, v)::tail     ->
        if !PlayerInventory.piv.Inventory.thystame = v then
          aux tail
        else
          false
    | (Inventory.Joueur, v)::tail     ->
        if !PlayerInventory.piv.Inventory.joueur = v then
          aux tail
        else
          false
  in
  if aux !ex_ll then
    Broadcast.bc (Broadcast.Rsh (!ex_fp, !PlayerInventory.pid))
