 (*
  *  Busina
  *  13.07.12
  *)

let child = ref []

let run () =

  let rec launch_fork = function
    | 0 -> ()
    | nb ->
      Bridge.push Bridge.Fork;
      ignore (Bridge.pull Bridge.Fork);
      launch_fork (nb - 1)
  in

  let rec connect_soldier = function
    | 0  -> ()
    | nb ->
      child := ((Unix.create_process Sys.argv.(0)
		   [|
		     Sys.argv.(0);
		     "-n";
		     !Param.team;
		     "-h";
		     !Param.host;
		     "-p";
		     (string_of_int !Param.port);
		     "-s"
		   |]
		   Unix.stdin Unix.stdout Unix.stderr)::(!child));
      print_endline "Des BEBES !!! plein de bebes !";
      connect_soldier (nb - 1)
  in

  let test_connect qt =
    Printf.printf "jep eu faire %d bebes\n" qt;
    flush stdout;
    match qt with
      | 0  -> ()
      | nb -> connect_soldier nb
  in

  let rec cycle () =
    Bridge.init ();
    Bridge.push Bridge.Connect_nbr;
    test_connect (Bridge.connect (Bridge.pull Bridge.Connect_nbr));
    FsmSurvival.min_survival [];
    cycle ()
  in

  Bridge.init ();
  launch_fork 8;
  cycle ()
