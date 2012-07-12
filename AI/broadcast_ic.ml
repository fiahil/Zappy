(*
 * Fiahil
 * 10.07.2012
 *)

let _ = Random.self_init ()
let ic_fp = ref ""
let ic_lvl = ref 0
let ic_mode = ref 0
let ic_id = ref (Random.int 100000)

let rec garbage = function
  | Broadcast.Ica fp    -> Broadcast.Ica fp
  | Broadcast.Err ""    -> Broadcast.pp Bridge.pull
  | _                   -> Broadcast.pp Bridge.take

let move = function
  | 0           -> true
  | 1           ->
      begin
        Bridge.push (Bridge.Avance);
        false
      end
  | 2           ->
      begin
        Bridge.push (Bridge.Avance);
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        false
      end
  | 3           ->
      begin
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        false
      end
  | 4           ->
      begin
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        false
      end
  | 5           ->
      begin
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Gauche);
        Bridge.push (Bridge.Avance);
        false
      end
  | 6           ->
      begin
        Bridge.push (Bridge.Droite);
        Bridge.push (Bridge.Avance);
        Bridge.push (Bridge.Droite);
        Bridge.push (Bridge.Avance);
        false
      end
  | 7           ->
      begin
        Bridge.push (Bridge.Droite);
        Bridge.push (Bridge.Avance);
        false
      end
  | 8           ->
      begin
        Bridge.push (Bridge.Avance);
        Bridge.push (Bridge.Droite);
        Bridge.push (Bridge.Avance);
        false
      end
  | _           -> false

let rec moving = function
  | Broadcast.Icz id    ->
      if id = !ic_fp then
        if move (Broadcast.gd ()) then
          Broadcast.bc (Broadcast.Icr (!ic_fp, !ic_id, true))
        else
          moving ((Broadcast.pp Bridge.pull))
      else
        moving ((Broadcast.pp Bridge.pull))
  | Broadcast.Ica fp    ->
      if (fp = !ic_fp) then
        ()
      else
        moving ((Broadcast.pp Bridge.pull))
  | _                   -> moving ((Broadcast.pp Bridge.pull))

let rec test_ici = function
    | Broadcast.Ici (fp, l)     ->
        if fp = !ic_fp && List.exists (fun v -> v = !ic_id) l then
          true
        else if fp = !ic_fp then
          false
        else
          test_ici (Broadcast.pp Bridge.pull)
    | Broadcast.Ica fp  ->
        if (fp = !ic_fp) then
          false
        else
          test_ici (Broadcast.pp Bridge.pull)
    | _                 -> test_ici (Broadcast.pp Bridge.pull)

let rec test_rcp = function
    | Broadcast.Icq (fp, lvl)   ->
        begin
          ic_fp := fp;
          ic_lvl := lvl;
          ic_mode := 1
        end
    | Broadcast.Rsn (fp, l)     ->
        begin
          Exchange_ic.ex_fp := fp;
          Exchange_ic.ex_ll := l;
          ic_mode := 2
        end
    | Broadcast.Err ""  -> ic_mode := 0
    | _                 -> test_rcp (Broadcast.pp Bridge.take)

let test_launch v = 
  let rec aux n = function
    | Broadcast.Icl id  ->
        if id = !ic_fp && n = 1 then
          ()
        else if (id = !ic_fp) then
          aux (n + 1) (Broadcast.pp Bridge.pull)
        else
          aux n (Broadcast.pp Bridge.pull)
    | Broadcast.Ica id  ->
        if id = !ic_fp then
          ()
        else
          aux n (Broadcast.pp Bridge.pull)
    | _                 -> aux n (Broadcast.pp Bridge.pull)
  in
  aux 0 v

let engage () =
  begin
    Broadcast.bc (Broadcast.Icr (!ic_fp, !ic_id, false));
    if test_ici (Broadcast.pp Bridge.pull) then
      begin
        moving ((Broadcast.pp Bridge.pull));
        test_launch (Broadcast.pp Bridge.pull)
      end
  end
