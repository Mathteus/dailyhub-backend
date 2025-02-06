#include "Dailyhub/Core/database.hpp"

PGconn* DataBase::conn_ = nullptr;
enum Tables {
  users,
  kanban,
  finance,
  blog,
};




bool DataBase::connect() {
  std::string url{std::getenv("URL_POSTGRES")};
  if (isConnected()) {
    spdlog::warn("Conexão já está estabelecida.");
    return true;
  }

  conn_ = PQconnectdb(url.c_str());
  if (PQstatus(conn_) == CONNECTION_OK) {
    spdlog::info("Conexão com o banco de dados estabelecida.");
    initWithSQLFiles();
    return true;
  } else {
    spdlog::error("Falha ao conectar no banco de dados: {}", PQerrorMessage(conn_));
    PQfinish(conn_);
    conn_ = nullptr;
    return false;
  }
}

void DataBase::close() {
  if (conn_ != nullptr) {
    PQfinish(conn_);
    conn_ = nullptr;
    spdlog::info("Conexão com o banco de dados fechada.");
  }
}

bool DataBase::isConnected() {
  return conn_ != nullptr && PQstatus(conn_) == CONNECTION_OK;
}

DataBase::Inner_Response DataBase::executeQuery(const std::string& query) {
  DataBase::Inner_Response response;
  if (!isConnected()) {
    std::string error{"Não há conexão com o banco de dados para executar a query."};
    spdlog::error(error);
    response.error = error;
    response.status = false;
    return response;
  }

  PGresult* res = PQexec(conn_, query.c_str());
  if(PQresultStatus(res) != PGRES_TUPLES_OK && PQresultStatus(res) != PGRES_COMMAND_OK) {
    std::string error{PQerrorMessage(conn_)};
    spdlog::error("Erro ao executar a query: {}", error);
    PQclear(res);
    response.status = false;
    response.error = error;
    return response;
  }

  response.status = true;
  response.result = res;
  response.error = "";
  return response;
}

void DataBase::initWithSQLFiles() {
  std::string sqlFile{Utility::readFilesSQL("../database/nanoid")};
  DataBase::executeQuery(sqlFile);
  sqlFile = Utility::readFilesSQL("../database/commands");
  DataBase::executeQuery(sqlFile);
}

void DataBase::DisplayQueryResult(PGresult* res) {
  if (PQntuples(res) == 0) {
    std::cout << "No results found.\n";
    return;
  }

  int cols = PQnfields(res);
  for (int col = 0; col < cols; ++col) {
    std::cout << std::setw(15) << std::left << PQfname(res, col);
  }

  std::cout << '\n';
  for (int col = 0; col < cols; ++col) {
    std::cout << std::setw(15) << std::left << "----------------";
  }

  std::cout << '\n';

  int rows = PQntuples(res);
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      if (PQgetisnull(res, row, col)) {
        std::cout << std::setw(15) << std::left << "(null)";
        } else {
        std::cout << std::setw(15) << std::left << PQgetvalue(res, row, col);
      }
    }
    std::cout << '\n';
  }
  PQclear(res);
}

nlohmann::json DataBase::resultToJson(PGresult* res) {
  nlohmann::json j;
  if (PQntuples(res) == 0) {
    PQclear(res);
    return j;
  }
    
  int cols = PQnfields(res);
  std::vector<std::string> column_names;
  for (int col = 0; col < cols; ++col) {
    column_names.push_back(PQfname(res,col));
  }
    
  int rows = PQntuples(res);
  for (int row = 0; row < rows; ++row) {
    nlohmann::json row_json;
    for (size_t col = 0; col < column_names.size(); ++col) {
      if(PQgetisnull(res, row, col)){
        row_json[column_names[col]] = nullptr;
      } else {
        row_json[column_names[col]] = PQgetvalue(res, row, col);
      }
    }
    j.push_back(row_json);
  }
  PQclear(res);
  return j;
}

std::string regexEscape(const std::string& input) {
    std::string escaped;
    for (char c : input) {
        if (c == '.' || c == '[' || c == ']' || c == '(' || c == ')' ||
            c == '{' || c == '}' || c == '*' || c == '+' || c == '?' ||
            c == '|' || c == '^' || c == '$' || c == '\\') {
            escaped += '\\';
        }
        escaped += c;
    }
    return escaped;
}

