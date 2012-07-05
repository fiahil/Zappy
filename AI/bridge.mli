(*
 * Fiahil
 * 25.06.2012
 *)

type resources =
  | Nourriture
  | Linemate
  | Deraumere
  | Sibur
  | Mendiane
  | Phiras
  | Thystame

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
  | Prend of resources
  | Pose of resources
  | Team of string

(*
 * Send a command to the connected server via socket
 *)
val push : command -> unit

(*
 * Receive a command to the connected server via socket
 *)
val pull : unit -> unit

(*
 * Unitest
 *)
val unitest : unit -> unit
