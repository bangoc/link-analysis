#!/bin/bash
if [ "$#" -ne 2 ]; then
  echo "Usage: ./post_hits.sh 0.0.0.0:8080 hits_input"
  exit 1
fi
curl -H "Content-Type: text/plain" -X POST $1/hits --data-binary "@$2"