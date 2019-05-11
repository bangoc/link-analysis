#!/bin/bash
if [ "$#" -ne 2 ]; then
  echo "Usage: ./post_pagerank.sh 0.0.0.0:8080 pagerank_input"
  exit 1
fi
curl -H "Content-Type: text/plain" -X POST $1/pagerank --data-binary "@$2"