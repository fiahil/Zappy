(*
 * Fiahil
 * 10.07.2012
 *)

let ic_fp = ref ""
let ic_id = ref (Random.int 100000)

let rec moving = function
  | Broadcast.Icz id    ->
      if id = !ic_fp then
        print_endline "OK"
      else
        moving (Broadcast.pp Bridge.pull)
  | _                   -> ()

let rec test_ici () =
  match Broadcast.pp Bridge.pull with
    | Broadcast.Ici (fp, l)     ->
        if fp = !ic_fp && List.exists (fun v -> v = !ic_id) l then
          true
        else
          test_ici ()
    | _                 -> false

let rec test_rcp () =
  match Broadcast.pp Bridge.take with
    | Broadcast.Icq (fp, lvl)   ->
        begin
          ic_fp := fp;
          lvl
        end
    | Broadcast.Err ""          -> 0
    | _                 -> test_rcp ()

let engage () =
  begin
    Broadcast.bc (Broadcast.Icr (!ic_fp, !ic_id, false));
    if test_ici () then
      moving (Broadcast.pp Bridge.pull)
  end
