(*
 * Player inventory
 *)
val piv : Inventory.t ref
val pid : int ref

(*
 * Valid or reset the player inventory
 *)
val valid : Inventory.t -> unit
