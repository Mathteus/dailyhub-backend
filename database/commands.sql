create table if not exists users (
  user_id varchar(6) not null default nanoid(6),
  hash varchar(30) not null,
  salt varchar(30) not null,
  role varchar(10) not null default 'user',
  name varchar(30) not null,
  tag varchar(26) not null unique,
  email varchar(60) not null unique,
  last_login date not null default now(),
  created_at date not null default now(),
  constraint pk_userid primary key (user_id)
);

create table if not exists blog (
  postid varchar(8) not null default nanoid(8),
  user_id varchar(6) not null,
  name varchar(30) not null,
  content text not null,
  created_at date not null default now(),
  awesome integer not null default 0,
  constraint pk_postid primary key (postid),
  constraint pk_userid foreign key (user_id) references users(user_id) on delete cascade
);

create table if not exists finance (
  transactionid varchar(8) not null default nanoid(8),
  user_id varchar(6) not null,
  type char not null default 's',
  name varchar(26) not null,
  description text not null,
  amount decimal(10, 2) not null,
  created_at date not null default now(),
  constraint pk_transactionid primary key (transactionid),
  constraint fk_userid foreign key (user_id) references users(user_id) on delete cascade
);

create table if not exists kanban (
  taskid varchar(8) not null default nanoid(8),
  user_id varchar(6) not null,
  title varchar(20) not null,
  description text not null,
  status char not null default 'a',
  created_at date not null default now(),
  last_update date not null default now(),
  constraint pk_taskid primary key (taskid),
  constraint fk_userid foreign key (user_id) references users(user_id) on delete cascade
);
