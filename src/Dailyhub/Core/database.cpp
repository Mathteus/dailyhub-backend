#include "Dailyhub/Core/database.hpp"
#define TEST

#ifdef TEST
	#define URL_DATABASE "URL_POSTGRES_TEST"
#else
	#define URL_DATABASE "URL_POSTGRES"
#endif

PGconn* Dailyhub::Core::DataBase::conn_ = nullptr;

bool Dailyhub::Core::DataBase::connect() {
	if (isConnected()) {
		spdlog::warn("Conexão já está estabelecida.\n");
		return true;
	}

	std::string urlConnection{Dailyhub::Core::DotEnv::get(URL_DATABASE, "postgres://postgres:abacaxi@127.0.0.1:5432/tests")};
	bool response{false};

	try {
		conn_ = PQconnectdb(urlConnection.c_str());
		if (PQstatus(conn_) == CONNECTION_OK) {
			spdlog::info("Conexão com o banco de dados estabelecida.\n");
			initWithSQLFiles();
			response = true;
		} else {
			spdlog::error("Falha ao conectar no banco de dados: {}\n", PQerrorMessage(conn_));
			PQfinish(conn_);
			conn_ = nullptr;
		}
	} catch (std::exception& e) {
		spdlog::error("Falha ao conectar no banco de dados: {}\n", e.what ());
	}

	return response;
}

void Dailyhub::Core::DataBase::close() {
	if (conn_ != nullptr) {
		PQfinish(conn_);
		conn_ = nullptr;
		spdlog::info("Conexão com o banco de dados fechada.\n");
	}
}

bool Dailyhub::Core::DataBase::isConnected() const {
	return conn_ != nullptr && PQstatus(conn_) == CONNECTION_OK;
}

Dailyhub::Core::DataBase::ResponsePGresult Dailyhub::Core::DataBase::executeQueryRaw(const std::string& query) {
	DataBase::ResponsePGresult response;
	if (!isConnected()) {
		const char* error{"Não há conexão com o banco de dados para executar a query.\n"};
		spdlog::error(error);
		response.error = error;
		response.success = false;
		response.data = std::nullopt;
		return response;
	}

	PGresult* res = PQexec(conn_, query.c_str());
	if(PQresultStatus(res) != PGRES_TUPLES_OK && PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::string error{PQerrorMessage(conn_)};
		spdlog::error("Erro ao executar a query: {}\n", error);
		PQclear(res);
		response.success = false;
		response.error = error;
		response.data = std::nullopt;
		return response;
	}

	response.success = true;
	response.data = res;
	response.error = std::nullopt;
	return response;
}

Dailyhub::Core::Errors::ResponseBoolean Dailyhub::Core::DataBase::execQuery(const char* query, Dailyhub::Core::DataBase::ParamsQuery params) {
	Dailyhub::Core::Errors::ResponseBoolean response;
	if (!DataBase::isConnected()) {
		const char* error{"Não há conexão com o banco de dados para executar a query.\n"};
		spdlog::error(error);
		response.error = error;
		response.success = false;
		response.data = std::nullopt;
		return response;
	}

	const char* identifier = static_cast<const char*>(Dailyhub::Core::Utility::gerateStringC(10));
	PGresult* result = PQprepare(DataBase::conn_, identifier, query, params.colums, NULL);
	if (PQresultStatus(result) != PGRES_COMMAND_OK) {
		std::string error{PQerrorMessage(DataBase::conn_)};
		spdlog::error("Erro ao preparar a consulta: {}\n", error);
		PQclear(result);
		response.success = false;
		response.error = error;
		response.data = std::nullopt;
		return response;
	}

	result = PQexecPrepared(DataBase::conn_, identifier, params.colums, params.params, NULL, NULL, 0);
	if (PQresultStatus(result) != PGRES_COMMAND_OK) {
		std::string error{PQerrorMessage(DataBase::conn_)};
		spdlog::error("Erro ao preparar a consulta: {}\n", error);
		PQclear(result);
		response.success = false;
		response.error = error;
		response.data = std::nullopt;
		PQclear(result);
		return response;
	}

	response.success = true;
	response.error = std::nullopt;
	response.data = true;
	PQclear(result);
	return response;
}

Dailyhub::Core::DataBase::ResponseJson Dailyhub::Core::DataBase::Select(const char* query, Dailyhub::Core::DataBase::ParamsQuery params) {
	DataBase::ResponseJson response;
	const char* identifier = static_cast<const char*>(Dailyhub::Core::Utility::gerateStringC(10));
	PGresult* result = PQprepare(DataBase::conn_, identifier, query, params.colums, NULL);
	if (PQresultStatus(result) != PGRES_COMMAND_OK) {
		std::string error{PQerrorMessage(DataBase::conn_)};
		spdlog::error("Erro ao preparar a consulta: {}\n", error);
		PQclear(result);
		response.success = false;
		response.error = error;
		response.data = std::nullopt;
		return response;
	}

	result = PQexecPrepared(DataBase::conn_, identifier, params.colums, params.params, NULL, NULL, 0);
	if (PQresultStatus(result) == PGRES_TUPLES_OK) {
		auto j{DataBase::resultToJson(result)};
		response.success = true;
		response.error = std::nullopt;
		response.data = j;
	} else {
		const char* error{PQerrorMessage(DataBase::conn_)};
		spdlog::error("Erro ao preparar a consulta: {}\n", error);
		response.success = false;
		response.error = error;
		response.data = std::nullopt;
		delete error;
	}

	delete identifier;
	PQclear(result);
	return response;
}

void Dailyhub::Core::DataBase::initWithSQLFiles() {
	std::string sqlFile{Utility::readFilesSQL("../database/nanoid")};
	DataBase::executeQueryRaw(sqlFile);
	sqlFile = Utility::readFilesSQL("../database/commands");
	DataBase::executeQueryRaw(sqlFile);
}

nlohmann::json Dailyhub::Core::DataBase::resultToJson(PGresult* res) {
	nlohmann::json j{{}};
	if (PQntuples(res) == 0) {
		PQclear(res);
		return j;
	}

	size_t cols{static_cast<size_t>(PQnfields(res))};
	std::vector<std::string> column_names;
	for (size_t col = 0; col < cols; ++col) {
		column_names.push_back(PQfname(res,col));
	}

	size_t rows{static_cast<size_t>(PQntuples(res))};
	for (size_t row = 0; row < rows; ++row) {
			nlohmann::json row_json;
			for (size_t col = 0; col < column_names.size(); ++col) {
				if (PQgetisnull(res, row, col)) {
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
