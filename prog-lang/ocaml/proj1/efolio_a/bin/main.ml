let rec find_existing_file files =
  match files with
  | [] -> None
  | file :: rest ->
      if Sys.file_exists file then
        Some file
      else
        find_existing_file rest

let database_path () =
  let env_path =
    try Some (Sys.getenv "EFOLIO_DATABASE") with
    | Not_found -> None
  in
  match env_path with
  | Some path when String.trim path <> "" -> path
  | _ ->
      match find_existing_file [ "database/database_26.pl"; "efolio_a/database/database_26.pl" ] with
      | Some path -> path
      | None -> "database/database_26.pl"

let read_file filename =
  let lines = ref [] in
  let channel = open_in filename in
  try
    while true do
      lines := input_line channel :: !lines
    done;
    []
  with End_of_file ->
    close_in channel;
    List.rev !lines

let carregar_base_dados () =
  read_file (database_path ())

let rec count_atvd_acc atvd aluno_id acc =
  match atvd with
  | [] -> 0
  | (id_aluno, _, _, _)::t -> if id_aluno = aluno_id then count_atvd_acc t aluno_id acc + 1 else count_atvd_acc t aluno_id acc

let rec get_assiduidade_percent ass aluno_id =
  match ass with
  | [] -> 0
  | (id, total_aulas, faltas)::t ->
      if id = aluno_id then
        if total_aulas = 0 then
          0
        else
          int_of_float ((float_of_int (total_aulas-faltas) /. float_of_int total_aulas) *. 100.0)
      else
        get_assiduidade_percent t aluno_id

let rec get_autoavaliacao av aluno_id =
  match av with
  | [] -> 0
  | (id, nota)::t -> if id = aluno_id then nota else get_autoavaliacao t aluno_id

let parse_aluno line =
  let regexp =
    Str.regexp
      "aluno(\\([0-9]+\\),[ \t]*'\\([^']+\\)',[ \t]*'\\([^']+\\)')\\."
  in
  if Str.string_match regexp line 0 then
    Some
      (
        int_of_string (Str.matched_group 1 line), (* ID *)
        Str.matched_group 2 line,                 (* Nome *)
        Str.matched_group 3 line                  (* Email *)
      )
  else
    None


let parse_atividade line =
  let regexp =
    Str.regexp
      "atividade_aluno(\\([0-9]+\\),[ \t]*\\([a-zA-Z_]+\\),[ \t]*\\([0-9]+\\),[ \t]*'\\([^']+\\)')\\."
  in
  if Str.string_match regexp line 0 then
    Some
      (
        int_of_string (Str.matched_group 1 line), (* ID Aluno *)
        Str.matched_group 2 line,                 (* Tipo: forum/tarefa/quiz *)
        int_of_string (Str.matched_group 3 line), (* Valor/Pontuação *)
        Str.matched_group 4 line                  (* Data *)
      )
  else
    None

let parse_assiduidade line =
  let regexp =
    Str.regexp
      "assiduidade(\\([0-9]+\\),[ \t]*\\([0-9]+\\),[ \t]*\\([0-9]+\\))\\."
  in
  if Str.string_match regexp line 0 then
    Some
      (
        int_of_string (Str.matched_group 1 line), (* ID Aluno *)
        int_of_string (Str.matched_group 2 line), (* Total Aulas *)
        int_of_string (Str.matched_group 3 line)  (* Faltas *)
      )
  else
    None

let parse_autoavaliacao line =
  let regexp =
    Str.regexp
      "autoavaliacao(\\([0-9]+\\),[ \t]*\\([0-9]+\\))\\."
  in
  if Str.string_match regexp line 0 then
    Some
      (
        int_of_string (Str.matched_group 1 line), (* ID Aluno *)
        int_of_string (Str.matched_group 2 line)  (* Nota *)
      )
  else
    None

let merge_aluno alunos atvd ass =
  List.map
  (fun (id, nome, email) -> (id, nome, email, (count_atvd_acc atvd id 0), (get_assiduidade_percent ass id)))
  alunos

(* indicadores *)

type indicadores_acc = {p_forum: int; count_n_tar: int; sum_n_tar: int; count_n_quiz: int; sum_n_quiz: int;}

