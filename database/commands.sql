create table if not exists users (
  user_id varchar(12) not null default nanoid('', 12),
  name varchar(30) not null,
  identifier varchar(26) not null unique,
  email varchar(60) not null unique,
  created_at date not null default now(),
  primary key (user_id)
);

create table if not exists blog (
  postid varchar(12) not null default nanoid('', 12),
  user_id varchar(12) not null default nanoid('', 12),
  name varchar(30) not null,
  content text not null,
  created_at date not null default now(),
  awesome integer not null default 0,
  primary key (postid),
  foreign key (user_id) references users(user_id)
);

create table if not exists finance (
  transactionid varchar(12) not null default nanoid('', 12),
  user_id varchar(12) not null default nanoid('', 12),
  type varchar(1) not null default 's',
  name varchar(26) not null,
  description text not null,
  amount decimal(10, 2) not null,
  created_at date not null default now(),
  primary key (transactionid),
  foreign key (user_id) references users(user_id)
);

create table if not exists kanban (
  taskid varchar(12) not null default nanoid('', 12),
  user_id varchar(12) not null default nanoid('', 12),
  title varchar(20) not null,
  description text not null,
  status varchar(1) not null default 'a',
  created_at date not null default now(),
  last_update date not null default now(),
  primary key (taskid),
  foreign key (user_id) references users(user_id)
);
