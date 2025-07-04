CREATE TABLE IF NOT EXISTS url_pattern (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    url_pattern TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS label (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS url_label (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    url_pattern_id INTEGER NOT NULL,
    label_id INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS response_body_template (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    response_body TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS active_blocked_url (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    url_pattern_id INTEGER NOT NULL
);

CREATE TABLE IF NOT EXISTS active_mocked_url (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    url_pattern_id INTEGER NOT NULL,
    response_body_template_id INTEGER NOT NULL
);