let rec get_indicadores atvd aluno_id (acc:indicadores_acc) =
  match atvd with
  | [] -> acc
  | (id_aluno, tipo, nota, _)::t ->
    if id_aluno = aluno_id then
      match tipo with
      | "forum" -> get_indicadores t aluno_id ({
          p_forum = acc.p_forum + nota;
          count_n_tar = acc.count_n_tar;
          sum_n_tar = acc.sum_n_tar;
          count_n_quiz = acc.count_n_quiz;
          sum_n_quiz = acc.sum_n_quiz;
        })
      | "tarefa" -> get_indicadores t aluno_id ({
          p_forum = acc.p_forum;
          count_n_tar = acc.count_n_tar + 1;
          sum_n_tar = acc.sum_n_tar + nota;
          count_n_quiz = acc.count_n_quiz;
          sum_n_quiz = acc.sum_n_quiz;
        })
      | "quiz" -> get_indicadores t aluno_id ({
          p_forum = acc.p_forum;
          count_n_tar = acc.count_n_tar;
          sum_n_tar = acc.sum_n_tar;
          count_n_quiz = acc.count_n_quiz  + 1;
          sum_n_quiz = acc.sum_n_quiz + nota;
        })
      | _ -> get_indicadores t aluno_id acc
    else
      get_indicadores t aluno_id acc

let print_alunos_enriched alunos_enriched  =
  if alunos_enriched = [] then
    print_endline "-1"
  else
    List.iter
    (fun (id, nome, email, atv, ass) ->
      Printf.printf "ID: %d | Nome: %s | Email: %s | Nº Atividades: %d | Assiduidade: %d p/cent \n" id nome email atv ass)
    alunos_enriched

let print_indicadores indicadores  =
  (fun (aluno_id, forum, media_tarefas, media_quizzes, conjunta, assiduidade, autoav) ->
    Printf.printf
      "ID: %d | Participações Fórum: %d | Média Tarefas: %d | Média Quizzes: %d | Média Conjunta: %d | Assiduidade: %d p/cent | Autoavaliação: %d\n"
      aluno_id
      forum
      media_tarefas
      media_quizzes
      conjunta
      assiduidade
      autoav)
    indicadores

(* avaliacao *)

let media soma quantidade =
  if quantidade = 0 then
    0.0
  else
    float_of_int soma /. float_of_int quantidade

let media_inteira soma quantidade =
  if quantidade = 0 then
    0
  else
    soma / quantidade


let estado_final r1 r2 r3 r4 =
  if r1 && r2 && r3 && r4 then
    "Aprovado"
  else
    "Retido"


let avaliar_aluno aluno_id atvd ass av =
  let ind_raw =
    get_indicadores atvd aluno_id
      {
        p_forum = 0;
        count_n_tar = 0;
        sum_n_tar = 0;
        count_n_quiz = 0;
        sum_n_quiz = 0;
      }
  in

  let media_tarefas_quizzes =
    media
      (ind_raw.sum_n_tar + ind_raw.sum_n_quiz)
      (ind_raw.count_n_tar + ind_raw.count_n_quiz)
  in

  let assiduidade = get_assiduidade_percent ass aluno_id in
  let autoav = get_autoavaliacao av aluno_id in

  let r1 = ind_raw.p_forum >= 3 in
  let r2 = media_tarefas_quizzes >= 10.0 in
  let r3 = assiduidade >= 75 in
  let r4 =
    abs_float (float_of_int autoav -. media_tarefas_quizzes) <= 2.0
  in

  let estado = estado_final r1 r2 r3 r4 in

  Printf.printf "ID: %d\n" aluno_id;

  Printf.printf
    "R1 (>=3 fórum): %b (%d participação%s)\n"
    r1
    ind_raw.p_forum
    (if ind_raw.p_forum = 1 then "" else "es");

  Printf.printf
    "R2 (média >=10): %b (%.1f)\n"
    r2
    media_tarefas_quizzes;

  Printf.printf
    "R3 (assid. >=75%%): %b (%d%%)\n"
    r3
    assiduidade;

  Printf.printf
    "R4 (autoav. coerente): %b (auto=%d, média=%.1f)\n"
    r4
    autoav
    media_tarefas_quizzes;

  Printf.printf "Estado final: %s\n" estado

(* estados *)

