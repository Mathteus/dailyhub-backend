# users 
CREATE TABLE IF NOT EXISTS users (
  user_id VARCHAR(6) NOT NULL DEFAULT nanoid(6),
  hash TEXT NOT NULL,
  salt BYTEA NOT NULL,
  name VARCHAR(26) NOT NULL,
  tag VARCHAR(12) NOT NULL UNIQUE,
  email TEXT NOT NULL UNIQUE,
  last_login TIMESTAMPTZ NOT NULL DEFAULT now(),
  created_at TIMESTAMPTZ NOT NULL DEFAULT now(),
  CONSTRAINT pk_userid PRIMARY KEY (user_id)
);

CREATE INDEX idx_users_name ON users (name)
CREATE INDEX idx_users_last_login ON users (last_login);

INSERT INTO users (hash, salt, name, tag, email) VALUES ('hash', 'salt', 'name', 'tag', 'email');
SELECT FROM users user_id, name, tag WHERE hash = 'hash' AND salt = 'salt' AND (email ILIKE 'email' OR name ILIKE 'name');
SELECT FROM users hash, salt, email WHERE user_id = 'id';
UPDATE INTO users (last_login) VALUES (now());
UPDATE users SET hash = 'new hash', salt = 'new Salt' WHERE user_id = 'id';
UPDATE users SET name = 'new name' WHERE user_id = 'id';
UPDATE users SET email = 'new name' WHERE user_id = 'id';
DELETE FROM users WHERE user_id = 'id';

CREATE TABLE IF NOT EXISTS blog (
  postid VARCHAR(8) NOT NULL DEFAULT nanoid(8),
  user_id VARCHAR(6) NOT NULL,
  name VARCHAR(30) NOT NULL,
  content TEXT NOT NULL,
  created_at TIMESTAMPTZ NOT NULL DEFAULT now(),
  awesome INTEGER NOT NULL DEFAULT 0,
  CONSTRAINT pk_postid PRIMARY KEY (postid),
  CONSTRAINT pk_userid FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
);

INSERT INTO blog (user_id, name, content) VALUES ('user', 'name', 'content');

CREATE TABLE IF NOT EXISTS finance (
  transactionid VARCHAR(8) NOT NULL DEFAULT nanoid(8),
  user_id VARCHAR(6) NOT NULL,
  type CHAR NOT NULL DEFAULT 's',
  name VARCHAR(26) NOT NULL,
  description TEXT NOT NULL,
  amount DECIMAL(10, 2) NOT NULL,
  date_
  created_at TIMESTAMPTZ NOT NULL DEFAULT now(),
  CONSTRAINT pk_transactionid PRIMARY KEY (transactionid),
  CONSTRAINT fk_userid FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
);

INSERT INTO finance (user_id, type, name, description, amount) VALUES ('user_id', 'type', 'name', 'description', 150.00);
UPDATE finance SET campo = 'new Data' WHERE user_id = 'id' AND transactionid = 'transactionid';
DELETE FROM finance WHERE user_id = 'id' AND transactionid = 'transactionid';


CREATE TABLE IF NOT EXISTS kanban (
  taskid VARCHAR(8) NOT NULL DEFAULT nanoid(8),
  user_id VARCHAR(6) NOT NULL,
  title VARCHAR(20) NOT NULL,
  description TEXT NOT NULL,
  status CHAR NOT NULL DEFAULT 'a',
  created_at TIMESTAMPTZ NOT NULL DEFAULT now(),
  last_update TIMESTAMPTZ NOT NULL DEFAULT now(),
  CONSTRAINT pk_taskid PRIMARY KEY (taskid),
  CONSTRAINT fk_userid FOREIGN KEY (user_id) REFERENCES users(user_id) ON DELETE CASCADE
);

CREATE OR REPLACE FUNCTION update_last_login()
RETURNS TRIGGER AS $$
BEGIN
  IF NEW.token IS DISTINCT FROM OLD.token THEN
    NEW.last_login = NOW();
  END IF;
  RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_update_last_login
BEFORE UPDATE ON users
FOR EACH ROW
EXECUTE FUNCTION update_last_login();
