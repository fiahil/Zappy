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

let push v = 
  let aux = function
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
  in
  begin
    aux v;
    ignore (Unix.select [] [] [] 0.5)
  end

let voir_cmd str =
  let rec re = Str.regexp "[{}, ]"
  and
      aux bat = function
        | []                                -> Array.of_list (List.rev bat)
        | (Str.Delim "{")::tail             -> aux bat tail
        | (Str.Delim " ")::tail             -> aux bat tail
        | (Str.Delim "}")::tail             -> aux bat tail
        | (Str.Delim ",")::tail             -> aux ((Inventory.empty ())::bat) tail
        | (Str.Text "nourriture")::tail     ->
          aux ((Inventory.inc (List.hd bat) Inventory.Nourriture)::(List.tl bat)) tail
        | (Str.Text "linemate")::tail       ->
          aux ((Inventory.inc (List.hd bat) Inventory.Linemate)::(List.tl bat)) tail
        | (Str.Text "deraumere")::tail      ->
          aux ((Inventory.inc (List.hd bat) Inventory.Deraumere)::(List.tl bat)) tail
        | (Str.Text "sibur")::tail          ->
          aux ((Inventory.inc (List.hd bat) Inventory.Sibur)::(List.tl bat)) tail
        | (Str.Text "mendiane")::tail       ->
          aux ((Inventory.inc (List.hd bat) Inventory.Mendiane)::(List.tl bat)) tail
        | (Str.Text "phiras")::tail         ->
          aux ((Inventory.inc (List.hd bat) Inventory.Phiras)::(List.tl bat)) tail
        | (Str.Text "thystame")::tail       ->
          aux ((Inventory.inc (List.hd bat) Inventory.Thystame)::(List.tl bat)) tail
        | (Str.Text _)::tail                -> aux bat tail
        | _::tail                           -> aux bat tail
  in
  aux [Inventory.empty ()] (Str.full_split re str)

let inventaire_cmd str =
  let rec re = Str.regexp "[{}, ]"
  and
      aux target iv = function
        | []                                -> iv
        | (Str.Delim "{")::tail             -> aux target iv tail
        | (Str.Delim " ")::tail             -> aux target iv tail
        | (Str.Delim "}")::tail             -> aux target iv tail
        | (Str.Delim ",")::tail             -> aux target iv tail
        | (Str.Text "nourriture")::tail     -> aux Inventory.Nourriture iv tail
        | (Str.Text "linemate")::tail       -> aux Inventory.Linemate iv tail
        | (Str.Text "deraumere")::tail      -> aux Inventory.Deraumere iv tail
        | (Str.Text "sibur")::tail          -> aux Inventory.Sibur iv tail
        | (Str.Text "mendiane")::tail       -> aux Inventory.Mendiane iv tail
        | (Str.Text "phiras")::tail         -> aux Inventory.Phiras iv tail
        | (Str.Text "thystame")::tail       -> aux Inventory.Thystame iv tail
        | (Str.Text value)::tail            ->
          (try
             aux target (Inventory.set iv (int_of_string value) target) tail
           with
             | Failure "int_of_string"     -> aux target iv tail)
        | _::tail                            -> aux target iv tail
  in
  aux Inventory.Nourriture (Inventory.empty ()) (Str.full_split re str)

let incantation_cmd str =
  let rec re = Str.regexp "[2-8]"
  and
      aux = function
        | []                    -> 0
        | (Str.Delim v)::tail   ->
            (try
              int_of_string v
            with
              | Failure "int_of_string" -> 0)
        | _::tail               -> aux tail
  in
    aux (Str.full_split re str)

let expulse_cmd str =
  let rec re = Str.regexp "[1357]"
  and
      aux = function
        | []                    -> 0
        | (Str.Delim v)::tail   ->
            (try
               int_of_string v
             with
               | Failure "int_of_string" -> 0)
        | _::tail               -> aux tail
  in
    aux (Str.full_split re str)

let broadcast_cmd str =
  let rec re = Str.regexp ","
  and
      extract_dir str =
    print_endline str;
    try
      int_of_string (String.sub str (String.length str - 1) 1)
    with
      | _       -> 0
  and
      aux l = (extract_dir (List.hd l)), (List.hd (List.tl l))
  in
    aux (Str.bounded_split re str 2)

let map_cmd str =
  let rec re = Str.regexp " "
  and
      aux l =
    try
      (int_of_string (List.hd l)), (int_of_string (List.hd (List.tl l)))
    with
      | _       -> (0, 0)
  in
    aux (Str.bounded_split re str 2)

let connect_cmd str =
  try
    int_of_string str
  with
    | _         -> 0

let fill raw = function
  | R_voir _            -> R_voir (RP_voir (voir_cmd raw))
  | R_inventaire _      -> R_inventaire (RP_inventaire (inventaire_cmd raw))
  | R_end_incant _      -> R_end_incant (RP_incantation  (incantation_cmd raw))
  | R_elevation _       -> R_elevation RP_empty
  | R_expulse _         -> R_expulse (RP_expulse (expulse_cmd raw))
  | R_broadcast _       -> R_broadcast (RP_broadcast (broadcast_cmd raw))
  | R_ko _              -> R_ko RP_empty
  | R_ok _              -> R_ok RP_empty
  | R_map_size _        -> R_map_size (RP_map_size (map_cmd raw))
  | R_connect_nbr _     -> R_connect_nbr (RP_connect (connect_cmd raw))

let pull v = 
  let rec aux str = function
    | Voir      ->
        if Str.string_match (fst (bat_re.(8))) str 0 then
          fill str (snd bat_re.(8))
        else
          aux (Socket.recv ()) Voir
    | _         -> R_ok RP_empty
  in
    aux (Socket.recv ()) v

(*
 * Unitest
 *)
let unitest () =
  (*
  let see (R_voir (RP_voir bat)) =
    let rec print_iv bat =
      begin
        Printf.printf "Nourriture %d\n" bat.Inventory.nourriture;
        Printf.printf "Linemate %d\n" bat.Inventory.linemate;
        Printf.printf "Deraumere %d\n" bat.Inventory.deraumere;
        Printf.printf "Sibur %d\n" bat.Inventory.sibur;
        Printf.printf "Mendiane %d\n" bat.Inventory.mendiane;
        Printf.printf "Phiras %d\n" bat.Inventory.phiras;
        Printf.printf "Thystame %d\n" bat.Inventory.thystame
      end
    in
      print_iv bat.(0)
  in*)
    begin
      Socket.connect "127.0.0.1" 4242;
      push (Team "Poney");
      push (Voir);
      (*see (pull Voir);*)
      Printf.printf "%d\n" (fst (map_cmd "666 888"))
    end
