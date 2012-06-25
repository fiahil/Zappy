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
  | Prend of string
  | Pose of string
  | Reponse of string

type action = command * (string -> unit)

let send_queue = Queue.create ()

(*
 * TODO
 *)
let update () =
  true

let push a =
  if Queue.length send_queue < 10 then
    begin
      Queue.push a send_queue;
      true
    end
  else
    false

let discard () =
  try
    ignore (Queue.pop send_queue)
  with
    | Queue.Empty       -> ()

let call () =
  let aux = function
    | (Reponse rep, fct)        -> fct rep
    | _                         -> ()
  in
    try
      aux (Queue.pop send_queue)
    with
      | Queue.Empty     -> ()

let make_action c f = (c, f)

(*
 * Unitest
 *)
let unitest () =
  let _ = push (make_action Incantation print_endline)
  and
      _ = push (make_action (Reponse "Poney") print_endline)
  in
    begin
      discard ();
      call ()
    end

