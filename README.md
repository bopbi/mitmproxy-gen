# mitmproxy-gen

## How To use
1. Generate json config using config gen tool
2. execute mitmproxy plugin `mitmproxy -s modify.py`

### Docs

#### Dependencies
1. mitmproxy installed and accessible from command line
2. sqlite
3. openJDK 17

#### Config Gen Tools
CRUD urls and mock patterns from the sqlite file `template.sqlite`

#### Sqlite DB Structure

##### url_pattern
| name        | type                              |
| ----------- | --------------------------------- |
| id          | INTEGER PRIMARY KEY AUTOINCREMENT |
| url_pattern | TEXT NOT NULL                     |

##### label
| name | type                              |
| ---- | --------------------------------- |
| id   | INTEGER PRIMARY KEY AUTOINCREMENT |
| name | TEXT NOT NULL                     |

##### url_label
| name           | type                              |
| -------------- | --------------------------------- |
| id             | INTEGER PRIMARY KEY AUTOINCREMENT |
| url_pattern_id | INTEGER NOT NULL                  |
| label_id       | INTEGER NOT NULL                  |

##### response_body_template
| name          | type                              |
| ------------- | --------------------------------- |
| id            | INTEGER PRIMARY KEY AUTOINCREMENT |
| response_body | TEXT NOT NULL                     |

##### active_blocked_url
| name           | type                              |
| -------------- | --------------------------------- |
| id             | INTEGER PRIMARY KEY AUTOINCREMENT |
| url_pattern_id | INTEGER NOT NULL                  |

##### active_mocked_url
| name                      | type                              |
| ------------------------- | --------------------------------- |
| id                        | INTEGER PRIMARY KEY AUTOINCREMENT |
| url_pattern_id            | INTEGER NOT NULL                  |
| response_body_template_id | INTEGER NOT NULL                  |


#### JSON Config
```json
{
  "block": [
    "/v1/feed",
    "/v1/notifications",
    "/v1/banners"
  ],
  "mock": [
    {
      "endpoint": "/v1/settings",
      "response": {
        "status_code": 200,
        "body": {"theme": "dark", "language": "en"},
        "headers": {"Content-Type": "application/json"}
      }
    }
  ]
}
```
