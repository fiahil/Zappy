(*
 * Fiahil
 * 25.06.2012
 *)

type command =
  | Connect_nbr
  | Voir
  | Inventaire
  | Expulse
  | Gauche
  | Droite
  | Avance
  | Fork
  | Incantation
  | Broadcast of string
  | Prend of Inventory.resources
  | Pose of Inventory.resources
  | Team of string

type response_param =
  | RP_empty
  | RP_inventaire of Inventory.t
  | RP_voir of Inventory.t array
  | RP_incantation of int
  | RP_expulse of int
  | RP_broadcast of (int * string)
  | RP_map_size of (int * int)
  | RP_connect of int

type response =
  | R_map_size of response_param
  | R_connect_nbr of response_param
  | R_ok of response_param
  | R_ko of response_param
  | R_broadcast of response_param
  | R_expulse of response_param
  | R_elevation of response_param
  | R_end_incant of response_param
  | R_inventaire of response_param
  | R_voir of response_param

(*
 * Send a command to the connected server via socket
 *)
val push : command -> unit

(*
 * Receive a command to the connected server via socket
 *)
val pull : command -> response

(*
 * Unitest
 *)
val unitest : unit -> unit
