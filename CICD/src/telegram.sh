#!/bin/bash

TIME="10"
TELEGRAM_USER_ID="858681991" 
TELEGRAM_BOT_TOKEN="6817491338:AAFwyjgVyn_aVBfKf9_LEUMym9njYDkUx9k"  

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="$CI_JOB_NAME status:  $CI_JOB_STATUS%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"
curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null