let calcular_estado_aluno aluno_id atvd ass av =
  let ind_raw =
    get_indicadores atvd aluno_id
      {
        p_forum = 0;
        count_n_tar = 0;
        sum_n_tar = 0;
        count_n_quiz = 0;
        sum_n_quiz = 0;
      }
  in

  let media_conjunta =
    media
      (ind_raw.sum_n_tar + ind_raw.sum_n_quiz)
      (ind_raw.count_n_tar + ind_raw.count_n_quiz)
  in

  let assiduidade = get_assiduidade_percent ass aluno_id in
  let autoav = get_autoavaliacao av aluno_id in

  let r1 = ind_raw.p_forum >= 3 in
  let r2 = media_conjunta >= 10.0 in
  let r3 = assiduidade >= 75 in
  let r4 =
    abs_float (float_of_int autoav -. media_conjunta) <= 2.0
  in

  let estado = estado_final r1 r2 r3 r4 in

  (estado, media_conjunta, assiduidade)

let merge_estado_alunos alunos atvd ass av =
  List.map
    (fun (id, nome, _) ->
      let estado, media_conjunta, assiduidade =
        calcular_estado_aluno id atvd ass av
      in
      (id, nome, estado, media_conjunta, assiduidade))
    alunos


let prioridade_estado estado =
  match estado with
  | "Aprovado" -> 0
  | "Retido" -> 1
  | _ -> 2

let print_estados alunos_estado =
  if alunos_estado = [] then
    print_endline "-1"
  else
    List.iter
      (fun (id, _, estado, media_conjunta, assiduidade) ->
        Printf.printf
          "ID: %d | Estado: %s | Média Conjunta: %.1f | Assiduidade: %d%%\n"
          id
          estado
          media_conjunta
          assiduidade)
      alunos_estado

let () =
  match Array.to_list Sys.argv with
  | _ :: "listar_alunos" :: _ ->
      let file_lines = carregar_base_dados () in
      let atvd = List.filter_map parse_atividade file_lines in
      let ass = List.filter_map parse_assiduidade file_lines in
      let alunos = List.filter_map parse_aluno file_lines in
      merge_aluno alunos atvd ass
      |> List.sort (fun (_, nome1, _, _, _) (_, nome2, _, _, _) ->
           String.compare nome1 nome2)
      |> print_alunos_enriched
  | _ :: "indicadores" :: aluno_id :: _ ->
      let id = int_of_string aluno_id in
      let file_lines = carregar_base_dados () in
      let atvd = List.filter_map parse_atividade file_lines in
      let ass = List.filter_map parse_assiduidade file_lines in
      let av = List.filter_map parse_autoavaliacao file_lines in
      let ind_raw = get_indicadores atvd id ({
          p_forum = 0;
          count_n_tar = 0;
          sum_n_tar = 0;
          count_n_quiz = 0;
          sum_n_quiz = 0;
      }) in
      print_indicadores (
        id,
        ind_raw.p_forum,
        media_inteira ind_raw.sum_n_tar ind_raw.count_n_tar,
        media_inteira ind_raw.sum_n_quiz ind_raw.count_n_quiz,
        media_inteira (ind_raw.sum_n_tar + ind_raw.sum_n_quiz) (ind_raw.count_n_tar + ind_raw.count_n_quiz),
        get_assiduidade_percent ass id,
        get_autoavaliacao av id);
  | _ :: "avaliar" :: aluno_id :: _ ->
    let id = int_of_string aluno_id in

    let file_lines = carregar_base_dados () in

    let atvd = List.filter_map parse_atividade file_lines in
    let ass = List.filter_map parse_assiduidade file_lines in
    let av = List.filter_map parse_autoavaliacao file_lines in

    avaliar_aluno id atvd ass av
  | _ :: "listar_estados" :: _ ->
    let file_lines = carregar_base_dados () in

    let alunos = List.filter_map parse_aluno file_lines in
    let atvd = List.filter_map parse_atividade file_lines in
    let ass = List.filter_map parse_assiduidade file_lines in
    let av = List.filter_map parse_autoavaliacao file_lines in

    merge_estado_alunos alunos atvd ass av
    |> List.sort
         (fun (_, nome1, estado1, _, _) (_, nome2, estado2, _, _) ->
           let cmp_estado =
             compare (prioridade_estado estado1) (prioridade_estado estado2)
           in
           if cmp_estado <> 0 then
             cmp_estado
           else
             String.compare nome1 nome2)
    |> print_estados
  | _ ->
      Printf.printf "Comandos Disponíveis:\n";
      Printf.printf "  listar_alunos\n";
      Printf.printf "  indicadores {aluno_id}\n";
      Printf.printf "  avaliar {id_aluno}\n";
      Printf.printf "  listar_estados\n"
