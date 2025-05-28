# mitmproxy-gen

generate a config like 
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

that later can be used on a mitmproxy addon script like
```python
import json
from mitmproxy import http

with open("mitm_rules.json") as f:
    config = json.load(f)

BLOCKED_PATHS = config.get("block", [])
MOCKED = {m["endpoint"]: m["response"] for m in config.get("mock", [])}

def request(flow: http.HTTPFlow) -> None:
    for path in BLOCKED_PATHS:
        if path in flow.request.path:
            flow.response = http.Response.make(403, b"Blocked by config", {"Content-Type": "text/html"})
            return

def response(flow: http.HTTPFlow) -> None:
    for endpoint, mock in MOCKED.items():
        if endpoint in flow.request.path:
            flow.response = http.Response.make(
                mock.get("status_code", 200),
                json.dumps(mock.get("body", {})).encode(),
                mock.get("headers", {"Content-Type": "application/json"})
            )
            return
```
