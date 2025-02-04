CREATE TABLE IF NOT EXISTS users (
  user_id VARCHAR(6) NOT NULL DEFAULT nanoid(6),
  hash VARCHAR(30) NOT NULL,
  salt VARCHAR(30) NOT NULL,
  role VARCHAR(10) NOT NULL DEFAULT 'user',
  name VARCHAR(30) NOT NULL,
  tag VARCHAR(26) NOT NULL UNIQUE,
  email VARCHAR(60) NOT NULL UNIQUE,
  last_login DATE NOT NULL DEFAULT now(),
  created_at DATE NOT NULL DEFAULT now(),
  CONSTRAINT pk_userid PRIMARY KEY (user_id)
);

CREATE TABLE IF NOT EXISTS blog (
  postid VARCHAR(8) NOT NULL DEFAULT nanoid(8),
  user_id VARCHAR(6) NOT NULL,
  name VARCHAR(30) NOT NULL,
  content TEXT NOT NULL,
  created_at DATE NOT NULL DEFAULT now(),
  awesome INTEGER NOT NULL DEFAULT 0,
  CONSTRAINT pk_postid PRIMARY KEY (postid),
  CONSTRAINT pk_userid FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS finance (
  transactionid VARCHAR(8) NOT NULL DEFAULT nanoid(8),
  user_id VARCHAR(6) NOT NULL,
  type CHAR NOT NULL DEFAULT 's',
  name VARCHAR(26) NOT NULL,
  description TEXT NOT NULL,
  amount DECIMAL(10, 2) NOT NULL,
  created_at DATE NOT NULL DEFAULT now(),
  CONSTRAINT pk_transactionid PRIMARY KEY (transactionid),
  CONSTRAINT fk_userid FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS kanban (
  taskid VARCHAR(8) NOT NULL DEFAULT nanoid(8),
  user_id VARCHAR(6) NOT NULL,
  title VARCHAR(20) NOT NULL,
  description TEXT NOT NULL,
  status CHAR NOT NULL DEFAULT 'a',
  created_at DATE NOT NULL DEFAULT now(),
  last_upDATE DATE NOT NULL DEFAULT now(),
  CONSTRAINT pk_taskid PRIMARY KEY (taskid),
  CONSTRAINT fk_userid FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
);

CREATE OR REPLACE FUNCTION upDATE_last_login()
RETURNS TRIGGER AS $$
BEGIN
  IF NEW.token IS DISTINCT FROM OLD.token THEN
    NEW.last_login = NOW();
  END IF;
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_upDATE_last_login
BEFORE UPDATE ON users
FOR EACH ROW
EXECUTE FUNCTION upDATE_last_login();

