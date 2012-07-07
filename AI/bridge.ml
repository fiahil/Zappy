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

let bat_re = Array.make 10 (Str.regexp ".*", R_ko RP_empty)

let _ = bat_re.(0) <- (Str.regexp "^[0-9]+\n", R_connect_nbr RP_empty)
let _ = bat_re.(1) <- (Str.regexp "^ok\n", R_ok RP_empty)
let _ = bat_re.(2) <- (Str.regexp "^ko\n", R_ko RP_empty)
let _ = bat_re.(3) <- (Str.regexp "^message [0-8],.*\n", R_broadcast RP_empty)
let _ = bat_re.(4) <- (Str.regexp "^deplacement [1357]\n", R_broadcast RP_empty)
let _ = bat_re.(5) <- (Str.regexp "^elevation en cours\n", R_elevation RP_empty)
let _ = bat_re.(6) <- (Str.regexp "^niveau actuel : [2-8]\n", R_end_incant RP_empty)
let _ = bat_re.(7) <- (Str.regexp "^{nourriture [0-9]+,linemate [0-9]+,deraumere [0-9]+,sibur [0-9]+,mendiane [0-9]+,phiras [0-9]+,thystame [0-9]+}\n", R_inventaire RP_empty)
let _ = bat_re.(8) <- (Str.regexp "^{\\(\\( \\(\\bjoueur\\b\\|\\bnourriture\\b\\|\\blinemate\\b\\|\\bderaumere\\b\\|\\bsibur\\b\\|\\bmendiane\\b\\|\\bphiras\\b\\|\\bthystame\\b\\)\\)*,\\( \\(\\bjoueur\\b\\|\\bnourriture\\b\\|\\blinemate\\b\\|\\bderaumere\\b\\|\\bsibur\\b\\|\\bmendiane\\b\\|\\bphiras\\b\\|\\bthystame\\b\\)\\)*\\)*}\n", R_voir RP_empty)
let _ = bat_re.(9) <- (Str.regexp "^[0-9]+ [0-9]+\n", R_map_size RP_empty)

let push = function
  | Connect_nbr         -> Socket.send "connect_nbr\n"
  | Voir                -> Socket.send "voir\n"
  | Inventaire          -> Socket.send "inventaire\n"
  | Expulse             -> Socket.send "expulse\n"
  | Gauche              -> Socket.send "gauche\n"
  | Droite              -> Socket.send "droite\n"
  | Avance              -> Socket.send "avance\n"
  | Fork                -> Socket.send "fork\n"
  | Incantation         -> Socket.send "incantation\n"
  | Broadcast value     -> Socket.send ("broadcast " ^ value ^ "\n")
  | Prend Inventory.Nourriture    -> Socket.send "prend nourriture\n"
  | Prend Inventory.Linemate      -> Socket.send "prend linemate\n"
  | Prend Inventory.Deraumere     -> Socket.send "prend deraumere\n"
  | Prend Inventory.Sibur         -> Socket.send "prend sibur\n"
  | Prend Inventory.Mendiane      -> Socket.send "prend mendiane\n"
  | Prend Inventory.Phiras        -> Socket.send "prend phiras\n"
  | Prend Inventory.Thystame      -> Socket.send "prend thystame\n"
  | Pose Inventory.Nourriture     -> Socket.send "pose nourriture\n"
  | Pose Inventory.Linemate       -> Socket.send "pose linemate\n"
  | Pose Inventory.Deraumere      -> Socket.send "pose deraumere\n"
  | Pose Inventory.Sibur          -> Socket.send "pose sibur\n"
  | Pose Inventory.Mendiane       -> Socket.send "pose mendiane\n"
  | Pose Inventory.Phiras         -> Socket.send "pose phiras\n"
  | Pose Inventory.Thystame       -> Socket.send "pose thystame\n"
  | Team value          -> Socket.send (value ^ "\n")

let voir_cmd str =
  let rec re = Str.regexp "[{}, ]"
  and
          aux bat = function
    | []                        -> Array.of_list (List.rev bat)
    | (Str.Delim "{")::tail     -> aux bat tail
    | (Str.Delim " ")::tail     -> aux bat tail
    | (Str.Delim "}")::tail     -> aux bat tail
    | (Str.Delim ",")::tail     -> aux ((Inventory.empty ())::bat) tail
    | (Str.Text "nourriture")::tail ->
        aux ((Inventory.inc (List.hd bat) Inventory.Nourriture)::(List.tl bat)) tail
    | (Str.Text "linemate")::tail ->
        aux ((Inventory.inc (List.hd bat) Inventory.Linemate)::(List.tl bat)) tail
    | (Str.Text "deraumere")::tail ->
        aux ((Inventory.inc (List.hd bat) Inventory.Deraumere)::(List.tl bat)) tail
    | (Str.Text "sibur")::tail ->
        aux ((Inventory.inc (List.hd bat) Inventory.Sibur)::(List.tl bat)) tail
    | (Str.Text "mendiane")::tail ->
        aux ((Inventory.inc (List.hd bat) Inventory.Mendiane)::(List.tl bat)) tail
    | (Str.Text "phiras")::tail ->
        aux ((Inventory.inc (List.hd bat) Inventory.Phiras)::(List.tl bat)) tail
    | (Str.Text "thystame")::tail ->
        aux ((Inventory.inc (List.hd bat) Inventory.Thystame)::(List.tl bat)) tail
    | (Str.Text _)::tail        -> aux bat tail
    | _::tail                   -> aux bat tail
  in
    aux [Inventory.empty ()] (Str.full_split re str)

let fill raw = function
  | R_voir _            -> R_voir (RP_voir (voir_cmd raw))
  | _                   -> R_ko RP_empty

let pull () =
  let rec aux idx str =
    if Str.string_match (fst (bat_re.(idx))) str 0 then
      fill str (snd bat_re.(idx))
    else if idx < 9 then
      aux (idx + 1) str
    else
      R_ko RP_empty
  in
    aux 0 (Socket.recv ())

(*
 * Unitest
 *)
let unitest () =
  let see (R_voir (RP_voir bat)) =
    let rec print_nourriture bat =
      begin
        Printf.printf "Nourriture %d\n" bat.Inventory.nourriture;
        Printf.printf "Linemate %d\n" bat.Inventory.linemate;
        Printf.printf "Deraumere %d\n" bat.Inventory.deraumere;
        Printf.printf "Sibur %d\n" bat.Inventory.sibur;
        Printf.printf "Mendiane %d\n" bat.Inventory.mendiane;
        Printf.printf "Phiras %d\n" bat.Inventory.phiras;
        Printf.printf "Thystame %d\n" bat.Inventory.thystame
      end
    and
            aux bat idx =
      if (idx != Array.length bat) then
        begin
          print_nourriture bat.(idx);
          aux bat (idx + 1)
        end
    in
      aux bat 0
  in
  begin
    Socket.connect "127.0.0.1" 4242;
    push (Team "Poney");
    ignore (Unix.select [] [] [] 0.5);
    ignore (pull ());
    ignore (pull ());
    push (Voir);
    ignore (Unix.select [] [] [] 0.5);
    see (pull ())
  end
