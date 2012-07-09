(*
 * Player inventory
 *)
val piv : Inventory.t ref

(*
 * Valid or reset the player inventory
 *)
val valid : Inventory.t -> unit
