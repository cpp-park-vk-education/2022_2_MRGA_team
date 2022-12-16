CREATE USER root WITH PASSWORD 'mashapg';
GRANT ALL PRIVILEGES ON DATABASE mashadb  TO root;

CREATE TABLE users (
    id serial PRIMARY KEY,
    nickname text UNIQUE NOT NULL,
    passcode text NOT NULL,
    email text UNIQUE NOT NULL,
    birth_date date NOT NULL,
    overview text
);

CREATE TABLE tokens (
    id serial PRIMARY KEY,
    token_content text NOT NULL UNIQUE,
    expire_date_time timestamp NOT NULL,

    user_id integer REFERENCES users ON DELETE CASCADE NOT NULL
);

CREATE TABLE addresses (
    id serial PRIMARY KEY,
    address_title text NOT NULL,
    longitude numeric DEFAULT NULL,
    latitude numeric DEFAULT NULL
);

CREATE TABLE events (
    id serial PRIMARY KEY,
    title text NOT NULL,
    overview text,
    date_time timestamp NOT NULL,
    max_visitors integer DEFAULT 100,
    
    user_id integer REFERENCES users ON DELETE CASCADE NOT NULL,
    address_id integer REFERENCES addresses ON DELETE CASCADE NOT NULL
);

INSERT INTO users (id, nickname, passcode, email, birth_date, overview) VALUES (0, 'admin', 'qwerty', 'admin@admin.ru', '1970-01-01', 'this user is admin');
INSERT INTO tokens (id, token_content, expire_date_time, user_id) VALUES (0, 'admin02022', '2050-01-02 12:00:00', 0);