std::string sanitizeString(const std::string& input) {
    std::string sanitized = input;
    std::vector<std::string> blacklist = {
        "--",             // Comentários SQL
        ";",              // Fim de declaração SQL
        "/*",             // Comentários SQL /* ... */
        "*/",             // Comentários SQL /* ... */
        "xp_",            // Comandos estendidos do SQL Server (não relevantes para PostgreSQL, mas incluídos por segurança)
        "%",              // Caracteres curinga SQL
        "=",              // Operador de igualdade
        "DROP",           // Remover objetos do banco de dados
        "drop",
        "CREATE",         // Criar objetos do banco de dados
        "create",
        "ALTER",          // Modificar objetos do banco de dados
        "alter",
        "TRUNCATE",       // Remover todos os dados de uma tabela
        "truncate",
        "SELECT",         // Consultar dados (pode ser usado para extrair informações sensíveis)
        "select",
        "INSERT",         // Inserir dados
        "insert",
        "UPDATE",         // Atualizar dados
        "update",
        "DELETE",         // Excluir dados
        "delete",
        "GRANT",          // Conceder privilégios
        "grant",
        "REVOKE",         // Revogar privilégios
        "revoke",
        "EXECUTE",        // Executar funções ou procedimentos armazenados
        "execute",
        "UNION",          // Combinar resultados de SELECTs
        "union",
        "ALL",            // Usado com UNION
        "all",
        "SYSTEM_USER",    // Funções que revelam informações do sistema
        "system_user",
        "SESSION_USER",   // Funções que revelam informações da sessão
        "session_user",
        "CURRENT_USER",   // Funções que revelam informações do usuário atual
        "current_user",
        "pg_catalog",     // Acesso ao catálogo do sistema (metadados do banco de dados)
        "pg_.*",          // Padrão para funções e tabelas do sistema
        "DECLARE",        // Usado para criar cursores (podem ser explorados)
        "declare",
        "FETCH",          // Usado para buscar dados com cursores
        "fetch",
        "sysdatabases",   // Tabela de sistema no SQL Server (não relevante, mas adicionado por precaução)
        "sysusers",       // Tabela de sistema no SQL Server (não relevante, mas adicionado por precaução)
        "INFORMATION_SCHEMA", // Acesso a metadados do banco de dados (pode revelar informações sensíveis)
        "information_schema",
        "TABLE_",       // Padrão para tabelas
        "table_",
         "OR",       // Operador booleano OR
        "or",
          "AND",       // Operador booleano AND
        "and",
          "LIKE",       // Cláusula LIKE
        "like"
    };

    std::stringstream patternStream;
    patternStream << "(";
    for (size_t i = 0; i < blacklist.size(); ++i) {
        patternStream << regexEscape(blacklist[i]);
        if (i < blacklist.size() - 1) {
            patternStream << "|";
        }
    }
    patternStream << ")";
    std::regex blacklistRegex(patternStream.str(), std::regex_constants::icase);
    sanitized = std::regex_replace(sanitized, blacklistRegex, "");
    size_t pos = sanitized.find("'");
    while (pos != std::string::npos) {
        sanitized.replace(pos, 1, "''");
        pos = sanitized.find("'", pos + 2);
    }

    return sanitized;
}

// template <typename TypeData> ResponseDatabase Generic(TypeData data) {
//     ResponseDatabase res;
//     res.json = {{}};
//     res.status = false;
//     if (user.empty() || token.empty()) {
//         res.error = "Dados estão vazios";
//         return res;
//     }

//     sanitizeString(user);
//     sanitizeString(token);

//     std::stringstream ss{};
//     ss << "UPDATE user SET TOKEN = '" << token << "' WHERE username = '" << user << "';";
//     auto response_query{DataBase::executeQuery(ss.str())};
//     if (response_query.status) {
//         ResponseDatabase response;
//         response.status = true;
//         response.json = DataBase::resultToJson(response_query.result);
//         res.error = "";
//         return response;
//     }

//     res.error = response_query.error;
//     return res;
// }



ResponseDatabase DataBase::Register_User(const std::string& hash, const std::string& salt, const std::string& username, const std::string& email) {
    ResponseDatabase res;
    res.json = {{}};
    res.status = false;
    if (hash.empty() || salt.empty() || username.empty() || email.empty()) {
        res.error = "Dados estão vazios";
        return res;
    }

    sanitizeString(hash);
    sanitizeString(salt);
    sanitizeString(username);
    sanitizeString(email);

    std::stringstream ss{};
    ss << "INSERT INTO users (hash, salt, username, email) VALUES ('" << hash << "', '" << salt << "', '" << username << "', '"  << email << "');";

    auto response_query{DataBase::executeQuery(ss.str())};
    if (response_query.status) {
        ResponseDatabase response;
        response.status = true;
        response.json = DataBase::resultToJson(response_query.result);
        res.error = "";
        return response;
    }

    res.error = response_query.error;
    return res;
}

ResponseDatabase DataBase::Login_user(const std::string& user, const std::string& token) {
    ResponseDatabase res;
    res.json = {{}};
    res.status = false;
    if (user.empty() || token.empty()) {
        res.error = "Dados estão vazios";
        return res;
    }

    sanitizeString(user);
    sanitizeString(token);

    std::stringstream ss{};
    ss << "UPDATE user SET TOKEN = '" << token << "' WHERE username = '" << user << "';";
    auto response_query{DataBase::executeQuery(ss.str())};
    if (response_query.status) {
        ResponseDatabase response;
        response.status = true;
        response.json = DataBase::resultToJson(response_query.result);
        res.error = "";
        return response;
    }

    res.error = response_query.error;
    return res;
}
